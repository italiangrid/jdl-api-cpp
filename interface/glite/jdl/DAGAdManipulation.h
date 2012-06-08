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

// File: DAGAdManipulation.h
// Author: Francesco Giacomini <Francesco.Giacomini@cnaf.infn.it>
// Copyright (c) 2003 EU DataGrid.

// $Id: DAGAdManipulation.h,v 1.3.6.1 2010/04/07 09:50:34 mcecchi Exp $

#ifndef GLITE_WMS_COMMON_REQUESTAD_DAGADMANIPULATION_H
#define GLITE_WMS_COMMON_REQUESTAD_DAGADMANIPULATION_H

#include <string>
#include <vector>

namespace glite {
namespace jdl {

class DAGAd;

bool set_edg_jobid(DAGAd& dagad, std::string const& id);
std::string get_edg_jobid(DAGAd const& dagad);
bool remove_edg_jobid(DAGAd& dagad);

bool set_x509_user_proxy(DAGAd& dagad, std::string const& proxy);
std::string get_x509_user_proxy(DAGAd const& dagad);
bool remove_x509_user_proxy(DAGAd& dagad);

bool set_certificate_subject(DAGAd& dagad, std::string const& subject);
std::string get_certificate_subject(DAGAd const& dagad);
bool remove_certificate_subject(DAGAd& dagad);

bool set_my_proxy_server(DAGAd& dagad, std::string const& id);
std::string get_my_proxy_server(DAGAd const& dagad);
bool remove_my_proxy_server(DAGAd& dagad);

bool set_lb_sequence_code(DAGAd& dagad, std::string const& sequence_code);
std::string get_lb_sequence_code(DAGAd const& dagad);
bool remove_lb_sequence_code(DAGAd& dagad);

bool set_input_sandbox(DAGAd& dagad, std::vector<std::string> const& is);
std::vector<std::string> get_input_sandbox(DAGAd const& dagad);
bool remove_input_sandbox(DAGAd& dagad);

bool set_virtual_organisation(DAGAd& dagad, std::string const& vo);
std::string get_virtual_organisation(DAGAd const& dagad);
bool remove_virtual_organisation(DAGAd& dagad);

bool get_nodes_collocation(DAGAd const& dagad);

bool check_vo(DAGAd const& dagad);

bool parent_child(DAGAd const& dagad, std::string const& parent_node, std::string const& child_node);

} // jdl namespace
} // glite namespace

#endif

// Local Variables:
// mode: c++
// End:
