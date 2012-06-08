/*
Copyright (c) Members of the EGEE Collaboration. 2004.
See http://www.eu-egee.org/partners/ for details on the
copyright holders.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

// File: DAGAd.cpp
// Author: Francesco Giacomini <Francesco.Giacomini@cnaf.infn.it>
//         Marco Cecchi

// $Id: DAGAd.cpp,v 1.4.2.2.2.1 2011/09/01 13:29:09 mcecchi Exp $

#include "DAGAd.h"

#include <memory>
#include <functional>
#include <algorithm>
#include <cctype>
#include <numeric>
#include <boost/tuple/tuple.hpp>
#include <boost/scoped_ptr.hpp>
#include <classad_distribution.h>

#include "glite/wmsutils/classads/classad_utils.h"

using namespace classad;
using namespace boost;
using namespace std;

namespace {

// Copy On Write of a pimpl; used in non-const member functions
template<typename Impl>
void cow(boost::shared_ptr<Impl>& impl)
{
  impl.reset(new Impl(*impl));
}

// Depth first search implementation (used to check cycles)
struct cycle_detector : public dfs_visitor<>
{
  cycle_detector(bool& has_cycle) 
    : m_has_cycle(has_cycle) { }
  template <class Edge, class Graph>
  void back_edge(Edge, Graph&) { m_has_cycle = true; }
protected:
  bool& m_has_cycle;
};

} // {anonymous}

namespace glite {
namespace jdl {

namespace {

static int const RETRY_COUNT_INVALID = -1;

int size(classad::ExprList const& l)
{
  return std::distance(l.begin(), l.end());
}

classad::ExprTree const* get_parent_decl(ExprList const& dep_decl)
{
  return *dep_decl.begin();
}

classad::ExprTree const* get_child_decl(ExprList const& dep_decl)
{
  return *++dep_decl.begin();
}

ExprList* get_parents(ExprList& dep_decl)
{
  ExprTree* et = *dep_decl.begin();
  assert(utilities::is_expression_list(et));
  return static_cast<ExprList*>(et);
}

classad::ExprList const* get_parents(ExprList const& dep_decl)
{
  ExprTree const* et = *dep_decl.begin();
  assert(utilities::is_expression_list(et));
  return static_cast<ExprList const*>(et);
}

ExprList* get_children(ExprList& dep_decl)
{
  ExprTree* et = *++dep_decl.begin();
  assert(utilities::is_expression_list(et));
  return static_cast<ExprList*>(et);
}

classad::ExprList const* get_children(ExprList const& dep_decl)
{
  ExprTree const* et = *++dep_decl.begin();
  assert(utilities::is_expression_list(et));
  return static_cast<ExprList const*>(et);
}

bool valid_dep_decl_syntax(classad::ExprTree const* dep)
{
  using namespace classad;

  if (!utilities::is_expression_list(dep)) {
    return false;
  }

  ExprList const* dep_decl = static_cast<ExprList const*>(dep);

  // must contain two elements
  if (size(*dep_decl) != 2) {
    return false;
  }
  ExprTree const* parent_decl = get_parent_decl(*dep_decl);
  ExprTree const* child_decl  = get_child_decl(*dep_decl);

  // simple declaration
  // { <parent>, <child> }
  if (utilities::is_attribute_reference(parent_decl)
      && utilities::is_attribute_reference(child_decl)) {
    return true;
  }

  // multi-parent declaration
  // 1) { { <parent>* },   <child>   }
  // 2) { { <parent>* }, { <child> } }
  // 3) { { <parent>* }, {         } }
  if (utilities::is_expression_list(parent_decl)
      && (utilities::is_attribute_reference(child_decl)
          || (utilities::is_expression_list(child_decl)
              && size(*static_cast<ExprList const*>(child_decl)) < 2))) {

    // there is no check that all the components of the list are references
    return true;

    // { { <parent>? }, { <child>? } } is considered here, although it would
    // match also the next test

  }

  // multi-children declaration
  // {   <parent>,   { <child>* }}
  // { { <parent> }, { <child>* }}
  // { {          }, { <child>* }
  if (utilities::is_expression_list(child_decl)
      && (utilities::is_attribute_reference(parent_decl)
          || (utilities::is_expression_list(parent_decl)
              && size(*static_cast<ExprList const*>(parent_decl)) < 2))) {
    // there is no check that all the components of the list are references
    return true;
  }

  // { { <parent>+ }, { <child>+ } }
  return false;
}

bool empty_dep_decl(classad::ExprTree const* decl)
{
  // precondition:
  // decl is a valid dependency declaration
  assert(utilities::is_expression_list(decl));

  ExprList const& dep_decl = *static_cast<ExprList const*>(decl);

  ExprTree const* parent_decl = get_parent_decl(dep_decl);
  ExprTree const* child_decl =  get_child_decl(dep_decl);

  return
       (utilities::is_expression_list(parent_decl)
        && size(*static_cast<ExprList const*>(parent_decl)) == 0)
    || (utilities::is_expression_list(child_decl)
        && size(*static_cast<ExprList const*>(child_decl)) == 0);
}

bool valid_reference_to_node(classad::ExprTree const* ref,
                             classad::ClassAd const* n)
{
  if (!utilities::is_attribute_reference(ref)) {
    return false;
  }

  ClassAd const& nodes = *n;
  AttributeReference const& node_ref = *static_cast<AttributeReference const*>(ref);

  ExprTree* t;
  std::string attribute;
  bool absolute_reference;
  node_ref.GetComponents(t, attribute, absolute_reference);
  return !absolute_reference && utilities::is_classad(nodes.Lookup(attribute));
}

bool dep_decl_contains_invalid_ref(classad::ExprTree const* dep_decl,
                                   classad::ClassAd const* n)
{
  // at this point the ExprTree's should all be ExprList's, so if the assert
  // below fails then the preliminary check on the syntax didn't work properly
  assert(utilities::is_expression_list(dep_decl));

  ClassAd const& nodes = *n;
  ExprList const& dep_decl_list = *static_cast<ExprList const*>(dep_decl);

  ExprTree const* parent_decl = *dep_decl_list.begin();
  if (utilities::is_expression_list(parent_decl)) {
    // non-empty list of parents; check that all the components are references
    // to existing nodes
    ExprList const& parent_list = *static_cast<ExprList const*>(parent_decl);
    if (
      std::find_if(
        parent_list.begin(),
        parent_list.end(),
        std::not1(
          std::bind2nd(
            std::ptr_fun(valid_reference_to_node),
            &nodes
          )
        )
      ) != parent_list.end()
    ) {
      return true;
    }
  } else {
    // the following is guaranteed by valid_dep_decl_syntax()
    assert(utilities::is_attribute_reference(parent_decl));
    if (!valid_reference_to_node(parent_decl, &nodes)) {
      return true;
    }
  }

  ExprTree const* child_decl = *++dep_decl_list.begin();
  if (utilities::is_expression_list(child_decl)) {
    // non-empty list of children; check that all the components are references
    // to existing nodes
    ExprList const& child_list = *static_cast<ExprList const*>(child_decl);
    if (std::find_if(
          child_list.begin(),
          child_list.end(),
          std::not1(
            std::bind2nd(
              std::ptr_fun(valid_reference_to_node),
              &nodes
            )
          )
        ) != child_list.end()) {
      return true;
    }
  } else {
    // the following is guaranteed by valid_dep_decl_syntax()
    assert(utilities::is_attribute_reference(child_decl));
    if (!valid_reference_to_node(child_decl, &nodes)) {
      return true;
    }
  }

  return false;
}

// transform a parent or child declaration consisting of a simple
// AttributeReference into a list of one AttributeReference
void normalize(ExprTree* dep)
{
  assert(utilities::is_expression_list(dep));
  ExprList* dep_decl = static_cast<ExprList*>(dep);
  ExprTree const* parent_decl = get_parent_decl(*dep_decl);
  ExprTree const* child_decl  = get_child_decl(*dep_decl);

  if (utilities::is_attribute_reference(parent_decl)) {
    std::auto_ptr<ExprList> new_parent_decl(new ExprList);
    new_parent_decl->push_back(parent_decl->Copy());
    dep_decl->erase(dep_decl->begin());
    dep_decl->insert(dep_decl->begin(), new_parent_decl.release());
  }

  if (utilities::is_attribute_reference(child_decl)) {
    std::auto_ptr<ExprList> new_child_decl(new ExprList);
    new_child_decl->push_back(child_decl->Copy());
    dep_decl->erase(++dep_decl->begin());
    dep_decl->insert(dep_decl->end(), new_child_decl.release());
  }
}

char const* dag_reserved_attrs[] = {
  "max_running_nodes",
  "nodes",
  "dependencies",
  "node_type",
  "node_retry_count"
};

char const** dag_reserved_attrs_begin = dag_reserved_attrs;
char const** dag_reserved_attrs_end
= dag_reserved_attrs + sizeof(dag_reserved_attrs) / sizeof(dag_reserved_attrs[0]);

inline
bool
description_file_is_valid(std::string const& file)
{
  return !file.empty();
}

inline
bool
description_ad_is_valid(classad::ClassAd const* ad)
{
  return ad != 0;
}

inline
bool
node_type_is_valid(std::string const& node_type)
{
  return !node_type.empty();
}

inline
bool
node_retry_count_is_valid(int count)
{
  return count >= 0;
}

inline
bool
pre_is_valid(std::string const& pre)
{
  return !pre.empty();
}

inline
bool
pre_args_is_valid(std::string const& pre_args)
{
  return !pre_args.empty();
}

inline
bool
post_is_valid(std::string const& post)
{
  return !post.empty();
}

inline
bool
post_args_is_valid(std::string const& post_args)
{
  return !post_args.empty();
}

} // {anonymous}

class DAGNodeInfo::Implementation
{
  int                                 m_retry_count;
  std::string                         m_type;
  std::string                         m_node_name;
  boost::scoped_ptr<classad::ClassAd> m_description_ad;
  std::string                         m_description_file;

public:

  Implementation()
  {
    // this constructor does not produce a usable object
    // it's necessary for node iterators, in particular to build a default
    // (i.e. pointing to nothing) node iterator
  }

  Implementation(
    classad::ClassAd const& node_description,
    std::string const& node_type,
    std::string const& node_name
  )
    : m_retry_count(RETRY_COUNT_INVALID),
      m_type(node_type),
      m_node_name(node_name)
  {

    if (node_type.empty()) {
      // evaluate or lookup?

      // it must contain either "file" (a string) or "description" (a classad),
      // not both
      classad::ExprTree const* file_et =
        node_description.Lookup(DAGAd::Attributes::DESCRIPTION_FILE);
      classad::ExprTree const* ad_et =
        node_description.Lookup(DAGAd::Attributes::DESCRIPTION_AD);

      if (!file_et && !ad_et) {
        throw NeitherAdNorFile(m_node_name);
      }

      if (file_et && ad_et) {
        throw BothAdAndFile(m_node_name);
      }

      if (
        file_et
        && node_description.EvaluateAttrString(
          DAGAd::Attributes::DESCRIPTION_FILE,
          m_description_file
        )
      ) {
        if (m_description_file.empty()) {
          throw InvalidDescriptionFilename(m_node_name, m_description_file);
        }
      } else if (ad_et && utilities::is_classad(ad_et)) {
        m_description_ad.reset(static_cast<ClassAd*>(ad_et->Copy()));
        m_description_ad->SetParentScope(0);
      } else {
        throw InvalidDescription(m_node_name);
      }

      // node_retry_count (int >= 0, optional)
      if (
        node_description.Lookup(DAGAd::Attributes::NODE_RETRY_COUNT)
        && !(node_description.EvaluateAttrInt(
          DAGAd::Attributes::NODE_RETRY_COUNT,
          m_retry_count
        )
        && m_retry_count >= 0
        )
      ) {
        throw InvalidRetryCount(m_node_name);
      }

      // node_type (non-empty string, optional)
      if (
        node_description.Lookup(DAGAd::Attributes::NODE_TYPE)
        && !(node_description.EvaluateAttrString(DAGAd::Attributes::NODE_TYPE, m_type)
          && !m_type.empty()
        )
      ) {
        throw InvalidNodeType(m_node_name, m_type);
      }

    } else { // node_type not empty

      m_description_ad.reset(new classad::ClassAd(node_description));
    }
  }

  Implementation(Implementation const& other)
    : m_description_file(other.m_description_file),
      m_description_ad(
        other.m_description_ad
        ? new classad::ClassAd(*other.m_description_ad)
        : 0
      ),
      m_type(other.m_type),
      m_retry_count(other.m_retry_count)
  {
  }

  Implementation& operator=(Implementation const& other)
  {
    if (this != &other) {
      m_description_file = other.m_description_file;
      m_description_ad.reset(
        other.m_description_ad
        ? new classad::ClassAd(*other.m_description_ad)
        : 0
      );
      m_type             = other.m_type;
      m_retry_count      = other.m_retry_count;
    }

    return *this;
  }

  std::string
  description_file() const
  {
    return m_description_file;
  }

  bool
  replace_description_file(std::string const& file)
  {
    bool result = false;

    if (description_file_is_valid(m_description_file)) {
      m_description_file = file;
      result = true;
    }

    return result;
  }

  classad::ClassAd const*
  description_ad() const
  {
    return m_description_ad.get();
  }

  bool
  replace_description_ad(classad::ClassAd* ad)
  {
    bool result = false;

    if (description_ad_is_valid(m_description_ad.get())) {
      m_description_ad.reset(ad);
      result = true;
    }

    return result;
  }

  bool
  description_file_for_ad(std::string const& file)
  {
    bool result = false;

    if (description_ad_is_valid(m_description_ad.get())) {
      m_description_file = file;
      m_description_ad.reset();
      result = true;
    }

    return result;
  }

  bool
  description_ad_for_file(std::auto_ptr<classad::ClassAd> ad)
  {
    bool result = false;

    if (description_file_is_valid(m_description_file)) {
      m_description_file.clear();
      m_description_ad.reset(ad.release());
      result = true;
    }

    return result;
  }

  std::string
  type() const
  {
    return m_type;
  }

  int
  retry_count() const
  {
    return m_retry_count;
  }

  bool
  retry_count(int n)
  {
    bool result = false;

    if (node_retry_count_is_valid(n)) {
      m_retry_count = n;
      result = true;
    }

    return result;
  }

  classad::ClassAd
  as_classad() const
  {
    classad::ClassAd result;
   
   //description shouldn't be empty, there must be either the description file 
   //either the description embedded
    assert(!m_description_file.empty() || m_description_ad);   
    
    if (!m_description_file.empty()) {
      result.InsertAttr(DAGAd::Attributes::DESCRIPTION_FILE, m_description_file);
    } else if (m_description_ad) {
      result.Insert(DAGAd::Attributes::DESCRIPTION_AD, m_description_ad->Copy()) ;
    } else {
      //  assert(false);
    }
    if (node_type_is_valid(m_type)) {
      result.InsertAttr(DAGAd::Attributes::NODE_TYPE, m_type);
    }
    if (node_retry_count_is_valid(m_retry_count)) {
      result.InsertAttr(DAGAd::Attributes::NODE_RETRY_COUNT, m_retry_count);
    }

    return result;
  }

};

DAGNodeInfo::DAGNodeInfo()
  : m_impl(new Implementation)
{
}

DAGNodeInfo::DAGNodeInfo(
  classad::ClassAd const& node_description,
  std::string const& node_type,
  std::string const& node_name
)
  : m_impl(new Implementation(node_description, node_type, node_name))
{
}

std::string
DAGNodeInfo::description_file() const
{
  return m_impl->description_file();
}

bool
DAGNodeInfo::replace_description_file(std::string const& file)
{
  cow(m_impl);
  return m_impl->replace_description_file(file);
}

classad::ClassAd const*
DAGNodeInfo::description_ad() const
{
  return m_impl->description_ad();
}

bool
DAGNodeInfo::replace_description_ad(classad::ClassAd* ad)
{
  cow(m_impl);
  return m_impl->replace_description_ad(ad);
}

bool
DAGNodeInfo::description_file_for_ad(std::string const& file)
{
  cow(m_impl);
  return m_impl->description_file_for_ad(file);
}

bool
DAGNodeInfo::description_ad_for_file(classad::ClassAd* ad)
{
  cow(m_impl);
 
   //newad now takes care of ad
  std::auto_ptr<classad::ClassAd> newad(ad);
  return m_impl->description_ad_for_file(newad);
 
}

std::string
DAGNodeInfo::type() const
{
  return m_impl->type();
}

int
DAGNodeInfo::retry_count() const
{
  return m_impl->retry_count();
}

bool
DAGNodeInfo::retry_count(int n)
{
  cow(m_impl);
  return m_impl->retry_count(n);
}

classad::ClassAd
DAGNodeInfo::as_classad() const
{
  return m_impl->as_classad();
}

DAGAdNodeIterator::DAGAdNodeIterator()
  : m_nodes(0), m_node(), m_value()
{
}

DAGAdNodeIterator::DAGAdNodeIterator(classad::ClassAd const* nodes, classad::ClassAd::const_iterator it)
  : m_nodes(nodes), m_node(it), m_value()
{
  // position at the first classad
  for ( ; m_node != nodes->end()
    && !utilities::is_classad(m_node->second);
    ++m_node
  ) {
    ; 
  }
  set_value();
}

DAGAdNodeIterator::DAGAdNodeIterator(DAGAdNodeIterator const& other)
  : m_nodes(other.m_nodes), m_node(other.m_node), m_value(other.m_value)
{
}

DAGAdNodeIterator&
DAGAdNodeIterator::operator=(DAGAdNodeIterator const& other)
{
  if (this != &other) {
    m_nodes = other.m_nodes;
    m_node = other.m_node;
    m_value = other.m_value;
  }

  return *this;
}

DAGAdNodeIterator&
DAGAdNodeIterator::operator++()
{
  // position at the next classad
  if (m_node != m_nodes->end()) {
    do {
      ++m_node;
    } while (m_node != m_nodes->end() && !utilities::is_classad(m_node->second));
  }
  set_value();

  return *this;
}

DAGAdNodeIterator
DAGAdNodeIterator::operator++(int)
{
  DAGAdNodeIterator tmp(*this);
  ++*this;
  return tmp;
}

void
DAGAdNodeIterator::set_value()
{
  if (is_good()) {
    if (utilities::is_classad(m_node->second)) {
      ClassAd* ad = static_cast<ClassAd*>(m_node->second);
      m_value = std::make_pair(m_node->first, DAGNodeInfo(*ad, "", m_node->first));
    }
  }
}

std::pair<std::string, DAGNodeInfo> const&
DAGAdNodeIterator::operator*() const
{
  return m_value;
}

void
DAGAdDependencyIterator::set_value()
{
  if (is_good()) {
    assert(utilities::is_attribute_reference(*m_parent));
    assert(utilities::is_attribute_reference(*m_child));
    ExprTree* t;
    std::string node1;
    std::string node2;
    bool a;
    static_cast<AttributeReference const*>(*m_parent)->GetComponents(t, node1, a);
    static_cast<AttributeReference const*>(*m_child)->GetComponents(t, node2, a);
    
    ClassAd const* nodes = static_cast<ClassAd const*>(m_dag->Lookup(DAGAd::Attributes::NODES));  
    m_value = std::make_pair(
      node_iterator(nodes, nodes->find(node1)),
      node_iterator(nodes, nodes->find(node2))
    );
  }      
}

DAGAdDependencyIterator::DAGAdDependencyIterator(classad::ClassAd const* dag, bool begin)
  : m_dag(dag)
{
  if (m_dag) {
    ExprTree* et = m_dag->Lookup(DAGAd::Attributes::DEPENDENCIES);  
    if (!et){
      ClassAd const* nodes = static_cast<ClassAd const*>(m_dag->Lookup(DAGAd::Attributes::NODES));  
      et = nodes->Lookup(DAGAd::Attributes::DEPENDENCIES);
    }    
    
    assert(utilities::is_expression_list(et));
    ExprList& deps = *static_cast<ExprList*>(et);

    if (begin) {
      m_dep = deps.begin();
      m_dep_end = deps.end();
      if (m_dep != m_dep_end) {
        m_parent = parents(*m_dep)->begin();
        m_child = children(*m_dep)->begin();
        set_value();
      }
    } else {
      m_dep = deps.end();
      m_dep_end = deps.end();
    }
  }
}

// copy ctor, operator=() and dtor are ok

DAGAdDependencyIterator&
DAGAdDependencyIterator::operator++()
{
  ++m_child;
  if (m_child == children(*m_dep)->end()) {
    ++m_parent;
    if (m_parent == parents(*m_dep)->end()) {
      ++m_dep;
      if (m_dep != m_dep_end) {
        m_parent = parents(*m_dep)->begin();
        m_child = children(*m_dep)->begin();
      }
    } else {
      m_child = children(*m_dep)->begin();
    }
  }

  set_value();

  return *this;
}

DAGAdDependencyIterator
DAGAdDependencyIterator::operator++(int)
{
  DAGAdDependencyIterator tmp(*this);
  ++*this;
  return tmp;
}

namespace {

void
check_and_normalize_dependencies(classad::ClassAd const& dag)
{
  bool result = true;

  ExprTree* et = dag.Lookup(DAGAd::Attributes::DEPENDENCIES);
  if (!et) {
    ClassAd const* nodes = static_cast<ClassAd const*>(
      dag.Lookup(DAGAd::Attributes::NODES)
    );
    et = nodes->Lookup(DAGAd::Attributes::DEPENDENCIES);
  }
  
  if (!utilities::is_expression_list(et)) {
    throw InvalidDependencies();
  }
  ExprList& deps_decl = *static_cast<ExprList*>(et);

  result &= std::find_if(
    deps_decl.begin(),
    deps_decl.end(),
    std::not1(std::ptr_fun(valid_dep_decl_syntax))
  ) == deps_decl.end();
    
  if (result) {
    // remove useless (empty) declarations
    deps_decl.erase(
  	  std::remove_if(
	      deps_decl.begin(),
	      deps_decl.end(),
	      empty_dep_decl
	      ),
	    deps_decl.end()
	  );

    std::for_each(deps_decl.begin(), deps_decl.end(), normalize);

    ExprTree* etnodes = dag.Lookup(DAGAd::Attributes::NODES);
    assert(utilities::is_classad(etnodes));
    ClassAd const& nodes = *static_cast<classad::ClassAd*>(etnodes);
    
    // check that all the dependency declarations refer to existing nodes
    if (std::find_if(
       deps_decl.begin(),
       deps_decl.end(),
       std::bind2nd(
		     std::ptr_fun(dep_decl_contains_invalid_ref),
		     &nodes
		   )
     ) != deps_decl.end()) {
      throw InconsistentDependencies();
    }
  } else {
    throw InvalidDependencies();
  }
}

void
check_node_info(std::iterator_traits<classad::ClassAd::iterator>::value_type const& node)
{
  ExprTree const* et = node.second;
  std::string const& node_name = node.first;

  if (utilities::is_classad(et)) {
    DAGNodeInfo node_info(*static_cast<classad::ClassAd const*>(et), "", node_name);
  }
}

void
check_and_normalize_dag(classad::ClassAd& dag)
{
  std::string node_type;
  dag.EvaluateAttrString(DAGAd::Attributes::TYPE, node_type);
  std::transform (
    node_type.begin(),
    node_type.end(),
    node_type.begin(),
    ::tolower
  );
  if (node_type != "dag") {
    throw NotDAG();
  }

  classad::ExprTree* nodes_et = dag.Lookup(DAGAd::Attributes::NODES);
  if (!nodes_et) {
    throw InvalidNodes();
  } else {
    if (!utilities::is_classad(nodes_et)) {
      throw InvalidNodes();
    }
  }

  classad::ClassAd const& nodes = *static_cast<classad::ClassAd*>(nodes_et);
  std::for_each(nodes.begin(), nodes.end(), check_node_info);

  int retry_count;
  if (dag.Lookup(DAGAd::Attributes::NODE_RETRY_COUNT)
    && !(
      dag.EvaluateAttrInt(DAGAd::Attributes::NODE_RETRY_COUNT, retry_count)
      && retry_count >= 0
    )
  ) {
    throw Invalid_DAG_RetryCount();
  }

  std::string type;
  if (dag.Lookup(DAGAd::Attributes::NODE_TYPE)
    && !(
      dag.EvaluateAttrString(DAGAd::Attributes::NODE_TYPE, type)
      && !type.empty()
    )
  ) {
    throw Invalid_DAG_NodeType(type);
  }

  //the attribute dependecies can be either inside nodes or outside
  check_and_normalize_dependencies(dag);
}

struct VertexHasName {
  DAGAd::Graph_t graph_;
  std::string name_;
  VertexHasName(DAGAd::Graph_t const& g, std::string n) : graph_(g), name_(n) { }
  bool operator()(DAGAd::Vertex const& v) {
    if (get(boost::vertex_name, graph_)[v] == name_ ) {
      return true;
    }
    return false;
  }
};
}

DAGAd::DAGAd()
  : m_ad(new classad::ClassAd)
{
  m_ad->InsertAttr(Attributes::TYPE, std::string("dag"));
  std::auto_ptr<classad::ClassAd> nodes(new classad::ClassAd);
  std::auto_ptr<classad::ExprList> dependencies(new classad::ExprList);
  nodes->Insert(Attributes::DEPENDENCIES, dependencies.release());
  m_ad->Insert(Attributes::NODES, nodes.release());  
}

DAGAd::DAGAd(classad::ClassAd const& ad)
  : m_ad(new ClassAd(ad))
{
  m_ad->SetParentScope(0);
  check_and_normalize_dag(*m_ad);
  
  //1. Add nodes to the graph
  ClassAd const* nodes = static_cast<ClassAd const*>(m_ad->Lookup(Attributes::NODES));
  ClassAd::const_iterator e = nodes->end();

  for (ClassAd::const_iterator it = nodes->begin(); it != e; ++it) {
    if (utilities::is_classad(it->second)) {
       Vertex node = add_vertex(m_graph);
       get(boost::vertex_name, m_graph)[node] = it->first;
       get(boost::vertex_color, m_graph)[node] = boost::white_color;
    }
  }
    
  //2. Add dependencies
  dependency_iterator dep_b;
  dependency_iterator dep_e;
  boost::tie(dep_b, dep_e) = classad_dependencies();
  graph_traits<Graph_t>::vertex_iterator graph_b, graph_e;
  boost::tie(graph_b, graph_e) = vertices(m_graph);
  
  for (dependency_iterator it=dep_b; it!=dep_e; ++it) {
    DAGAd::node_iterator parent = it->first;
    DAGAd::node_iterator child = it->second;  
    
    Vertex father;
    VertexHasName father_has_name(m_graph, parent->first);
    graph_traits<Graph_t>::vertex_iterator tmp = find_if(graph_b, graph_e, father_has_name);
    if (tmp == graph_e) {
      // raise some error
      continue;
    } else {
      father = *tmp;
    }
  
    Vertex son;
    VertexHasName son_has_name(m_graph, child->first);
    tmp = find_if(graph_b, graph_e, son_has_name);
    if (tmp == graph_e) {
      // raise some error
      continue;
    } else {
      son = *tmp;
    }
  
    add_edge(father, son, m_graph); // waiting for labeled_graph
  }
       
  //3. Check for cycles
  bool has_cycle = false;
  
  //check with DSF if there is a cycle in the graph
  cycle_detector vis(has_cycle);
  boost::depth_first_search(m_graph, visitor(vis));
  
  if (has_cycle) {
    throw DAG_HasCycle();
  }
}

classad::ClassAd const&
DAGAd::ad() const
{
  return *m_ad;
}

std::string
DAGAd::default_node_type(std::string const& new_value)
{
  std::string current;
  bool exists = utilities::evaluate_attribute(*m_ad, Attributes::NODE_TYPE, current);

  if (new_value.empty()) {
    m_ad->Delete(Attributes::NODE_TYPE);
  } else {
    if (!exists) {
      m_ad->InsertAttr(Attributes::NODE_TYPE, new_value);
    } else if (exists && new_value != current) {
      m_ad->Delete(Attributes::NODE_TYPE);
      m_ad->InsertAttr(Attributes::NODE_TYPE, new_value);
    }
  }

  return current;
}

std::string
DAGAd::default_node_type() const
{
  std::string result;
  utilities::evaluate_attribute(*m_ad, Attributes::NODE_TYPE, result);

  return result;
}

int
DAGAd::default_node_retry_count(int new_value)
{
  assert(new_value >= -1);

  int current = -1;
  bool exists = utilities::evaluate_attribute(*m_ad, Attributes::NODE_RETRY_COUNT, current);

  if (new_value == -1) {
    m_ad->Delete(Attributes::NODE_RETRY_COUNT);
  } else {
    if (!exists) {
      m_ad->InsertAttr(Attributes::NODE_RETRY_COUNT, new_value);
    } else if (exists && new_value != current) {
      m_ad->Delete(Attributes::NODE_RETRY_COUNT);
      m_ad->InsertAttr(Attributes::NODE_RETRY_COUNT, new_value);
    }
  }

  return current;
}

int
DAGAd::default_node_retry_count() const
{
  int result = -1;
  utilities::evaluate_attribute(*m_ad, Attributes::NODE_RETRY_COUNT, result);

  return result;
}

namespace {

bool
is_valid_node(classad::ClassAd const& node)
{
  // - node is supposed to be already in the DAG classad scope
  // - node is supposed to come from a DAGNodeInfo => the only check needed is
  //   the presence (possibly inherited) of the node_type attribute, which is
  //   mandatory

  // node_type (non-empty string, mandatory, can be inherited)
  std::string node_type;
  if (!node.EvaluateAttrString(DAGAd::Attributes::NODE_TYPE, node_type)
      || node_type.empty()) {
    return false;
  }

  return true;
}

}

bool
DAGAd::add_node(std::string const& name, DAGNodeInfo const& info)
{
  ClassAd* nodes = static_cast<ClassAd*>(m_ad->Lookup(Attributes::NODES));
  std::auto_ptr<classad::ClassAd> info_tmp(new ClassAd(info.as_classad()));
  info_tmp->SetParentScope(nodes);

  bool success = is_valid_node(*info_tmp)
    && !nodes->Lookup(name)
    && nodes->Insert(name, info_tmp.release());
  
  //add node in the graph structure
  if (success) {
    Vertex node = add_vertex(m_graph);
     get(boost::vertex_name, m_graph)[node] = name;
     get(boost::vertex_color, m_graph)[node] = boost::white_color;
  }
  
  return success; 
}

bool
DAGAd::replace_node(std::string const& name, DAGNodeInfo const& info)
{
  ClassAd* nodes = static_cast<ClassAd*>(m_ad->Lookup(Attributes::NODES));
  std::auto_ptr<classad::ClassAd> info_tmp(new ClassAd(info.as_classad()));
  info_tmp->SetParentScope(nodes);

  return is_valid_node(*info_tmp)
    && nodes->Lookup(name)
    && nodes->Insert(name, info_tmp.release());
}

namespace {

struct DependencyIsIncidentOnNode
  : std::unary_function<DAGAd::dependency_value_type, bool>
{
  std::string m_node_name;

  DependencyIsIncidentOnNode(std::string const& node_name): m_node_name(node_name) {}
  bool operator()(DAGAd::dependency_value_type const& dependency) const
  {
    DAGAd::node_iterator parent_it = dependency.first;
    DAGAd::node_iterator child_it = dependency.second;

    return parent_it->first == m_node_name || child_it->first == m_node_name;
  }
};

}

bool
DAGAd::remove_node(std::string const& node_name)
{
  ClassAd* nodes = static_cast<ClassAd*>(m_ad->Lookup(Attributes::NODES));
  if (!nodes->Lookup(node_name)) {
    return false;
  }

  dependency_iterator dep_b;
  dependency_iterator dep_e;
  boost::tie(dep_b, dep_e) = classad_dependencies();
  if (std::find_if(dep_b, dep_e, DependencyIsIncidentOnNode(node_name)) != dep_e) {
    return false;
  }

  nodes->Remove(node_name);

  //remove node from graph
  graph_traits<Graph_t>::vertex_iterator graph_b, graph_e;
  boost::tie(graph_b, graph_e) = vertices(m_graph);
  VertexHasName node_has_name(m_graph, node_name);
  graph_traits<Graph_t>::vertex_iterator tmp = find_if(graph_b, graph_e, node_has_name);
  if (tmp != graph_e) {
    clear_vertex(*tmp, m_graph); //clear dependency
    remove_vertex(*tmp, m_graph);
  }

  return true;
}

std::size_t
DAGAd::num_nodes() const
{
  std::size_t result = 0;

  ClassAd const* nodes = static_cast<ClassAd const*>(m_ad->Lookup(Attributes::NODES));
  ClassAd::const_iterator e = nodes->end();
  for (ClassAd::const_iterator it = nodes->begin(); it != e; ++it) {
    if (utilities::is_classad(it->second)) {
      ++result;
    }
  }

  return result;
}

DAGAd::node_iterator
DAGAd::find(std::string const& name) const
{
  ClassAd const* nodes = static_cast<ClassAd const*>(m_ad->Lookup(Attributes::NODES));
  return node_iterator(nodes, nodes->find(name));
}

bool
DAGAd::add_dependency(std::string const& parent_name, std::string const& child_name)
{
  ClassAd const* nodes = static_cast<ClassAd const*>(m_ad->Lookup(Attributes::NODES));
  node_iterator parent(nodes, nodes->find(parent_name));
  node_iterator child(nodes, nodes->find(child_name));
  node_iterator node_b;
  node_iterator node_e;
  boost::tie(node_b, node_e) = DAGAd::nodes();
  if (parent == node_e || child == node_e) {
    return false;
  }
  dependency_value_type new_dep(parent, child);
  dependency_iterator dep_b;
  dependency_iterator dep_e;
  boost::tie(dep_b, dep_e) = classad_dependencies();
  if (std::find(dep_b, dep_e, new_dep) != dep_e) {
    return false;
  }

  graph_traits<Graph_t>::vertex_iterator graph_b, graph_e;
  boost::tie(graph_b, graph_e) = vertices(m_graph);
  //I'm sure nodes exist, and dependency hasn't been added before
  VertexHasName parent_has_name(m_graph, parent_name);
  graph_traits<Graph_t>::vertex_iterator tmp = find_if(graph_b, graph_e, parent_has_name);
  Vertex father;
  if (tmp != graph_e) {
    father = *tmp;
    VertexHasName child_has_name(m_graph, child_name);
    tmp = find_if(graph_b, graph_e, child_has_name);
    Vertex son;
    if (tmp != graph_e) {
      son = *tmp;
      add_edge(father, son, m_graph);
    } else {
      return false;
    }
  } else {
    return false;
  }
  
  bool has_cycle = false;
  //check with DSF if there is a cycle in the graph
  cycle_detector vis(has_cycle);
    	
  boost::depth_first_search(m_graph, visitor(vis));
  //if there is a cycle, the dependency isn't added in the classad!
  if (has_cycle) {
    return false;
  }
 
  std::auto_ptr<AttributeReference> parent_ref(
    AttributeReference::MakeAttributeReference(0, parent_name)
  );
  std::auto_ptr<ExprList> new_parent_decl(new ExprList);
  new_parent_decl->push_back(parent_ref.release());

  std::auto_ptr<AttributeReference> child_ref(
    AttributeReference::MakeAttributeReference(0, child_name)
  );
  std::auto_ptr<ExprList> new_child_decl(new ExprList);
  new_child_decl->push_back(child_ref.release());

  std::auto_ptr<ExprList> new_dep_decl(new ExprList);
  new_dep_decl->push_back(new_parent_decl.release());
  new_dep_decl->push_back(new_child_decl.release());

  ExprList* dependencies = static_cast<ExprList*>(m_ad->Lookup(Attributes::DEPENDENCIES));  
  if (!dependencies){
    dependencies = static_cast<ExprList*>(nodes->Lookup(Attributes::DEPENDENCIES));
  }   
   
  dependencies->push_back(new_dep_decl.release());

  return true;
}

bool
DAGAd::remove_dependency(std::string const& parent_name, std::string const& child_name)
{
  // find the dependency
  ClassAd const* nodes = static_cast<ClassAd const*>(m_ad->Lookup(Attributes::NODES));
  node_iterator parent(nodes, nodes->find(parent_name));
  node_iterator child(nodes, nodes->find(child_name));
  node_iterator node_b;
  node_iterator node_e;
  boost::tie(node_b, node_e) = DAGAd::nodes();
  if (parent == node_e || child == node_e) {
    return false;
  }

  dependency_value_type dep(parent, child);
  dependency_iterator dep_b;
  dependency_iterator dep_e;
  boost::tie(dep_b, dep_e) = classad_dependencies();
  dependency_iterator dep_it = std::find(dep_b, dep_e, dep);
  if (dep_it == dep_e) {
    return false;
  }
  
  ExprList* dep_decl = static_cast<ExprList*>(*dep_it.m_dep);

  ExprList* parents = get_parents(*dep_decl);
  ExprList* children = get_children(*dep_decl);

  if (size(*parents) > 1) {
    parents->erase(dep_it.m_parent);
  } else if (size(*children) > 1) {
    children->erase(dep_it.m_child);
  } else {
    ExprList* dependencies = static_cast<ExprList*>(m_ad->Lookup(Attributes::DEPENDENCIES));  
    if (!dependencies){
      dependencies = static_cast<ExprList*>(nodes->Lookup(Attributes::DEPENDENCIES));
    }   
    dependencies->erase(dep_it.m_dep);
  }

  graph_traits<Graph_t>::vertex_iterator graph_b, graph_e;
  boost::tie(graph_b, graph_e) = vertices(m_graph);
  //remove dependency in the graph
  VertexHasName parent_has_name(m_graph, parent_name);
  graph_traits<Graph_t>::vertex_iterator tmp = find_if(graph_b, graph_e, parent_has_name);
  Vertex father;
  if (tmp != graph_e) {
    father = *tmp;
    VertexHasName child_has_name(m_graph, child_name);
    tmp = find_if(graph_b, graph_e, child_has_name);
    Vertex son;
    if (tmp != graph_e) {
      son = *tmp;
      boost::remove_edge(father, son, m_graph);
    } else {
      return false;
    }
  } else {
    return false;
  }

  return true;
}

std::size_t
DAGAd::num_dependencies() const
{
  dependency_iterator dep_b;
  dependency_iterator dep_e;
  boost::tie(dep_b, dep_e) = classad_dependencies();
  return std::distance(dep_b, dep_e);
}

bool
DAGAd::set_generic(std::string const& attribute, classad::ExprTree* value)
{
  if (std::find(
        dag_reserved_attrs_begin,
        dag_reserved_attrs_end,
        attribute
      ) == dag_reserved_attrs_end) {
    return m_ad->Insert(attribute, value);
  } else {
    return false;
  }
}

classad::ExprTree const*
DAGAd::get_generic(std::string const& attribute) const
{
  if (std::find(
        dag_reserved_attrs_begin,
        dag_reserved_attrs_end,
        attribute
      ) == dag_reserved_attrs_end) {
    return m_ad->Lookup(attribute);
  } else {
    return false;
  }
}

bool
DAGAd::remove_generic(std::string const& attribute)
{
  if (std::find(
        dag_reserved_attrs_begin,
        dag_reserved_attrs_end,
        attribute
      ) == dag_reserved_attrs_end) {
    return m_ad->Delete(attribute);
  } else {
    return false;
  }
}

std::pair<DAGAd::dependency_iterator, DAGAd::dependency_iterator>
DAGAd::classad_dependencies() const
{
  dependency_iterator b(m_ad.get(), true);
  dependency_iterator e(m_ad.get());
  return std::make_pair(b, e);
}

std::pair<DAGAd::node_iterator, DAGAd::node_iterator>
DAGAd::nodes() const
{
  ClassAd const* nodes = static_cast<ClassAd const*>(m_ad->Lookup(Attributes::NODES));
  return std::make_pair(
    node_iterator(nodes, nodes->begin()),
    node_iterator(nodes, nodes->end())
  );
}

const std::string DAGAd::Attributes::TYPE              = "type";
const std::string DAGAd::Attributes::NODES             = "nodes";
const std::string DAGAd::Attributes::DEPENDENCIES      = "dependencies";
const std::string DAGAd::Attributes::NODE_RETRY_COUNT  = "node_retry_count";
const std::string DAGAd::Attributes::NODE_TYPE         = "node_type";
const std::string DAGAd::Attributes::DESCRIPTION_FILE  = "file";
const std::string DAGAd::Attributes::DESCRIPTION_AD    = "description";

} // jdl namespace
} // glite namespace
