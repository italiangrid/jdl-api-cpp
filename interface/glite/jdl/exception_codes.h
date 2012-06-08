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

#ifndef GLITE_WMS_COMMON_REQUESTAD_EXCEPTION_CODES_H
#define GLITE_WMS_COMMON_REQUESTAD_EXCEPTION_CODES_H
 /*
 * exception_codes.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */
#include "glite/wmsutils/exception/exception_codes.h"

namespace glite {
namespace jdl {

   enum{
        WMS_JDLFULL= glite::wmsutils::exception::WMS_REQUESTAD_ERROR_BASE+1,   //full attribute
        WMS_JDLEMPTY, //empty attribute
        WMS_JDLMISMATCH, //JDL mistake Error
        WMS_JDL_MEMBER, //Wrong JDL Member-IsMember Usage
        WMS_JDLMANDATORY, //Mandatory attribute Error
        WMS_JDLSYN,
	WMS_JDLPARSE,
        WMS_JDLGROUP,
        WMS_JDLDUPLICATE,
        WMS_JDLTOOMANY,
        WMS_JOBADSCHEMA,
        WMS_JOBADSCH_GET,
	WMS_DAG_CHECK  //while retrieving Dag submission strings
   };

} // jdl namespace
} // glite namespace

#endif
// EOF
