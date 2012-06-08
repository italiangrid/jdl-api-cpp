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

/* **************************************************************************
*  filename  : JobAdSchema.cpp
*  author    : Alessandro Maraschini <alessandro.maraschini@datamat.it>
*  copyright : (C) 2003 by DATAMAT
***************************************************************************/

#include "JobAdSchema.h"

// Exception handling:
#include "RequestAdExceptions.h"
#include "exception_codes.h"

#include <iostream>
#include <typeinfo>

namespace glite {
namespace jdl {

using namespace std ;
using namespace glite::wmsutils::exception ;


	/** GLUE schema static constructor  (JobAd default utilised schema)*/
	JobAdSchema* JobAdSchema::glueSchema( ) {
		// GLTIE_STACK_TRY("glueSchema( )");
		JobAdSchema *schema = new JobAdSchema() ;
		schema->values.push_back("other.DataAccessCost") ;
		schema->values.push_back("other.GlueHostApplicationSoftwareRunTimeEnvironment") ;
		schema->values.push_back("other.GlueCEInfoTotalCPUs") ;
		schema->values.push_back("other.GlueCEStateFreeCPUs") ;
		schema->values.push_back("other.GlueHostNetworkAdapterOutboundIP") ;
		return schema ;
		// GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}
	JobAdSchema* JobAdSchema::Copy( ){ return new JobAdSchema ( values) ; } ;

/*
	/ GLITE schema static constructor /
	static public *JobAdSchema JobAdSchema::edgSchema( ) {
		string values [] =  {  } ;
		return new JobAdSchema ( values) ;
	}
*/

	/** CUSTOM schema constructor
	* @param values an array of string of #SCHEMA_ARRAY dimension  */
	JobAdSchema::JobAdSchema (vector <string > vals) {
		string METHOD = "JobAdSchema" ;
		values.resize(0) ;
		// chek the dimension:
		if ( vals.size() != SCHEMA_ARRAY  )
			throw AdFormatException (__FILE__ , __LINE__ ,METHOD, WMS_JOBADSCHEMA, "") ;
		for (unsigned int i = 0 ; i< SCHEMA_ARRAY; i++ ){
			values.push_back(  vals[i]   );
		}
	}

	string JobAdSchema::get ( attribute attrName ) {
		if ( attrName >= SCHEMA_ARRAY )
			// attribute is wfongly casted by an integer
			throw std::bad_cast() ;
		return values[attrName] ;
	} ;


	JobAdSchema::JobAdSchema(){
		/** Do nothing, this megtod is private */
	} ;


} // jdl namespace
} // glite namespace
