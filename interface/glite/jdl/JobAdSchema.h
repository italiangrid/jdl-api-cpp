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

#ifndef GLITE_WMS_COMMON_REQUESTAD_JOBADSCHEMA_H
#define GLITE_WMS_COMMON_REQUESTAD_JOBADSCHEMA_H
/*
* JobAdSchema.h
*
* Copyright (c) 2001 The European DataGrid Project - IST programme, all rights reserved.
*
* Contributors are mentioned in the code there appropriate.
*
*/
#include <string>
#include <vector>

namespace glite {
namespace jdl {

/**
 * Provides a Schema used to check the attribute in the JobAd
 * The default utilised schema is GLUE. To instanciate a schema you
 * will need to provide an array of Strings, one per attribute
 * @version 0.1
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
*/
class JobAdSchema {
	public:
	// int SCHEMA_MAX_ATTR
	/******************Public methods********************/
	enum attribute {
		/** other.DataAccessCost attribute */
		SCHEMA_DAC ,
		/** other.GlueHostApplicationSoftwareRunTimeEnvironment attribute.
		* Appended for MPI jobs in Requirements expression */
		SCHEMA_RTE     ,
		/** other.GlueCEInfoTotalCPUs attribute.
		* Appended for MPI jobs in Requirements expression */
		SCHEMA_TCPU  ,
		/**  other.GlueCEStateFreeCPUs attribute
		* Set for MPI jobs as a default rank (if not given) */
		SCHEMA_FCPU  ,
		/** other.GlueHostNetworkAdapterOutboundIP
		* Added for  Interactive Jobs in requirements expression*/
		SCHEMA_OIP  ,
		/** Max index array dimension for Schema Attributes */
		SCHEMA_ARRAY
	};
	/** CUSTOM schema constructor
	* @param values an array of string of #SCHEMA_ARRAY dimension  */
	JobAdSchema ( std::vector<std::string> values  )  ;
	/** GLUE schema static constructor  (JobAd default utilised schema)*/
	static JobAdSchema*  glueSchema() ;
	/** EDG schema static constructor: deprecated */
	static JobAdSchema edgSchema( ) ;
	/** Retrieve the value for a specified attribute
	*@param attrName the attribute to be retrieved
	*@return the string representation of the value to be retrieved*/
	std::string get ( attribute attrName ) ;
	/** Make a deep copy of the current JobAdSchema instance
	*@return the copy of the current schema*/
	JobAdSchema* Copy( ) ;
	private :
	/******************Private memebrs********************/
	std::vector<std::string> values ;
	JobAdSchema() ;
};

} // jdl namespace
} // glite namespace

#endif
