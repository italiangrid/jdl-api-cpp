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

#include "PrivateAttributes.h"

namespace glite {
namespace jdl {

const std::string JDLPrivate::CONDOR_TRANSFER = "Transfer_Executable";
const std::string JDLPrivate::CONDOR_COPYTOSPOOL = "Copy_to_Spool";
const std::string JDLPrivate::STREAM_OUTPUT = "stream_output";
const std::string JDLPrivate::STREAM_ERROR = "stream_error";
const std::string JDLPrivate::NOTIFICATION = "Notification";
const std::string JDLPrivate::CONDOR_LOG = "Log";
const std::string JDLPrivate::CONDOR_OUTPUT = "Output";
const std::string JDLPrivate::CONDOR_ERROR = "Error";
const std::string JDLPrivate::CONDOR_ERROR_ = "Error_";
const std::string JDLPrivate::USERPROXY = "X509UserProxy";
const std::string JDLPrivate::SUBMITEVENTNOTES = "Submit_Event_Notes";
const std::string JDLPrivate::SUBMITEVENTUSERNOTES = "Submit_Event_User_Notes";
const std::string JDLPrivate::INPUT_SANDBOX_PATH = "InputSandboxPath";
const std::string JDLPrivate::OUTPUT_SANDBOX_PATH = "OutputSandboxPath";
const std::string JDLPrivate::CONDOR_GLOBUS_SCHEDULER = "GlobusScheduler";
const std::string JDLPrivate::CONDOR_GRID_TYPE = "grid_type";
const std::string JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE = "REMOTE_JobUniverse";
const std::string JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE = "REMOTE_SubUniverse";
const std::string JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE = "REMOTE_JobGridType";
const std::string JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME = "daemon_unique_name";
const std::string JDLPrivate::CONDOR_REQUIREMENTS = "requirements";
const std::string JDLPrivate::CONDOR_REMOTE_REQUIREMENTS = "REMOTE_Requirements";
const std::string JDLPrivate::CONDOR_REMOTE_ENV = "REMOTE_Env";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE = "REMOTE_REMOTE_Queue";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE = "REMOTE_REMOTE_GridType";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE = "REMOTE_REMOTE_JobUniverse";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS = "REMOTE_REMOTE_Requirements";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN = "REMOTE_REMOTE_FileSystemDomain";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN = "REMOTE_REMOTE_UidSystemDomain";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES = "REMOTE_REMOTE_ShouldTransferFiles";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT = "REMOTE_REMOTE_WhenToTransferOutput";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER = "REMOTE_REMOTE_Nodenumber";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD = "REMOTE_REMOTE_Stagecmd";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID = "REMOTE_REMOTE_edg_jobid";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT = "REMOTE_REMOTE_UserSubjectName";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_CEID = "REMOTE_REMOTE_ceid";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN = "REMOTE_REMOTE_VomsFqan";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION = "REMOTE_REMOTE_VirtualOrganisation";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS = "REMOTE_REMOTE_CeRequirements";
const std::string JDLPrivate::CONDOR_REMOTE_SCHEDD = "remote_schedd";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD = "REMOTE_RemoteSchedd";
const std::string JDLPrivate::CONDOR_REMOTE_REMOTE_POOL = "REMOTE_RemotePool";
const std::string JDLPrivate::CONDOR_GLOBUS_RESOURCE = "GlobusResource";
const std::string JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE = "REMOTE_GlobusResource";
const std::string JDLPrivate::CONDOR_SITE_NAME = "SiteName";
const std::string JDLPrivate::CONDOR_INITIAL_DIR = "InitialDir";
const std::string JDLPrivate::CONDOR_SITE_GATEKEEPER = "SiteGatekeeper";
const std::string JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES = "should_transfer_files";
const std::string JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT = "when_to_transfer_output";
const std::string JDLPrivate::CONDOR_PERIODIC_HOLD = "periodic_hold";
const std::string JDLPrivate::CONDOR_PERIODIC_REMOVE = "periodic_remove";
const std::string JDLPrivate::CONDOR_TRANSFER_INPUT_FILES = "transfer_input_files";
const std::string JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES = "transfer_output_files";
const std::string JDLPrivate::CONDOR_TRANSFEROUTPUT = "TransferOutput";
const std::string JDLPrivate::CONDOR_GLOBUS_RSL = "GlobusRSL";
const std::string JDLPrivate::CONDOR_SUBJECT = "UserSubjectName";
const std::string JDLPrivate::CONDOR_UNIVERSE = "Universe";
const std::string JDLPrivate::CONDOR_SUBMIT_FILE = "CondorSubmitFile";
const std::string JDLPrivate::DAGID = "edg_dagid";
const std::string JDLPrivate::PU_LIST_FILE_URI = "PerusalListFileURI";
const std::string JDLPrivate::ZIPPED_ISB = "ZippedISB";
const std::string JDLPrivate::EDG_PREVIOUS_MATCHES = "edg_previous_matches";
const std::string JDLPrivate::REALLY_RUNNING_TOKEN = "ReallyRunningToken";
const std::string JDLPrivate::GETENV = "Getenv";
const std::string JDLPrivate::REMOVE_KILL_SIG = "Remove_Kill_Sig";
const std::string JDLPrivate::VOMS_FQAN = "VOMS_FQAN";
const std::string JDLPrivate::DEFAULT_NODE_RETRYCOUNT = "DefaultNodeRetryCount";
const std::string JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT = "DefaultNodeShallowRetryCount";
const std::string JDLPrivate::CE_APPLICATION_DIR = "CeApplicationDir";
const std::string JDLPrivate::GRID_RESOURCE = "grid_resource";
const std::string JDLPrivate::NORDUGRID_RSL = "nordugrid_rsl";
const std::string JDLPrivate::CE_REQUIREMENTS = "CeRequirements";
const std::string JDLPrivate::CE_INFO_HOST = "CEInfoHostName";
const std::string JDLPrivate::REPLANS_COUNT = "ReplansCount";


} // namespace jdl
} // namespace glite

// Local Variables:
// mode: c++
// End:
