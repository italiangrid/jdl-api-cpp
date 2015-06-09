#  See http://www.eu-egee.org/partners/ for details on the copyright
#  holders.
#  
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#  
#     http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
#  implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#  

message("-- checking for module 'GLiteJobid'")
find_path(GLite_JOBID_INCLUDE_DIR
          NAMES glite/jobid/JobId.h
          PATHS /usr/include)

find_library(GLite_JOBID_LIBRARY
             NAMES glite_jobid
             PATHS /usr/lib /usr/lib64)

set(GLite_JOBID_INCLUDE_DIRS ${GLite_JOBID_INCLUDE_DIR})
set(GLite_JOBID_LIBRARIES ${GLite_JOBID_LIBRARY})

if(GLite_JOBID_INCLUDE_DIRS AND GLite_JOBID_LIBRARIES)
    message("--   found  GLiteJobid")
    message("--   GLiteJobid_INCLUDE_DIRS: ${GLite_JOBID_INCLUDE_DIRS}")
    message("--   GLiteJobid_LIBRARIES: ${GLite_JOBID_LIBRARIES}")
    set(GLite_JOBID_FOUND TRUE)
else(gLite_INCLUDE_DIRS AND gLite_LIBRARIES)
    message("--   GLiteJobid not found")
    set(GLite_JOBID_FOUND FALSE)
endif(GLite_JOBID_INCLUDE_DIRS AND GLite_JOBID_LIBRARIES)
