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
*  filename  : Ad.cpp
*  author    : Alessandro Maraschini <alessandro.maraschini@datamat.it>
*  copyright : (C) 2002 by DATAMAT
***************************************************************************/
//
// $Id: Ad.cpp,v 1.7.2.1.6.4 2012/03/07 10:14:28 adorigo Exp $
//
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRINGSTREAM
#include <sstream>
#else
#include <strstream>
#endif
#include <ctype.h>

#include "glite/wmsutils/classads/classad_utils.h"
#include "Ad.h"
#include "exception_codes.h"
#include "RequestAdExceptions.h"
#include "grammar.h"
#include "JDLAttributes.h"

//#include <boost/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
namespace glite {
namespace jdl {

using namespace classad;
using namespace std ;
using namespace glite::wmsutils::classads ;
using namespace glite::wmsutils::exception ;

typedef vector< pair< string, ExprTree *> > 	vectorPairStrExpr;
typedef vector<ExprTree*>			vectorExpr;
typedef std::vector<std::string>		vectorStr;

std::string glite_wms_jdl_toLower ( const std::string &src) {
	std::string result(src);
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}
Ad::Ad(){}
Ad::~Ad()throw(){  }
Ad::Ad(const string& jdl){ fromString (jdl);}
Ad::Ad(const classad::ClassAd& classAd ):classad::ClassAd(classAd){}
Ad::Ad(const Ad& ad) {
	clear();
	vectorPairStrExpr vec ;
	ad.GetComponents(vec ) ;
	vectorPairStrExpr::iterator it = vec.begin();
	vectorPairStrExpr::iterator const end = vec.end();
	for ( ; it != end; ++it) {
		Insert (it->first, it->second->Copy());
	}
}
void Ad::operator=(const Ad& ad){
	clear();
	vectorPairStrExpr vec ;
	ad.GetComponents(vec ) ;
	vectorPairStrExpr::iterator it = vec.begin();
	vectorPairStrExpr::iterator const end = vec.end();
	for ( ; it != end; ++it) {
		Insert (it->first, it->second->Copy());
	}
}
/******************************************************************
 method :   fromFile ( file)
*******************************************************************/
void Ad::fromFile(const string& jdl_file){
	GLITE_STACK_TRY("Ad::fromFile(const string& jdl_file)");
#ifdef HAVE_STRINGSTREAM
	stringstream buffer ;
#else
	strstream buffer;
#endif
	ifstream jdl_in( jdl_file.c_str()  );
	if (!jdl_in.good()){
		throw AdSemanticPathException(__FILE__,__LINE__,METHOD,WMS_JDLMANDATORY,"",jdl_file);
	}
	string result = "", tmpStr ;
	int blank ;
	while ( getline(jdl_in, tmpStr, '\n') ){
		//find the first no-blank character
		blank = 0 ;
		while (tmpStr[blank]==' ') blank++;
		//Check For Commented lines:
		if ( tmpStr[blank] =='#' ){
		//Python Comment: do nothing
		}else if (tmpStr[blank] =='/' && tmpStr[blank+1] =='/'){
		//C/C++ Comment: do nothing
		}else result += " " + tmpStr;
	}
	while(result.length()!=0){
		if(result.substr(0,1)==" "){result=result.substr(1);}
		else  break;
	}
	while(result.find("\t")<result.size()){
		result=result.substr(0,result.find("\t"))+result.substr( result.find("\t")+1);
	}
	fromString( result, jdl_file );
	GLITE_STACK_JDL_CATCH_ALL() ;   //Exiting from method: remove line from stack trace
}
/******************************************************************
 method :   toString ()
*******************************************************************/
string Ad::toString(){
	string       buffer="";
	PrettyPrint  unp;
	//flat the classAd into one single line
	unp.SetClassAdIndentation(0);
	unp.SetListIndentation(0);
	//Unparse the ClassAd instance
	unp.Unparse(buffer, this );
	return buffer;
}
/******************************************************************
 method :   toString ( attr_name )
*******************************************************************/
string Ad::toString( const string& attr_name ){
	ExprTree *tree = Lookup(attr_name) ;
	if (tree==NULL){
		throw AdEmptyException (__FILE__,__LINE__,"toString( const string& attr_name )",
		WMS_JDLEMPTY ,attr_name);
	}
	return toString();
}
/******************************************************************
 method :toLines()
*******************************************************************/
string Ad::toLines(){
	string       buffer="";
	PrettyPrint  unp;
	//Unparse the ClassAd instance
	unp.SetClassAdIndentation(1);
	unp.SetListIndentation(0);
	// create the JobAd string representation
	unp.Unparse(buffer, this );
	return buffer;
}
/******************************************************************
 method :  isSet
Check whether the JobAd has been initialised (true) or not (false)
*******************************************************************/
bool  Ad::isSet(){
	vector < pair < string, ExprTree* > >  vect ;
	GetComponents( vect ) ;
	if (vect.size() >0)  return true ;
	return false ;
}
/******************************************************************
 method :  clear
*******************************************************************/
void Ad::clear(){Clear();};
/******************************************************************
 method : insertAttribute
*******************************************************************/
void Ad::insertAttribute(const std::string& attr_name , ExprTree* val){

  string AttrName = attr_name;
  boost::to_lower( AttrName );
  string jdlenv = JDL::ENVIRONMENT;
  boost::to_lower( jdlenv );
  if(AttrName == jdlenv ) {
    if (val->GetKind() != EXPR_LIST_NODE)
      {
	//classad::ClassAdUnParser unp;
	string buffer = glite::wmsutils::classads::unparse( val );
	classad::ClassAdParser parser;
	ExprTree* tree = parser.ParseExpression( string("{") + buffer + "}");
        cout << "Inserting {" + buffer + "}" << endl;
	insertAttribute( attr_name, tree );
	return;
      }
  }
  

	if (!  Insert (attr_name  , val) ){
		throw AdSyntaxException(__FILE__,__LINE__,
		"insertAttribute(const std::string& attr_name , ExprTree* val)",WMS_JDLSYN ,attr_name);
	}
}
void Ad::insertAttribute(const std::string& attr_name , Value val){
	GLITE_STACK_TRY("Ad::insertAttribute(const std::string& attr_name , Value val)") ;
	insertAttribute (attr_name , (ExprTree*)Literal::MakeLiteral (val) ) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/******************************************************************
 method :   delAttribute/remAttribute
*******************************************************************/
classad::ExprTree* Ad::delAttribute(const string& attr_name) {
	if  (   Lookup(attr_name) ==NULL   ){
		throw AdEmptyException (__FILE__,__LINE__,
			"Ad::delAttribute(const string& attr_name)",WMS_JDLEMPTY ,attr_name);
	}
	// Make a new Copy that will be returned
	ExprTree *result = Lookup (attr_name)->Copy();
	Delete (  attr_name );
	return result ;
}
void Ad::remAttribute(const string& attr_name) {
	delete delAttribute(attr_name);
}
/******************************************************************
method :  hasAttribute
 check if the attribute name is present
*******************************************************************/
bool Ad::hasAttribute(ExprTree* tree,const std::string& attr_value){
	Value val ;
	string str;
	// Parse the attribute
	if (!EvaluateExpr( tree, val ) ){return false;}
	// Check The TYPE
	if ( val.GetType() == Value::CLASSAD_VALUE){
		// The attribute has to be a string or a list of strings
		return false ;
	}else if ( val.GetType() == Value::LIST_VALUE){
			const ExprList    *el;
			vectorExpr vectList ;
			val.IsListValue(el) ;
			el->GetComponents(vectList) ;
			vectorExpr::iterator it = vectList.begin();
			vectorExpr::iterator const end = vectList.end();
			for ( ; it != end; ++it) {
				if (hasAttribute (*it, attr_value) ){return true ;}
			};
			return false ;
	}else if ( val.IsStringValue( str ) ){
		if (glite_wms_jdl_toLower(str)==glite_wms_jdl_toLower(attr_value)) {return true ;}
		else {return false ;}
	}else if (val.GetType() == Value::BOOLEAN_VALUE ||
				val.GetType() == Value::INTEGER_VALUE  ||
				val.GetType() == Value::REAL_VALUE){return false ;
	}else{return false ;}

}
/*******************************************************************
* methods:  Has attribute
*******************************************************************/
bool Ad::hasAttribute( const std::string& attr_name, const std::string& attr_value){
	ExprTree            *tree ;
	tree = Lookup (attr_name);
	if (tree == NULL){return false;}
	else {return hasAttribute (tree , attr_value);}
}
bool Ad::hasAttribute(const string& attr_name){
	ExprTree            *tree ;
	tree = Lookup (attr_name);
	if (tree == NULL)
		return false;
	else
		return true;
}
std::vector<std::string> Ad::attributes(){
	vectorPairStrExpr vect ;
	GetComponents(  vect  ) ;
	vectorStr attributes;
	vectorPairStrExpr::iterator it = vect.begin();
	vectorPairStrExpr::iterator const end = vect.end();
	for ( ; it != end; ++it) {
		attributes.push_back(it->first);
	}
	return attributes ;
}
void Ad::merge (Ad source,bool overwrite){
	std::vector<std::string> attributes = source.attributes();
	string attrName ;
	Ad tbMerged;
	for (unsigned int i = 0 ; i< attributes.size() ; i++ ){
		attrName =attributes[i];
		if( hasAttribute(attrName)){
			// ATTRIBUTE already present
			if (getType(attrName)==TYPE_CLASSAD){
				// ClassAd to be merged
				tbMerged = getAd(attrName) ;
				tbMerged.merge(source.getAd(attrName), overwrite);
				insertAttribute(attrName,tbMerged.Copy());
			}else if (getType(attrName)==TYPE_UNKNOWN){
				// can be an empty list or a non evaluated expr, insert the value
				insertAttribute(attrName,source.delAttribute(attrName)); //Copy needed?
			}else if (overwrite){
				// Insert the attribute only when needed
				insertAttribute(attrName,source.delAttribute(attrName)); //Copy needed?
			}
		}else{
			// Attribute not present: simply set
			insertAttribute(attrName,source.delAttribute(attrName)); //Copy needed?
		}
	}
}


/******************************************************************
 methods : from (stream,string,classad)
*******************************************************************/
void Ad::fromClassAd(const classad::ClassAd& classAd){
	vectorPairStrExpr vect;
	classAd.GetComponents( vect ) ;
	vectorPairStrExpr::iterator it = vect.begin();
	vectorPairStrExpr::iterator const end = vect.end();
	for ( ; it != end; ++it) {
		insertAttribute (it->first, it->second->Copy());
	}
}

  /**
   *
   *
   *
   *
   *
   *
   *
   *
   *
   */
void Ad::fromStream(istream& jdl_in)  {
	GLITE_STACK_TRY("Ad::fromStream(istream& jdl_in)") ;
#ifdef HAVE_STRINGSTREAM
	stringstream buffer ;
#else
	strstream buffer;
#endif
	string result = "", tmpStr ;
	int blank ;
	while (  getline(jdl_in, tmpStr,'\n')  ){
		//find the first no-blank character
		blank = 0 ;
		while ( tmpStr[blank]==' ' ){blank++;}
		//Check For Commented lines:
		if ( tmpStr[blank] =='#' ){
			//Python Comment: do nothing
		}else if ( tmpStr[blank] =='/' && tmpStr[blank+1] =='/' ){
			//C/C++ Comment: do nothing
		}else {result += " " + tmpStr;}
	}
	fromString ( result );
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

  /**
   *
   *
   *
   *
   *
   *
   *
   *
   *
   */
void Ad::fromString(const string& jdl_toParse, string jdl_file ){
	GLITE_STACK_TRY("Ad::fromString(const string& jdl )");
	string jdl = jdl_toParse ;
	// Removing spurious chars (tabs, newlines, extra spaces)
	while(( jdl.find(" ") ==0 )
		|| ( jdl.find("\t") ==0 )
		|| ( jdl.find("\n") ==0 )){
			jdl =jdl.substr(1, jdl.length()-1 ) ;
	}
	// Appending parenthesis, if necessary
	if (!jdl.find("[")==0){jdl="[" +jdl +"]";}
	// Parse the resulting string
	vectorPairStrExpr vect;
	try{

		ClassAd* ad (parse_classad(jdl));
		if(ad==NULL){
			throw AdSyntaxException (__FILE__,__LINE__,"fromString(const string& jdl )",
			WMS_JDLPARSE , "Not a valid ClassAd");
		}
		ad->GetComponents(  vect  ) ;
	}catch(std::exception &exc){
		jdl_parser parser;
		if (jdl_file.empty()){
		parser.parseString ( jdl ) ;
		} else {
		parser.parseFile ( jdl_file ) ;
		}
		// Remap Exception: classad_utils throws a std::exception
		throw AdSyntaxException (__FILE__,__LINE__,"fromString(const string& jdl )",
		WMS_JDLPARSE , string(exc.what()));
	}
	if(vect.size()==0){
		throw AdSyntaxException (__FILE__,__LINE__,"fromString(const string& jdl )",
		WMS_JDLPARSE , "Not a valid ClassAd"  );
	}
	string fxm ="" ;
	vectorPairStrExpr::iterator it = vect.begin();
	vectorPairStrExpr::iterator const end = vect.end();
	for ( ; it != end; ++it) {
		try{
			insertAttribute (it->first, it->second) ;
		}catch (Exception &exc) {
			fxm += (string) exc.what() +"\n";
		}
	}
	if (fxm!= ""){
		throw AdSyntaxException (__FILE__,__LINE__,"fromString(const string& jdl )",
		WMS_JDLPARSE , fxm  );
	}
	GLITE_STACK_JDL_CATCH_ALL() ;   //Exiting from method: remove line from stack trace
}
/******************************
*  Add /append attribute Methods
********************************/
void Ad::addAttribute(string attr_name , Value val){ 
	GLITE_STACK_TRY("Ad::addAttribute(string attr_name , Value val)");
	//allowed values:
	string		strVal;
	int		intVal;
	bool		bolVal;
	double		douVal;
	const ExprList	*el;

	if   (val.IsIntegerValue(intVal)){
		addAttribute(attr_name , intVal);   //  Integer TYPE
	}else if (val.IsStringValue(strVal)){
		addAttribute(attr_name , strVal);   //  String  TYPE
	}else if (val.IsBooleanValue(bolVal)){
		addAttribute(attr_name , bolVal);   //  Boolean TYPE
	}else if (val.IsRealValue(douVal)){
		addAttribute(attr_name , douVal);   //  Real    TYPE
	}else if (val.IsListValue(el)){
		ExprListIterator elIter(el);            //  LIST    TYPE: Iteration
		elIter.ToFirst();
		elIter.CurrentValue(val);
		while (!elIter.IsAfterLast()){
			//Recursive Function  call:
			addAttribute(attr_name,val);
			elIter. NextValue(val);
		}
	}  else  throw AdMismatchException ( __FILE__ , __LINE__ ,METHOD, WMS_JDLSYN, attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void Ad::appendValue(ExprTree* trees , const Value& val , const string& attr_name){
	string METHOD ="Ad::appendValue(ExprTree* trees , const Value& val , const string& attr_name)" ;
	Value      valSource;
	const ExprList    *el;
	vector<ExprTree*>    vect;
	//ExprTree trees has to be copied in order to avoid memory-conflicts
	ExprTree *tree =  trees->Copy();
	if (tree== NULL){
		throw  AdClassAdException (__FILE__ , __LINE__ ,METHOD,
			WMS_JDLSYN , "ExprTree::Copy();");
	}
	//Converts the Source tree Expression to a Value valueSource
	if(  !EvaluateExpr( tree, valSource )    ){
		throw  AdClassAdException (__FILE__ , __LINE__ ,METHOD,
			EPERM , "ClassAd::EvaluateExpr",attr_name);
	}
	// Check The Source Value and retrieve/create the Vector
	if (  valSource.IsListValue(el)     ){
		el-> GetComponents(vect);  //It's a list ->retrieve vector components
	}else{
		vect.push_back(tree);           //It's a single value -> append it to an empty vector
	}
	/* val is the new value that needs to be inserted in the list:
	Set the new Value to a Literal (ExpTree son) and appends it*/
	Literal   *lit = Literal::MakeLiteral (val);
	if (lit!= NULL){vect.push_back((ExprTree*)lit);}
	else{
		throw  AdClassAdException (__FILE__ , __LINE__ ,METHOD,
			WMS_JDLSYN , "Literal::MakeLiteral");
	}
	//Re-Generate the new ExprTreelist from the vector
	ExprList* newEl;
	newEl= ExprList::MakeExprList(vect);
	newEl -> SetParentScope((const ClassAd *)this);
	insertAttribute(attr_name , newEl ) ;
}


void Ad::addAttribute(const string& attr_name, Ad* attr_value){
	GLITE_STACK_TRY("Ad::addAttribute(const string& attr_name, Ad attr_value)");
	ExprTree*     tree= Lookup(attr_name) ;
	if (tree== NULL){
		//The attribute doesn't exist, it should be set
		setAttribute(attr_name , attr_value);
	}else {
		// Implementing appendValue without passing through Value:
		const ExprList    *el;
		Value val ;
		vector<ExprTree*>    vect;
		ExprTree*     trees =  tree->Copy();
		//Converts the Source tree Expression to a Value valueSource
		if(  !EvaluateExpr( trees, val )    ){
			throw  AdClassAdException (__FILE__ , __LINE__ ,METHOD,
			EPERM, "ClassAd::EvaluateExpr" , attr_name);
		}
		// Create a Vector with the previous value, wheter is a list or a simple classad
		if (  val.IsListValue(el)     ){
			el-> GetComponents(vect);  //It's a list ->retrieve vector components
		}else{
			vect.push_back(trees);           //It's a single value -> append it to an empty vector
		}
		// Now Add the new value:
		vect.push_back(  attr_value->Copy()  );
		//Re-Generate the new ExprTreelist from the vector
		ExprList* newEl;
		newEl= ExprList::MakeExprList(vect);
		newEl -> SetParentScope(  (const ClassAd *) this ) ;
		insertAttribute(attr_name , newEl ) ;
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void Ad::addAttribute(const string& attr_name, int attr_value){
	GLITE_STACK_TRY("Ad::addAttribute(const string& attr_name, int attr_value)");
	//Check the couple attr_name/attr_value
	ExprTree*     tree=Lookup(attr_name);
	if (tree==NULL){setAttribute(attr_name , attr_value);}
	else {
		//The attribute already exist. a list should be made
		Value      val;
		val.SetIntegerValue(attr_value);
		appendValue(tree , val , attr_name ) ;
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void Ad::addAttribute(const string& attr_name, double attr_value){
	GLITE_STACK_TRY("Ad::addAttribute(const string& attr_name, double attr_value)") ;
	//Check the couple attr_name/attr_value
	ExprTree*     tree=Lookup(attr_name);
	if (tree==NULL){
		//The attribute doesn't exist, it should be set
		setAttribute(attr_name , attr_value);
	}else {
		//The attribute already exist. a list should be made
		Value      val;
		val.SetRealValue(attr_value);
		appendValue(tree , val , attr_name );
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void Ad::addAttribute(const string& attr_name, bool attr_value){
	GLITE_STACK_TRY("Ad::addAttribute(const string& attr_name, bool attr_value)") ;
	//Check the couple attr_name/attr_value
	ExprTree*     tree=Lookup(attr_name);
	if (tree==NULL){
		//The attribute doesn't exist, it should be set
		setAttribute(attr_name , attr_value);
	}else {
		//The attribute already exist. A list should be made, aclling append Value method
		Value      val;
		val.SetBooleanValue(attr_value);
		//Append the value to the already existing Expression
		appendValue(tree , val , attr_name );
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void Ad::addAttribute(const string& attr_name, const string& attr_value){
	GLITE_STACK_TRY("Ad::addAttribute(const string& attr_name, const string& attr_value)") ;
	//Check the couple attr_name/attr_value
	ExprTree*     tree=Lookup(attr_name);
	Value      val;
	val.SetStringValue(attr_value);

	if (tree==NULL){
		//The attribute doesn't exist, a new list should be set
		appendValue(new ExprList(), val , attr_name );
	}else {
		//The attribute already exist. a list should be made
		//Append the value to the already existing Expression
		appendValue(tree , val , attr_name );
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/***************************
* SetAttribute Methods
****************************/
void  Ad::setAttributeExpr (const std::string& attr_name, classad::ExprTree* attr_value) {
	if (  Lookup(attr_name) != NULL   ){
		throw AdEmptyException (__FILE__ , __LINE__ ,
		"Ad::setAttributeExpr (const string& attr_name, classad::ExprTree* attr_value)",
		WMS_JDLFULL ,attr_name);
	}
	insertAttribute (attr_name , attr_value);
}

void Ad::setAttributeExpr (const string& attr_name, const string& attr_value) {
	if (  Lookup(attr_name) != NULL  ){
		throw AdEmptyException (__FILE__ , __LINE__ ,
		"Ad::setAttributeExpr (const string& attr_name, const string& attr_value)",
		WMS_JDLFULL ,attr_name);
	}
	// JdlAttributeList jdlist ;
	ClassAdParser par ;
	ExprTree *expr =par.ParseExpression(attr_value, true) ;
	if (expr != NULL){insertAttribute (attr_name , expr);}
	else{
		throw  AdClassAdException (__FILE__ , __LINE__ ,
		"Ad::setAttributeExpr (const string& attr_name, const string& attr_value)",
		WMS_JDLSYN , "ClassAdParser::ParseExpression");
	}
}

void Ad::setAttribute (const string& attr_name, int attr_value){
	GLITE_STACK_TRY("Ad::setAttribute (const string& attr_name, int attr_value)");
	if (  Lookup(attr_name) != NULL   ){
		throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLFULL ,attr_name);
	}
	// jdlist.checkInt (attr_name , attr_value) ;
	Value val ;
	val.SetIntegerValue(attr_value) ;
	insertAttribute( attr_name , val) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void Ad::setAttribute (const string& attr_name, double attr_value){
	GLITE_STACK_TRY("Ad::setAttribute (const string& attr_name, double attr_value)");
	if (  Lookup(attr_name) != NULL   ){
		throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLFULL ,attr_name);
	}
	// jdlist.checkDouble(attr_name , attr_value);
	Value val ;
	val.SetRealValue(attr_value) ;
	insertAttribute( attr_name , val) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void Ad::setAttribute (const string& attr_name, bool attr_value){
	GLITE_STACK_TRY("Ad::setAttribute (const string& attr_name, bool attr_value)");
	if (  Lookup(attr_name) != NULL   ){
		throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLFULL ,attr_name);
	}
	// jdlist.checkBool(attr_name , attr_value);
	Value val ;
	val.SetBooleanValue(attr_value) ;
	insertAttribute( attr_name , val) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void Ad::setAttribute (const string& attr_name, const string& attr_value){
	GLITE_STACK_TRY("Ad::setAttribute (const string& attr_name, const string& attr_value)");
	if (  Lookup(attr_name) != NULL   ){
		throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLFULL ,attr_name);
	}
	Value val ;
	val.SetStringValue(attr_value) ;
	insertAttribute( attr_name , val) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void Ad::setAttribute (const string& attr_name, Ad* attr_value){
	GLITE_STACK_TRY("Ad::setAttribute (const string& attr_name, Ad* attr_value)");
	if (  Lookup(attr_name) != NULL   ){
		throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLFULL ,attr_name);
	}
	insertAttribute( attr_name , attr_value->Copy()) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*************************************
* get Methods :
*************************************/
string Ad::getAttributeExpr (const string& attr_name){
	ExprTree* tree = Lookup (attr_name);
	ClassAdUnParser unp;
	if (tree == NULL ){
		throw AdEmptyException (__FILE__ , __LINE__ ,
		"Ad::getAttributeExpr (const string& attr_name)throw (exception)",
		WMS_JDLEMPTY ,attr_name);
	}
	string buffer;
	unp.Unparse( buffer , tree);
	return buffer ;
}
int Ad::getType (const string &attr_name ){
	GLITE_STACK_TRY( "Ad::getType (const string &attr_name )")
	ExprTree *tree = Lookup(attr_name) ;
	if (tree==NULL){
		throw AdEmptyException (__FILE__,__LINE__,
		"getTypeValue(const string& attr_name)",WMS_JDLEMPTY ,attr_name);
	}
	Value val;
	switch (tree->GetKind()){
		case ExprTree::CLASSAD_NODE:
			return Value::CLASSAD_VALUE;
			break;
		case ExprTree::EXPR_LIST_NODE:{
			ExprList* el = static_cast<classad::ExprList*>(tree);
			vector<ExprTree*> vectList ;
			el->GetComponents (vectList);
			if (vectList.size()){ EvaluateExpr(vectList[0],val);}
			else{ return TYPE_UNKNOWN ;}
		}
		break;
		default: // LITERAL_NODE, ATTRREF_NODE, OP_NODE, FN_CALL_NODE,
			// OLD behaviour:
			val =getTypeValue(attr_name);
			break;
	}
	switch (val.GetType()  ){
		case Value::ERROR_VALUE:
		case Value::INTEGER_VALUE:
		case Value::BOOLEAN_VALUE:
		case Value::STRING_VALUE:
		case Value::REAL_VALUE:
		case Value::UNDEFINED_VALUE:
		case Value::CLASSAD_VALUE:
			return val.GetType() ;
		default:
			return TYPE_UNKNOWN ;
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*
* Retrieve a Value instance of the selected type
* This Method is used by all  get<type>value methods
*/
Value Ad::getTypeValue(const string& attr_name){
	ExprTree            *tree ;
	Value                val;
	tree = Lookup(attr_name.c_str()) ;
	if (tree==NULL){
		throw AdEmptyException (__FILE__,__LINE__,
		"getTypeValue(const string& attr_name)",WMS_JDLEMPTY ,attr_name);
	}else{EvaluateAttr(attr_name , val);}
	return val;
}
vector<double> Ad::getDoubleValue(const string& attr_name)   {
	GLITE_STACK_TRY("Ad::getDoubleValue(const string& attr_name)");
	double d;
	int    i;
	vector<double> vect;
	const ExprList *el;
	//Retrieve the Value type and Check
	Value val =  getTypeValue(attr_name);
	if (  val.IsRealValue(d)  ){             //It's a Real --->OK
		vect.push_back(d);
	}else if (  val.IsIntegerValue(i)  ){    //It's an Int --->OK (casting)
		vect.push_back(   (double) i);
	}else if (val.IsListValue(el)){          //It's a List, Iterate over values
		EvalState *es = NULL;
		for ( ExprList::const_iterator elIter = el->begin();elIter != el->end(); elIter++ ) {
			(*elIter)->Evaluate(*es, val);
			if (val.IsRealValue(d)){
				vect.push_back(d);
			} else if  ( val.IsIntegerValue(i)  ){
				vect.push_back ( (double) i);
			}else{
				throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
			}
		}
	}else{
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	return vect;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/* *****************************************************************
 methods :   get<type>[Value]
 Retreive the value of an attribute (if Value is specified return the value of the specified attribute as a vector)
 where <type> could be:
 -int
 -double
 -bool
 -string

*******************************************************************/
vector<bool> Ad::getBoolValue(const string& attr_name){
	GLITE_STACK_TRY("Ad::getBoolValue(const string& attr_name)");
	bool            b;
	vector<bool>    vect ;
	const ExprList *el;
	//Retrieve the Value type and Check
	Value val =  getTypeValue(attr_name);
	if (  val.IsBooleanValue(b)  ){          //It's a Boolean --->OK
		vect.push_back(b);
	}else if (val.IsListValue(el)){          //It's a List, Iterate over values
		EvalState *es = NULL;
		for ( ExprList::const_iterator elIter = el->begin();elIter != el->end(); elIter++ ) {
			(*elIter)->Evaluate(*es, val);
			if (val.IsBooleanValue(b)){
				vect.push_back(b);
			}else{
				throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
			}
		}
	} else {
		throw  AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	return vect;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/**  This is a static method that transforms a Value into a vector of string (if possible)*/
vector<string> vectorString ( Value &val , const string& attr_name , const string& METHOD) {
	string s;
	vector<string> vect;
	const ExprList *el;
	if (val.IsStringValue(s)){           //It's astring --->OK
		vect.push_back(s);
	}else if (val.IsListValue( el)){          //It's a List, Iterate over values
		for ( ExprList::const_iterator elIter = el->begin(); elIter != el->end(); elIter++ ) {
			(*elIter)->Evaluate(val);
			if (val.IsStringValue(s)){vect.push_back(s);}
			else {
				throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
			}
		}
	}else {
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	return vect;
}
vector<vector<string> > Ad::getStringList(const string& attr_name){
	GLITE_STACK_TRY("Ad::getStringList(const string& attr_name)");
	Value val =  getTypeValue(attr_name);
	string s ;
	const ExprList *el;
	vector<vector<string> > vect;
	if (val.IsStringValue(s)){           //It's astring --->OK
		vector< string> one ;
		one.push_back(s);
		vect.push_back(one) ;
		// single value, just return
		return vect;
	}else if (val.IsListValue( el)){          //It's a List, Iterate over values
		EvalState *es = NULL;
		vector< string> one ;
		for ( ExprList::const_iterator elIter = el->begin(); elIter != el->end(); elIter++ ) {
			/*  Iterate over the list values, could be list of strings, lists, mixed:
				attr = {  "value1" , "value2" ...   }
				attr = {  "value1",  {"valueB1" , "valueB2"} ...   }
			*/
			(*elIter)->Evaluate(*es, val);
			if (val.IsStringValue(s)){
				// it's a string, all values must be string
				if ( vect.size() >0)
					throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
				one.push_back(s);
			}else if (val.IsListValue( )){
				// it's a list of string: all values must be string
				if ( one.size() >0)
					throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
				vect.push_back (   vectorString ( val , attr_name , METHOD ) ) ;
			}
		}
		if ( one.size() >0 )
			vect.push_back(one) ;
	}else  throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	return vect ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
vector<string> Ad::getStringValue(const string& attr_name) {
	Value val=getTypeValue(attr_name);
	return vectorString(val,attr_name,"getStringValue(const string& attr_name)");
}

vector<int> Ad::getIntValue(const string& attr_name){
	GLITE_STACK_TRY("Ad::getIntValue(const string& attr_name)");
	int i ;
	vector<int> vect ;
	const ExprList *el;
	//Retrieve the Value type and Check
	Value val =  getTypeValue(attr_name);
	if (val.IsListValue(el)){             //It's a List, Iterate over values
		EvalState *es = NULL;
		for ( ExprList::const_iterator elIter = el->begin();elIter != el->end(); elIter++ ) {
			(*elIter)->Evaluate(*es, val);
			if (  val.IsIntegerValue(i)  )
				vect.push_back (i);
			else {
				throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
			}
		}
	}else  if (  val.IsIntegerValue(i)  ){  //It's an Int --->OK (casting)
		vect.push_back (i);
	}else{
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	return vect;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

Ad Ad::getAd(const std::string& attr_name) {
	GLITE_STACK_TRY("Ad::getAd(const std::string& attr_name)");
	ExprTree* tree = Lookup (attr_name);
	if ( tree== NULL ){ throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLEMPTY, attr_name);}
	if ( tree->GetKind() != ExprTree::CLASSAD_NODE  ){
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	return Ad(*static_cast<ClassAd*>(tree));
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
string Ad::getString(const string& attr_name) {
	GLITE_STACK_TRY("Ad::getString(const string& attr_name)");
	Value val=getTypeValue(attr_name);
	string result;
	if (val.IsStringValue(result)){ return result;}
	else { throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

bool Ad::getBool(const string& attr_name) {
	GLITE_STACK_TRY("Ad::getBool(const string& attr_name)");
	Value val=getTypeValue(attr_name);
	bool result;
	if (val.IsBooleanValue(result)){
		return result;
	}else {
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

int Ad::getInt(const string& attr_name) {
	GLITE_STACK_TRY("Ad::getInt(const string& attr_name)");
	Value val=getTypeValue(attr_name);
	int result;
	if (val.IsIntegerValue(result)){
		return result;
	}else {
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

double Ad::getDouble(const string& attr_name) {
	GLITE_STACK_TRY("Ad::getDouble(const string& attr_name)");
	Value val=getTypeValue(attr_name);
	double result;
	if (val.IsRealValue(result)){
		return result;
	}else {
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
// WARNING MANAGEMENT
bool  Ad::hasWarnings(){
	return warning_messages_v.size()!=0;
}
std::vector<std::string>  Ad::getWarnings(){
	return warning_messages_v;
}
void  Ad::addWarning(const std::string &msg){
	warning_messages_v.push_back(msg);
}
} // jdl namespace
} // glite namespace
