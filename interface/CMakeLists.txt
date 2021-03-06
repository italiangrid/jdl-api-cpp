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


file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
     "PROJECT_NAME=${CMAKE_PROJECT_NAME}-${PKGVER}\n"
     "OUTPUT_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}\n"
     "CREATE_SUBDIRS=NO\n"
     "OUTPUT_LANGUAGE=English\n"
     "BRIEF_MEMBER_DESC=YES\n"
     "REPEAT_BRIEF=YES\n"
     "ALWAYS_DETAILED_SEC=NO\n"
     "INLINE_INHERITED_MEMB=NO\n"
     "STRIP_FROM_INC_PATH=${CMAKE_CURRENT_SOURCE_DIR}\n"
     "FULL_PATH_NAMES=YES\n"
     "STRIP_FROM_PATH=${CMAKE_CURRENT_SOURCE_DIR}\n"
     "SHORT_NAMES=NO\n"
     "MULTILINE_CPP_IS_BRIEF=NO\n"
     "INHERIT_DOCS=YES\n"
     "DISTRIBUTE_GROUP_DOC=NO\n"
     "OPTIMIZE_OUTPUT_FOR_C=YES\n"
     "SUBGROUPING=YES\n"
     "EXTRACT_ALL=YES\n"
     "EXTRACT_PRIVATE=NO\n"
     "EXTRACT_STATIC=NO\n"
     "EXTRACT_LOCAL_CLASSES=YES\n"
     "EXTRACT_LOCAL_METHODS=NO\n"
     "HIDE_UNDOC_MEMBERS=NO\n"
     "HIDE_UNDOC_CLASSES=NO\n"
     "HIDE_FRIEND_COMPOUNDS=NO\n"
     "HIDE_IN_BODY_DOCS=NO\n"
     "INTERNAL_DOCS=NO\n"
     "CASE_SENSE_NAMES=NO\n"
     "HIDE_SCOPE_NAMES=NO\n"
     "SHOW_INCLUDE_FILES=YES\n"
     "INLINE_INFO=YES\n"
     "SORT_MEMBER_DOCS=YES\n"
     "SORT_BRIEF_DOCS=NO\n"
     "SORT_BY_SCOPE_NAME=NO\n"
     "GENERATE_TODOLIST=YES\n"
     "GENERATE_TESTLIST=YES\n"
     "GENERATE_BUGLIST=YES\n"
     "GENERATE_DEPRECATEDLIST=YES\n"
     "MAX_INITIALIZER_LINES=30\n"
     "SHOW_USED_FILES=YES\n"
     "QUIET=YES\n"
     "WARNINGS=NO\n"
     "WARN_IF_UNDOCUMENTED=YES\n"
     "WARN_IF_DOC_ERROR=YES\n"
     "WARN_FORMAT=\"$file:$line: $text\"\n"
     "INPUT=${CMAKE_CURRENT_SOURCE_DIR}\n"
     "FILE_PATTERNS=*.cpp *.h\n"
     "RECURSIVE=YES\n"
     "EXCLUDE_SYMLINKS=NO\n"
     "FILTER_SOURCE_FILES=NO\n"
     "SOURCE_BROWSER=NO\n"
     "INLINE_SOURCES=NO\n"
     "STRIP_CODE_COMMENTS=YES\n"
     "REFERENCED_BY_RELATION=YES\n"
     "REFERENCES_RELATION=YES\n"
     "VERBATIM_HEADERS=YES\n"
     "ALPHABETICAL_INDEX=YES\n"
     "COLS_IN_ALPHA_INDEX=5\n"
     "GENERATE_HTML=YES\n"
     "HTML_OUTPUT=html\n"
     "HTML_FILE_EXTENSION=.html\n"
     "HTML_ALIGN_MEMBERS=YES\n"
     "GENERATE_HTMLHELP=NO\n"
     "BINARY_TOC=NO\n"
     "TOC_EXPAND=NO\n"
     "DISABLE_INDEX=NO\n"
     "ENUM_VALUES_PER_LINE=4\n"
     "GENERATE_TREEVIEW=YES\n"
     "TREEVIEW_WIDTH=250\n"
     "GENERATE_LATEX=NO\n"
     "GENERATE_RTF=NO\n"
     "GENERATE_MAN=NO\n"
     "GENERATE_XML=NO\n"
     "GENERATE_AUTOGEN_DEF=NO\n"
     "GENERATE_PERLMOD=NO\n")

file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/glite/jdl/*.h)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
                   DEPENDS ${HEADER_FILES}
                   COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg)

add_custom_target(doxygen ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/glite/jdl/
        DESTINATION usr/include/glite/jdl
        FILES_MATCHING PATTERN "*.h"
        PATTERN "CMakeFiles" EXCLUDE)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
        DESTINATION usr/share/doc/glite-jdl-api-cpp)

