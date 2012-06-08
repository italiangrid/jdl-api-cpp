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

#include "JDLAttributes.h"

namespace glite {
namespace jdl {

const std::string JDL::REQUIREMENTS = "requirements";
const std::string JDL::FUZZY_RANK = "FuzzyRank";
const std::string JDL::ALLOW_ZIPPED_ISB = "AllowZippedISB";
const std::string JDL::PU_FILE_ENABLE = "PerusalFileEnable";
const std::string JDL::NODES_COLLOCATION = "NodesCollocation";
const std::string JDL::MOVE_TO_CE = "MoveToCE";
const std::string JDL::SHORT_DEADLINE_JOB = "ShortDeadlineJob";
const std::string JDL::WHOLENODES = "WholeNodes";
const std::string JDL::ENABLE_WMS_FEEDBACK = "EnableWmsFeedback";
const std::string JDL::EXITCODE = "ExitCode";
const std::string JDL::NODENUMB = "NodeNumber";
const std::string JDL::CPUNUMBER = "CpuNumber";
const std::string JDL::SHPORT = "ListenerPort";
const std::string JDL::RETRYCOUNT = "RetryCount";
const std::string JDL::SHALLOWRETRYCOUNT = "ShallowRetryCount";
const std::string JDL::PU_TIME_INTERVAL = "PerusalTimeInterval";
const std::string JDL::SMPGRANULARITY = "SMPGranularity";
const std::string JDL::HOSTNUMBER = "HostNumber";
const std::string JDL::CE_MATCH = "CeMatch";
const std::string JDL::CHKPT_STEPS = "JobSteps";
const std::string JDL::CHKPT_CURRENTSTEP = "CurrentStep";
const std::string JDL::EXPIRY_TIME = "ExpiryTime";
const std::string JDL::CREATION_TIME = "CreationTime";
const std::string JDL::VALIDITY_TIME = "ValidityTime";
const std::string JDL::PARTITION_NUMBER = "PartitionNumber";
const std::string JDL::RANK = "rank";
const std::string JDL::FUZZY_FACTOR = "fuzzy_factor";
const std::string JDL::NOTIFYTYPE = "NotificationType";
const std::string JDL::JOBSTATUS = "JobStatus";
const std::string JDL::ABORTREASON = "AbortedReason";
const std::string JDL::GLOBUSRESOURCE = "GlobusResourceContactString";
const std::string JDL::QUEUENAME = "QueueName";
const std::string JDL::MATCHSTATUS = "MatchStatus";
const std::string JDL::CE_RANK = "CE_Rank";
const std::string JDL::CANCELSTATUS = "CancelStatus";
const std::string JDL::FAILUREREASON = "FailureReason";
const std::string JDL::TRANSFERSTATUS = "TransferStatus";
const std::string JDL::SANDBOXFILE = "SandboxFile";
const std::string JDL::JOBID = "edg_jobid";
const std::string JDL::CEID = "ce_id";
const std::string JDL::SUBMIT_TO = "SubmitTo";
const std::string JDL::EXECUTABLE = "Executable";
const std::string JDL::STDOUTPUT = "StdOutput";
const std::string JDL::STDINPUT = "StdInput";
const std::string JDL::STDERROR = "StdError";
const std::string JDL::ARGUMENTS = "Arguments";
const std::string JDL::PROLOGUE = "Prologue";
const std::string JDL::PROLOGUE_ARGUMENTS = "PrologueArguments";
const std::string JDL::EPILOGUE = "Epilogue";
const std::string JDL::EPILOGUE_ARGUMENTS = "EpilogueArguments";
const std::string JDL::MYPROXY = "MyProxyServer";
const std::string JDL::JOBTYPE = "JobType";
const std::string JDL::OUTPUT_SE = "OutputSE";
const std::string JDL::REPLICA_CATALOG = "ReplicaCatalog";
const std::string JDL::USER_CONTACT = "UserContact";
const std::string JDL::CERT_SUBJ = "CertificateSubject";
const std::string JDL::TYPE = "Type";
const std::string JDL::LB_SEQUENCE_CODE = "LB_sequence_code";
const std::string JDL::LRMS_TYPE = "lrms_type";
const std::string JDL::ISB_BASE_URI = "InputSandboxBaseURI";
const std::string JDL::WMPISB_BASE_URI = "WMPInputSandboxBaseURI";
const std::string JDL::OSB_BASE_DEST_URI = "OutputSandboxBaseDestURI";
const std::string JDL::JDL_ORIGINAL = "JDL_Original";
const std::string JDL::DELEGATION_ID = "Delegation_ID";
const std::string JDL::CHKPT_STATEID = "StateId";
const std::string JDL::CHKPT_DATA = "UserData";
const std::string JDL::LB_ADDRESS = "LBAddress";
const std::string JDL::VIRTUAL_ORGANISATION = "VirtualOrganisation";
const std::string JDL::DSUPLOAD = "DSUpload";
const std::string JDL::OD_OUTPUT_FILE = "OutputFile";
const std::string JDL::OD_LOGICAL_FILENAME = "LogicalFileName";
const std::string JDL::OD_STORAGE_ELEMENT = "StorageElement";
const std::string JDL::HLR_LOCATION = "HLRLocation";
const std::string JDL::GLITE_WMS_UI_DAG_NODE_NAME = "glite_wl_ui_DagNodeName";
const std::string JDL::NODE_NAME = "NodeName";
const std::string JDL::NODE_FILE = "File";
const std::string JDL::SHHOST = "ListenerHost";
const std::string JDL::SHPIPEPATH = "ListenerPipeName";
const std::string JDL::PU_FILES_DEST_URI = "PerusalFilesDestURI";
const std::string JDL::JOB_PROVENANCE = "JobProvenance";
const std::string JDL::MW_VERSION = "MwVersion";
const std::string JDL::OUTPUTDATA = "OutputData";
const std::string JDL::USERTAGS = "UserTags";
const std::string JDL::DATA_REQUIREMENTS = "DataRequirements";
const std::string JDL::DATA_CATALOG_TYPE = "DataCatalogType";
const std::string JDL::OUTPUTSB = "OutputSandbox";
const std::string JDL::OSB_DEST_URI = "OutputSandboxDestURI";
const std::string JDL::ISB_DEST_FILENAME = "InputSandboxDestFileName";
const std::string JDL::INPUTSB = "InputSandbox";
const std::string JDL::ENVIRONMENT = "Environment";
const std::string JDL::INPUTDATA = "InputData";
const std::string JDL::DATA_ACCESS = "DataAccessProtocol";
const std::string JDL::DATA_CATALOG = "DataCatalog";
const std::string JDL::STORAGE_INDEX = "StorageIndex";
const std::string JDL::SIGNIFICANT_ATTRIBUTES = "SignificantAttributes";
const std::string JDL::STEPWEIGHT = "StepWeight";
const std::string JDL::PREJOB = "Prejob";
const std::string JDL::POSTJOB = "Postjob";
const std::string JDL::CHKPT_JOBSTATE = "JobState";
const std::string JDL::CES = "Ces";




/* Parameters not requiring a function */
const std::string JDL::JOBTYPE_MPICH = "MPICH";
const std::string JDL::JOBTYPE_NORMAL = "NORMAL";
const std::string JDL::JOBTYPE_PARTITIONABLE = "PARTITIONABLE";
const std::string JDL::JOBTYPE_MULTIPLE = "MULTIPLE";
const std::string JDL::JOBTYPE_CHECKPOINTABLE = "CHECKPOINTABLE";
const std::string JDL::JOBTYPE_INTERACTIVE = "INTERACTIVE";
const std::string JDL::INTERACTIVE_SHADOWHOST = "BYPASS_SHADOW_HOST";
const std::string JDL::INTERACTIVE_SHADOWPORT = "BYPASS_SHADOW_PORT";
const std::string JDL::REQ_DEFAULT = "TRUE";
const std::string JDL::RANK_DEFAULT = "-EstimatedTraversalTime";

} // namespace jdl
} // namespace glite

// Local Variables:
// mode: c++
// End:
