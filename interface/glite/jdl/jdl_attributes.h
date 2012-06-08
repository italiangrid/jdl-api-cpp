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

#ifndef  __JSUIJDLATTRIBUTES_H__
#define __JSUIJDLATTRIBUTES_H__

namespace glite {
namespace jdl {

// TBD these attributes have to be moved into a private section of JDLAttributes.def
#define JDL_TYPE_JOB "job"
#define JDL_TYPE_DAG "dag"
#define JDL_TYPE_COLLECTION "collection"
// #define JDL_SUBMIT_TO           "SubmitTo"

#define JDL_JOBTYPE_MPICH          "mpich"
#define JDL_JOBTYPE_NORMAL         "normal"
#define JDL_JOBTYPE_PARTITIONABLE  "partitionable"
#define JDL_JOBTYPE_PARAMETRIC     "parametric"
#define JDL_JOBTYPE_CHECKPOINTABLE "checkpointable"
#define JDL_JOBTYPE_INTERACTIVE    "interactive"

// Checkpointable JobType values: //TBD where to put them
#define JDL_CHKPT_JOBSTATE    "JobState"
#define JDL_CHKPT_DATA        "UserData"
#define JDL_CHKPT_STATEID     "StateId"
#define JDL_CHKPT_STEPS       "JobSteps"
#define JDL_CHKPT_CURRENTSTEP "CurrentStep"

// DagAd attribute names and values://TBD where to put them
#define JDL_TYPE_DAGAD       "DagAd"
#define JDL_DEPENDENCIES     "Dependencies"
#define JDL_HLR_LOCATION_ENV "HLR_LOCATION"

//Interactive Jobtype environment variables:
#define JDL_INTERACTIVE_SHADOWHOST   "BYPASS_SHADOW_HOST"
#define JDL_INTERACTIVE_SHADOWPORT   "BYPASS_SHADOW_PORT"
#define JDL_INTERACTIVE_STDIN        "GRID_CONSOLE_STDIN"
#define JDL_INTERACTIVE_STDOUT       "GRID_CONSOLE_STDOUT"
#define JDL_INTERACTIVE_STDERR       "GRID_CONSOLE_STDERR"
/*Classical JDL schema:
#define JDL_JOBTYPE_MPICH_REQ_RTE   "other.RunTimeEnvironment"
#define JDL_JOBTYPE_MPICH_REQ_CPU   "other.TotalCPUs"
#define JDL_JOBTYPE_MPICH_RANK_FREE "other.FreeCPUs"
*/
/** Glue JDL Schema: */

#define JDL_JOBTYPE_MPICH_REQ_RTE   "other.GlueHostApplicationSoftwareRunTimeEnvironment"
#define JDL_JOBTYPE_MPICH_REQ_CPU   "other.GlueCEInfoTotalCPUs"
#define JDL_JOBTYPE_MPICH_RANK_FREE "other.GlueCEStateFreeCPUs"
#define JDL_RANK_DATA_ACC_COST      "DataAccessCost"

//Requirements & Rank default values
#define JDL_DEFAULT_RANK "DefaultRank"
#define JDL_REQ_DEFAULT  "TRUE"
#define JDL_RANK_DEFAULT "-other.GlueCEStateEstimatedResponseTime"

} // jdl namespace
} // glite namespace

#endif
