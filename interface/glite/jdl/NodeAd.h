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

#ifndef GLITE_WMS_COMMON_REQUESTAD_NODEAD_H
#define GLITE_WMS_COMMON_REQUESTAD_NODEAD_H
/*
 * NodeAdNode.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */

#include "JobAd.h"
#include "JdlAttributeList.h"

namespace glite {
namespace jdl {

/**
 *
 * @brief Provides a representation of the job description in the JDL language
 *
 * @ingroup UserInterface
 * @version 0.1
 * @date 15 April 2002
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
*/
class NodeAd : public glite::jdl::JobAd{
 public:
	/** Default constructor */
	NodeAd():JobAd(){};
	/** Constructor with a string
	* @param jdl the string to be loaded
	*/
	NodeAd(const std::string& jdl):JobAd(){fromString(jdl);};
	/** Constructory by Classad */
	NodeAd(const classad::ClassAd& classAd):JobAd(){fromClassAd(classAd);};
	/** Constructory by NodeAd*/
	NodeAd(const NodeAd& nodead);
	/** Operator "=" performs a deep copy of the JobAd instance  */
	void operator=(const NodeAd& nodead);
	/** Operator = */
	virtual ~NodeAd() throw();
	/** Retrieve the inputSandbox remote files extracted while checking the Ad
	* @return a vector of all the Expression of remote sandbox i.e. all the &lt;node name&gt;_&lt;sbx file&gt; linked in the inputsandbox attribute
	*/
	std::vector<classad::ExprTree*> getRemoteSandbox() ;
	/** Retrieves the string value for the specified attribute
	* @param attr_name the name of the attribute to be looked up
	* @return the values, as a vector of strings, corresponding to the searched attribute
	*/
	std::vector<std::string> getStringValue(const std::string& attr_name) ;
	/** Add a UserTag to the node
	*@param attr_name the name of the usertag to be added
	*@param attr_value the value for the usertag
	*/
	void addUserTag ( const std::string& attr_name,  const std::string& attr_value );
	/** Check the syntax of the specified attribute
	* @param attr_name the name of the attribute
	* @param attr_value the classad value of the attribute
	*/
	void checkSyntax( const std::string& attr_name , classad::Value attr_value )  ;
  protected:
	/** Retrieves only string InputSandbox values for this node.
	* reference values will not be taken into consideration
	* @return the list of all string values
	*/
	std::vector<std::string> getISBStrings();
	/** Check InputSandbox value. Could be overloaded in order to perform different checks
	*@param extracted a vector listing all the files that have to be extracted i.e. whoose path has to be solved
	*/
	void checkInputSandbox(  std::vector<std::string>& extracted ) ;
	/** Perform Special checks for VirtualOrganisation attribute
	* Notice: for a NodeAd instance it is not mandatory (as for a JobAd)  */
	void checkSpecials( ) ;
	/**
	* JobAd overloaded method: used to insert an attribute inside the classad
	*@param attr_name the name of the attribute
	*@param val the value of the inserted attribute as a classad expression
	*/
	void insertAttribute(const std::string& attr_name , classad::ExprTree* val);

  private:
	// This vector contains all ISB expr Values, later will be used
	std::vector<classad::ExprTree*> inputRemotes ;
	friend class ExpDagAd ;
};

} // jdl namespace
} // glite namespace

#endif

//EOF
