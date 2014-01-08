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
*  filename  : JobAd.cpp
*  author    : Alessandro Maraschini <alessandro.maraschini@datamat.it>
*  copyright : (C) 2002 by DATAMAT
***************************************************************************/
//
// $Id: JobAd.cpp,v 1.17.2.8.2.2 2012/01/24 16:04:06 adorigo Exp $
//

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "JobAd.h"
#include "RequestAdExceptions.h"
#include "exception_codes.h"
#include "extractfiles.h"
#include "JDLAttributes.h"
#include "jdl_attributes.h"
// Boost File System
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include "glite/wmsutils/classads/classad_utils.h"
#ifdef HAVE_STRINGSTREAM
#include <sstream>
#else
#include <strstream>
#endif
namespace glite {
namespace jdl {
using namespace classad;
using namespace std ;
using namespace glite::wmsutils::classads ;
namespace utilities = glite::wmsutils::classads ;
#define WIN_SEP "\\"
#define UNIX_SEP "/"
typedef vector< pair< string, ExprTree *> > 	vectorPairStrExpr;
typedef vector<ExprTree*>			vectorExpr;
typedef std::vector<std::string>		vectorStr;


ClassAd* prepost(ClassAd *job ,const string& vo, ExprTree *defaultRank, ExprTree *defaultReq){
	JobAd jad (*job);
	if (defaultRank){jad.setDefaultRank(defaultRank->Copy());}
	if (defaultReq) {jad.setDefaultReq(defaultReq->Copy());}
	if (!jad.hasAttribute(JDL::VIRTUAL_ORGANISATION)) {
		jad.setAttribute(JDL::VIRTUAL_ORGANISATION, vo);
	}
	jad.check(false);
	return jad.ad();
}

/******************************************************************
 methods : Constructors
*******************************************************************/
JobAd::JobAd() {
	reset();
}
//Constuctor From  string
JobAd::JobAd(const string& jdl_string){
	GLITE_STACK_TRY("JobAd::JobAd(const string& jdl_string)") ;
	reset();
	fromString(jdl_string);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
JobAd::JobAd(const classad::ClassAd& classAd){
	fromClassAd(classAd);  //reset made by fromClassAd method
}
JobAd::~JobAd() throw(){
//	if (schema != NULL)  delete schema ;
//	if (extractedAd != NULL)  delete extractedAd ;
}
JobAd::JobAd(const JobAd& jobad){
	GLITE_STACK_TRY("JobAd::JobAd(const JobAd& )") ;
	fromJobAd(jobad);  //reset made by fromJobAd method
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void JobAd::operator=(const JobAd& jobad){
	GLITE_STACK_TRY("JobAd::operator=(const JobAd& jobad)") ;
	fromClassAd(jobad);//reset mada by fromClassAd method
	checking = jobad.checking;
	toBretrieved = jobad.toBretrieved;
	lookInto_b = jobad.lookInto_b ;
	warning_messages_v = jobad.warning_messages_v;
	if (jobad.defaultRank!=NULL){  defaultRank = jobad.defaultRank->Copy() ;}
	else {defaultRank = NULL ;}
	if (jobad.defaultReq!=NULL){ defaultReq = jobad.defaultReq->Copy() ;}
	else {defaultReq = NULL ;}
	if (jobad.schema.get() !=NULL){ schema.reset ( jobad.schema.get() ) ;}
	else{ schema.reset() ;}
	if (jobad.extractedAd.get() !=NULL){ extractedAd.reset ( jobad.extractedAd.get() )  ;}
	else {extractedAd.reset() ;}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void JobAd::fromJobAd(const JobAd& jobad){
	fromClassAd(jobad);//reset made by fromClassAd method
	checking = jobad.checking;
	toBretrieved = jobad.toBretrieved;
	lookInto_b = jobad.lookInto_b ;
	warning_messages_v = jobad.warning_messages_v;
	// DEF rank & Req
	if (jobad.defaultRank!=NULL){  defaultRank = jobad.defaultRank->Copy() ;}
	else {defaultRank = NULL ;}
	if (jobad.defaultReq!=NULL){ defaultReq = jobad.defaultReq->Copy() ;}
	else {defaultReq = NULL ;}
	// Schema
	if (jobad.schema.get() !=NULL){ schema.reset ( jobad.schema.get() ) ;}
	else{ schema.reset() ;}
	// ExtractedAd
	if (jobad.extractedAd.get() !=NULL){ extractedAd.reset ( jobad.extractedAd.get() )  ;}
	else {extractedAd.reset() ;}
}

void JobAd::fromClassAd(const classad::ClassAd& classAd){
	reset();
	vectorPairStrExpr vect ;
	classAd.GetComponents( vect ) ;
	vectorPairStrExpr::iterator it = vect.begin();
	vectorPairStrExpr::iterator const end = vect.end();
	for ( ; it != end; ++it) {
		insertAttribute (  it->first , it->second->Copy()  );
		user.Insert(it->first, it->second->Copy() ) ;
	}
}
/******************************************************************
 method :   toSubmissionString
*******************************************************************/
string JobAd::toSubmissionString(){
	GLITE_STACK_TRY("JobAd::toSubmissionString()") ;
	string       buffer="";
	check( false );
	PrettyPrint  unp;
	//flat the classAd into one single line
	unp.SetClassAdIndentation(0);
	unp.SetClassAdIndentation(0);
	unp.SetListIndentation(0);
	//Unparse the ClassAd instance
	unp.Unparse(buffer, this );
	restore() ;
	return buffer;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

/******************************************************************
 method :   toFile
 Print the jdl in a string format in the specified file
*******************************************************************/
void JobAd::toFile(const string& file_path){
	GLITE_STACK_TRY("JobAd::toFile(const string& file_path)") ;
	string jdl=toLines() ;
	ofstream fout (file_path.c_str());
	fout << jdl ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

/******************************************************************
 methods : setAttribute
 Add A couple attr_name = attr_value to the jdl
 where value-type could be:
 -int
 -double
 -bool
 -string
 -generic ClassAd expression
*******************************************************************/
void JobAd::insertAttribute(const std::string& attr_name ,ExprTree* tree){
	string METHOD ="insertAttribute(const std::string attr_name , ExprTree* val)" ;
	//Empty attribute -> try to fill
	//checkSyntax(attr_name,tree);
	if (!   Insert (attr_name  , tree)     ){
		throw AdSyntaxException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLSYN ,attr_name);
	}
	// fill the attribute in the user's classAd (if necessary)
	if (  jdlist.findCheck(attr_name)   && !checking   ){
		user.Insert (attr_name  , tree->Copy()) ;
	}
}
void JobAd::setLocalAccess(bool lookInto){
	lookInto_b = lookInto?EXISTENCE:WMPROXY;
}
void JobAd::setDefaultRank (const std::string& attr_value ){
	ClassAdParser par ;
	defaultRank =par.ParseExpression(attr_value, true) ;
	if (  defaultRank==NULL)
	throw  AdClassAdException (__FILE__ , __LINE__ ,
		" JobAd::setDefaultRank (const string& attr_value)", WMS_JDLSYN , "ClassAdParser::ParseExpression");
}
void JobAd::setDefaultReq   (const std::string& attr_value ){
	ClassAdParser par ;
	defaultReq = par.ParseExpression(attr_value, true) ;
	if (  defaultReq==NULL)
	throw  AdClassAdException (__FILE__ , __LINE__ ,
		"JobAd::setDefaultReq(const string& attr_value)", WMS_JDLSYN , "ClassAdParser::ParseExpression");
}

void JobAd::setDefaultRank (classad::ExprTree *attr_value ){
	if (attr_value!=NULL){ defaultRank=attr_value->Copy();}
	else{ throw  AdClassAdException (__FILE__ , __LINE__ ,
		" JobAd::setDefaultRank (const string& attr_value)", WMS_JDLSYN , "Empty Expression");
	}
}
void JobAd::setDefaultReq   (classad::ExprTree *attr_value ){
	if (attr_value!=NULL){ defaultReq=attr_value->Copy();}
	else{ throw  AdClassAdException (__FILE__ , __LINE__ ,
		" JobAd::setDefaultReq (const string& attr_value)", WMS_JDLSYN , "Empty Expression");
	}
}

void JobAd::setAllowedProtocols (const std::vector<std::string>&  attr_value ) {
	allowed_protocols = attr_value;
}

const std::vector<std::string> JobAd::getAllowedProtocols (){
	return allowed_protocols;
}

void  JobAd::setAttributeExpr (const std::string& attr_name, ExprTree* attr_value){
	GLITE_STACK_TRY("JobAd::setAttributeExpr (const string& attr_name, const string& attr_value)") ;
	if (  hasAttribute(attr_name)   ) throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLFULL ,attr_name);
	insertAttribute (attr_name, attr_value) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void JobAd::setAttributeExpr (const string& attr_name, const string& attr_value) {
	GLITE_STACK_TRY("JobAd::setAttributeExpr (const string& attr_name, const string& attr_value)") ;
	if (  hasAttribute(attr_name)   ){
		throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLFULL ,attr_name);
	}
	jdlist.checkExpr (attr_name , attr_value) ;
	Ad::setAttributeExpr (attr_name, attr_value) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/******************************************************************
 methods :   is<type>value
 Retreive the value of an attribute
 where <type> could be:
 -int
 -double
 -bool
 -string
*******************************************************************/
Ad JobAd::getAd(const std::string& attr_name) {
	GLITE_STACK_TRY("JobAd::getAd(const std::string& attr_name)");
	JdlAttributeList jdlist ;
	if(jdlist.findList(attr_name)){
		throw  AdListException (__FILE__,__LINE__,METHOD,EPERM,attr_name);
	}
	return Ad::getAd(attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
 std::string JobAd::getString(const std::string& attr_name) {
	GLITE_STACK_TRY("JobAd::getString(const std::string& attr_name)");
	JdlAttributeList jdlist ;
	if (   jdlist.findList(attr_name)   ){
		throw  AdListException (__FILE__,__LINE__,METHOD,EPERM,attr_name);
	}
	return Ad::getString(attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
 }
 int JobAd::getInt(const std::string& attr_name) {
	GLITE_STACK_TRY("JobAd::getInt(const std::string& attr_name)");
	JdlAttributeList jdlist ;
	if (   jdlist.findList(attr_name)   ){
		throw  AdListException (__FILE__,__LINE__,METHOD,EPERM,attr_name);
	}
	return Ad::getInt(attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
 }
 double JobAd::getDouble(const std::string& attr_name) {
	GLITE_STACK_TRY("JobAd::getDouble(const std::string& attr_name)");
	JdlAttributeList jdlist ;
	if (   jdlist.findList(attr_name)   ){
		throw  AdListException (__FILE__,__LINE__,METHOD,EPERM,attr_name);
	}
	return Ad::getDouble(attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
 }
 bool JobAd::getBool(const std::string& attr_name) {
	GLITE_STACK_TRY("JobAd::getBool(const std::string& attr_name)");
	JdlAttributeList jdlist ;
	if(jdlist.findList(attr_name)){
		throw  AdListException (__FILE__,__LINE__,METHOD,EPERM,attr_name);
	}
	return Ad::getBool(attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	 }

ExtractedAd* JobAd::getExtractedAd(){
	if (extractedAd.get()==NULL){
		check();
	}
	ExtractedAd *result = new ExtractedAd();
	ExtractedAd::ExtractedAdCopy ( *( extractedAd.get() ), result );
	return result;
 }
/******************************************************************
 method :   delAttribute
*******************************************************************/
classad::ExprTree* JobAd::delAttribute(const string& attr_name) {
	GLITE_STACK_TRY("JobAd::delAttribute(const string& attr_name)");
	user.Delete(attr_name);
	//Call superclass method
	return Ad::delAttribute(attr_name) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/******************************************************************
 PUBLIC method :  check
 Check the jobAd syntax and semantics built classAd. Don' t restore the attributes
*******************************************************************/
void JobAd::check(const bool &rest ){
	GLITE_STACK_TRY("JobAd::check()") ;
	checking = true ;  //Set the checking tag to true
	warning_messages_v.resize(0);
	//Check for semantic Error in classAd
	checkSemantic();
	checkSpecials() ;
        /////////////////////////////////////////////////////////////////////////////////////////////
        boost::array<std::string,3> attrs = { {JDL::WHOLENODES,JDL::SMPGRANULARITY,JDL::HOSTNUMBER} };
        void (JobAd::*fn)(const string&,ExprTree*) = &JobAd::checkSyntax;
        std::for_each( attrs.begin(),attrs.end(), 
          boost::bind(fn,this,_1,boost::bind(&JobAd::lookUp,this,_1) )
        );
        /////////////////////////////////////////////////////////////////////////////////////////////
	checking = false ;
	if (rest) restore() ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/******************************************************************
 PRIVATE methods :  checkSyntax
 Check the jobAd syntax
******************************************************************/
/**
* checkSyntax(const string attr_name , Value val)
* This method is used by checkSyntax( const string attr_name ,   ExprTree  *attr_expr )*/
void JobAd::checkSyntax(const string& attr_name, Value val){
	GLITE_STACK_TRY("JobAd::checkSyntax(const string& attr_name , const Value attr_value)");
	//Check the Value to the ClassAd
	switch ( val.GetType() ){
	case Value::BOOLEAN_VALUE :{
		bool b ;
		if (val.IsBooleanValue( b )  )    jdlist.checkBool (attr_name , b) ;
		else throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
		}
		break;
	case Value::INTEGER_VALUE:{
		int i;
		if (val.IsIntegerValue( i )  )     jdlist.checkInt (attr_name , i) ;
		else throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
		}
		break;
	case Value::REAL_VALUE:{
		double d ;
		if (val.IsRealValue( d )  )       jdlist.checkDouble (attr_name , d) ;
		else throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
		}
		break;
	case Value::STRING_VALUE:{
		string s ;
		if ( val.IsStringValue( s )  )      jdlist.checkString ( attr_name , s) ;
		else throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
		}
		break;
	case Value::CLASSAD_VALUE:{
		ClassAd* ad  ;
		if (val.IsClassAdValue( ad )  )  jdlist.checkAd (attr_name , ad) ;
		else throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
		}
		break;
	case Value::UNDEFINED_VALUE:{
		// Is an expression
	}
	default:
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

/******************************************************************
 Check the jobAd syntax
*******************************************************************/
void JobAd::checkSyntax( const string& attr_name ,   ExprTree  *attr_expr ) {

        if (!attr_expr) return; 

	GLITE_STACK_TRY("JobAd::checkSyntax(const string& attr_name ,   ExprTree  *attr_expr)");
	Value              val ;
	if (jdlist.findAttribute(attr_name)){
		// The Attribute is known: check needed
		//Converts the expression to a Value
		if (!EvaluateExpr(attr_expr, val )){
			throw AdClassAdException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH,
				"ClassAd::EvaluateExpr" , attr_name );
		}
		switch (val.GetType()){
			case Value::LIST_VALUE:{
				if (   !jdlist.findList(attr_name)   ){
					throw AdListException (__FILE__ , __LINE__ ,METHOD,  WMS_JDLSYN,attr_name );
				}
				const ExprList    *el;
				vectorExpr vectList ;
				val.IsListValue(el) ;
				el->GetComponents(vectList) ;
				vectorExpr::iterator it = vectList.begin();
				vectorExpr::iterator const end = vectList.end();
				for ( ; it != end; ++it) {
					EvaluateExpr(*it,val);
					if (val.GetType() == Value::CLASSAD_VALUE){
						jdlist.checkAd (attr_name,(ClassAd*)(*it));
					}else {checkSyntax(attr_name,val);}
				}
			}
			break;
			case  Value::STRING_VALUE:
			case  Value::BOOLEAN_VALUE:
			case  Value::INTEGER_VALUE:
			case  Value::REAL_VALUE:
				checkSyntax(attr_name, val) ;
				break;
			case  Value::CLASSAD_VALUE:
				jdlist.checkAd (attr_name, (ClassAd*) attr_expr);
				break ;
			default:
				jdlist.checkExpr(attr_name,attr_name);
				break ;
		}  // END switch
	} // END findAttribute
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

/******************************************************************
 PRIVATE method :  checkSemantic, checkSpecials
 Check the jobAd semantic attribute expressions
*******************************************************************/
void JobAd::checkSpecials(){
	GLITE_STACK_TRY("JobAd::checkSpecials()");
	/**
	*    JDL::VIRTUAL_ORGANISATION  attribute check
	*/
	if (!hasAttribute(JDL::VIRTUAL_ORGANISATION)){
		throw AdSemanticMandatoryException (__FILE__ , __LINE__ ,METHOD , WMS_JDLMANDATORY ,JDL::VIRTUAL_ORGANISATION);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

//Check the Semantic of a classAd
void JobAd::checkSemantic() {
	//This Method check the co-existance of the attributes in classAd
	GLITE_STACK_TRY("JobAd::checkSemantic()");
	// JdlAttributeList jdlist ;
	bool stdinput_tofind = true ;
	bool exec_tofind = true ;
	bool prologue_tofind = true ;
	bool epilogue_tofind = true ;
	bool parametric= hasAttribute(JDL::JOBTYPE, JDL_JOBTYPE_PARAMETRIC);
	// Initialise default Schema (if null)
	//if (schema==NULL)   schema = JobAdSchema::glueSchema () ;
	if ( schema.get() == NULL ) schema.reset( JobAdSchema::glueSchema() ) ;
	//extractedAd= new ExtractedAd() ;
	extractedAd.reset (new ExtractedAd ( ) ) ;
	if (hasAttribute(JDL::JOBID)){
		extractedAd -> setJobId(getString(JDL::JOBID));
	}
	if (hasAttribute(JDL::NODE_NAME)){
		extractedAd -> setNodeName(getString(JDL::NODE_NAME));
	}
	// This variable stores the value of extracted inputsandbox files:
	vector<string> extracted   ;
	/**
	*     TYPE attribute check
	*/
	if (hasAttribute(JDL::TYPE) ){
		const string type = getString(JDL::TYPE);
		Delete (JDL::TYPE);
		setAttribute (JDL::TYPE ,  glite_wms_jdl_toLower(type));
		if (!  ( glite_wms_jdl_toLower( type )== JDL_TYPE_JOB) )
			throw AdSyntaxException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLSYN ,  JDL::TYPE );
	}else {setAttribute ( JDL::TYPE , (string)JDL_TYPE_JOB  );}
	/**
	* Check Rank And Requirements
	*/
	checkRankReq() ;
	/**
	*    JDL::INPUTSB  attribute check
	*/
	if ( hasAttribute(JDL::INPUTSB) ){
		if (!parametric){  // PARAMETRIC CONDITIONAL CHECK
			checkInputSandbox (  extracted )  ;
		}
	}
	// On server Side check ISB_DEST_FILENAME value
	if (lookInto_b==WMPROXY){
		namespace fs = boost::filesystem;
		if(hasAttribute(JDL::ISB_DEST_FILENAME)){
			// Attribute present: check the cardinality
			if (extracted.size()!=  getStringValue(JDL::ISB_DEST_FILENAME).size()){
				throw  AdSemanticGroupException (__FILE__ , __LINE__ ,METHOD, WMS_JDLGROUP,
				JDL::INPUTSB+" and "+JDL::ISB_DEST_FILENAME +" cardinalities are different");
			}
		}else{
			// attribute not present: make a list of ISB leaves:
			vectorStr::iterator it = extracted.begin();
			vectorStr::iterator const end = extracted.end();
			for ( ; it != end; ++it) {
				addAttribute(JDL::ISB_DEST_FILENAME, fs::path(*it, fs::native).leaf());  // upgrade to boost 1.32
			}
		}
	}
	/**
	*    JDL::HLR_LOCATION attribute check
	*/
	if ( hasAttribute(JDL::HLR_LOCATION) ){
		string hlr = string (JDL_HLR_LOCATION_ENV ) + "=" +  getString (JDL::HLR_LOCATION) ;
		// Append only if not yet present (Multiple tide check might repeat)
		if (!hasAttribute(JDL::ENVIRONMENT,hlr)){
			addAttribute (JDL::ENVIRONMENT,hlr);
		}
	}
	/**
	*     JDL::EXECUTABLE attribute check
	*/
	if (hasAttribute(JDL::EXECUTABLE) ){
		const string exec = getString(JDL::EXECUTABLE);
		if(isAbsolutePath(exec,false)){
			// Absolute path is not to be checked:file available on remote file system
  			exec_tofind= false;
		}else{
#ifdef WIN		// Windows Check
			if(exec.find(WIN_SEP )!=string::npos)
#else   		// Linux-Unix Check
			if(exec.find(UNIX_SEP)!=string::npos)
#endif
			{
				// It's a relative path: error
				throw AdSemanticPathException (__FILE__ , __LINE__ ,METHOD,
					WMS_JDLMANDATORY, JDL::EXECUTABLE, exec);
				throw AdFormatException (__FILE__ , __LINE__ ,METHOD,
						WMS_JDLMISMATCH,JDL::EXECUTABLE,"<absolute path>||<simple path>");
			}
		}
		if(  (exec_tofind)&&(!jdlist.findTail(exec,extracted))  ){
   			if (lookInto_b != EXISTENCE){  // In EXISTENCE mode some attributes can be still a classad reference
			if (!parametric){  // PARAMETRIC CONDITIONAL CHECK
				// not found the executable inside the inputsandbox: ERROR
				throw AdSemanticPathException (__FILE__ , __LINE__ ,METHOD,
					WMS_JDLMANDATORY, JDL::EXECUTABLE +" (inside " +JDL::INPUTSB+")", exec);
			}
			}
		}
	} else{
		// Mandator Executable attribute not found
		throw AdSemanticMandatoryException (__FILE__,__LINE__,METHOD,
			WMS_JDLMANDATORY ,JDL::EXECUTABLE );
	}
	/**
	*   JDL::STDINPUT   attribute check
	*/
	if ( hasAttribute(JDL::STDINPUT) ){
		const string  stdInput=getString(JDL::STDINPUT);
		// stinput has to be found when the path is not absolute:
		stdinput_tofind=!isAbsolutePath(stdInput,false);
		if((stdinput_tofind)&&(!jdlist.findTail(stdInput,extracted))){
			if (lookInto_b != EXISTENCE){   // In EXISTENCE mode some attributes can be still a classad reference
			if (!parametric){  // PARAMETRIC CONDITIONAL CHECK
				throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
					WMS_JDLMANDATORY,JDL::STDINPUT+" (inside " +JDL::INPUTSB+")", stdInput);
			}
			}
		}
	}
	/**
	*   JDL::PROLOGUE/EPILOGUE attribute check
	*/
	if ( hasAttribute(JDL::PROLOGUE) ){
		const string  proLogue=getString(JDL::PROLOGUE);
		// prologue has to be found when the path is not absolute:
		prologue_tofind=!isAbsolutePath(proLogue,false);
		if((prologue_tofind)&&(!jdlist.findTail(proLogue,extracted))){
			if (lookInto_b != EXISTENCE){   // In EXISTENCE mode some attributes can be still a classad reference
			if (!parametric){  // PARAMETRIC CONDITIONAL CHECK
				throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
					WMS_JDLMANDATORY,JDL::PROLOGUE+" (inside " +JDL::INPUTSB+")", proLogue);
			}
			}
		}
	}else if (hasAttribute(JDL::PROLOGUE_ARGUMENTS)){
		throw AdSemanticGroupException (__FILE__,__LINE__,METHOD,
			WMS_JDLMANDATORY, JDL::PROLOGUE +", "+JDL::PROLOGUE_ARGUMENTS) ;
	}
	if ( hasAttribute(JDL::EPILOGUE) ){
		const string  epiLogue=getString(JDL::EPILOGUE);
		// epilogue has to be found when the path is not absolute:
		epilogue_tofind=!isAbsolutePath(epiLogue,false);
		if((epilogue_tofind)&&(!jdlist.findTail(epiLogue,extracted))){
			if (lookInto_b != EXISTENCE){   // In EXISTENCE mode some attributes can be still a classad reference
			if (!parametric){  // PARAMETRIC CONDITIONAL CHECK
				throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
					WMS_JDLMANDATORY,JDL::EPILOGUE+" (inside " +JDL::INPUTSB+")", epiLogue);
			}
			}
		}
	}else if (hasAttribute(JDL::EPILOGUE_ARGUMENTS)){
		throw AdSemanticGroupException (__FILE__,__LINE__,METHOD,
			WMS_JDLMANDATORY, JDL::EPILOGUE +", "+JDL::EPILOGUE_ARGUMENTS) ;
	}

	/**
	*   JDL::INPUTDATA, JDL::DATA_REQUIREMENTS , JDL::DATA_ACCESS  attributes check
	*/
	bool id = hasAttribute(JDL::INPUTDATA);
	bool dr = hasAttribute(JDL::DATA_REQUIREMENTS);
	if (id&&dr){
		// InputData & DataRequirements cannot be specified togheter
		throw AdSemanticGroupException (__FILE__ , __LINE__ ,METHOD,WMS_JDLGROUP,
			JDL::INPUTDATA +","+JDL::DATA_REQUIREMENTS);
	}else if (id || dr){
		// Either InputData or Datarequirements specified: therefore DataAccessProtocol is MANDATORY
		if (!hasAttribute(JDL::DATA_ACCESS)){
			string errStr = JDL::INPUTDATA+ "||"+JDL::DATA_REQUIREMENTS+","+JDL::DATA_ACCESS;
				throw AdSemanticGroupException (__FILE__ , __LINE__ ,METHOD,WMS_JDLMANDATORY, errStr );
		}
	}
	/**
	*    STDOUTPUT - STDERROR check:
	* StdOutput & StdError can have the same file name
	* only if the absolute path is the same*/
	if (  hasAttribute(JDL::STDOUTPUT) && hasAttribute(JDL::STDERROR) ){
		string stdOutput = getString(JDL::STDOUTPUT);
		string stdError = getString(JDL::STDERROR);
		if (   getName (stdOutput) == getName (stdError)   ){
			if (stdOutput != stdError){
			string errMsg = JDL::STDOUTPUT +","+JDL::STDERROR+
				": can have the same file name only if the absolute path is the same" ;
			throw AdSemanticGroupException (__FILE__ , __LINE__ ,METHOD,WMS_JDLMANDATORY, errMsg );
			}
		}
	}
	/**
	*    JDL::OUTPUSB attribute check
	*/
	if (  hasAttribute(JDL::OUTPUTSB)){
		vector<string> outputFiles = getStringValue(JDL::OUTPUTSB);
		vector<string> outMap ;  // keep track of simple file names
		vector<string> outDupli;  // keep track of duplicated file names
		vector<string>::iterator it ;
		vector<string>::iterator iter ;
		string outSimple ;
		bool osbHasWildCards = false;
		//Create a list of all outputsandbox files
		for (iter = outputFiles.begin(); iter!=outputFiles.end(); ++iter){
			osbHasWildCards = osbHasWildCards || hasWildCards(*iter);
			outSimple = getName (*iter) ;
			for (it = outMap.begin() ; it!=outMap.end() ; ++it){
				if(*it ==outSimple){
					// Two files have the same name
					outDupli.push_back(outSimple);
					break;
				}
			}
			if (it== outMap.end()){outMap.push_back( outSimple ) ;}
		}
		for (it = outDupli.begin() ; it!=outDupli.end() ; ++it){
			throw AdSemanticPathException (__FILE__ , __LINE__ ,METHOD, WMS_JDLDUPLICATE , JDL::OUTPUTSB, *it );
		}

		if (hasAttribute(JDL::OSB_DEST_URI)){
			if (osbHasWildCards){
				// WildCards inside OSB do not allow OSB_DEST_URI attribute existence
				// Cardinality will be significant only when job is executed
				throw  AdSemanticGroupException (__FILE__ , __LINE__ ,METHOD, WMS_JDLGROUP,
				JDL::OUTPUTSB+" (with WildCards), "+JDL::OSB_DEST_URI);
			}
			if (outputFiles.size()!=getStringValue(JDL::OSB_DEST_URI).size()){
				// Output sandbox cardinalities differ
				throw  AdSemanticGroupException (__FILE__ , __LINE__ ,METHOD, WMS_JDLGROUP,
				JDL::OUTPUTSB+" and "+JDL::OSB_DEST_URI +" cardinalities are different");
			}
		}


	}
	/**
	*    JDL::JOBTYPE attribute check
	*/
	if (!hasAttribute(JDL::JOBTYPE)){ setAttribute(JDL::JOBTYPE,string(JDL_JOBTYPE_NORMAL )); }
        checkJobType( getStringValue(JDL::JOBTYPE ) );
	/**
	*    JDL_DEFAULT_RANK private attribute check
	*/
	if (  hasAttribute(JDL_DEFAULT_RANK)){delAttribute(JDL_DEFAULT_RANK );}
	setAttributeExpr (JDL_DEFAULT_RANK , JDL_RANK_DEFAULT ) ;
	/*
	* DataAccessManagemente check
	*/
	if (hasAttribute(JDL::RANK)){checkDataManagement();}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
} // checkSemantic end

void JobAd::checkMultiAttribute (const vector<string> &multi){
	GLITE_STACK_TRY("JobAd::checkMultiAttribute (const vector<string> &multi )")
	std::string requirements, lowercase ;
	checkRankReq() ;
	for (unsigned int  att = 0 ; att<2 ; att++){
		if ( att==1){requirements =  getAttributeExpr ( JDL::RANK);}
		else {requirements        =  getAttributeExpr ( JDL::REQUIREMENTS);}
		lowercase= glite_wms_jdl_toLower(requirements);
		const int  DIM = 128 ;
		string values [DIM];
		string lists  [DIM];
		int len = requirements.length() ;
		//find Keyword member:
		int position = lowercase.find ("member") ;
		int openPar, comma1, comma2 , closedPar ;
		int i = 0 ;
		while (position < len   && position >=0){
			openPar   = requirements.find ("("  , position) +1;
			while (requirements[openPar] == ' '){openPar++;}
			comma1 = requirements.find (","  , position) - 1 ;
			comma2 =comma1+2 ;
			while (requirements[comma1] == ' '){comma1-- ;}
			while (requirements[comma2] == ' '){comma2++ ;}
			closedPar = requirements.find (")"  , position) -1 ;
			while (requirements[closedPar] == ' '){closedPar--;}
			//check Consistency:
			if (  openPar < len && closedPar < len  && comma1 < len && openPar<comma1 && comma2 < closedPar ){
				values[i] = requirements.substr (openPar , comma1 - openPar +1 )   ;
				lists[i]  = requirements.substr (comma2 , closedPar - comma2 +1)   ;
			}
			position = lowercase.find ("member", closedPar ) ;
			i++ ;
			if (i==DIM)
			break ;
		} //end while position...
		string* ip ; //  used to find string
		// vector<string>::const_iterator it  = multi.begin() ;
		for  (vector<string>::const_iterator it = multi.begin();it!=multi.end();it++){
			if (  (int)requirements.find ("other."+*it)>=0  && (int) requirements.find ("other."+*it)<len   ){
				//The Attribute cannot be present in the values
				ip = std::find(  values, values + DIM , "other."+*it );
				if  (ip != values + DIM){ // found
					throw AdSyntaxException (__FILE__ , __LINE__ ,METHOD,  WMS_JDL_MEMBER  ,*it);
				}
				//The Attribute must be present in the lists
				ip = std::find(  lists, lists + DIM , "other."+*it );
				if  (ip == lists + DIM) {  //not found
					throw AdSyntaxException (__FILE__ , __LINE__ ,METHOD,  WMS_JDL_MEMBER  ,*it);
				}
			} // end if
		} // end for (const iterator )
	} // end for (int i )
	// Restore user value for Rank and requirements attributes
	restore() ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/******************************************************************
 PRIVATE methods :checkDataManagement
 Check the Rank attribute, if contains DataAccessCost then
 1) InputDAta, DataAccessProtocol Are mandatory
 2) it is the one value
*******************************************************************/
void JobAd::checkDataManagement( ){
	GLITE_STACK_TRY("JobAd::checkDataManagement (  )");
	vectorStr attrs;
	utilities::insertAttributeInVector(&attrs, Lookup(JDL::RANK) , utilities::is_reference_to("other"));
	string dac = string (JDL_RANK_DATA_ACC_COST);
	vectorStr::iterator it = attrs.begin();
	vectorStr::iterator const end = attrs.end();
	for ( ; it != end; ++it) {
		if ( glite_wms_jdl_toLower(*it) == glite_wms_jdl_toLower(dac) ){
			// DataAccessCost found
			if ((!hasAttribute( JDL::INPUTDATA))||(!hasAttribute(JDL::DATA_ACCESS))){
				throw AdSemanticGroupException(__FILE__,__LINE__,METHOD,
				WMS_JDLGROUP, "DataAccessCost rank, InputData, DataAccessProtocol") ;
			} else if ( attrs.size() >1 ){
				throw AdSemanticGroupException(__FILE__ , __LINE__ ,METHOD,
				WMS_JDLGROUP ,"DataAccessCost rank not alone") ;
			} else break;
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void JobAd::checkRankReq () {
	GLITE_STACK_TRY("JobAd::checkRankReq(  )");
	/**
	*    JDL::REQUIREMENTS,
	*/
	if (!  hasAttribute(JDL::REQUIREMENTS)  ){
		if ( defaultReq== NULL){
			throw AdSemanticMandatoryException (__FILE__,__LINE__,METHOD,
				WMS_JDLMANDATORY,JDL::REQUIREMENTS);
		} else {
			insertAttribute ( JDL::REQUIREMENTS, defaultReq->Copy() ) ;
		}
	} else if ( defaultReq != NULL){
		// JobAd already contains REQUIREMENTS: append default value (if present)
		PrettyPrint  unp;
		unp.SetClassAdIndentation(0) ;
		unp.SetListIndentation(0) ;
		string buffer ;
		unp.Unparse( buffer, Lookup ( JDL::REQUIREMENTS )  );
		if ( !(defaultReq -> SameAs ( Lookup (JDL::REQUIREMENTS)))) {
			buffer = "(" + buffer +") && (" ;
			unp.Unparse( buffer, defaultReq ) ;
			buffer+=")" ;
		}
		Delete (JDL::REQUIREMENTS ) ;
		setAttributeExpr ( JDL::REQUIREMENTS, buffer) ;
	}
	/*
	* JDL::RANK attribute check
	*/
	if (!  hasAttribute(JDL::RANK)  ){
		if (defaultRank == NULL){
			throw AdSemanticMandatoryException (__FILE__ , __LINE__ ,METHOD , WMS_JDLMANDATORY ,JDL::RANK);
		}else{
			insertAttribute (JDL::RANK, defaultRank->Copy());
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/******************************************************************
 PRIVATE methods :checkInputSandbox
Check The inputSandbox attribute and extract the absolute file names
*******************************************************************/
void JobAd::checkInputSandbox(std::vector<std::string>& extracted){

  std::vector<std::string>::const_iterator it = extracted.begin();
//   for( ; it != extracted.end( ); ++it )
//     cout << "JobAd::checkISB: " << *it << endl;
  
  GLITE_STACK_TRY("JobAd::checkInputSandbox(std::vector<std::string>& extracted)")
    // This Vector will replace the old InputSanbox with the extracted values
    vector<ExprTree*> isVect ;
  // This vector contains all ISB string values
  vector<string> inputFiles=getStringValue(JDL::INPUTSB);
  // Old files have to be replaced
  vector<string>::iterator it ;
  const string isbURI=   (hasAttribute(JDL::ISB_BASE_URI))   ?(getString(JDL::ISB_BASE_URI)   ):"";
  const string wmpURI=   (hasAttribute(JDL::WMPISB_BASE_URI))?(getString(JDL::WMPISB_BASE_URI)):"";
  //Create a list of all inputsandbox files
  toBretrieved =false;
  for (it = inputFiles.begin() ; it!=inputFiles.end() ; ++it){
    toBretrieved=extractFiles (JDL::INPUTSB,*it,extracted,lookInto_b,wmpURI,isbURI,extractedAd.get())||toBretrieved;
  }
  //Update InputSandbox with new files:
  vector<string>::iterator iter ;
  // put the extracted files back into the InputSandbox attribute
  Value  val ;
  for (iter = extracted.begin(); iter!=extracted.end(); iter++){
    val.SetStringValue( *iter) ;
    isVect.push_back( Literal::MakeLiteral( val ) ) ;
  }
  delAttribute( JDL::INPUTSB  );
  insertAttribute ( JDL::INPUTSB ,(ExprTree*) ExprList::MakeExprList( isVect  ) ) ;
  GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
  
//   for( it = extracted.begin(); it != extracted.end( ); ++it ) {
    
//     cout << "JobAd::checkISB: " << *it << endl;

  
}
/******************************************************************
 PRIVATE methods :  checkJobType
 check the type of the job and update several involved attributes such as Rank, Rbequirements, Environment...
*******************************************************************/
void JobAd::checkJobType(const vector<string>& attr_value) {
GLITE_STACK_TRY("JobAd::checkJobType( const vector<string>& attr_value   )");
	// If this point is reached JobType attribute IS definitely SET
	// DELETING previous JobType
	Delete (JDL::JOBTYPE);
	string requirements = "" ;
	string rank = "" ;
	string buffer = "" ;
	bool makeList = attr_value.size() >1 ;
	vectorStr::const_iterator it = attr_value.begin();
	vectorStr::const_iterator const end = attr_value.end();
	for ( ; it != end; ++it) {
		buffer = glite_wms_jdl_toLower(*it);
		if ((buffer !=JDL_JOBTYPE_MPICH)
		&&  (buffer !=JDL_JOBTYPE_NORMAL)
		&&  (buffer !=JDL_JOBTYPE_PARTITIONABLE)
		&&  (buffer !=JDL_JOBTYPE_PARAMETRIC)
		&&  (buffer !=JDL_JOBTYPE_CHECKPOINTABLE)
		&&  (buffer !=JDL_JOBTYPE_INTERACTIVE)    ){
			throw AdFormatException (__FILE__,__LINE__,METHOD,
			WMS_JDLMISMATCH,JDL::JOBTYPE,"MpiCh | Normal | Parametric | Interactive") ;
		}
		if (makeList){addAttribute (JDL::JOBTYPE, glite_wms_jdl_toLower(*it));}
		else         {setAttribute (JDL::JOBTYPE, glite_wms_jdl_toLower(*it));}
	}
	/* Initial checks:
	- NodeNumber ->Mpi
	- ShPort -> interacive
	- JobSteps-> checkponintable
	- Parametric & Partitionable are exclusive
	*/
	if (hasAttribute(JDL::SHPORT) && !hasAttribute ( JDL::JOBTYPE, JDL_JOBTYPE_INTERACTIVE ) ){
		throw AdSemanticGroupException(__FILE__,__LINE__,
			METHOD,WMS_JDLMANDATORY,"ListenerPort, INTERACTIVE jobs") ;
	}
	if (hasAttribute(JDL::JOBTYPE, JDL_JOBTYPE_PARAMETRIC) &&
		hasAttribute(JDL::JOBTYPE, JDL_JOBTYPE_PARTITIONABLE)){
		throw AdSemanticGroupException(__FILE__,__LINE__,
				METHOD,WMS_JDLGROUP,"JobType PARAMETRIC & PARTITIONABLE");
	}
        //
        //  Handling of CPUNumber / NodeNumber
        //
        bool exists_CPUNumber = hasAttribute(JDL::CPUNUMBER);
 
        if ( exists_CPUNumber || hasAttribute(JDL::NODENUMB) ) {
 
          std::string NodeNum;

          if (exists_CPUNumber) {
            NodeNum = boost::lexical_cast<std::string>(getInt(JDL::CPUNUMBER));
          }
          else { 
            // Deprecated attribute NodeNumber is still accepted
            NodeNum = boost::lexical_cast<std::string>(getInt(JDL::NODENUMB));
              addWarning(JDL::NODENUMB
                + " attribute is going to be deprecated very soon. Use "
                + JDL::CPUNUMBER +" instead"
              );
          }
              
          // Modify Requirements:
          std::string const buffer(
            "( " + getAttributeExpr (JDL::REQUIREMENTS) + " )" 
            + " && " + schema->get( JobAdSchema::SCHEMA_TCPU ) + " >= " + NodeNum
          );
          Delete ( JDL::REQUIREMENTS);
          setAttributeExpr (JDL::REQUIREMENTS , buffer) ;
          // Rank attribute value: if not present initialise:
          if (!hasAttribute (JDL::RANK) ){
            setAttributeExpr(JDL::RANK , schema->get( JobAdSchema::SCHEMA_FCPU )  ) ;
          }
	}
        // Checking use of SMPGRANULARITY and HOSTNUMBER 
        // which should be mutually exclusive when WholeNodes==false
        if ( (!hasAttribute(JDL::WHOLENODES) || 
               !getBool(JDL::WHOLENODES) ) && 
             hasAttribute(JDL::SMPGRANULARITY) && 
             hasAttribute(JDL::HOSTNUMBER)) {
          throw AdSemanticGroupException(__FILE__,__LINE__, METHOD,WMS_JDLGROUP,
           JDL::SMPGRANULARITY + " and " + JDL::HOSTNUMBER + 
           " are mutually exclusive when WholeNodes allocation is not requested"
          );

	}
        // Handling SMPGranularity
        if (hasAttribute(JDL::SMPGRANULARITY)) {
          std::string const buffer(
            "( " + getAttributeExpr (JDL::REQUIREMENTS) + " )"
            + " && other.GlueHostArchitectureSMPSize >= " + JDL::SMPGRANULARITY
          );
          Delete ( JDL::REQUIREMENTS);
          setAttributeExpr (JDL::REQUIREMENTS , buffer);
        }
        else
        if (hasAttribute(JDL::HOSTNUMBER) && 
            hasAttribute(JDL::CPUNUMBER) && 
            (!hasAttribute(JDL::WHOLENODES) || !getBool(JDL::WHOLENODES))) {
         // Adding other.GlueHostArchitectureSMPSize >=
         // CPUNumber % HostNumber ? 1 + CPUNumber / > HostNumber : CPUNumber / HostNumber ;  
         // to the requirements expression required for use case 2.2 MPIWG
          std::string const buffer(
            "( " + getAttributeExpr (JDL::REQUIREMENTS) + " )"
            + " && other.GlueHostArchitectureSMPSize >= ((" 
            + JDL::CPUNUMBER + " % " + JDL::HOSTNUMBER + " > 0) ? ("
            + " 1 + " + JDL::CPUNUMBER + " / " + JDL::HOSTNUMBER 
            + ") : (" + JDL::CPUNUMBER + " / " + JDL::HOSTNUMBER + "))"
          );
          Delete ( JDL::REQUIREMENTS);
          setAttributeExpr (JDL::REQUIREMENTS , buffer);
        } 
	/**
	*                        INTERACTIVE  Jobs
	*/
	if (hasAttribute(JDL::JOBTYPE, JDL_JOBTYPE_INTERACTIVE)){
		// Update Requirements attribute:
		requirements = getAttributeExpr (JDL::REQUIREMENTS) + " && " + schema->get( JobAdSchema::SCHEMA_OIP );
		Delete(JDL::REQUIREMENTS);
		setAttributeExpr(JDL::REQUIREMENTS , requirements);
	}
	/**
	*                        CHKPT Jobs
	*/
	if (  hasAttribute ( JDL::JOBTYPE, JDL_JOBTYPE_CHECKPOINTABLE ) ){
		// CHECKPOINTABLE JOBS DEPRECATED!!!
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH ,
			JDL::JOBTYPE, "Checkpointable jobs have been deprecated!" );
		// if (!hasAttribute(JDL::CHKPT_CURRENTSTEP)){setAttribute(JDL::CHKPT_CURRENTSTEP,0);}
	}
	/**
	*                        PARTITIONABLE Jobs
	*/
	if (  hasAttribute ( JDL::JOBTYPE, JDL_JOBTYPE_PARTITIONABLE) ){
		// PARTITIONABLE JOBS DEPRECATED!!!
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH ,
			JDL::JOBTYPE, "Partitionable jobs have been deprecated!" );
	}
	GLITE_STACK_JDL_CATCH_ALL() ;   //Exiting from method: remove line from stack trace
}


/******************************************************************
 PRIVATE method :   restore ()
  restore values inserted by the user which could have been changed by previous
  check() method callls
  reset() clear  JobAd and reset all its values to initialisation
*******************************************************************/
void JobAd::reset(){
	clear();  // delete all inserted attributes
	checking = false ;
	toBretrieved=false;
	lookInto_b = EXISTENCE;
	defaultReq= NULL ;
	defaultRank = NULL ;
	schema.reset() ;
	extractedAd.reset() ;
	warning_messages_v.resize(0);
}
void JobAd::restore(){
	for (unsigned int i = 0 ; i< jdlist.checkAttrs.size() ; i++ ) {
		string attr_name =  jdlist.checkAttrs[i] ;
		ExprTree* tree = user.Lookup (  attr_name  );
		if (tree != NULL){
				string buffer = "";
				PrettyPrint  unp;
				//flat the classAd into one single line
				unp.SetClassAdIndentation(0);
				unp.SetClassAdIndentation(0);
				unp.SetListIndentation(0);
				//Unparse the ClassAd instance
				unp.Unparse(buffer, this );
				// the user has set this attribute, restoring the previous value
				Delete(   attr_name    ) ;
				insertAttribute (attr_name , tree->Copy()) ;
		}
	}
	// Special Attributes could have been created by check():
	string specials []= {string (JDL_DEFAULT_RANK), JDL::ENVIRONMENT, JDL::TYPE, JDL::JOBTYPE,
		JDL::RANK, JDL::REQUIREMENTS};
	// This variable is used because   sizeof &specials does not seem to work properly
	unsigned int SIZEOF_SPECIALS = 6;
	for (unsigned int i = 0 ; i < SIZEOF_SPECIALS ; i++ ){
		if (  user.Lookup ( specials[i]   )  == NULL    ){
			// If the attribute is not present in user, then try and delete it (was not initialised by user)
			try { Delete (specials[i] );}
			catch (RequestAdException &exc){/* do nothing*/}
		}
	}
	string buffer = "";
	PrettyPrint  unp;
	//flat the classAd into one single line
	unp.SetClassAdIndentation(0);
	unp.SetClassAdIndentation(0);
	unp.SetListIndentation(0);
	//Unparse the ClassAd instance
	unp.Unparse(buffer, this );
}
/******************
* getName (const std::string &path , bool platform_dependence  )
* return the simple filename of the path
******************/
const std::string JobAd::getName (const std::string &path , bool platform_dependence  )  {
	int unix_sep = path.find_last_of (UNIX_SEP );
	int win_sep = path.find_last_of ( WIN_SEP );
	if ( unix_sep + win_sep == -2) {
		//no sep found, return the simple file
		return path ;
	}
	if (platform_dependence) {
		if (  unix_sep >  win_sep) {return path.substr ( unix_sep) ;}
		else {return path.substr ( win_sep) ;}
	}
#ifndef WIN
	// Linux Unix Check
	return path.substr(unix_sep);
#else
	// Windows Check
	return path.substr(win_sep);
#endif
}

/**
* This method verifies wheter the specified path is absolute or not
* if the optional platform_dependence is set to false then the check doesn't depend on the system operator running
*/
bool JobAd::isAbsolutePath(const string &path , bool platform_dependence ) {
	if ( path.empty() ) { return false;}
	if (path.find("$")==0){return true;}
	// platform un-dependendent check
	if (! platform_dependence) {
		int unix_sep = path.find (UNIX_SEP  );
		int win_sepa = path.find ( WIN_SEP );
		int win_sepb = path.find (":\\" );
		if (unix_sep > (int)path.length() -1) {
			unix_sep = -1 ;
		}
		if (  win_sepa> (int) path.length() -1) {
			win_sepa= -1 ;
		}
		if ( win_sepb> (int)path.length() -1) {
			win_sepb= -1 ;
		}
		if ( unix_sep==0 && win_sepa<0 ) {
			return true ;
		}
		if ( win_sepa==0 && unix_sep <0 ) {
			return true ;
		}
		if ( win_sepb==1 && unix_sep <0 ) {
			return true ;
		}
		// if this poiunt is reached no absolute path found:
		return false;
	}
#ifdef WIN
	// Windows Check
	return ( path.find (WIN_SEP)==1 || path.find ("\\")==0);
#else
	// Linux Unix Check
	return (    path.find ( UNIX_SEP ) == 0   ) ;
#endif
	return false;
}
} // jdl namespace
} // glite namespace
