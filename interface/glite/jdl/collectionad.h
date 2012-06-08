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

#ifndef GLITE_WMS_COMMON_REQUESTAD_COLLECTIONAD_H
#define GLITE_WMS_COMMON_REQUESTAD_COLLECTIONAD_H
/*
 * collectionad.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */

#include "Ad.h"
#include "NodeAd.h"
#include "extractfiles.h"
namespace glite {
namespace jdl {
/**
 *
 * @brief Provides a representation of collection (bunch) of jobs
 *
 * @version 0.1
 * @date April 2005
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
*/
class CollectionAd: public glite::jdl::Ad{
public:
	/** Constructory by Classad */
	CollectionAd( const classad::ClassAd& classAd );
	/** Default constructor */
	CollectionAd();
	/** Constructory by Stirng */
	CollectionAd( const std::string& classAd );
	/** operator = */
	void operator=(const CollectionAd& collect) ;
	/**  Default Destructor */
	virtual ~CollectionAd() throw();
	/** Check both syntax and semantic rules for a collection. Fill default values
	@return the checked/filled collection instance
	*/
	CollectionAd* check();
	/** Performs a check and return the checked/filled collection result
	*@return the checked collection into its string representation
	*/
	std::string toSubmissionString();
	/**
	* Retrieve (if present) the string value for the specified attribute
	*@param node the name of the node to be looked for
	*@param attr_name the name of the attributeto be retrieved
	*@return the value of the specified string attribute*/
	std::vector< std::string > getNodeStringValue (const std::string &node, const std::string &attr_name);
	/**
	* Retrieve  the string values for the specified attribute for all the nodes
	*@param attr_name the name of the attribute to be retrieved
	*@return a  vector of pair, each pair containing respectively the name of the node and a vector of
	* all the string values corresponding to the specified attr_name
	*/
	std::vector< std::pair<std::string ,std::vector< std::string > > >
	getNodeStringValues (const std::string &attr_name);
        /**
        * Retrieve  the string values for the specified attribute for all the nodes
        *@param attr_name the name of the attribute to be retrieved
        *@return a map with the nodes name and the vector of
        * all the string values corresponding to the specified attr_name
        */
        std::map<std::string, std::vector< std::string > >
        getNodeStringValuesMap (const std::string &attr_name);

	/**
	* If Collection is used by a remove machine, it is impossible to look into the
	* local hard-disk by default this parameter is set to true
	@param lookInto allow all the check methods to access to the local hard disk (true) or skip the check (false)
	*/
	void setLocalAccess(bool lookInto);
	/**
	* Set the default value for Rank attribute
	* (take in consideration if not specified in JDL)
	* @param attr_value the value to be set to the default rank  */
	void setDefaultRank (classad::ExprTree* attr_value);

	/**
	* Set the default value for Requirements attribute
	* (take in consideration if not specified in JDL)
	* @param attr_value the value to be set to the default requirements */
	void setDefaultReq (classad::ExprTree* attr_value );
	/**
	* Return wheter are there any files to be retrieved
	* This value has significant meaning only after a previous check
	*/
	bool gettoBretrieved(){return toBretrieved;}
	/**
	* Retrieve the local files to be for the current instance
	* @return a pointer to an ExtractedAd instance, containing all local
	* files to be extracted
	*/
	ExtractedAd* getExtractedAd();
	/**
	* Add a node to the collection
	* @param node the node to be added
	*/
	void addNode(Ad node);
private:
	void checkNode(NodeAd &nodead,std::vector<std::string> &extracted);
	void checkNodes(CollectionAd *collect,std::vector<std::string> &extracted);
	// decide whether to check file extistence (EXISTENCE) or not (WMPROXY)
	checkType lookInto_b;
	bool toBretrieved ;
	// Default special attributes:
	classad::ExprTree *defaultRank ;
	classad::ExprTree  *defaultReq ;
	// extracted local files
	ExtractedAd *extractedAd ;
};

} // jdl namespace
} // glite namespace

#endif

//EOF
