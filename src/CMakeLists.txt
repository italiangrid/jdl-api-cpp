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

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

find_package(PkgConfig REQUIRED)
pkg_check_modules(CLASSAD REQUIRED emi-classad-ns)
pkg_check_modules(GLITE_WMSUTILS_EXCEPTION REQUIRED jobman-exception)
pkg_check_modules(GLITE_WMSUTILS_CLASSADS REQUIRED classad-utils)
pkg_check_modules(GLITE_JOBID REQUIRED emi-jobid)

if( ${CMAKE_VERSION} VERSION_LESS "2.8.2" )
    if( IS_DIRECTORY "/usr/lib64" )
        set(LIBSUBDIR "lib64")
    else( IS_DIRECTORY "/usr/lib64" )
        set(LIBSUBDIR "lib")
    endif( IS_DIRECTORY "/usr/lib64" )
else( ${CMAKE_VERSION} VERSION_LESS "2.8.2" )
    if( IS_DIRECTORY "/usr/lib64" AND NOT IS_SYMLINK "/usr/lib64" )
        set(LIBSUBDIR "lib64")
    else( IS_DIRECTORY "/usr/lib64" AND NOT IS_SYMLINK "/usr/lib64" )
        set(LIBSUBDIR "lib")
    endif( IS_DIRECTORY "/usr/lib64" AND NOT IS_SYMLINK "/usr/lib64" )
endif( ${CMAKE_VERSION} VERSION_LESS "2.8.2" )

if( NOT DEFINED BOOST_LIBRARYDIR AND IS_DIRECTORY "/usr/lib64" )
    set(BOOST_LIBRARYDIR "/usr/lib64")
endif( NOT DEFINED BOOST_LIBRARYDIR AND IS_DIRECTORY "/usr/lib64" )

set(Boost_USE_MULTITHREADED ON)
find_package( Boost COMPONENTS filesystem regex )

add_subdirectory(requestad)

