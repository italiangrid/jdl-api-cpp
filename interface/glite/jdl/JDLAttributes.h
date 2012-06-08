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

#ifndef GLITE_WMS_COMMON_REQUESTAD_JDLATTRIBUTES_H
#define GLITE_WMS_COMMON_REQUESTAD_JDLATTRIBUTES_H

#ifndef GLITE_WMS_X_STRING
#define GLITE_WMS_X_STRING
#include <string>
#endif

namespace glite {
namespace jdl {

class JDL {
public:
  static const std::string REQUIREMENTS;
  static const std::string FUZZY_RANK;
  static const std::string ALLOW_ZIPPED_ISB;
  static const std::string PU_FILE_ENABLE;
  static const std::string NODES_COLLOCATION;
  static const std::string MOVE_TO_CE;
  static const std::string SHORT_DEADLINE_JOB;
  static const std::string WHOLENODES;
  static const std::string ENABLE_WMS_FEEDBACK;
  static const std::string EXITCODE;
  static const std::string NODENUMB;
  static const std::string CPUNUMBER;
  static const std::string SHPORT;
  static const std::string RETRYCOUNT;
  static const std::string SHALLOWRETRYCOUNT;
  static const std::string PU_TIME_INTERVAL;
  static const std::string SMPGRANULARITY;
  static const std::string HOSTNUMBER;
  static const std::string CE_MATCH;
  static const std::string CHKPT_STEPS;
  static const std::string CHKPT_CURRENTSTEP;
  static const std::string EXPIRY_TIME;
  static const std::string CREATION_TIME;
  static const std::string VALIDITY_TIME;
  static const std::string PARTITION_NUMBER;
  static const std::string RANK;
  static const std::string FUZZY_FACTOR;
  static const std::string NOTIFYTYPE;
  static const std::string JOBSTATUS;
  static const std::string ABORTREASON;
  static const std::string GLOBUSRESOURCE;
  static const std::string QUEUENAME;
  static const std::string MATCHSTATUS;
  static const std::string CE_RANK;
  static const std::string CANCELSTATUS;
  static const std::string FAILUREREASON;
  static const std::string TRANSFERSTATUS;
  static const std::string SANDBOXFILE;
  static const std::string JOBID;
  static const std::string CEID;
  static const std::string SUBMIT_TO;
  static const std::string EXECUTABLE;
  static const std::string STDOUTPUT;
  static const std::string STDINPUT;
  static const std::string STDERROR;
  static const std::string ARGUMENTS;
  static const std::string PROLOGUE;
  static const std::string PROLOGUE_ARGUMENTS;
  static const std::string EPILOGUE;
  static const std::string EPILOGUE_ARGUMENTS;
  static const std::string MYPROXY;
  static const std::string JOBTYPE;
  static const std::string OUTPUT_SE;
  static const std::string REPLICA_CATALOG;
  static const std::string USER_CONTACT;
  static const std::string CERT_SUBJ;
  static const std::string TYPE;
  static const std::string LB_SEQUENCE_CODE;
  static const std::string LRMS_TYPE;
  static const std::string ISB_BASE_URI;
  static const std::string WMPISB_BASE_URI;
  static const std::string OSB_BASE_DEST_URI;
  static const std::string JDL_ORIGINAL;
  static const std::string DELEGATION_ID;
  static const std::string CHKPT_STATEID;
  static const std::string CHKPT_DATA;
  static const std::string LB_ADDRESS;
  static const std::string VIRTUAL_ORGANISATION;
  static const std::string DSUPLOAD;
  static const std::string OD_OUTPUT_FILE;
  static const std::string OD_LOGICAL_FILENAME;
  static const std::string OD_STORAGE_ELEMENT;
  static const std::string HLR_LOCATION;
  static const std::string GLITE_WMS_UI_DAG_NODE_NAME;
  static const std::string NODE_NAME;
  static const std::string NODE_FILE;
  static const std::string SHHOST;
  static const std::string SHPIPEPATH;
  static const std::string PU_FILES_DEST_URI;
  static const std::string JOB_PROVENANCE;
  static const std::string MW_VERSION;
  static const std::string OUTPUTDATA;
  static const std::string USERTAGS;
  static const std::string DATA_REQUIREMENTS;
  static const std::string DATA_CATALOG_TYPE;
  static const std::string OUTPUTSB;
  static const std::string OSB_DEST_URI;
  static const std::string ISB_DEST_FILENAME;
  static const std::string INPUTSB;
  static const std::string ENVIRONMENT;
  static const std::string INPUTDATA;
  static const std::string DATA_ACCESS;
  static const std::string DATA_CATALOG;
  static const std::string STORAGE_INDEX;
  static const std::string SIGNIFICANT_ATTRIBUTES;
  static const std::string STEPWEIGHT;
  static const std::string PREJOB;
  static const std::string POSTJOB;
  static const std::string CHKPT_JOBSTATE;
  static const std::string CES;




  /* Parameters not requiring a function */
  static const std::string JOBTYPE_MPICH;
  static const std::string JOBTYPE_NORMAL;
  static const std::string JOBTYPE_PARTITIONABLE;
  static const std::string JOBTYPE_MULTIPLE;
  static const std::string JOBTYPE_CHECKPOINTABLE;
  static const std::string JOBTYPE_INTERACTIVE;
  static const std::string INTERACTIVE_SHADOWHOST;
  static const std::string INTERACTIVE_SHADOWPORT;
  static const std::string REQ_DEFAULT;
  static const std::string RANK_DEFAULT;

};

} // namespace jdl
} // namespace glite

#endif // EDG_WORKLOAD_COMMON_REQUESTAD_JDLATTRIBUTES_H

// Local Variables:
// mode: c++
// End:

