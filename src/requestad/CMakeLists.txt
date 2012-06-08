#
#  Copyright (c) Members of the EGEE Collaboration. 2010.
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

include_directories(${CLASSAD_INCLUDE_DIRS}
                    ${GLITE_WMSUTILS_EXCEPTION_INCLUDE_DIRS}
                    ${GLITE_WMSUTILS_CLASSADS_INCLUDE_DIRS}
                    ${GLITE_JOBID_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/interface/glite/jdl)

add_definitions( -pipe -DWANT_NAMESPACES -DWANT_CLASSAD_NAMESPACE )

link_directories(${GLITE_WMSUTILS_EXCEPTION_LIBRARY_DIRS}
                 ${GLITE_WMSUTILS_CLASSADS_LIBRARY_DIRS}
                 ${GLITE_JOBID_LIBRARY_DIRS}
                 ${CLASSAD_INCLUDE_DIRS}
                 ${Boost_INCLUDE_DIRS})

add_library(glite_jdl_api_cpp SHARED JDLAttributes.cpp
                                     PrivateAttributes.cpp
                                     JobAdManipulation.cpp
                                     PrivateAdManipulation.cpp
                                     ManipulationExceptions.cpp
                                     JdlAttributeList.cpp
                                     JobAd.cpp
                                     JobAdSchema.cpp
                                     Ad.cpp
                                     RequestAdExceptions.cpp
                                     NodeAd.cpp
                                     parametricad.cpp
                                     ExpDagAd.cpp
                                     DAGAd.cpp
                                     DAGAdManipulation.cpp
                                     adconverter.cpp
                                     extractfiles.cpp
                                     collectionad.cpp
                                     convert.cpp
                                     grammar.cpp)

link_directories(${GLITE_WMSUTILS_EXCEPTION_LIBRARY_DIRS}
                 ${GLITE_WMSUTILS_CLASSADS_LIBRARY_DIRS}
                 ${GLITE_JOBID_LIBRARY_DIRS}
                 ${CLASSAD_INCLUDE_DIRS}
                 ${Boost_INCLUDE_DIRS})

install(TARGETS glite_jdl_api_cpp
        LIBRARY DESTINATION usr/lib)


add_subdirectory(pkgconfig)


