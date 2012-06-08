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

#ifndef GLITE_WMS_COMMON_REQUESTAD_JOBAD_H
#define GLITE_WMS_COMMON_REQUESTAD_JOBAD_H
/*
 * JobAd.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */
#include "Ad.h"
#include "JobAdSchema.h"
#include "classad_distribution.h"
#include "JdlAttributeList.h"
#include "extractfiles.h"
#include <boost/scoped_ptr.hpp>
namespace glite{
namespace jdl {
// class JdlAttributeList ;
/**
  * Provides a representation of the job description in the JDL language
 * and the functions for building and manipulating it. Basically the
 * JDL is the Condor ClassAd language, so it is legitimate the direct
 * use of the Condor API library for creating, modifying, deleting a
 * job description. However the JobAd class extends the ClassAd class
 * of the Condor ClassAd library additionally providing some helper methods
 * that ease the construction of job descriptions being fully compliant to
 * WP1 WMS specification.
 *
 * @brief Provides a representation of the job description in the JDL language
 *
 * @ingroup UserInterface
 * @version 0.1
 * @date 15 April 2002
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
*/

// class JobAd : private classad::ClassAd{
class JobAd : public glite::jdl::Ad{
	public:
				/**@name Constructors/Destructor */
 //@{
		/** Instantiates an  empty  JobAd object */
		JobAd() ;
		/** JobAd destructor */
		virtual ~JobAd() throw();
		/**Instantiates a JobAd object from the given ClassAd-jdl string
		* @param  jdl_string  A string representig the description of the job*/
		JobAd( const std::string& jdl_string);
		/**
		* Constructor with a ClassAd instance
		* @param classAd the ClassAd instance where to build the JobAd from
		*/
		JobAd(const classad::ClassAd& classAd);
		/** Copy constructor
		* @param jobad a JobAd instance to be copied from */
		JobAd(const JobAd& jobad);
		/** Operator "=" performs a deep copy of the JobAd instance  */
		void operator=(const JobAd& jobad);
		/**
		* Constructor with a ClassAd instance
		* @param classAd the ClassAd instance where to build the JobAd from
		*/
		void fromClassAd(const classad::ClassAd& classAd);
		/**
		* Constructor with a JobAd instance
		* @param jobad a JobAd instance to be copied */
		void fromJobAd(const JobAd& jobad);
 //@}
				/**@name String and Stream Constructor/Destructor */
 //@{
		/**
		* Convert the JobAd Instance into a single line string representation ready for submission
		* @return the string reoresentation that goes to the NetworkServer */
		std::string toSubmissionString();
		/** Put the JobAd Instance as a string into a file
		* @param file_path the string representation of the file where to copy the JobAd to
		*/
		void toFile(const std::string& file_path) ;
 //@}
					/**@name Insertion Methods*/
 //@{
 		/**
		* If JobAd is used by a remove machine, it is impossible to look into the local hard-disk
		* by default this parameter is set to true
		@param lookInto allow all the check methods to access to the local hard disk (true) or skip the check (false)
		*/
		void setLocalAccess(bool lookInto);
		/**
		* Set the default value for Rank attribute
		* (take in consideration if not specified in JDL)
		* @param attr_value the value to be set to the default rank  */
		void setDefaultRank (const std::string& attr_value ) ;
		/**
		* Set the default value for Requirements attribute
		* (take in consideration if not specified in JDL)
		* @param attr_value the value to be set to the default requirements */
		void setDefaultReq (const std::string& attr_value ) ;
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
		* Add a list of protocols to the set of allowed inputsandbox protocols
		* @param attr_value the list of protocol to be allowed for inputsandbox URL values
		*/
		void setAllowedProtocols (const std::vector<std::string>& attr_value ) ;
		/**
		* Retrieve the list of all allowed protocols for inputsandbox URL format
		*@return a vector containing all the protocols valid for the inputsandbox if provided with a URL format
		*/
		const std::vector<std::string> getAllowedProtocols ();
		/**
		* Add The specified Expression Attribute to the jdl istance
		* @param  attr_name  The Name of the attribute to be added
		* @param  attr_value  The string expression of the attribute to be added
		* @exception AdMismatchException  The type of value is not allowed for the specified attribute name
		* @exception AdClassAdException  a classAd method raised an error   */
		void  setAttributeExpr (const std::string& attr_name, const std::string& attr_value);
		/**
		* Add The specified Expression Attribute to the jdl istance
		* @param  attr_name  The Name of the attribute to be added
		* @param  attr_value  The string expression of the attribute to be added
		* @exception AdMismatchException  The type of value is not allowed for the specified attribute name
		* @exception AdClassAdException  a classAd method raised an error   */
		void  setAttributeExpr (const std::string& attr_name, ExprTree* attr_value);



 //@}
					/**@name Retrieval Methods*/
 //@{
		/**
		* Retreive the value of the specified attribute
		* @param attr_name The name of the attribute name to be retrieved
		* @return the Ad instance for the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The type of retrieved value is not allowed for the specified attribute name   */
		Ad getAd(const std::string& attr_name);
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The type of retrieved value is not allowed for the specified attribute name   */
		std::string getString(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the  value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The type of retrieved value is not allowed for the specified attribute name   */
		int getInt(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the  value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The type of retrieved value is not allowed for the specified attribute name   */
		double getDouble(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the  value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The type of retrieved value is not allowed for the specified attribute name   */
		bool getBool(const std::string& attr_name) ;
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
 //@}
                        /**@name Miscellaneous Methods*/
//@{
		/**Check if the couple attribute/value is admitted
		* @param attr_name  the name of the attribute
		* @param attr_value  a pointer to an ExprTree representing the value to be checkted
		* @exception AdMismatchException  The type of value is not allowed for the specified attribute name   */
		virtual void checkSyntax(const std::string& attr_name, classad::ExprTree* attr_value);
		virtual void checkSyntax(const std::string& attr_name, classad::Value attr_value);
		/**Check if the Member/isMember expression is properly used in rank and requirements attributes expressions
		* @param multi a vector containing all the attributes that could be of multiple value type
		* @exception   AdSyntaxException when the Member/IsMember expression is badly used*/
		void checkMultiAttribute ( const std::vector<std::string> &multi ) ;
		/**
		* Delete an Attribute. It fails if the attribute doesn't exist
		* @param attr_name The name of the attibute to be deleted
		* @return a deep copy of the expression that has been just deleted for the specified attribute
		* @exception AdEmptyException  The attribute has not been set yet  */
		classad::ExprTree* delAttribute(const std::string& attr_name) ;
		/**
		* Check the JobAd instance for both syntax and semanthic errors
		* @exception AdMismatchException  A value is not of the right type for an attribute name in the JobAd
		* @exception AdFormatException  A value is not in the right format for the  an attribute name in the JobAd
		* @exception AdSyntaxException  Syntax error catched while trying to add an attribute
		* @exception AdClassAdException  a classAd method raised an error
		* @exception AdListException  A list has been mad with a non-list value attribute
		*/
		void check( const bool& restore = true ) ;
//@}
	protected:
		/**
		* check values inside inputsanbox attribute and if necessar/y extrapolate them. Could be inherited to change check
		@param extracted a vector containing all the found values
		*/
		virtual void checkInputSandbox( std::vector<std::string>& extracted );
		/**
		* Check and control Rank and Requirements attribute. could be inherited to change check
		*/
		virtual void checkRankReq () ;
		/**
		* Evaluate the specified expression and set is as the value of the specified attribute
		*@param attr_name the name of the attribute to be set
		*@param val the expression for the value to be set
		*/
		virtual void insertAttribute(const std::string& attr_name , classad::ExprTree* val);
		/**
		* Analise a path and resolve the wildcards (if present) on it
		* check the existence of (at least one file) the path. Leave URI/URL address unchanged
		*@param attr_name the attribute to be checked (generally Sandbox values)
		*@param path the path to be checked (could contain wildcards)
		*@param extracted vector containing the extracted values
		*@param wmpUri the WMProxyBaseUri attribute value
		*@param isbUri an option parameter specifying the base path for non-local files
		*@return the vector with the extracted files

		void extractFiles(const std::string& attr_name,const std::string& path,std::vector<std::string> &extracted,
			const std::string &wmpUri="", const std::string &isbUri="") ;
		*/
		/** user classAd: classad containing all the attributes that could be possibly changed by the check method.
		* This member is utilized in order to  ripristinate (restore method ) the old classad situation*/
		classad::ClassAd user ;
		/** decide whether to check file extistence (EXISTENCE) or not (WMPROXY) */
		checkType lookInto_b;
		bool checking,toBretrieved;
		/** extracted local files */
		//ExtractedAd *extractedAd ;
		boost::scoped_ptr<ExtractedAd> extractedAd  ;
	private:
		void reset();
		//JobAdSchema *schema ;
		boost::scoped_ptr<JobAdSchema> schema ;
		JdlAttributeList jdlist ;
		// Check Only the syntax of the Jdl
		void checkJobType(const std::vector<std::string> & attr_value) ;
		void checkDataManagement( ) ;
		// This method is not yet implemented, used for future implementation (like DagAd)
		virtual void checkSpecials( ) ;
		// Default special attributes:
		classad::ExprTree *defaultRank ;
		classad::ExprTree  *defaultReq ;
		// Check Jdl semantic co-existance rules
		void checkSemantic() ;
		// Add an attribute, this method is used by all public addAttribute methods
		void restore () ;
		//This Variable is utilized to iterate over the threads
		friend class Job ;
		friend class ExpDagAd ;
		std::vector < std::string > allowed_protocols ;
		static bool isAbsolutePath(const std::string &path , bool platform_dependence = true) ;
		static const std::string getName (const std::string &path , bool platform_dependence = true)  ;
};

} // jdl namespace
} // glite namespace

#endif

//EOF
