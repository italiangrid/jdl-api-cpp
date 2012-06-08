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

#ifndef GLITE_WMS_COMMON_REQUESTAD_EXPDAGAD_H
#define GLITE_WMS_COMMON_REQUESTAD_EXPDAGAD_H
/*
 * ExpDagAd.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */
#include "boost/scoped_ptr.hpp"
#include "NodeAd.h"
#include "DAGAd.h"
#include "JdlAttributeList.h"
#include "glite/jobid/JobId.h"
#include <classad_distribution.h>
#include "extractfiles.h"
namespace glite {
namespace jdl {

/**
* Used to specify the JobId of a Dag and of all its nodes recoursively (each node could be a Dag itself)
* name can be NULL
*/
struct JobIdStruct{

	/**Default Constructor*/
	JobIdStruct();
	
	/**Copy Constructor*/
	JobIdStruct(const JobIdStruct& jobStruct);

	/** Distructor */
	~JobIdStruct();

	/** Operator = */
	JobIdStruct& operator=(const JobIdStruct& jobStruct);
	
	/** The identifier of the job*/
	glite::jobid::JobId jobid ;

	/** The name of the node*/
	std::string* nodeName ;

	/** The list of the sub-jobs of this struct (0-size vector if of job type) */
	std::vector< JobIdStruct* > children ;
	
private:

	/** Method to be invoked by the destructor and assign operator to free
	* allocated memory in children vector
	*/
	void flushMemory(void);	
};

/**
 * Provide a Userinterface-friendly utilisation for DagAd class for the WMS environment
 * The user is able to create , modify and check a DagAd in order to prepare it to
 * the submission and to perform other simple operations
 *
 * @brief Provides a representation of the job description in the JDL language
 *
 * @ingroup UserInterface
 * @version 0.1
 * @date 18 7 2003
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
*/
class ExpDagAd{
	typedef std::vector<classad::ExprTree*>  isb_value;
	public:
		/** Possible attribute (of string type) to be set/get/removed from instance**/
		enum attribute {
			/** identifier of the Job */
			EDG_JOBID,
			/** Virtual Organisation related to the user*/
			VIRTUAL_ORGANISATION,
			/** certificate stored with MyProxy*/
			MYPROXY_SERVER,
			/** Sequence code provided by LB*/
			SEQUENCE_CODE,
			/** InputSandbox common path where job files are stored*/
			ISB_DEST_URI,
			/** Resource where to direclty submit the job*/
			SUBMIT_TO
		};
		/** Possible attribute (of vector of string type)to be set/get/removed from instance**/
		enum multiAttribute {
			/** InputSandbox */
			INPUTSB,
			/** Zipped InputSandbox*/
			ZIPPED_ISB
		};
		enum level {
			/** Representation up-to-date*/
			CURRENT ,
			/** Representation ready for submission (all checks performed)*/
			SUBMISSION,
			/** No information about nodes(attribute hidden) */
			NO_NODES,
			/** One attribute per line representation */
			MULTI_LINES,
			/** Deprecated */
			RESTORED
		};
					/**@name Constructors/Destructor */
 		//@{
		/** Constructor  from String*/
		ExpDagAd(  const std::string& jdl ) ;
		/** Constructor  from Stream*/
		ExpDagAd(  std::ifstream&  jdl_in ) ;
		/** Constructor  Copy */
		ExpDagAd( const ExpDagAd& dag );
		/** Constructor  From Ad*/
		ExpDagAd( Ad *ad );
		/** Constructor  From classad*/
		ExpDagAd( const classad::ClassAd &classAd);
		/** Operator =*/
		void operator=(const ExpDagAd& dag);
		/** Constructor  from DagAd */
		ExpDagAd( DAGAd* ad);
		/** destructor */
		virtual ~ExpDagAd() throw();
		/** Check whether the instance
		* can be submitted or not, verifying all the inserted attribute and their values
		* return the parsed (possibly internally modified ExpDagAd)
		*/
		ExpDagAd* check ();
 		//@}
		/** Return the string representation of the DagAd
		@return the ExpDagAd with the requested level string representation
		@param lev one of the allowed level    */
		std::string toString (const level &lev = CURRENT ) ;

		/** Check the node of the DagAd and retrieve their submission strings
		* @param jobids fill the vector with jobids value
		* in the same order as returned submission strings
		* @return a vector of DagAd node's submission strings   */
		std::vector<std::string> getSubmissionStrings (std::vector<std::string> *jobids=NULL) ;
		/** Retrieve the node for the specified Jobid
		* @param jobid the string representatio of the required jobid*/
		std::string jobid2node(const std::string &jobid);
		//@}
					/**@name Has attribute */
 		//@{
		/**Check if an attribute is present inside the DagAd
		*@param attr_name the name of the attribute to be looked for
		*@return true if the attribute is prensent, false otherwise  */
		bool hasAttribute (const std::string& attr_name ) ;
		/**
		* Check wheter the attribute has been already specified for the jobid
		*@param node the jobid of the node to be modified
		*@param attr_name the name of the attribute to be inserted */
		bool hasNodeAttribute ( const glite::jobid::JobId &node,
			const std::string &attr_name);
		/**
		* Check wheter the attribute has been already specified for the jobid
		*@param node the name of the node to be modified
		*@param attr_name the name of the attribute to be inserted */
		bool hasNodeAttribute (const std::string &node,
			const std::string &attr_name);
 		//@}
					/**@name Node Replacing */
		//@{
		/**
		* Replace the specified node with the gived NodeAd
		* @param nodeId the jobid of the node to be replaced
		* @param nodeAd the NodeAd to be set for the specified node*/
		void replaceNode (const glite::jobid::JobId &nodeId, NodeAd &nodeAd);
		/**
		* Set the couple  attribute = value for the specified node inside the classad
		* @param nodeName the name of the node to be replaced
		* @param nodeAd the NodeAd to be set for the specified node*/
		void replaceNode (const std::string &nodeName, NodeAd &nodeAd);
		//@}
					/**@name setNodeAttribute */
		//@{
		/**
		* Set the couple  attribute = value for the specified node inside the classad
		*@param node the jobid of the node to be modified
		*@param attr_name the name of the attribute to be inserted
		*@param attr_value the value of the string attribute to be inserted for the specified attribute */
		void setNodeAttribute ( const glite::jobid::JobId &node,
			const std::string &attr_name,const std::string &attr_value);
		/**
		* Set the couple  attribute = value for the specified node inside the classad
		*@param node the name of the node to be modified
		*@param attr_name the name of the attribute to be inserted
		*@param attr_value the value of the string attribute to be inserted for the specified attribute */
		void setNodeAttribute (const std::string &node,
			const std::string &attr_name , const std::string &attr_value);
		/**
		* Set the couple  attribute = value for the specified node inside the classad
		*@param node the jobid of the node to be modified
		*@param attr_name the name of the attribute to be inserted
		*@param attr_value the value of the integer attribute to be inserted for the specified attribute */
		void setNodeAttribute ( const glite::jobid::JobId &node,
			const std::string &attr_name,int &attr_value);
		/**
		* Set the couple  attribute = value for the specified node inside the classad
		*@param node the name of the node to be modified
		*@param attr_name the name of the attribute to be inserted
		*@param attr_value the value of the integer attribute to be inserted for the specified attribute */
		void setNodeAttribute (const std::string &node,
			const std::string &attr_name , int &attr_value);
		/**
		* Set the couple  attribute = value for the specified node inside the classad
		*@param node the jobid of the node to be modified
		*@param attr_name the name of the attribute to be inserted
		*@param attr_value the value of the boolean attribute to be inserted for the specified attribute */
		void setNodeAttribute ( const glite::jobid::JobId &node,
			const std::string &attr_name,bool &attr_value);
		/**
		* Set the couple  attribute = value for the specified node inside the classad
		*@param node the name of the node to be modified
		*@param attr_name the name of the attribute to be inserted
		*@param attr_value the value of the boolean attribute to be inserted for the specified attribute */
		void setNodeAttribute (const std::string &node,
			const std::string &attr_name , bool &attr_value);
		/**
		* Set a vector of strings for the specified attribute and node
		* @param node the jobid to be modified
		* @param attr_name the attribute to be added
		* @param attr_value the list of values (expressed as a vector of strings) to be inserted
		*/
		void setNodeAttribute (const glite::jobid::JobId &node,
			const std::string &attr_name , const std::vector<std::string> &attr_value);
		/**
		* Set a vector of strings for the specified attribute and node
		* @param node the name of the node to be modified
		* @param attr_name the attribute to be added
		* @param attr_value the list of values (expressed as a vector of strings) to be inserted
		*/
		void setNodeAttribute (const std::string &node,
			const std::string &attr_name , const std::vector<std::string> &attr_value);
		//@}
				/**@name getNode methods*/
		//@{
		/** Retrieve the NodeAd corresponding to the searched node
		* @param nodeId the jobid of the node to be retrieved
		* @return the NodeAd corresponding for the seeked node */
		NodeAd getNode (const glite::jobid::JobId &nodeId);
		/** Retrieve the NodeAd corresponding to the searched node
		* @param nodeName the name of the node to be retrieved
		* @return the NodeAd corresponding for the seeked node */
		NodeAd getNode (const std::string &nodeName);
		/**
		* Retrieve (if present) the string values for the specified attribute
		*@param node the jobid to be looked for
		*@param attr_name the name of the attributeto be retrieved
		*@return the values of the specified string attribute as a vector of strings*/
		std::vector< std::string > getNodeStringValue (const glite::jobid::JobId &node,
			const std::string &attr_name);
		/**
		* Retrieve (if present) the string values for the specified attribute
		*@param node the name of the node to be looked for
		*@param attr_name the name of the attributeto be retrieved
		*@return the values of the specified string attribute as a vector of strings*/
		std::vector< std::string > getNodeStringValue (const std::string &node,
			const std::string &attr_name);
		/**
		* Retrieve (if present) the string values for the specified attribute
		*@param node the jobid to be looked for
		*@param attr_name the name of the attributeto be retrieved
		*@return the integer value for the specified node and attribute */
		int getNodeInt (const glite::jobid::JobId &node,
			const std::string &attr_name);
		/**
		* Retrieve (if present) the string values for the specified attribute
		*@param node the name of the node to be looked for
		*@param attr_name the name of the attributeto be retrieved
		*@return the integer value for the specified node and attribute */
		int getNodeInt (const std::string &node,
			const std::string &attr_name);
		/**
		* Retrieve (if present) the string values for the specified attribute
		*@param node the jobid to be looked for
		*@param attr_name the name of the attributeto be retrieved
		*@return the boolean value for the specified node and attribute */
		bool getNodeBool (const glite::jobid::JobId &node,
			const std::string &attr_name);
		/**
		* Retrieve (if present) the string values for the specified attribute
		*@param node the name of the node to be looked for
		*@param attr_name the name of the attributeto be retrieved
		*@return the boolean value for the specified node and attribute */
		bool getNodeBool (const std::string &node,
			const std::string &attr_name);
		/**
		* Retrieve (if present) the string value for the specified attribute
		*@param node the name of the node to be looked for
		*@param attr_name the name of the attributeto be retrieved
		*@return the value of the specified string attribute*/
		std::string getNodeAttribute (const std::string &node,
			const std::string &attr_name );
		/** Retrieve the DagAd nodes values of a specified attribute
		* @param attr_name the name of the attribute to be retrieved
		* @return a vector of pairs. Each pair contain the string representation of the jobid and a deep copy of the Expression  		representing the value of attr_name for this sub-job */
		std::vector<  std::pair<  std::string  ,     classad::ExprTree* > >
		getSubAttributes (const std::string &attr_name);
		/** Retrieve the DagAd nodes names
		* @return a vector of string containing all the dag nodes names */
		std::vector<std::string> getNodes();
		//@}
				/**@name Del/Remove */
		//@{
		/**
		* Delete the specified attribute for the selected node
		* @param node the jobid to be analized
		* @param attr_name the attribute to be removed
		*/
		void delNodeAttribute (const glite::jobid::JobId &node,
			const std::string &attr_name );
		/**
		Remove (if present) the attribute from the specified nde
		*@param node the name of the node to be looked for
		*@param attr_name the name of the attributeto be retrieved*/
		void delNodeAttribute (const std::string &node,
			const std::string &attr_name );
		/** delete an attribue from the DagAd
		* @param attr_name the name of the attribute to be removed
		* @return true if attribute successfully removed */
		bool removeAttribute(attribute attr_name);
		/** delete an attribue from the DagAd
		* @param attr_name the name of the attribute to be removed
		* @return true if attribute successfully removed */
		bool removeAttribute(const std::string& attr_name);
		//@}
				/**@name Miscellanous methods*/
		//@{
		
		/** Retrieve the structure of the DagAd as in the current position.
		* The first item is the Dag itself which has no node (NULL) and which contains all its children info inside
		* all jobids must be already inserted (exception thrown otherwise)
		* @param jobIdStruct the JobId structure of the DagAd.*/
		void getJobIdStruct (JobIdStruct& jobIdStruct);
		
		/** Retrieve the structure of the DagAd as a map of jobid,node
		* all jobids must be already inserted (exception thrown otherwise)
		*@result a map of jobid,node representing the structure of the current DagAd*/
		std::map<std::string,std::string> getJobIdMap();
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
		* Set an attribute to be inherited at once inside the ExpDagAd
		* @param attr_name the attribute to be inherited*/
		void inherit(const std::string& attr_name);
		/**
		* If JobAd is used by a remove machine, it is impossible to look
		* into the local hard-disk by default this parameter is set to true
		* @param lookInto allow all the check methods to access to the local
		* hard disk (true) or skip the check (false)
		*/
		void setLocalAccess(bool lookInto);
		/** Expand the "nodes" attribute into a vector of JobAds
		* Load jdls for files-nodes type */
		void expand () ;
		/** Represent dependency by a formatted string
		@return dependency representation*/
		std::string showDependencies () ;
		//@}
				/**@name get Attributes*/
		//@{
		/** Retrieve the value of an attribute in the DagAd
		@param attr_name the name of the attribute to be retrieved
		@return the string representation of the value */
		std::string getAttribute (attribute attr_name );
		/** Retrieve the string value of an attribute in the DagAd
		@param attr_name the name of the attribute to be retrieved
		@return the string value of the needed attribute*/
		std::string getString(const std::string &attr_name);
		/** Retrieve the boolean value of an attribute in the DagAd
		@param attr_name the name of the attribute to be retrieved
		@return the boolean value of the attribute*/
		bool getBool(const std::string &attr_name);
		/** Retrieve the value of an Ad attribute in the DagAd
		@param attr_name the name of the attribute to be retrieved
		@return the Ad of the value (if of Ad type)*/
		Ad getAttributeAd (const std::string& attr_name);
		/** Retrieve the list of InputSandbox values of the DagAd
		@return the list containing all the string InputSandbox values */
		std::vector<std::string> getInputSandbox ();
		/*
		*Retreive a Value instance of the selected type
		* This Method is used by all  get<type>value methods
		*/
		classad::Value getTypeValue(const std::string& attr_name);
		std::vector<std::string> getStringValue(const std::string& attr_name);
		/**
		* DEPRECATED
		* Set the value of a vector of strings attribute in the DagAd
		@param attr_name the name of the attribute to be set
		@return the multiAttribute of the value to be retrieved as a vector of strings*/
		std::vector<std::string> getAttribute (multiAttribute attr_name);
		//@}
				/**@name set Attributes*/
		//@{
		/**
		* Set the string value of an attribute in the DagAd
		@param attr_name the name of the attribute to be set
		@param attr_value the attribute of the value to be set */
		void setAttribute (attribute attr_name, const std::string& attr_value);
		/**
		* Set the value of a vector of strings attribute in the DagAd
		@param attr_name the name of the attribute to be set
		@param attr_values the multiAttribute of the value to be set as a vector of strings*/
		void setAttribute (multiAttribute attr_name, const std::vector<std::string>& attr_values);

		/** DagAd dimension retrieval
		@return the number of the sub-job belonging to the DagAd  */
		std::size_t size();
		//@}
				/**@name default values*/
		//@{
		/** Retrieve the default Rank value as set by the user
		@return  default rank string representation (or empty string if not set)*/
		const std::string getDefaultRank ();
		/** Retrieve the default Requrirements value as set by the user
		@return  default requirements string representation (or empty string if not set)*/
		const std::string getDefaultReq  ();
		/**
		* Set the default value for Rank attribute
		* (take in consideration if not specified in JDL)
		* @param attr_value the value to be set to the default rank
		*/
		void setDefaultRank (const std::string& attr_value ) ;
		/**
		* Set the default value for Requirements attribute
		* (take in consideration if not specified in JDL)
		* @param attr_value the value to be set to the default requirements
		*/
		void setDefaultReq   (const std::string& attr_value ) ;
		/**
		* Set the default value for Rank attribute
		* (take in consideration if not specified in JDL)
		* @param attr_value the value to be set to the default rank
		*/
		void setDefaultRank (classad::ExprTree *attr_value ) ;
		/**
		* Set the default value for Requirements attribute
		* (take in consideration if not specified in JDL)
		* @param attr_value the value to be set to the default requirements
		*/
		void setDefaultReq   (classad::ExprTree *attr_value ) ;
		/**
		* Set the default values for UI manipulation
		* such as:
		* userTag UI node name
		* @param val whether to set (true) or not (false) such values while submitting  */
		void setDefaultValues   (bool val) {  uiManipulation = val;  };
		//@}

		/**@name Warnings Management*/
		//@{
		/** Determine whether there are any warning.
		* Warnings may be due to usage of deprecated attributes, methods, procedures.
		* @see #getWarnings
		* @see #addWarning
		* @return true whether warnings have been found
		*/
		bool hasWarnings();
		/** Retrieve all collected warnings
		* Warnings may be due to usage of deprecated attributes, methods, procedures.
		* @see #hasWarnings
		* @see #addWarning
		* @return a list of string, each one represent the warning message
		*/
		std::vector<std::string> getWarnings();
		/** Add a new warning message to
		* Warnings may be due to usage of deprecated attributes, methods, procedures.
		* @see #hasWarnings
		* @see #getWarnings
		* @param msg the warning message to be appended
		*/
		void addWarning(const std::string &msg);
		/** Add all warnings (if any) from a specified ad
		* @see #hasWarnings
		* @see #getWarnings
		* @see #addWarnings
		* @param nodeName the name of the node
		* @param ad the ad where to retrieves warning messages to be appended
		*/
		void addWarnings(const std::string &nodeName, Ad *ad);
		//@}
	protected:
		/** Internal DAGAd instance */
		boost::shared_ptr<glite::jdl::DAGAd> dagad;
	private:
		// Reset all values
		void reset() ;
		void inherit(glite::jdl::NodeAd* jobad, const std::string& attr_name,
			classad::ExprTree* expression, bool force=false);
		void inherit(glite::jdl::NodeAd* jobad,classad::ClassAd &dagClassAd);
		void evaluateAttribute(const std::string& attr_name, bool flatten=false) ;
		/**
		* Iterate over the nodes and order their names
		* first nodes will be expression free
		* last nodes will need an evaluation
		*/
		std::vector<DAGAd::node_iterator> orderNodes();
		void createMap();
		classad::ExprTree* EvaluateValue(classad::Value val, classad::ExprList* list );
		void checkSandBox( std::vector < std::pair<std::string , isb_value > >&  isb  , Ad& osb_nodes   );
		void fromString (const std::string& jdl, std::string jdl_file ="") ;
		void fromFile ( std::ifstream&  jdl_int ) ;
		void extract();
		bool checked ;
		std::map<std::string,std::string> map_nodes;
		checkType lookInto_b;
		classad::ExprTree *defaultRank ;
		classad::ExprTree  *defaultReq ;
		bool uiManipulation,toBretrieved ;
		// extracted local files
		ExtractedAd *extractedAd ;
		std::vector<std::string> warning_messages_v ;
}; //ExpDag class definition end

} // jdl namespace
} // glite namespace

#endif
//EOF
