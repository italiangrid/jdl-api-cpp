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

// File: convert.h
// Author: Francesco Giacomini <Francesco.Giacomini@cnaf.infn.it>
// Copyright (c) 2002 EU DataGrid.

// $Id: convert.h,v 1.3.6.1 2010/04/07 09:50:34 mcecchi Exp $

#ifndef GLITE_WMS_COMMON_REQUESTAD_CONVERT_H
#define GLITE_WMS_COMMON_REQUESTAD_CONVERT_H

#include <iosfwd>

namespace classad {
class ClassAd;
}

namespace glite {
namespace jdl {

class DAGAd;

// convert a classad for a job to a condor submit file (stream in general)
std::ostream& to_submit_stream(std::ostream& os, classad::ClassAd const& ad);

// convert a DAGAd to a condor DAG file (stream in general)
std::ostream& to_dag_stream(std::ostream& os, DAGAd const& dag_ad);

bool to_dag_job(DAGAd const& dag_ad, classad::ClassAd& result);

} // jdl namespace
} // glite namespace

#endif // GLITE_WMS_COMMON_REQUESTAD_CONVERT_H
