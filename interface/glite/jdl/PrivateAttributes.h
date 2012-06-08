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

#ifndef GLITE_WMS_COMMON_REQUESTAD_PRIVATEATTRIBUTES_H
#define GLITE_WMS_COMMON_REQUESTAD_PRIVATEATTRIBUTES_H

#ifndef GLITE_WMS_X_STRING
#define GLITE_WMS_X_STRING
#include <string>
#endif

namespace glite {
namespace jdl {

class JDLPrivate {
public:
  static const std::string CONDOR_TRANSFER;
  static const std::string CONDOR_COPYTOSPOOL;
  static const std::string STREAM_OUTPUT;
  static const std::string STREAM_ERROR;
  static const std::string NOTIFICATION;
  static const std::string CONDOR_LOG;
  static const std::string CONDOR_OUTPUT;
  static const std::string CONDOR_ERROR;
  static const std::string CONDOR_ERROR_;
  static const std::string USERPROXY;
  static const std::string SUBMITEVENTNOTES;
  static const std::string SUBMITEVENTUSERNOTES;
  static const std::string INPUT_SANDBOX_PATH;
  static const std::string OUTPUT_SANDBOX_PATH;
  static const std::string CONDOR_GLOBUS_SCHEDULER;
  static const std::string CONDOR_GRID_TYPE;
  static const std::string CONDOR_REMOTE_JOBUNIVERSE;
  static const std::string CONDOR_REMOTE_SUBUNIVERSE;
  static const std::string CONDOR_REMOTE_JOBGRIDTYPE;
  static const std::string CONDOR_DAEMON_UNIQUE_NAME;
  static const std::string CONDOR_REQUIREMENTS;
  static const std::string CONDOR_REMOTE_REQUIREMENTS;
  static const std::string CONDOR_REMOTE_ENV;
  static const std::string CONDOR_REMOTE_REMOTE_QUEUE;
  static const std::string CONDOR_REMOTE_REMOTE_GRID_TYPE;
  static const std::string CONDOR_REMOTE_REMOTE_JOB_UNIVERSE;
  static const std::string CONDOR_REMOTE_REMOTE_REQUIREMENTS;
  static const std::string CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN;
  static const std::string CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN;
  static const std::string CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES;
  static const std::string CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT;
  static const std::string CONDOR_REMOTE_REMOTE_NODENUMBER;
  static const std::string CONDOR_REMOTE_REMOTE_STAGECMD;
  static const std::string CONDOR_REMOTE_REMOTE_JOBID;
  static const std::string CONDOR_REMOTE_REMOTE_SUBJECT;
  static const std::string CONDOR_REMOTE_REMOTE_CEID;
  static const std::string CONDOR_REMOTE_REMOTE_VOMS_FQAN;
  static const std::string CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION;
  static const std::string CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS;
  static const std::string CONDOR_REMOTE_SCHEDD;
  static const std::string CONDOR_REMOTE_REMOTE_SCHEDD;
  static const std::string CONDOR_REMOTE_REMOTE_POOL;
  static const std::string CONDOR_GLOBUS_RESOURCE;
  static const std::string CONDOR_REMOTE_GLOBUS_RESOURCE;
  static const std::string CONDOR_SITE_NAME;
  static const std::string CONDOR_INITIAL_DIR;
  static const std::string CONDOR_SITE_GATEKEEPER;
  static const std::string CONDOR_SHOULD_TRANSFER_FILES;
  static const std::string CONDOR_WHEN_TO_TRANSFER_OUTPUT;
  static const std::string CONDOR_PERIODIC_HOLD;
  static const std::string CONDOR_PERIODIC_REMOVE;
  static const std::string CONDOR_TRANSFER_INPUT_FILES;
  static const std::string CONDOR_TRANSFER_OUTPUT_FILES;
  static const std::string CONDOR_TRANSFEROUTPUT;
  static const std::string CONDOR_GLOBUS_RSL;
  static const std::string CONDOR_SUBJECT;
  static const std::string CONDOR_UNIVERSE;
  static const std::string CONDOR_SUBMIT_FILE;
  static const std::string DAGID;
  static const std::string PU_LIST_FILE_URI;
  static const std::string ZIPPED_ISB;
  static const std::string EDG_PREVIOUS_MATCHES;
  static const std::string REALLY_RUNNING_TOKEN;
  static const std::string GETENV;
  static const std::string REMOVE_KILL_SIG;
  static const std::string VOMS_FQAN;
  static const std::string DEFAULT_NODE_RETRYCOUNT;
  static const std::string DEFAULT_NODE_SHALLOWRETRYCOUNT;
  static const std::string CE_APPLICATION_DIR;
  static const std::string GRID_RESOURCE;
  static const std::string NORDUGRID_RSL;
  static const std::string CE_REQUIREMENTS;
  static const std::string CE_INFO_HOST;
  static const std::string REPLANS_COUNT;


};

} // namespace jdl
} // namespace glite

#endif // GLITE_WMS_COMMON_REQUESTAD_PRIVATEATTRIBUTES_H

// Local Variables:
// mode: c++
// End:

