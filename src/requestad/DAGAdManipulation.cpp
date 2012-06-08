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

// File: DAGAdManipulation.cpp
// Author: Francesco Giacomini <Francesco.Giacomini@cnaf.infn.it>
// Copyright (c) 2003 EU DataGrid.

// $Id: DAGAdManipulation.cpp,v 1.3.6.1.6.1 2011/09/01 13:29:09 mcecchi Exp $

#include "DAGAdManipulation.h"
#include <boost/tuple/tuple.hpp>
#include "DAGAd.h"
#include "JDLAttributes.h"
#include "PrivateAttributes.h"
#include "glite/wmsutils/classads/classad_utils.h"

namespace glite {
namespace jdl {

namespace {

bool
set_generic(DAGAd& dagad, std::string const& attribute, std::string const& value)
{
  classad::Value v;
  v.SetStringValue(value);
  return dagad.set_generic(attribute, classad::Literal::MakeLiteral(v));  
}

void
get_generic(DAGAd const& dagad, std::string const& attribute, std::string& result)
{
  classad::ExprTree const* et = dagad.get_generic(attribute);
  if (utilities::is_literal(et)) {
    classad::Literal const& l = *static_cast<classad::Literal const*>(et);
    classad::Value v;
    l.GetValue(v);
    v.IsStringValue(result);
  }
}

void
get_generic(DAGAd const& dagad, std::string const& attribute, bool& result)
{
  classad::ExprTree const* et = dagad.get_generic(attribute);
  if (utilities::is_literal(et)) {
    classad::Literal const& l = *static_cast<classad::Literal const*>(et);
    classad::Value v;
    l.GetValue(v);
    v.IsBooleanValue(result);
  }
}

}

bool
set_edg_jobid(DAGAd& dagad, std::string const& id)
{
  return set_generic(dagad, JDL::JOBID, id);
}

std::string
get_edg_jobid(DAGAd const& dagad)
{
  std::string result;

  get_generic(dagad, JDL::JOBID, result);

  return result;
}

bool
remove_edg_jobid(DAGAd& dagad)
{
  return dagad.remove_generic(JDL::JOBID);
}

bool set_x509_user_proxy(DAGAd& dagad, std::string const& proxy)
{
  return set_generic(dagad, JDLPrivate::USERPROXY, proxy);
}

std::string get_x509_user_proxy(DAGAd const& dagad)
{
  std::string result;

  get_generic(dagad, JDLPrivate::USERPROXY, result);

  return result;
}

bool remove_x509_user_proxy(DAGAd& dagad)
{
  return dagad.remove_generic(JDLPrivate::USERPROXY);
}

bool set_certificate_subject(DAGAd& dagad, std::string const& subject)
{
  return set_generic(dagad, JDL::CERT_SUBJ, subject);
}

std::string get_certificate_subject(DAGAd const& dagad)
{
  std::string result;

  get_generic(dagad, JDL::CERT_SUBJ, result);

  return result;
}

bool remove_certificate_subject(DAGAd& dagad)
{
  return dagad.remove_generic(JDL::CERT_SUBJ);
}

bool
set_my_proxy_server(DAGAd& dagad, std::string const& proxy_server)
{
  return set_generic(dagad, JDL::MYPROXY, proxy_server);
}

std::string
get_my_proxy_server(DAGAd const& dagad)
{
  std::string result;

  get_generic(dagad, JDL::MYPROXY, result);

  return result;
}

bool
remove_my_proxy_server(DAGAd& dagad)
{
  return dagad.remove_generic(JDL::MYPROXY);
}

bool
set_lb_sequence_code(DAGAd& dagad, std::string const& sequence_code)
{
  return set_generic(dagad, JDL::LB_SEQUENCE_CODE, sequence_code);
}

std::string
get_lb_sequence_code(DAGAd const& dagad)
{
  std::string result;

  get_generic(dagad, JDL::LB_SEQUENCE_CODE, result);

  return result;
}

bool
remove_lb_sequence_code(DAGAd& dagad)
{
  return dagad.remove_generic(JDL::LB_SEQUENCE_CODE);
}

bool
set_input_sandbox(DAGAd& dagad, std::vector<std::string> const& is)
{
  return dagad.set_generic(JDL::INPUTSB, utilities::asExprList(is));
}

std::vector<std::string>
get_input_sandbox(DAGAd const& dagad)
{
  std::vector<std::string> result;

  classad::ExprTree const* et = dagad.get_generic(JDL::INPUTSB);
  if (et) {
    if (utilities::is_literal(et)) {
      std::string one_entry;
      if (utilities::evaluate(*static_cast<classad::Literal const*>(et), one_entry)) {
        result.push_back(one_entry);
      }
    } else if (utilities::is_expression_list(et)) {
      utilities::evaluate(*static_cast<classad::ExprList const*>(et), result);
    }
  }

  return result;
}

bool
remove_input_sandbox(DAGAd& dagad)
{
  return dagad.remove_generic(JDL::INPUTSB);
}
  
bool
set_virtual_organisation(DAGAd& dagad, std::string const& vo)
{
  return set_generic(dagad, JDL::VIRTUAL_ORGANISATION, vo);
}

std::string
get_virtual_organisation(DAGAd const& dagad)
{
  std::string result;

  get_generic(dagad, JDL::VIRTUAL_ORGANISATION, result);

  return result;
}

bool
remove_virtual_organisation(DAGAd& dagad)
{
  return dagad.remove_generic(JDL::VIRTUAL_ORGANISATION);
}

bool
get_nodes_collocation(DAGAd const& dagad)
{
  bool result = false;
  get_generic(dagad, "NodesCollocation", result);
  return result;
}

namespace {

template<typename T>
class DescriptionAttributeEquals
  : public std::unary_function<DAGAd::node_value_type, bool>
{
  std::string m_attribute;
  T m_value;

public:
  DescriptionAttributeEquals(std::string const& attribute, T const& value)
    : m_attribute(attribute), m_value(value)
  {}
  bool operator()(DAGAd::node_value_type const& node_info) const
  {
    bool result = false;

    classad::ClassAd const* ad(node_info.second.description_ad());
    if (ad) {
      T current;
      if (utilities::evaluate_attribute(*ad, m_attribute, current)) {
        result = current == m_value;
      }
    }

    return result;
  }
};

}

bool check_vo(DAGAd const& dagad)
{
  std::string vo = get_virtual_organisation(dagad);
  DAGAd::node_iterator b, e;
  boost::tie(b, e) = dagad.nodes();
  DescriptionAttributeEquals<std::string> pred(JDL::VIRTUAL_ORGANISATION, vo);

  return std::find_if(b, e, std::not1(pred)) == e;
}

bool
parent_child(
  DAGAd const& dagad,
  std::string const& parent_node,
  std::string const& child_node
)
{
  DAGAd::dependency_iterator dep_b, dep_e;
  boost::tie(dep_b, dep_e) = dagad.classad_dependencies();
  DAGAd::node_iterator node_b, node_e;
  boost::tie(node_b, node_e) = dagad.nodes();
  DAGAd::node_iterator parent_it = dagad.find(parent_node);
  DAGAd::node_iterator child_it = dagad.find(child_node);
  return
    parent_it != node_e
    && child_it != node_e
    && std::find(dep_b, dep_e, std::make_pair(parent_it, child_it)) != dep_e;
}

} // jdl namespace
} // glite namespace
