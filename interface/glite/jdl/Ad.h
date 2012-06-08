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

#ifndef GLITE_WMS_COMMON_REQUESTAD_AD_H
#define GLITE_WMS_COMMON_REQUESTAD_AD_H
/*
 * Ad.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */


/** \mainpage JDL API C++
*
* \section intro_sec Description
* <p>
* This set of APIs is ment to allow the user manipulating several kind of JDL with a higher level than the pure condor classad language.<BR>
* In particular, it allows to
* <UL>
* <LI>Manipulate simple and complex types of  \link glite::jdl::JobAd Jobs \endlink</LI>
* <LI>Manipulate \link glite::jdl::ExpDagAd DAG \endlink jobs and their \link glite::jdl::NodeAd nodes \endlink</LI>
* <LI>Manipulate \link glite::jdl::CollectionAd collections of\endlink jobs</LI>
* <LI>\link glite::jdl::AdConverter Convert\endlink the above kind of instances</LI>
* <LI>Manage, extract and check the \link glite::jdl::ExtractedAd files listed \endlink inside jobs, dags, collections ...</LI>
* </UL>
* */








#include "classad_distribution.h"

namespace glite {
namespace jdl {

/**
 * Provides a common interface for all Ad components.
 * It allows the user to create a valid ClassAd instance utilizing native classes and
 * retrieve any kind of information from it. It is utilised as a superclass for JobAd class
 * @see JobAd
 *
 *
 * @version 0.1
 * @date 15 April 2002
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it> */

class Ad : protected classad::ClassAd{
	public :
					/**@name Constructors*/
		//@{
		/**
		* default Constructor   */
		Ad() ;
		/**
		* Default Destructor   */
		virtual ~Ad() throw();
		/**
		* Constructor by ClassAd
		@param classAd the classad source where to create the Ad instance from*/
		Ad(const classad::ClassAd& classAd );
		/**
		* Constructor by string
		@param jdl_string the Ad string representation */
		Ad(const std::string& jdl_string) ;
		Ad(const Ad& jobad);
		/** Operator "=" performs a deep copy of the Ad instance  */
		virtual void operator=(const Ad& jobad);

		//@}
					/**@name From methods*/
		//@{
		/**
		* Create an Ad instance from a string
		@param jdl_string the ad string representation
		@param jdl_file path of the jdl file*/
		void fromString(const std::string& jdl_string, std::string jdl_file= "") ;
		/**
		* Create an Ad instacne from a file
		@param jdl_file the string representing the path containing the jdl to be parsed */
		void fromFile(const std::string& jdl_file) ;
		/**
		* Create the JobAd object with the given input stream.
		* @param  jdl_in  this is the job description passed in the form of a generic input stream
		* so that it can be taken from a terminal input stream, file input stream, string streams etc.*/
		void fromStream(std::istream& jdl_in) ;
		/**
		* Create the JobAd object with the given classad
		* @param  classAd  this is the job description passed as a classad*/
		virtual void fromClassAd(const classad::ClassAd& classAd);
		//@}
					/**@name To methods*/
		//@{
		/**
		* Convert the Ad Instance into a single line string representation
		* @return the ad as in its string representation */
		virtual std::string toString();
		/**Convert an Ad attribute into its string representation
		@param attr_name the attribute to be looked up
		@return return the attrbute string representation*/
		virtual std::string toString( const std::string& attr_name );
		/**
		* Convert the Ad Instance into a multi line indented string representation
		*@return as in toString() methods but splits the string one line per attribute */
		virtual std::string toLines();
		/** Check whether the JobAd has been initialised
		*@return whether the JobAd has been initialised(true) or not (false)*/
		bool isSet() ;
		/**Reset the JobAd Instance. All the previous existing attributes will be deleted*/
		void clear();
		//@}
					/**@name general methods*/
		//@{
		/**Deep copy of Ad.
		@return a ClassAd pointer representing a copy of all Ad attributes**/
		classad::ClassAd* const ad(){return static_cast<ClassAd*>(Copy());}
		/** Check If the specified attribute has already been set
		* @param attr_name The name of the attibute to be looked for
		* @return @a true if the attribute has been found, @a false otherwise  */
		bool hasAttribute(const std::string& attr_name);
		/**
		* Delete an Attribute. It fails if the attribute doesn't exist
		* @exception  AdEmptyException attribute has not been set yet
		* @return the deep copy of the expression for the deleted attribute
		* @param attr_name The name of the attibute to be deleted */
		virtual classad::ExprTree* delAttribute(const std::string& attr_name) ;
		/**
		* Delete an Attribute. It fails if the attribute doesn't exist
		* @exception  AdEmptyException attribute has not been set yet
		* @param attr_name The name of the attibute to be deleted */
		void remAttribute(const std::string& attr_name) ;
		/**
		* Returns an expression. NULL returned if the attribute doesn't exist
		* @return the deep copy of the expression for the attribute
		* @param attr_name The name of the attibute to be deleted */
		virtual classad::ExprTree* lookUp(const std::string& attr_name){ return Lookup(attr_name);};

		/**
		* Check if the specified value is present in the specified attribute  */
		bool hasAttribute(const std::string& attr_name, const std::string& attr_value);
		/**
		* Retrieve the list of attribugtes present inside the instance
		* @return a vector containing (with no order) all the attributes of the Ad
		*/
		std::vector<std::string> attributes() ;
		/**
		* merge the attributes of the specified classad overriding the attribute with the same name
		* Classad type attribute will be recoursively merged
		* @param source the Ad instance which will be merged in the current Ad. attributes with the same name will have its values
		* @param overwrite in case of already exising attriubte, determine whether to overwrite it
		*/
		void merge (Ad source, bool overwrite=true);
		//@}
			/**@name Get Methods*/
		//@{
		enum {
		/** Unknown type
		@see #getType*/
		TYPE_UNKNOWN = classad::Value::ERROR_VALUE,
		/**Attribute Integer type value
		@see #getType*/
		TYPE_INTEGER =classad::Value::INTEGER_VALUE,
		/**Attribute Boolean type value
		@see #getType*/
		TYPE_BOOLEAN =classad::Value::BOOLEAN_VALUE,
		/**Attribute String type value
		@see #getType*/
		TYPE_STRING =classad::Value::STRING_VALUE,
		/**Attribute Real/Double type value
		@see #getType*/
		TYPE_REAL =classad::Value::REAL_VALUE,
		/**Attribute Real/Double type value
		@see #getType*/
		TYPE_CLASSAD =classad::Value::CLASSAD_VALUE,
		/**Attribute Expression type value
		@see #getType*/
		TYPE_EXPRESSION =classad::Value::UNDEFINED_VALUE
		};
		/**
		* Retrieve the type of the value specified for attr_name
		*@param attr_name the name of the attribute
		*@return an integer representing the type of the attribute
		*@exception AdEmptyException if the attribute is not present in the JobAd instance
		*@see #TYPE_UNKNOWN
		*@see #TYPE_INTEGER
		*@see #TYPE_BOOLEAN
		*@see #TYPE_STRING
		*@see #TYPE_REAL
		*@see #TYPE_CLASSAD
		*@see #TYPE_EXPRESSION */
		int getType (const std::string& attr_name )   ;
		/**
		* Allow adding a value to an already set attribute of the JobAd instance
		* (i.e. it transforms it in a list attribute). if used on a non-set attribute the corresponding setAttribute method is automatically called.
		*  @param attr_name a string representing the attribute name
		*  @param attr_value -  The value of the attribute to be added
		* @exception AdMismatchException - The type of value is not allowed for the specified attribute name
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute */
		void  addAttribute (const std::string& attr_name, int attr_value)          ;
		/**
		* Allow adding a value to an already set attribute of the JobAd instance
		* (i.e. it transforms it in a list attribute). if used on a non-set attribute the corresponding setAttribute method is automatically called.
		*  @param attr_name a string representing the attribute name
		*  @param attr_value -  The value of the attribute to be added
		* @exception AdMismatchException - The type of value is not allowed for the specified attribute name
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute */
		void  addAttribute (const std::string& attr_name, double attr_value)       ;
		/**
		* Allow adding a value to an already set attribute of the JobAd instance
		* (i.e. it transforms it in a list attribute). if used on a non-set attribute the corresponding setAttribute method is automatically called.
		*  @param attr_name a string representing the attribute name
		*  @param attr_value -  The value of the attribute to be added
		* @exception AdMismatchException - The type of value is not allowed for the specified attribute name
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute*/
		void  addAttribute (const std::string& attr_name, bool attr_value)         ;
		/**
		* Allow adding a value to an already set attribute of the Ad instance
		* (i.e. it transforms it in a list attribute). if used on a non-set attribute the corresponding setAttribute method is automatically called.
		*  @param attr_name a string representing the attribute name
		*  @param attr_value -  The value of the attribute to be added
		* @exception AdMismatchException - The type of value is not allowed for the specified attribute name
		* @exception AdFormatException The type of value is not allowed for the specified attribute name
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute  */
		void  addAttribute (const std::string& attr_name, const std::string& attr_value);
		/**
		* Allow adding a value to an already set attribute of the Ad instance
		* (i.e. it transforms it in a list attribute). if used on a non-set attribute the corresponding setAttribute method is automatically called.
		*  @param attr_name a string representing the attribute name
		*  @param attr_value -  The value of the attribute to be added
		* @exception AdMismatchException - The type of value is not allowed for the specified attribute name
		* @exception AdFormatException The type of value is not allowed for the specified attribute name
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute  */
		void  addAttribute (const std::string& attr_name, const char *attr_value){addAttribute(attr_name , std::string(attr_value));}
		/**
		* Allow adding a value to an already set attribute of the JobAd instance
		* (i.e. it transforms it in a list attribute). if used on a non-set attribute the corresponding setAttribute method is automatically called.
		*  @param attr_name a string representing the attribute name
		*  @param attr_value -  The value of the attribute to be added
		* @exception AdMismatchException - The type of value is not allowed for the specified attribute name
		* @exception AdFormatException The type of value is not allowed for the specified attribute name
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute  */
		void  addAttribute (const std::string& attr_name, Ad* attr_value);
		/**
		* Add The specified Expression Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The string expression of the attribute to be added
		* @exception AdClassAdException - a classAd method raised an error
		* @exception AdEmptyException - The attribute  attr_name had been already set */
		virtual void  setAttributeExpr (const std::string& attr_name, const std::string& attr_value);
		/**
		* Add The specified Integer Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The value of the attribute to be added
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute
		* @exception AdEmptyException - The attribute  attr_name had been already set   */
		virtual void  setAttribute (const std::string& attr_name, int attr_value) ;
		/**
		* Add The specified String Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The value of the attribute to be added
		* @exception AdEmptyException - The attribute  attr_name had been already set
		* @exception AdFormatException The type of value is not allowed for the specified attribute name   */
		virtual void  setAttribute (const std::string& attr_name, const std::string& attr_value) ;
		/**
		* Add The specified String Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The value of the attribute to be added
		* @exception AdEmptyException - The attribute  attr_name had been already set
		* @exception AdFormatException The type of value is not allowed for the specified attribute name   */
		virtual void  setAttribute (const std::string& attr_name, const char *attr_value ) {  setAttribute (attr_name , std::string(attr_value) ); }
		/**
		* Add The specified String Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The value of the attribute to be added
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute
		* @exception AdEmptyException - The attribute  attr_name had been already set   */
		virtual void  setAttribute (const std::string& attr_name, double attr_value)   ;
		/**
		* Add The specified String Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The value of the attribute to be added
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute
		* @exception AdEmptyException - The attribute  attr_name had been already set   */
		virtual void  setAttribute (const std::string& attr_name, bool attr_value)   ;
		/**
		* Add The specified Integer Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The value of the attribute to be added
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute
		* @exception AdEmptyException - The attribute  attr_name had been already set   */
		virtual void  setAttribute (const std::string& attr_name, Ad* attr_value) ;
		/**
		* Add The specified Expression Attribute to the jdl istance
		* @param  attr_name - The Name of the attribute to be added
		* @param  attr_value - The value of the attribute to be added
		* @exception AdSyntaxException - Syntax error caught while trying to add the attribute
		* @exception AdEmptyException - The attribute  attr_name had been already set   */
		virtual void  setAttributeExpr (const std::string& attr_name, classad::ExprTree* attr_value) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the string representation of this attribute
		* @exception AdEmptyException - The checked attribute has not been set yet
		* @exception AdMismatchException - The type of retrieved value is not allowed for the specified attribute name   */
		virtual std::string  getAttributeExpr (const std::string& attr_name) 	;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return a vector cantaining the values listed in the specified attribute ,  (1-size vector if the attribute has a single value)
		* @exception AdEmptyException - The checked attribute has not been set yet
		* @exception AdMismatchException - The type of retrieved value is not allowed for the specified attribute name   */
		std::vector<int> getIntValue(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute  to be retrieved
		* @return a vector cantaining the values listed in the specified attribute ,  (1-size vector if the attribute has a single value)
		* @exception AdEmptyException - The checked attribute has not been set yet
		* @exception AdMismatchException - The type of retrieved value is not allowed for the specified attribute name   */
		std::vector<double> getDoubleValue(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute  to be retrieved
		* @return a vector cantaining the values listed in the specified attribute ,  (1-size vector if the attribute has a single value)
		* @exception AdEmptyException - The checked attribute has not been set yet
		* @exception AdMismatchException - The type of retrieved value is not allowed for the specified attribute name   */
		std::vector<bool> getBoolValue(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute  to be retrieved
		* @return a vector cantaining the values listed in the specified attribute ,  (1-size vector if the attribute has a single value)
		* @exception AdEmptyException - The checked attribute has not been set yet
		* @exception AdMismatchException - The type of retrieved value is not allowed for the specified attribute name   */
		virtual std::vector<std::string> getStringValue(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute  to be retrieved
		* @return a vector cantaining the a vector of strings  (1-size vector if the attribute has a single value)
		* @exception AdEmptyException - The checked attribute has not been set yet
		* @exception AdMismatchException - The type of retrieved value is not allowed for the specified attribute name   */
		std::vector<std::vector<std::string> > getStringList(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		* @param attr_name The name of the attribute name to be retrieved
		* @return the Ad instance for the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The type of retrieved value is not allowed for the specified attribute name   */
		virtual Ad getAd(const std::string& attr_name);
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The value is not a single string   */
		virtual std::string getString(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the  value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The value is not a single int   */
		virtual int getInt(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the  value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The value is not a single double  */
		virtual double getDouble(const std::string& attr_name) ;
		/**
		* Retreive the value of the specified attribute
		*  @param attr_name The name of the attribute name to be retrieved
		* @return the  value of the specified attribute
		* @exception AdEmptyException  The checked attribute has not been set yet
		* @exception AdMismatchException  The value is not a single bool  */
		virtual bool getBool(const std::string& attr_name) ;
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
		//@}
	protected:
		/**
		* Add a value to a list (if already present) or set the first value of this attribute
		*  @param attr_name a string representing the attribute name
		*  @param val   The value of the attribute to be added
		* @exception AdMismatchException  The type of value is not allowed for the specified attribute name
		* @exception AdFormatException The type of value is not allowed for the specified attribute name
		*/
		virtual void addAttribute(std::string attr_name , classad::Value val) ;
		/**
		* Append a value to a list
		*  @param attr_name a string representing the attribute name
		*  @param val -  The value of the attribute to be added
		* @param tree the current value (before appending) of the attribute
		*/
		virtual void appendValue(classad::ExprTree* tree , const classad::Value& val, const std::string& attr_name) ;
		/**
		* Insert a classad Exptression inside the Ad instance
		*  @param attr_name a string representing the attribute name
		*  @param val -  The value of the attribute to be added
		*/
		virtual void insertAttribute(const std::string& attr_name , classad::ExprTree* val);
		/**
		* Insert a classad Exptression inside the Ad instance
		*  @param attr_name a string representing the attribute name
		*  @param val -  The value of the attribute to be added
		*/
		virtual void insertAttribute(const std::string& attr_name , classad::Value val);
		/**
		* Retrieve the Value of the specified attribute
		*  @param attr_name a string representing the attribute name
		*  @return the Value of the attribute inside the Ad instance
		*/
		virtual classad::Value getTypeValue(const std::string& attr_name);
		/**Check whether a value is present inside a classad Expression
		* @param tree the expression to be checked
		* @param attr_value the value to be checked
		* @return true (if the value is present) false otherwise */
		bool hasAttribute( classad::ExprTree* tree ,  const std::string& attr_value);
		/** Collection of all warning messages (if any)*/
		std::vector<std::string> warning_messages_v ;

};
/******************************************************************
 method :   glite_wms_jdl_toLower
return the input string as in lower case
*******************************************************************/
std::string glite_wms_jdl_toLower ( const std::string &src);
} // jdl namespace
} // glite namespace

#endif

//EOF

