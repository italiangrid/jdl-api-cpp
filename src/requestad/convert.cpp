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

// File: convert.cpp
// Author: Francesco Giacomini <Francesco.Giacomini@cnaf.infn.it>
// Copyright (c) 2002 EU DataGrid.

// $Id: convert.cpp,v 1.3.6.2.6.1 2011/10/24 11:08:14 mcecchi Exp $

#include "convert.h"

#include <numeric>
#include <algorithm>
#include <set>
#include <iostream>
#include <cassert>

#include <classad_distribution.h>
#include <boost/lexical_cast.hpp>

namespace glite {
namespace jdl {

namespace {
// condor submit file keywords
const char* c_condor_keys_begin[] = {
  "allow_startup_script",
  "append_files",
  "arguments",
  "buffer_block_size",
  "buffer_files",
  "buffer_size",
  "compress_files",
  "copy_to_spool",
  "core_size",
  "dagman_job_id",
  "dag_node_name",
  "environment",
  "error",
  "executable",
  "exit_requirements",
  "fetch_files",
  "file_remaps",
  "getenv",
  "globus_rematch",
  "globus_resubmit",
  "globusrsl",
  "globusscheduler",
  "grid_resource",
  "grid_type",
  "hold",
  "ImageSize",
  "initialdir",
  "input",
  "jar_files",
  "kill_sig",
  "leave_in_queue",
  "local_files",
  "log",
  "log_xml",
  "machine_count",
  "match_list_length",
  "nice_user",
  "node_count",
  "nordugrid_rsl",
  "notification",
  "notify_user",
  "on_exit_hold",
  "on_exit_remove",
  "output",
  "parallel_script_shadow",
  "parallel_script_starter",
  "periodic_hold",
  "periodic_release",
  "periodic_remove",
  "preferences",
  "priority",
  "rank",
  "remote_initialdir",
  "remote_schedd",
  "remove_kill_sig",
  "rendezvousdir",
  "requirements",
  "rootdir",
  "should_transfer_files",
  "stream_error",
  "stream_output",
  "submit_event_notes",
  "submit_event_user_notes",
  "transfer_error",
  "transfer_executable",
  "transfer_files",
  "transfer_input",
  "transfer_input_files",
  "transfer_output",
  "transfer_output_files",
  "universe",
  "when_to_transfer_output",
  "x509userproxy"
};

const char** c_condor_keys_end = c_condor_keys_begin +
sizeof(c_condor_keys_begin) / sizeof(c_condor_keys_begin[0]);

const std::set<std::string> condor_keys(c_condor_keys_begin, c_condor_keys_end);

// keys whose string values should not be quoted in a condor submit file
// This allows to pass string expressions through without parsing them.

const char* c_noquote_keys_begin[] = {
  "grid_resource",
  "nordugrid_rsl",
  "requirements",
  "remote_requirements",
  "remote_remote_requirements"
};

const char** c_noquote_keys_end = c_noquote_keys_begin +
sizeof(c_noquote_keys_begin) / sizeof(c_noquote_keys_begin[0]);

const std::set<std::string> noquote_keys(c_noquote_keys_begin, c_noquote_keys_end);

bool
eq_char_nocase(char c1, char c2)
{
  return tolower(c1) == tolower(c2);
}

struct eq_string_nocase: std::binary_function<std::string, std::string, bool>
{
  bool operator()(std::string const& s1, std::string const& s2) const
  {
    if (s1.size() < s2.size()) {
      return std::equal(s1.begin(), s1.end(), s2.begin(), eq_char_nocase);
    } else {
      return std::equal(s2.begin(), s2.end(), s1.begin(), eq_char_nocase);
    }
  }
};

std::string stringize_literal(classad::Literal const* literal, bool quote_strings)
{
  std::string result;

  classad::Value value;
  literal->GetValue(value);
 
  switch (value.GetType()) {
  case classad::Value::BOOLEAN_VALUE:
    bool b;
    value.IsBooleanValue(b);
    result = (b ? "True" : "False");
    break;
  case classad::Value::INTEGER_VALUE:
    int i;
    value.IsIntegerValue(i);
    result = boost::lexical_cast<std::string>(i);
    break;
  case classad::Value::REAL_VALUE:
    double d;
    value.IsRealValue(d);
    result = boost::lexical_cast<std::string>(d);
    break;
  case classad::Value::STRING_VALUE: {
    std::string s;
    value.IsStringValue(s);
    if (quote_strings) {
      result = "\"" + s + "\"";
    } else {
      result = s;
    }
    break;}
  default:
    break;
  }

  return result;
}

struct InsertAttributeInSubmitFile:
  std::binary_function<std::ostream*, classad::AttrList::value_type, std::ostream*>
{
  std::ostream* operator()(
    std::ostream* osp,
    const classad::AttrList::value_type& key_value
  ) const
  {
    switch (key_value.second->GetKind()) {

    case classad::ExprTree::LITERAL_NODE: {

      std::string key;
      bool quote_strings = false;

      if (eq_string_nocase()(key_value.first, std::string("error_"))) {
          key = "error";
      } else if (count_if(condor_keys.begin(), condor_keys.end(),
                          bind1st(eq_string_nocase(), key_value.first)) > 0) {
        key = key_value.first;
      } else {
        key = "+" + key_value.first;
        if (count_if(noquote_keys.begin(), noquote_keys.end(),
                     bind1st(eq_string_nocase(), key_value.first)) == 0) {
          quote_strings = true; // quote user-defined attribute values
				// except for expressions that need to be
				// passed over to Condor
	}
      }

      assert(! key.empty());

      if (!key.empty()) {
        *osp << key << " = "
          << stringize_literal(dynamic_cast<classad::Literal*>(key_value.second), quote_strings)
          << "\n";
      }
      break;
    }

    default:
      // nothing for the moment
      break;
      
    }
  
    return osp;
  }

};

} // {anonymous}

std::ostream&
to_submit_stream(std::ostream& os, classad::ClassAd const& ad)
{
  std::accumulate(ad.begin(), ad.end(), &os, InsertAttributeInSubmitFile());
  os << "Queue 1" << std::endl;

  return os;
}

} // jdl namespace
} // glite namespace
