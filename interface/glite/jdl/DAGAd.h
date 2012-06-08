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

// File: DAGAd.h
// Author: Francesco Giacomini <Francesco.Giacomini@cnaf.infn.it>
//         Marco Cecchi

// $Id: DAGAd.h,v 1.5.2.2.6.1 2011/09/01 13:29:09 mcecchi Exp $

#ifndef GLITE_WMS_COMMON_REQUESTAD_DAGAD_H
#define GLITE_WMS_COMMON_REQUESTAD_DAGAD_H

#include <string>
#include <utility>
#include <map>
#include <set>
#include <iosfwd>
#include <classad_distribution.h>
#include <exception>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/config.hpp>

#include "glite/wmsutils/classads/classad_utils.h"

//graph libraries
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>

namespace glite {
namespace jdl {

namespace utilities = glite::wmsutils::classads;

class DAG_Error: public std::exception
{
protected:
  std::string m_msg;
public:
  virtual char const* what() const throw() { return "Invalid DAG"; }
  virtual ~DAG_Error() throw() { };
};

class NotDAG: public DAG_Error
{
public:
  virtual char const* what() const throw() {
    return "'node_type' must be \"dag\"";
  }
};

class InvalidMaxRunningNodes: public DAG_Error
{
public:
  virtual char const* what() const throw() {
    return "'max_running_nodes' has to be an integer > 0";
  }
};

class InvalidNodes: public DAG_Error
{
public:
  virtual char const* what() const throw() {
    return "'nodes' not valid";
  }
};

class InvalidDependencies: public DAG_Error
{
public:
  virtual char const* what() const throw() {
    return "'dependencies' not valid";
  }
};

class InconsistentDependencies: public DAG_Error
{
public:
  virtual char const* what() const throw() {
    return "Invalid reference in 'dependencies'";
  }
};

class DAG_HasCycle: public DAG_Error
{
public:
  virtual char const* what() const throw() {
    return "DAG has a cycle";
  }
};

class Invalid_DAG_NodeType: public DAG_Error
{
private:
  std::string m_type;
public:
  Invalid_DAG_NodeType(std::string const& type)
    : DAG_Error(), m_type(type)
  { }
  virtual char const* what() throw() {
    m_msg = "'node_type': " + m_type + " is not valid";
    return m_msg.c_str();
  }
  virtual ~Invalid_DAG_NodeType() throw() { }
};

class Invalid_DAG_RetryCount: public DAG_Error
{
public:
  virtual char const* what() const throw() {
    return "'node_retry_count' must be an integer >= 0";
  }
};

class DAG_NodeError: public std::exception
{
protected:
  std::string m_node_name;
  std::string m_msg;
public:
  DAG_NodeError(std::string const& node_name)
    : m_node_name(node_name) { }
  virtual char const* what() throw()
  {
    m_msg = "Invalid node " + m_node_name;
    return m_msg.c_str();
  }
  std::string node() const { return m_node_name; }
  virtual ~DAG_NodeError() throw() { };
};

class NeitherAdNorFile: public DAG_NodeError
{
public:
  virtual char const* what() throw()
  {
    m_msg = "Neither 'ad' nor 'file' specified" +
      (m_node_name.empty() ? "" : " for node " + m_node_name);
    return m_msg.c_str();
  }
  NeitherAdNorFile(std::string const& node)
    : DAG_NodeError(node) { }
};

class BothAdAndFile: public DAG_NodeError
{
public:
  virtual char const* what() throw()
  {
    m_msg = "Both 'ad' and 'file' specified" +
      (m_node_name.empty() ? "" : " for node " + m_node_name);
    return m_msg.c_str();
  }
  BothAdAndFile(std::string const& node)
    : DAG_NodeError(node) { }
};

class InvalidDescriptionFilename: public DAG_NodeError
{
  std::string m_description;
public:
  virtual char const* what() throw()
  {
    m_msg = "'file' not valid" +
      (m_description.empty() ? "" : " (" + m_description + ")");
      (m_node_name.empty() ? "" : " for node " + m_node_name);
    return m_msg.c_str();
  }
  InvalidDescriptionFilename(
    std::string const& node,
    std::string const& description
  )
    : DAG_NodeError(node), m_description(description) { }
  virtual ~InvalidDescriptionFilename() throw() { };
};

class InvalidDescription: public DAG_NodeError
{
public:
  virtual char const* what() throw()
  {
    m_msg = "'description' not valid" +
      (m_node_name.empty() ? "" : " for node " + m_node_name);
    return m_msg.c_str();
  }
  InvalidDescription(std::string const& node)
    : DAG_NodeError(node) { }
};

class InvalidRetryCount: public DAG_NodeError
{
public:
  virtual char const* what() throw()
  {
    m_msg = "'node_retry_count' must be an integer >= 0" +
      (m_node_name.empty() ? "" : " for node " + m_node_name);
    return m_msg.c_str();
  }
  InvalidRetryCount(std::string const& node)
    : DAG_NodeError(node) { }
};

class InvalidNodeType: public DAG_NodeError
{
  std::string m_type;
public:
  virtual char const* what() throw()
  {
    m_msg = "node_type not valid" +
      (m_type.empty() ? "" : " (" + m_type + ")");
      (m_node_name.empty() ? "" : " for node " + m_node_name);
    return m_msg.c_str();
  }
  InvalidNodeType(std::string const& node, std::string const& type)
    : DAG_NodeError(node), m_type(type) { }
  virtual ~InvalidNodeType() throw() { };
};

class DAGNodeInfo
{
  class Implementation;
  boost::shared_ptr<Implementation> m_impl;

public:
  DAGNodeInfo();
  DAGNodeInfo(classad::ClassAd const& node_description,
              std::string const& node_type = std::string(),
              std::string const& node_name = std::string()
  );
  ~DAGNodeInfo() { };

public:
  std::string             description_file() const;
  bool                    replace_description_file(std::string const& file);
  classad::ClassAd const* description_ad() const;
  bool                    replace_description_ad(classad::ClassAd* ad);
  bool                    description_file_for_ad(std::string const& file);
  bool                    description_ad_for_file(classad::ClassAd* ad);

  std::string             type() const;

  int                     retry_count() const;
  bool                    retry_count(int n);

  classad::ClassAd        as_classad() const;
};

class DAGAdNodeIterator
  : public std::iterator<
  std::input_iterator_tag
  ,std::pair<std::string, DAGNodeInfo>
  ,ptrdiff_t
  ,std::pair<std::string, DAGNodeInfo> const*
  ,std::pair<std::string, DAGNodeInfo> const&
>
{
  friend bool operator==(DAGAdNodeIterator const& lhs,
    DAGAdNodeIterator const& rhs
  );

  classad::ClassAd const* m_nodes;
  classad::ClassAd::const_iterator m_node;
  value_type m_value;

  bool is_good() const
  {
    return m_node != m_nodes->end();
  }

  void set_value();

public:

  DAGAdNodeIterator();
  ~DAGAdNodeIterator() {};
  DAGAdNodeIterator(classad::ClassAd const* nodes,
    classad::ClassAd::const_iterator it
  );
  DAGAdNodeIterator(DAGAdNodeIterator const& other);
  DAGAdNodeIterator& operator=(DAGAdNodeIterator const& other);
  DAGAdNodeIterator& operator++();
  DAGAdNodeIterator operator++(int);
  reference operator*() const;

  pointer operator->() const
  {
    return &(operator*());
  }

};

inline bool operator==(DAGAdNodeIterator const& lhs,
  DAGAdNodeIterator const& rhs
) {
  return lhs.m_nodes == rhs.m_nodes && lhs.m_node == rhs.m_node;
}

inline bool operator!=(DAGAdNodeIterator const& lhs,
  DAGAdNodeIterator const& rhs
) {
  return !(lhs == rhs);
}

struct DAGAdDependencyIterator
  : public std::iterator<
  std::input_iterator_tag
  ,std::pair<DAGAdNodeIterator, DAGAdNodeIterator>
  ,ptrdiff_t
  ,std::pair<DAGAdNodeIterator, DAGAdNodeIterator> const*
  ,std::pair<DAGAdNodeIterator, DAGAdNodeIterator> const&
>
{
  friend bool operator==(DAGAdDependencyIterator const& lhs,
                         DAGAdDependencyIterator const& rhs);

  typedef DAGAdNodeIterator node_iterator;
  typedef classad::ExprList::iterator Iterator;

  classad::ClassAd const* m_dag;
  Iterator m_dep;
  Iterator m_dep_end;
  Iterator m_parent;
  Iterator m_child;
  value_type m_value;

  static classad::ExprList* parents(classad::ExprTree* dep)
  {
    assert(utilities::is_expression_list(dep));
    classad::ExprTree* et = *static_cast<classad::ExprList*>(dep)->begin();
    assert(utilities::is_expression_list(et));
    return static_cast<classad::ExprList*>(et);
  }
  static classad::ExprList* children(classad::ExprTree* dep)
  {
    assert(utilities::is_expression_list(dep));
    classad::ExprTree* et = *++static_cast<classad::ExprList*>(dep)->begin();
    assert(utilities::is_expression_list(et));
    return static_cast<classad::ExprList*>(et);
  }
  bool is_good() const { return m_dep != m_dep_end; }
  void set_value();

  DAGAdDependencyIterator(classad::ClassAd const* dag = 0, bool begin = false);

  // copy ctor, operator=() and dtor are ok

  DAGAdDependencyIterator& operator++();
  DAGAdDependencyIterator operator++(int);

  reference operator*() const
  {
    return m_value;
  }

  pointer operator->() const
  {
    return &(operator*());
  }
};

inline bool operator==(DAGAdDependencyIterator const& lhs,
                       DAGAdDependencyIterator const& rhs)
{
  return (!lhs.is_good() && !rhs.is_good())
    || (lhs.is_good() && rhs.is_good()
        && lhs.m_dep == rhs.m_dep
        && lhs.m_parent == rhs.m_parent
        && lhs.m_child == rhs.m_child
        );
}

inline bool operator!=(DAGAdDependencyIterator const& lhs,
                DAGAdDependencyIterator const& rhs)
{
  return !(lhs == rhs);
}

class DAGAd: boost::noncopyable
{
public:

  typedef DAGAdNodeIterator node_iterator;
  typedef DAGAdNodeIterator::value_type node_value_type;
  typedef DAGAdDependencyIterator dependency_iterator;
  typedef DAGAdDependencyIterator::value_type dependency_value_type;

  typedef boost::property<
      boost::vertex_name_t, std::string, boost::property<
      boost::vertex_color_t, boost::default_color_type
  > > VertexProperties;

  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperties> Graph_t; // bidirectional to have in_edges
  typedef boost::graph_traits<Graph_t>::vertex_descriptor Vertex;
  typedef boost::graph_traits<Graph_t >::vertex_iterator VertexIterator;
  typedef boost::graph_traits<Graph_t>::in_edge_iterator InEdgeIterator;

private:
  boost::shared_ptr<classad::ClassAd> m_ad;
  Graph_t m_graph;

public:
  DAGAd();
  explicit DAGAd(classad::ClassAd const& ad);

  Graph_t& graph() { return m_graph; }
  classad::ClassAd const& ad() const;

  // set the default node type
  // if new_value is "" the attribute becomes unspecified
  // return the previous value ("" means unspecified)
  std::string default_node_type(std::string const& new_value);

  // get the default node type
  // "" means unspecified
  std::string default_node_type() const;

  // set the default retry count for a node
  // if new_value is -1 the attribute becomes unspecified
  // return the previous value (-1 means unspecified)
  int default_node_retry_count(int new_value);

  // get the default retry count for a node
  // -1 means unspecified
  int default_node_retry_count() const;

  bool add_node(std::string const& name, DAGNodeInfo const& info);
  bool replace_node(std::string const& name, DAGNodeInfo const& info);
  bool remove_node(std::string const& name);
  std::size_t num_nodes() const;
  node_iterator find(std::string const& name) const;

  bool add_dependency(std::string const& first, std::string const& second);
  bool remove_dependency(std::string const& first, std::string const& second);
  std::size_t num_dependencies() const;

  bool set_generic(std::string const& attribute, classad::ExprTree* value);
  classad::ExprTree const* get_generic(std::string const& attribute) const;
  bool remove_generic(std::string const& attribute);

  std::pair<dependency_iterator, dependency_iterator> classad_dependencies() const;
  std::pair<node_iterator, node_iterator> nodes() const;

  struct Attributes
  {
    static std::string const TYPE;
    static std::string const NODES;
    static std::string const DEPENDENCIES;
    static std::string const NODE_RETRY_COUNT;
    static std::string const NODE_TYPE;
    static std::string const DESCRIPTION_FILE;
    static std::string const DESCRIPTION_AD;
  };
};

} // jdl namespace
} // glite namespace

#endif
