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
*  filename  : ExpDagAd.cpp
*  author    : Alessandro Maraschini <alessandro.maraschini@datamat.it>
*  copyright : (C) 2002 by DATAMAT
***************************************************************************/

#include "RequestAdExceptions.h"
#include "NodeAd.h"
#include "ExpDagAd.h"
#include "extractfiles.h"
#include "DAGAdManipulation.h"
#include "JDLAttributes.h"
#include"PrivateAttributes.h"  // ZIPPED_ISB attribute
#include "exception_codes.h"
#include "grammar.h"
/* allow classad parsing creation */
#include "glite/wmsutils/classads/classad_utils.h"
#include <boost/tuple/tuple.hpp>
#include <boost/algorithm/string/replace.hpp>

namespace glite {
namespace jdl {

using namespace classad;
using namespace std ;
using namespace glite::wmsutils::classads ;
using namespace glite::wmsutils::exception ;
using namespace boost::algorithm ;

typedef std::map<std::string,std::string> MapNodes;

/*********************************************
*JobIdStruct default constructor
*********************************************/
JobIdStruct::JobIdStruct()
:nodeName(0)
{
}

/******************************************************************
*JobIdStruct copy constructor
*******************************************************************/
JobIdStruct::JobIdStruct(const JobIdStruct &jobStruct)
{
  // Copy the Job ID
  jobid = jobStruct.jobid;

  // Copy the Node name
  nodeName = jobStruct.nodeName;

  // Retrieve the children vector
  std::vector<JobIdStruct*> tempChildrenNodes = jobStruct.children;

  // Retrieve the Iterator of the children and the last child
  std::vector<JobIdStruct*>::iterator childrenIterator =  tempChildrenNodes.begin();
  std::vector<JobIdStruct*>::iterator lastChild = tempChildrenNodes.end();

  // Scan all the available children and copy the Vector
  while(childrenIterator < lastChild)
  {
    // Create a new Child
    JobIdStruct* newChild = new JobIdStruct();

    // Copy the child
    *newChild = *((JobIdStruct *)*childrenIterator);

    // Add the new Child to the vector
    children.push_back(newChild);

    // Move to the next child
    childrenIterator++;
  }

}

/******************************************************************
*JobIdStruct destructor
*******************************************************************/
JobIdStruct::~JobIdStruct()
{
  // Free the memory allocated
  flushMemory();
}

/******************************************************************
*JobIdStruct operator=
*******************************************************************/
JobIdStruct& JobIdStruct::operator=(const JobIdStruct& jobStruct)
{
  // Perform the assign if the node is NOT 'this'
  if (this != &jobStruct) {

    // Free the memory allocated
    flushMemory();

    // Copy the Job ID
    jobid = jobStruct.jobid;

    // Copy the Node name
    nodeName = jobStruct.nodeName;

    // Retrieve the children vector
    std::vector<JobIdStruct*> tempChildrenNodes = jobStruct.children;

    // Retrieve the Iterator of the children and the last child
    std::vector<JobIdStruct*>::iterator childrenIterator =  tempChildrenNodes.begin();
    std::vector<JobIdStruct*>::iterator lastChild = tempChildrenNodes.end();

    // Scan all the available children and copy the Vector
    while(childrenIterator < lastChild)
    {
      // Create a new Child
      JobIdStruct* newChild = new JobIdStruct();

      // Copy the child
      *newChild = *((JobIdStruct *)*childrenIterator);

      // Add the new Child to the vector
      children.push_back(newChild);

      // Move to the next child
      childrenIterator++;
    }

  }

  // Return the copied Node
  return *this;
}

/******************************************************************
*JobIdStruct flushMemory method
*******************************************************************/
void JobIdStruct::flushMemory(void)
{
  // Check if the Job has children
  if(children.size() > 0) {
    // Retrieve the Iterator of the children and the last child
    std::vector<JobIdStruct*>::iterator childrenIterator = children.begin();
    std::vector<JobIdStruct*>::iterator lastChild = children.end();

    // Scan all the available children and free the memory
    while(childrenIterator < lastChild)
    {
      // Retrieve a child
      JobIdStruct *currentChild = (JobIdStruct *)*childrenIterator;

      // Delete the current child
      delete(currentChild);

      // Move to the next child
      childrenIterator++;
    }

  }

  // Clean the vector
  children.clear();

}

/******************************************************************
 methods : parse_file
*******************************************************************/
std::string parse_file (std::ifstream& jdl_in  ) {
	if (!jdl_in.good()){return "";}
	string result = "", tmpStr ;
	int blank ;
	while ( getline( jdl_in, tmpStr, '\n') ){
		//find the first no-blank character
		blank = 0 ;
		while (tmpStr[blank]==' ') blank++;
		//Check For Commented lines:
		if ( tmpStr[blank] =='#' ){
			//Python Comment: do nothing
		}else if (tmpStr[blank] =='/' && tmpStr[blank+1] =='/'){
			//C/C++ Comment: do nothing
		}else{ result += " " + tmpStr; }
	}
	while (result.length()!=0) if ( result.substr(0,1)==" " ){result = result.substr(1); }else {break;}
	while (result.find("\t") < result.size() ) result = result.substr(0 , result.find("\t")) + result.substr( result.find("\t")+1);
	while (result.find("\n") < result.size() ) result = result.substr(0 , result.find("\n")) + result.substr( result.find("\n")+1);
	return result ;
}


/******************************************************************
 methods : Constructors
*******************************************************************/
ExpDagAd::ExpDagAd( const std::string& jdl ) {
	reset();
	fromString (jdl) ;
}
ExpDagAd::ExpDagAd(std::ifstream& jdl_in ) {
	reset();
	fromString (parse_file (jdl_in) ) ;
}
ExpDagAd::ExpDagAd( DAGAd* ad ){
	reset();
	try {
		dagad.reset( new DAGAd (ad->ad()));
	}catch(std::exception &exc){
                throw AdSyntaxException (__FILE__,__LINE__,"dagadReset( DAGAd* target, DAGAd* source)",
                WMS_JDLPARSE , string(exc.what()));
        }
}
ExpDagAd::ExpDagAd( Ad* ad  ){
	reset();
	try {
		dagad.reset( new DAGAd (*(ad->ad())));
	}catch(std::exception &exc){
                throw AdSyntaxException (__FILE__,__LINE__,"dagadReset( DAGAd* target, DAGAd* source)",
                WMS_JDLPARSE , string(exc.what()));
        }
}
ExpDagAd::ExpDagAd( const classad::ClassAd &classAd ){
	reset();
	try {
		dagad.reset( new DAGAd (classAd));
	}catch(std::exception &exc){
                throw AdSyntaxException (__FILE__,__LINE__,"dagadReset( DAGAd* target, DAGAd* source)",
                WMS_JDLPARSE , string(exc.what()));
        }
}
ExpDagAd::ExpDagAd( const ExpDagAd& dag ){
	reset();
	try {
		dagad.reset( new DAGAd (dag.dagad->ad())) ;
	}catch(std::exception &exc){
                throw AdSyntaxException (__FILE__,__LINE__,"dagadReset( DAGAd* target, DAGAd* source)",
                WMS_JDLPARSE , string(exc.what()));
        }
	// Initialising private members
	if (dag.defaultRank){defaultRank = dag.defaultRank->Copy();}
	if (dag.defaultReq) {defaultReq  = dag.defaultReq->Copy();}
	if (dag.extractedAd) {extractedAd  = dag.extractedAd->Copy();}
	uiManipulation = dag.uiManipulation ;
	toBretrieved   = dag.toBretrieved;
	lookInto_b     = dag.lookInto_b ;
	warning_messages_v=dag.warning_messages_v;

}
void ExpDagAd::operator=(const ExpDagAd& dag){
	reset();
	dagad.reset(new DAGAd (dag.dagad->ad()));
	// Initialising private members
	if (dag.defaultRank){defaultRank = dag.defaultRank->Copy();}
	if (dag.defaultReq) {defaultReq  = dag.defaultReq->Copy();}
	if (dag.extractedAd) {extractedAd  = dag.extractedAd->Copy();}
	uiManipulation = dag.uiManipulation ;
	toBretrieved   = dag.toBretrieved;
	lookInto_b     = dag.lookInto_b ;
	warning_messages_v=dag.warning_messages_v;
}
ExpDagAd::~ExpDagAd() throw(){ } ;
ExpDagAd* ExpDagAd::check (){
	ExpDagAd *dagad = new ExpDagAd(*this);
	dagad->getSubmissionStrings ();
	return dagad;
}

/**
* RESET ALL EXPDAG
*/
void ExpDagAd::reset(){
	uiManipulation = false;
	toBretrieved=false;
	lookInto_b  = EXISTENCE;
	defaultRank = NULL;
	defaultReq  = NULL;
	extractedAd =NULL;
	warning_messages_v.resize(0);
}
/*************
* fromString
*************/
void ExpDagAd::fromString (const std::string& jdl, string jdl_file) {
	GLITE_STACK_TRY("ExpDagAd::fromString");
	try{
		std::auto_ptr<classad::ClassAd> ad( parse_classad( jdl ) );
		dagad.reset(new DAGAd ( *ad ));
	}catch(std::exception &exc){
		jdl_parser parser;
		if (jdl_file.empty()){
		parser.parseString ( jdl ) ;
		} else {
		parser.parseFile ( jdl_file ) ;
		}
		throw AdSyntaxException (__FILE__,__LINE__,"fromString(const string& jdl )",
		WMS_JDLPARSE , string(exc.what()));
	}
	defaultReq= NULL ;
	defaultRank = NULL ;
	extractedAd = NULL ;
	uiManipulation = false ;
	lookInto_b = EXISTENCE;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*************
* fromFile
*************/
void ExpDagAd::fromFile ( ifstream & jdl_in ) {
	GLITE_STACK_TRY("ExpDagAd::fromFile");
	fromString (parse_file(jdl_in) ) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*************
* toString
*************/
std::string ExpDagAd::toString ( const level  &l ) {
	string buffer ;
	PrettyPrint unp;
	unp.SetClassAdIndentation(0) ;
	unp.SetListIndentation(0) ;
	switch ( l ) {
		case CURRENT :
		unp.Unparse( buffer, &dagad->ad() );
		break ;
		case NO_NODES:{
		ClassAd ad ( dagad->ad() );
		ad.Delete(DAGAd::Attributes::NODES) ;
		unp.Unparse( buffer, &ad );
		}
		break;
		case MULTI_LINES:
		unp.SetClassAdIndentation( 1 ) ;
		// unp.SetListIndentation( 1 ) ;
		unp.Unparse( buffer, &dagad->ad() );
		break;
		default : // RESTORED || SUBMISSION (deprecated)
		// Not used at the moment
		unp.Unparse( buffer, &dagad->ad() );
		break;
	}
	return buffer ;
}

/*************
* hasAttribute
*************/
bool ExpDagAd::hasAttribute (const std::string& attr_name ) {
	return (dagad->ad().Lookup(attr_name)!=NULL);

}

/*************
* Load jdls for files-nodes type
*************/
void ExpDagAd::expand () {
	string finalExc = "";
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	Ad ad ;
	for ( iter = begin ; iter!= end ; iter ++){
		try{
			if ( iter->second.description_ad()==0 ){
				// Parse the node
				ad.clear();
				ad.fromFile(iter->second.description_file());
				// Create a new DAG node and replacing the old one
				DAGNodeInfo replacing_node (*(ad.ad()),"edg_jdl");
				replacing_node.description_ad_for_file(ad.ad());
				dagad->replace_node (iter->first , replacing_node ) ;
			}
		} catch ( Exception &exc ){
			if ( !finalExc.empty() ) { finalExc += "\n"; }
			finalExc += iter->first + " ->" + string (exc.what() ) ;
		} catch ( std::exception &exc ){
			// can be parsing ClassAd...
			if (!finalExc.empty()) { finalExc += "\n"; }
			finalExc += iter->first + " ->" + string (exc.what() ) ;
		}
	}
	if ( !finalExc.empty() )
		throw AdSyntaxException ( __FILE__ , __LINE__ , "ExpDagAd::expand ()", WMS_DAG_CHECK , finalExc );
}
/*************
* Retrieve a generic attribute string value (if present)
*************/

void
get_generic(DAGAd const& dagad, std::string const& attribute, std::string& result){
	classad::ExprTree const* et = dagad.get_generic(attribute);
	if (utilities::is_literal(et)) {
		classad::Literal const& l = *static_cast<classad::Literal const*>(et);
		classad::Value v;
		l.GetValue(v);
		if(!v.IsStringValue(result)){
			throw AdMismatchException (__FILE__,__LINE__,
				"get_generic(DAGAd const& dagad, std::string const& attribute, std::string& result)",
				WMS_JDLMISMATCH, attribute);
		}
	}
	// Attribute not present or not literal
}
/*************
* extract Files for InputSandbox
*************/
void ExpDagAd::extract(){
	GLITE_STACK_TRY("ExpDagAd::extract");
	// retrieve wmp and base URI
	string wmpUri, isbUri;
	get_generic(*dagad, JDL::WMPISB_BASE_URI, wmpUri);
	get_generic(*dagad, JDL::ISB_BASE_URI , isbUri);
	// Retrieve dagad ISB value
	Ad ad ;
	const ExprTree *tree =dagad->get_generic(JDL::INPUTSB);
	if (tree==NULL) {return;}
	// dagad ISB values are stored in Ad instance (all of them must be of tring type)
	ad.setAttributeExpr(JDL::INPUTSB, tree->Copy());
	vector<string> isbox = ad.getStringValue(JDL::INPUTSB);
	// Extract (i.e. resolve path) dagad ISB values
	std::vector<std::string> extracted;
	std::vector<std::string>::iterator it = isbox.begin();
	std::vector<std::string>::iterator end = isbox.end();
	for (;it!=end; ++it){
		toBretrieved = extractFiles(JDL::INPUTSB, *it, extracted,lookInto_b,wmpUri,isbUri,extractedAd) || toBretrieved ;
	}
	ad.delAttribute(JDL::INPUTSB);
	// replace old ISB values with the extracted ones...
	it  = extracted.begin();
	end = extracted.end();
	for(; it!=end;++it){
		ad.addAttribute(JDL::INPUTSB, *it) ;
	}
	dagad->set_generic(JDL::INPUTSB, ad.delAttribute(JDL::INPUTSB));
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*************
* dependencies
*************/
std::string ExpDagAd::showDependencies(){
	GLITE_STACK_TRY("ExpDagAd::showDependencies");
	DAGAd::dependency_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->classad_dependencies() ;
	DAGAd::node_iterator nod_1, nod_2;
	vector<pair <string , vector<string> > > nodesNames ;
	bool found = false ;
	unsigned int i = 0 ;
	for ( iter = begin ; iter!= end ; ++iter){
		nod_1 = iter->first ;
		nod_2 = iter->second ;
		found = false;
		for (i = 0 ; i < nodesNames.size() ; i++ ){
			if ( nodesNames[i].first == nod_1->first ){
				nodesNames[i].second.push_back( nod_2->first ) ;
				found = true ;
				break ;
			}
		}
		if (!found){
			nodesNames.push_back( pair <string , vector<string> > (
					nod_1->first ,
					vector<string> ( 1 , nod_2->first )
			) );
		}
	}
	string EQUALS = ":" ;
	string SEP = " " ;
	string result = "" ;
	vector<string>::iterator it ;
	for (i = 0 ; i < nodesNames.size() ; i++ ){
		result += nodesNames[i].first + EQUALS ;
		for ( it = nodesNames[i].second.begin() ; it != nodesNames[i].second.end(); it++ )
			result += *it + SEP ;
		result += "\n" ;
	}
	return result ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

const string ExpDagAd::getDefaultRank (){
	string buffer="";
	if ( defaultRank!=NULL){
		PrettyPrint unp;
		unp.SetClassAdIndentation(0);
		unp.SetListIndentation(0);
		unp.Unparse(buffer,defaultRank );
	}
	return buffer ;
}
const string ExpDagAd::getDefaultReq (){
	string buffer="";
	if ( defaultReq!=NULL){
		PrettyPrint unp;
		unp.SetClassAdIndentation(0);
		unp.SetListIndentation(0);
		unp.Unparse(buffer,defaultReq );
	}
	return buffer ;
}
std::vector<std::string> ExpDagAd::getInputSandbox (){
	return get_input_sandbox(*dagad );
}

void ExpDagAd::setLocalAccess(bool lookInto){
	lookInto_b = lookInto?EXISTENCE:WMPROXY;
}

void ExpDagAd::setDefaultRank (const std::string& attr_value ){
	ClassAdParser par ;
	defaultRank =par.ParseExpression(attr_value, true) ;
	if ( defaultRank==NULL)
		throw AdClassAdException (__FILE__ , __LINE__ ,
		" ExpDagAd::setDefaultRank (const string& attr_value)", WMS_JDLSYN , "ClassAdParser::ParseExpression");
}
void ExpDagAd::setDefaultReq (const std::string& attr_value ){
	ClassAdParser par ;
	defaultReq = par.ParseExpression(attr_value, true) ;
	if ( defaultReq==NULL)
		throw AdClassAdException (__FILE__ , __LINE__ ,
		"ExpDagAd::setDefaultReq(const string& attr_value)", WMS_JDLSYN , "ClassAdParser::ParseExpression");
}
void ExpDagAd::setDefaultRank (classad::ExprTree *attr_value ){
	if (attr_value!=NULL){defaultRank=attr_value->Copy();}
	else{
		throw AdClassAdException (__FILE__ , __LINE__ ,
		"ExpDagAd::setDefaultRank(const string& attr_value)", WMS_JDLSYN , "Null Expression");
	}
}
void ExpDagAd::setDefaultReq (classad::ExprTree *attr_value ){
	if (attr_value!=NULL){defaultReq=attr_value->Copy();}
	else{
		throw AdClassAdException (__FILE__ , __LINE__ ,
		"ExpDagAd::setDefaultReq(const string& attr_value)", WMS_JDLSYN , "Null Expression");
	}
}




/*************
* ExpDagAd::getAttribute
*************/

std::map<std::string,std::string> ExpDagAd::getJobIdMap(){
	GLITE_STACK_TRY("ExpDagAd::getJobIdMap");
	if (!map_nodes.size()){
		createMap();
	}
	return map_nodes;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
std::string ExpDagAd::getString(const std::string &attr_name){
	string result;
	get_generic(*dagad, attr_name, result);
	//if (result==""){
	//	throw AdMismatchException (__FILE__,__LINE__,
	//		"ExpDagAd::getString(const std::string &attr_name)",
	//		WMS_JDLMISMATCH, attr_name);
	//}
	return result;
}
bool ExpDagAd::getBool(const std::string &attr_name){
	bool result = false;
	classad::ExprTree const* et = dagad->get_generic(attr_name);
	if (utilities::is_literal(et)) {
		classad::Literal const& l = *static_cast<classad::Literal const*>(et);
		classad::Value v;
		l.GetValue(v);
		if(!v.IsBooleanValue(result)){
			throw AdMismatchException (__FILE__,__LINE__,
				"ExpDagAd::getBool(const std::string &attr_name)",
				WMS_JDLMISMATCH, attr_name);
		}
	}
	return result;
}
Ad ExpDagAd::getAttributeAd (const std::string& attr_name ){
	classad::ExprTree const* et=dagad->get_generic(attr_name);
	if (utilities::is_classad(et)) {
		classad::ClassAd const& c = *static_cast<classad::ClassAd const*>(et);
		return Ad (c);
	}
	throw AdMismatchException (__FILE__,__LINE__,"getAttributeAd(const std::string& attr_name)",
			WMS_JDLMISMATCH , attr_name);
}

std::string ExpDagAd::getAttribute (attribute attr_name ){

	switch (attr_name) {
	case EDG_JOBID:
		 return get_edg_jobid( *dagad );
	break;
	case VIRTUAL_ORGANISATION:
		return get_virtual_organisation( *dagad ) ;
	break;
	case MYPROXY_SERVER:
		return get_my_proxy_server( *dagad);
	break;
	case SEQUENCE_CODE:
		return get_lb_sequence_code( *dagad );
	case SUBMIT_TO:{
		string result;
		get_generic(*dagad, JDL::SUBMIT_TO, result);
		return result ;
	}
	break;
	default:
		throw AdMismatchException (__FILE__,__LINE__,"getAttribute(const std::string& attr_name)",
			WMS_JDLMISMATCH , "Unknown attribute" );
	break;
	}
}

/**
* This is a static method that transforms a Value into a vector of string (if possible)
*/
vector<string> stringVector ( Value &val , const string& attr_name , const string& METHOD) {
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

/*
*Retreive a Value instance of the selected type
* This Method is used by all  get<type>value methods
*/
Value ExpDagAd::getTypeValue(const string& attr_name){
	ExprTree *tree ;
	Value val;
	tree = dagad->ad().Lookup(attr_name.c_str()) ;
	if (tree==NULL){
		throw AdEmptyException (__FILE__,__LINE__,
		"getTypeValue(const string& attr_name)",WMS_JDLEMPTY ,attr_name);
	}else{dagad->ad().EvaluateAttr(attr_name , val);}
	return val;
}

vector<string> ExpDagAd::getStringValue(const string& attr_name) {
	Value val=getTypeValue(attr_name);
	return stringVector(val,attr_name,"getStringValue(const string& attr_name)");
}

/**
* DEPRECATED, is replaced by getStringValue
*/
std::vector<std::string> ExpDagAd::getAttribute (multiAttribute attr_name){
	classad::ExprTree const*et =NULL;
	switch (attr_name) {
		case INPUTSB:
			et= dagad->get_generic(JDL::INPUTSB);
			if (et!=NULL){
				return getStringValue(JDL::INPUTSB);
			}
			break;
		case ZIPPED_ISB:
			et= dagad->get_generic(JDLPrivate::ZIPPED_ISB);
			if (et!=NULL){
				return getStringValue(JDLPrivate::ZIPPED_ISB);
			}
		break;
		default:
		break;
	}
	vector<string> result ;
	return result;
}

ExtractedAd* ExpDagAd::getExtractedAd(){
	if(!extractedAd){
		getSubmissionStrings();
	}
	return extractedAd;
}

/*************
* ExpDagAd::removeAttribute
*************/
bool ExpDagAd::removeAttribute ( attribute attr_name ){
	switch (attr_name) {
	case EDG_JOBID:
		 return remove_edg_jobid( *dagad );
	break;
	case VIRTUAL_ORGANISATION:
		return remove_virtual_organisation( *dagad ) ;
	break;
	case MYPROXY_SERVER:
		return remove_my_proxy_server( *dagad);
	break;
	case SEQUENCE_CODE:
		return remove_lb_sequence_code( *dagad );
	break;
	default:
		// Unknown attribute
		return false ;
	break;
	}
}

bool ExpDagAd::removeAttribute ( std::string const&  attr_name ){
	  return dagad->remove_generic(attr_name);
}

/*************
* ExpDagAd::setAttribute
*************/
void ExpDagAd::setAttribute (multiAttribute attr_name , const std::vector<std::string>& attr_values){
	switch (attr_name) {
		case INPUTSB:
			set_input_sandbox (*dagad,attr_values);
			break;
		case ZIPPED_ISB:{
			classad::Value v;
			std::vector< ExprTree *> exprs;
			vector<std::string>::const_iterator it = attr_values.begin();
			vector<std::string>::const_iterator const  end = attr_values.end();
			for(; it!=end; ++it){
				v.Clear ();
				v.SetStringValue(*it);
				exprs.push_back(classad::Literal::MakeLiteral(v));
			}
			dagad->set_generic(JDLPrivate::ZIPPED_ISB, new ExprList(exprs));
			}
			break;
		default:  // no other values so far
			break;
	}
};


/*************
* ExpDagAd::setAttribute
*************/
void ExpDagAd::setAttribute (attribute attr_name , const std::string& attr_value ){
	switch (attr_name) {
	case EDG_JOBID:
		 set_edg_jobid( *dagad, attr_value);
	break;
	case VIRTUAL_ORGANISATION:
		set_virtual_organisation( *dagad, attr_value);
	break;
	case MYPROXY_SERVER:
		set_my_proxy_server( *dagad, attr_value);
	break;
	case SEQUENCE_CODE:
		set_lb_sequence_code( *dagad, attr_value);
	break;
	case ISB_DEST_URI:{
		classad::Value v;
		v.SetStringValue(attr_value);
		dagad->set_generic(JDL::ISB_BASE_URI, classad::Literal::MakeLiteral(v));
		}
	break;
	case SUBMIT_TO:{
		classad::Value v;
		v.SetStringValue(attr_value);
		dagad->set_generic(JDL::SUBMIT_TO, classad::Literal::MakeLiteral(v));
		}
	break;
	default:
	break;
	}
} ;
/*************
* ExpDagAd::size()
*************/
size_t ExpDagAd::size(){ return dagad->num_nodes() ; };

/***
* Inherit specified attribute and expression ONLY if
1) attribute is not already present in the node (UNLESS force is TRUE)
2) expression is set (not NULL)
****/
void ExpDagAd::inherit(NodeAd* jobad, const string& attr_name, ExprTree* expression,bool force){
	if (expression){
		if (!jobad->hasAttribute (attr_name)||force){
			// Replace node attribute when force is required
			// Insert node attribute when not yet present
			jobad->insertAttribute ( attr_name, expression->Copy() ) ;
		}
	}else if (jobad->hasAttribute(attr_name) && force){
		// Remove node attribute when force is required (even if expression not specified in Dag)
		jobad->delAttribute(attr_name);
	}
}
/***
* Inherit a set of attributes from dagClassAd into nodeAd
* This method is called for each node
****/
void ExpDagAd::inherit(glite::jdl::NodeAd* jobad,classad::ClassAd &dagClassAd){
	// WMPROXY side Inheritance Management
	if (lookInto_b==WMPROXY){
		inherit (jobad, JDL::FUZZY_RANK, 	dagClassAd.Lookup(JDL::FUZZY_RANK));
		inherit (jobad, JDL::INPUTSB,           dagClassAd.Lookup(JDL::INPUTSB));
		inherit (jobad, JDL::OUTPUTSB,          dagClassAd.Lookup(JDL::OUTPUTSB));
		inherit (jobad, JDL::OSB_DEST_URI,      dagClassAd.Lookup(JDL::OSB_DEST_URI));
		inherit (jobad, JDL::OSB_BASE_DEST_URI, dagClassAd.Lookup(JDL::OSB_BASE_DEST_URI));
		inherit (jobad, JDL::CERT_SUBJ, dagClassAd.Lookup(JDL::CERT_SUBJ ));
		inherit (jobad, JDL::RETRYCOUNT, dagClassAd.Lookup(JDL::RETRYCOUNT));
		inherit (jobad, JDL::SHALLOWRETRYCOUNT, dagClassAd.Lookup(JDL::SHALLOWRETRYCOUNT));
	}
	// Normal Inheritance Management
	inherit (jobad, JDL::PU_FILE_ENABLE, dagClassAd.Lookup(JDL::PU_FILE_ENABLE));
	inherit (jobad, JDL::SUBMIT_TO,      dagClassAd.Lookup(JDL::SUBMIT_TO));
	inherit (jobad, JDL::ISB_BASE_URI,   dagClassAd.Lookup(JDL::ISB_BASE_URI));
	inherit (jobad, JDLPrivate::VOMS_FQAN,  dagClassAd.Lookup(JDLPrivate::VOMS_FQAN));
	inherit (jobad, JDL::SHORT_DEADLINE_JOB,dagClassAd.Lookup( JDL::SHORT_DEADLINE_JOB));
	inherit (jobad, JDL::EXPIRY_TIME,dagClassAd.Lookup( JDL::EXPIRY_TIME));
	// Forced Inheritance Management (overriding)
	inherit (jobad, JDL::HLR_LOCATION,   dagClassAd.Lookup( JDL::HLR_LOCATION ),true);
	inherit (jobad, JDL::MYPROXY,        dagClassAd.Lookup( JDL::MYPROXY), true);
	inherit (jobad, JDL::JOB_PROVENANCE, dagClassAd.Lookup( JDL::JOB_PROVENANCE),true);
};
/***
* Inherit a specific attribute
* from the dag into all the nodes authomatically
****/
void ExpDagAd::inherit(const std::string& attr_name){
	// Resolve the nodes that are not yet fully expanded (if necessary)
	expand() ;
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	NodeAd* jobad ;
	ExprTree* expr =dagad->ad().Lookup(attr_name);
	if (expr==NULL) return;
	for ( iter = begin ; iter!= end ; iter ++){
		jobad = new NodeAd (*(iter->second.description_ad()));
		inherit (jobad , attr_name, expr);
		// Create a new DAG node and replacing the old one
		DAGNodeInfo replacing_node(iter->second) ;
		replacing_node.replace_description_ad( jobad );
		dagad->replace_node (iter->first , replacing_node ) ;
	}
}

/** STATIC PRIVATE method
* Parses and attribute and return its integer value
* zero returned if attribute not found
* Mismatch exception otherwise */
int getInt(ClassAd & ad, const string& attrName){
	try {
		if (ad.Lookup(attrName)){return evaluate_attribute(ad, attrName);}
	}catch (InvalidValue&){
		throw AdMismatchException (__FILE__,__LINE__,
				"getInt", WMS_JDLMISMATCH, attrName);
	}
	// DEFAULT VALUE
	return 0;
}

/*************
* ExpDagAd::getSubmissionStrings
*************/
std::vector<std::string> ExpDagAd::getSubmissionStrings (vector<string> *jobids) {
	GLITE_STACK_TRY("ExpDagAd::getSubmissionStrings")
	dagad->default_node_type("edg_jdl");
	toBretrieved = false;
	warning_messages_v.resize(0);
	//this instance will be returned to the method, up to the user to delete it
	extractedAd = new ExtractedAd();
	// Resolve the nodes that are not yet fully expanded
	if (lookInto_b!=WMPROXY) { expand() ; }
	// Evaluate, Check, Resolve and Extract ISB files only for the DAG (father) level
	// nodes will be able to refer to root.ISB without any problem (all strings found)
	extract();
	// Virtual Organisation Check
	string defaultVo =get_virtual_organisation(*dagad) ;
	if (defaultVo ==""){
		// No VO found
		throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,
			WMS_JDLEMPTY , JDL::VIRTUAL_ORGANISATION );
	}
	// Some useful variables:
	std::vector<std::string> jdls ;
	Ad osb_nodes;
	vector < pair<string , isb_value > > isb ;
	NodeAd* jobad ;
	ClassAd *classAd =NULL;
	Value val;
	ExprTree* isbTree;
	const ClassAd *nodes = static_cast<classad::ClassAd const*>(dagad->ad().Lookup(DAGAd::Attributes::NODES));
	// Nodes [Shallow] RetryCount special values (are inherited from nodes attribute)
	ExprTree* nodesRetryC   = nodes->Lookup(JDL::RETRYCOUNT);
	ExprTree* nodesShallowC = nodes->Lookup(JDL::SHALLOWRETRYCOUNT);
	// ClassAd representation of current DAG:
	ClassAd dagClassAd   = dagad->ad() ;
	// check possible DefaultValues
        ExprTree* defaultRetryC = dagClassAd.Lookup(JDLPrivate::DEFAULT_NODE_RETRYCOUNT);
        ExprTree* defaultShallowC = dagClassAd.Lookup(JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT);
	// Store some useful variables
	ExprTree* dagRank    = dagClassAd.Lookup( JDL::RANK );
	ExprTree* dagReq     = dagClassAd.Lookup( JDL::REQUIREMENTS );
	ExprTree* osb ;  // Used to check OSB nodes value
	std::vector<DAGAd::node_iterator> orderedNodes;
	string finalExc ="" ;
	// Nodes Check
	DAGAd::node_iterator begin, end , iter, actual;
	boost::tie ( begin, end )= dagad->nodes() ;
	if (begin==end){/*No nodes found*/throw AdEmptyException (__FILE__,__LINE__,METHOD,
		WMS_JDLEMPTY,DAGAd::Attributes::NODES);
	}
	if (lookInto_b==WMPROXY) {
		// Server side: Order nodes' names: first non-referenced names, than the others
		// This is done in order to resolve path when ISB are fully extracted
		orderedNodes=orderNodes();
	}
	int iter_int = 0;
	bool mapEmpty= map_nodes.size()==0;
	for ( actual = begin ; actual!= end ; actual++){
		try{
			iter = actual;
			if (lookInto_b==WMPROXY) {
				// Server side
				// Resolve and evaluate InputSandbox for the nodes
				// attribute for shared files
				// iterate over all the children
				iter = orderedNodes[iter_int];
				iter_int++;
				classAd = new ClassAd (*(iter->second.description_ad()));
				// Retrieve required Value
				isbTree= (static_cast<classad::ClassAd const*>(nodes->Lookup(iter->first)))->Lookup("description");
				isbTree= (static_cast<classad::ClassAd const*>(isbTree))->Lookup(JDL::INPUTSB);
				// ISB now is an epxtree
				if ( isbTree!=NULL ){
					if (isbTree->Evaluate(val)){
						if (!val.IsUndefinedValue()){
							classad::ExprTree* tmp_expr = EvaluateValue(val,true?new ExprList():NULL);
							classAd->Insert (JDL::INPUTSB, tmp_expr);
						} else{
							// TBD could be remote reference, do SOMETHING
						}
					}
				}
				// Actualizing the node:
				jobad = new NodeAd(*classAd);
			}else {
				jobad = new NodeAd (*(iter->second.description_ad()));
			}
			// Load ad from provided description (nodes have already been expanded)
			// Set local access
			jobad->setLocalAccess(lookInto_b==EXISTENCE?true:false); // check about TRANSFER tag
			// User Tag Management (only if UI manipulation adopted)
			if (uiManipulation){
				jobad->addUserTag ( JDL::GLITE_WMS_UI_DAG_NODE_NAME, iter->first ) ;
			}else if (!jobad->hasAttribute(JDL::NODE_NAME)){
				jobad->setAttribute(JDL::NODE_NAME,iter->first);
			}
			// Special dag attributes Management (rank-req):
			inherit (jobad, JDL::RANK,           dagRank);
			inherit (jobad, JDL::REQUIREMENTS,   dagReq) ;
			// Special nodes attributes Management (shallow-reTR):
                        if (nodesRetryC != NULL) {
                                inherit (jobad, JDL::RETRYCOUNT, nodesRetryC  ) ;
                        } else if (defaultRetryC != NULL) {
                                inherit (jobad, JDL::RETRYCOUNT, defaultRetryC ) ;
                        }
                        if (nodesShallowC != NULL) {
                                inherit (jobad, JDL::SHALLOWRETRYCOUNT, nodesShallowC) ;
                        } else if (defaultShallowC != NULL) {
                                inherit (jobad, JDL::SHALLOWRETRYCOUNT, defaultShallowC ) ;
                        }
			// Rank (default value)
			if (defaultRank!=NULL){jobad->defaultRank=defaultRank->Copy();}  // Friend approach
			// Requirements (default value)
			if (defaultReq!=NULL){jobad->defaultReq = defaultReq->Copy();}   // Friend approach
			// Virtual Organisation Management (string forcing)
			if ( jobad->hasAttribute (JDL::VIRTUAL_ORGANISATION) ){
				jobad->delAttribute( JDL::VIRTUAL_ORGANISATION );
			}
			jobad->setAttribute (JDL::VIRTUAL_ORGANISATION, defaultVo);
			//OutputSandbox
			osb= jobad->Lookup( JDL::OUTPUTSB );
			if (osb!=NULL) { osb_nodes.setAttributeExpr( iter->first , osb->Copy() );}
			// Manage Inheritance:
			inherit(jobad,dagClassAd);
			// Check the job without restoring user attributes
			jobad->check( false ) ;
			// UPDATE extractedAd files
			ExtractedAd *nodeExtractedAd = jobad->getExtractedAd()->Copy();
			nodeExtractedAd->setNodeName(iter->first);
			// Manage warning messages (if any)
			addWarnings(iter->first,jobad);
			extractedAd->addNode(nodeExtractedAd);
			// UPDATE retrieving Policy (toBretrieved):
			toBretrieved = toBretrieved || jobad->gettoBretrieved();
			// UPDATE (if necessary) id node map (map_nodes):
			if (mapEmpty && jobad->hasAttribute (JDL::JOBID)){
				map_nodes.insert(make_pair(jobad->getString(JDL::JOBID),iter->first));
			}
			// UPDATE (if necessary) ID (jobids):
			if (jobids){
				// JOBID must be present inside NODE, error otherwise
				jobids->push_back(jobad->getString(JDL::JOBID));
			}
			// UPDATE Submission Strings (jdls):
			jdls.push_back ( jobad->toString() ) ;
			// UPDATE remote sandbox link (isb):
			isb.push_back( pair <string , isb_value >(iter->first,jobad->getRemoteSandbox())) ;
			// UPDATE Dagad (dagad):
			DAGNodeInfo replacing_node(iter->second) ;
			replacing_node.replace_description_ad( jobad );
			dagad->replace_node(iter->first, replacing_node);
		} catch ( Exception &exc ){
			if (finalExc!="") { finalExc += "\n"; }
			finalExc += iter->first + " ->" + string (exc.what() ) ;
		}
	}
	if ( !finalExc.empty() )
		throw AdSyntaxException ( __FILE__ , __LINE__ ,METHOD, WMS_DAG_CHECK , finalExc );
	/** General DAG attributes management */
	if (dagClassAd.Lookup(DAGAd::Attributes::NODE_RETRY_COUNT)){
		// Deprecated NODE_RETRY_COUNT attribute is present
		addWarning(DAGAd::Attributes::NODE_RETRY_COUNT + " attribute is deprecated");
	}
	if ( get_nodes_collocation(*dagad) ){
		if(  (dagRank||defaultRank) && (dagReq||defaultReq) ){
			// Submission allowed - attributes management
			if (!dagRank){
				// missing Rank: Set from default
				dagad->set_generic(JDL::RANK,defaultRank->Copy());
			}
			if (!dagReq) {
				// missing Requiremtns: Set from default
				dagad->set_generic(JDL::REQUIREMENTS,defaultReq->Copy());
			}else if (defaultReq){
				// ExpDagAd already contains both Requirements and default
				// append default value
				PrettyPrint  unp;
				string buffer ;
				unp.Unparse(buffer,dagReq);
				buffer = "(" + buffer +") && (" ;
				unp.Unparse( buffer, defaultReq ) ;
				buffer+=")" ;
				ClassAdParser par ;
				ExprTree *expr =par.ParseExpression(buffer, true) ;
				if (expr != NULL){
					dagad->set_generic(JDL::REQUIREMENTS,expr->Copy());
				}else {
					throw  AdClassAdException (__FILE__ , __LINE__ ,
						METHOD, WMS_JDLSYN , "ClassAdParser::ParseExpression");
				}
			}
		} else {
			throw AdSemanticGroupException (__FILE__,__LINE__,METHOD,WMS_JDLMANDATORY,
				JDL::RANK+" " +JDL::REQUIREMENTS+" " + JDL::NODES_COLLOCATION);
		}
	}
	// Check For Errors (only on server SIDE):
	if (lookInto_b==WMPROXY){checkSandBox(isb, osb_nodes);}
	// Everything ok, set checked to true
	checked = true ;
	return jdls ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/****************************************
 get/set/has/del JobId Attribute methods:
*****************************************/
void ExpDagAd::createMap(){
	GLITE_STACK_TRY("ExpDagAd::createMap()");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		Ad ad ( *(iter->second.description_ad() ) ) ;
		if (ad.hasAttribute (JDL::JOBID)){
			// update njobid-nodes map
			map_nodes.insert(make_pair(ad.getString(JDL::JOBID),iter->first));
		} else {
			// JobId not yet initialized: unable to create Map
			throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLEMPTY,"jobid");
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
std::string ExpDagAd::jobid2node(const std::string &jobid){
	return (getJobIdMap())[jobid];
}
void ExpDagAd::delNodeAttribute (const glite::jobid::JobId &node,
	const std::string &attr_name ){
	delNodeAttribute(jobid2node(node.toString()),attr_name);
}
bool ExpDagAd::hasNodeAttribute ( const glite::jobid::JobId &node ,
	const std::string &attr_name ){
	return hasNodeAttribute(jobid2node(node.toString()) , attr_name);
}
//        SET NODE

void ExpDagAd::replaceNode (const glite::jobid::JobId &nodeId, NodeAd &nodeAd){
	replaceNode(jobid2node(nodeId.toString()),nodeAd);
}

void ExpDagAd::setNodeAttribute ( const glite::jobid::JobId &node,
	const std::string &attr_name , const std::string &attr_value) {
	setNodeAttribute (jobid2node(node.toString()) , attr_name, attr_value);
}
void ExpDagAd::setNodeAttribute (const glite::jobid::JobId &node,
	const std::string &attr_name,int &attr_value){
	setNodeAttribute (jobid2node(node.toString()) , attr_name, attr_value);
}
void ExpDagAd::setNodeAttribute (const glite::jobid::JobId &node,
	const std::string &attr_name,bool &attr_value){
	setNodeAttribute (jobid2node(node.toString()) , attr_name, attr_value);
}
void ExpDagAd::setNodeAttribute (const glite::jobid::JobId &node,
	const std::string &attr_name , const std::vector<std::string> &attr_value){
	setNodeAttribute(jobid2node(node.toString()), attr_name,attr_value);
}

//        GET NODE  <TYPE> [VALUE]


NodeAd ExpDagAd::getNode (const glite::jobid::JobId &nodeId){
	return getNode(jobid2node(nodeId.toString()));
}
std::vector< std::string > ExpDagAd::getNodeStringValue (const glite::jobid::JobId &node,
	const std::string &attr_name){
	return getNodeStringValue (jobid2node(node.toString()), attr_name);
}

int ExpDagAd::getNodeInt (const glite::jobid::JobId &node,
	const std::string &attr_name){
	return getNodeInt (jobid2node(node.toString()), attr_name);

}
bool ExpDagAd::getNodeBool (const glite::jobid::JobId &node,
	const std::string &attr_name){
	return getNodeBool (jobid2node(node.toString()), attr_name);

}


/****************************************
 get/set/has/del Node Attribute methods:
*****************************************/
bool ExpDagAd::hasNodeAttribute (const std::string &node,const std::string &attr_name){
	GLITE_STACK_TRY("ExpDagAd::hasNodeAttribute");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 )
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			Ad ad ( *(iter->second.description_ad() ) ) ;
			return ad.hasAttribute(attr_name);
		}
	}
	return false;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}


void ExpDagAd::replaceNode (const std::string &nodeName, NodeAd &nodeAd){
	GLITE_STACK_TRY("ExpDagAd::replaceNode(const std::string &nodeName, NodeAd &nodeAd)");
	// Check whether the node already exists:
	if ( !dagad->ad().Lookup(nodeName) ) {
		DAGNodeInfo replacing_node (*nodeAd.ad(),"edg_jdl");
		dagad->replace_node (nodeName, replacing_node );
	} else {
		// The NodeName already exists
		throw AdEmptyException (__FILE__, __LINE__, METHOD,
			WMS_JDLFULL,"Duplicated " + JDL::NODE_NAME +"("+nodeName+ ")");
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
NodeAd ExpDagAd::getNode (const std::string &nodeName){
	GLITE_STACK_TRY("ExpDagAd::getNode(const std::string &nodeName)");
	classad::ClassAd *cad = static_cast<classad::ClassAd *>(dagad->ad().Lookup(DAGAd::Attributes::NODES));
	cad = static_cast<classad::ClassAd *>(cad->Lookup(nodeName));
	// Check whether the node already exists:
	if (!cad){throw AdEmptyException (__FILE__,__LINE__,METHOD,WMS_JDLEMPTY,nodeName);}
	else{
		cad = static_cast<classad::ClassAd *>(cad->Lookup(DAGAd::Attributes::DESCRIPTION_AD));
		if(!cad){throw AdEmptyException (__FILE__,__LINE__,METHOD,WMS_JDLEMPTY,DAGAd::Attributes::DESCRIPTION_AD);}
		return NodeAd(*cad);

	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}


void ExpDagAd::setNodeAttribute ( const std::string &node , const std::string &attr_name , const std::string &attr_value) {
	GLITE_STACK_TRY("ExpDagAd::setNodeAttribute");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			const classad::ClassAd *cad = iter->second.description_ad() ;
			if (cad==0){ throw AdEmptyException (__FILE__ , __LINE__ ,METHOD,
					WMS_JDLFULL , iter->first);
			}
			classad::ClassAd *cadCopy =  static_cast<classad::ClassAd *>(cad->Copy());
			classad::Value v;
			v.Clear ();
			v.SetStringValue(attr_value);
			classad:ExprTree* tmp_expr = classad::Literal::MakeLiteral(v);
			cadCopy->Insert(attr_name, tmp_expr);
			DAGNodeInfo replacing_node (*cadCopy,"edg_jdl") ;
			dagad->replace_node (iter->first , replacing_node ) ;
			break;
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void ExpDagAd::setNodeAttribute (const std::string &node ,  const std::string &attr_name , const std::vector<std::string> &attr_value){
	GLITE_STACK_TRY("ExpDagAd::setNodeAttribute");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 )
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			Ad ad ( *(iter->second.description_ad() ) ) ;
			for (unsigned int j=0;j<attr_value.size();j++){
				ad.addAttribute (attr_name, attr_value[j]);
			}
			DAGNodeInfo replacing_node (*(ad.ad()),"edg_jdl") ;
			replacing_node.replace_description_ad( ad.ad() );
			dagad->replace_node (iter->first , replacing_node ) ;
			break;
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void ExpDagAd::setNodeAttribute (const std::string &node,const std::string &attr_name , int &attr_value){
	GLITE_STACK_TRY("ExpDagAd::setNodeAttribute");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 )
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			Ad ad ( *(iter->second.description_ad() ) ) ;
			ad.setAttribute (attr_name, attr_value);
			DAGNodeInfo replacing_node (*(ad.ad()),"edg_jdl") ;
			replacing_node.replace_description_ad( ad.ad() );
			dagad->replace_node (iter->first , replacing_node ) ;
			break;
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void ExpDagAd::setNodeAttribute (const std::string &node,const std::string &attr_name , bool &attr_value){
	GLITE_STACK_TRY("ExpDagAd::setNodeAttribute");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 )
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			Ad ad ( *(iter->second.description_ad() ) ) ;
			ad.setAttribute (attr_name, attr_value);
			DAGNodeInfo replacing_node (*(ad.ad()),"edg_jdl") ;
			replacing_node.replace_description_ad( ad.ad() );
			dagad->replace_node (iter->first , replacing_node ) ;
			break;
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

std::string ExpDagAd::getNodeAttribute ( const std::string &node , const std::string &attr_name ){
	return getNodeStringValue (node,attr_name)[0];
}
vector<string> ExpDagAd::getNodeStringValue(const string &node, const std::string &attr_name){
	GLITE_STACK_TRY("ExpDagAd::getNodeStringValue");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 ){
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			}
			NodeAd node ;
			node.fromString (Ad (*(iter->second.description_ad())).toString()) ;
			return node.getStringValue(attr_name);
		}
	}
	// Unable to find specified node name
	throw AdEmptyException (__FILE__,__LINE__,METHOD,WMS_JDLFULL,attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

int ExpDagAd::getNodeInt (const std::string &node,const std::string &attr_name){
	GLITE_STACK_TRY("ExpDagAd::getNodeInt");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 ){
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			}
			NodeAd node ;
			node.fromString (Ad (*(iter->second.description_ad())).toString()) ;
			return node.getInt(attr_name);
		}
	}
	// Unable to find specified node name
	throw AdEmptyException (__FILE__,__LINE__,METHOD,WMS_JDLFULL,attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
bool ExpDagAd::getNodeBool (const std::string &node,const std::string &attr_name){
	GLITE_STACK_TRY("ExpDagAd::getNodeBool");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 ){
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			}
			NodeAd node ;
			node.fromString (Ad (*(iter->second.description_ad())).toString()) ;
			return node.getBool(attr_name);
		}
	}
	// Unable to find specified node name
	throw AdEmptyException (__FILE__,__LINE__,METHOD,WMS_JDLFULL,attr_name);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void ExpDagAd::delNodeAttribute ( const std::string &node , const std::string &attr_name) {
	GLITE_STACK_TRY("ExpDagAd::remNodeAttribute");
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if (node.compare( iter->first) ==0){
			if ( iter->second.description_ad() ==0 )
				throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
			Ad ad ( *(iter->second.description_ad() ) ) ;
			ad.delAttribute ( attr_name ) ;
			DAGNodeInfo replacing_node (*(ad.ad()),"edg_jdl") ;
			replacing_node.replace_description_ad( ad.ad() );
			dagad->replace_node (iter->first , replacing_node ) ;
			break;
		}
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void ExpDagAd::getJobIdStruct (JobIdStruct &jobidStruct)
{
	GLITE_STACK_TRY("ExpDagAd::getJobIdStruct ()");
	using namespace glite::jobid;
	jobidStruct.jobid = JobId (get_edg_jobid( *dagad ) );
	jobidStruct.nodeName = NULL;
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for (iter = begin ; iter!= end ; iter ++){
		if ( iter->second.description_ad() ==0 )
			throw AdEmptyException (__FILE__ , __LINE__ ,METHOD, WMS_JDLFULL , iter->first);
		// Create the node jobid struct to be appended
		JobIdStruct *nodeJobIdStruct = new JobIdStruct ();
		Ad ad ( *(iter->second.description_ad() ) ) ;
		if(ad.hasAttribute(JDL::JOBID)){ nodeJobIdStruct->jobid=JobId(ad.getString(JDL::JOBID)); }
		else{ nodeJobIdStruct->jobid = JobId ();}
		nodeJobIdStruct->nodeName = new string (iter->first);
		jobidStruct.children.push_back(nodeJobIdStruct);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
std::vector< std::pair< std::string , classad::ExprTree* > > ExpDagAd::getSubAttributes ( const std::string &attr_value ){
	GLITE_STACK_TRY("ExpDagAd::getSubAttributes");
	std::vector < std::pair<std::string , ExprTree* > > result ;
	// Iterate over the NODES
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	Value val ;
	string jobid ;
	ExprTree* tree = NULL ;
	ClassAd* ad = NULL ;
	for ( iter = begin ; iter!= end ; ++iter){
		if ( iter->second.description_ad() !=0 ){
			ad = new ClassAd (*( iter->second.description_ad()) );
			tree = ad->Remove ( attr_value ) ;
			if (tree!= NULL){
				// Attribute Found. Now appending the pair (jobid , expression) to the result vector:
				if(ad->Lookup(JDL::JOBID)==NULL){
					throw AdSyntaxException ( __FILE__ , __LINE__ ,METHOD,
						WMS_DAG_CHECK , "Found non-initialized edg_jobid attribute ") ;
				}
				ad->EvaluateAttr (JDL::JOBID , val ) ;
				if ( val.IsStringValue(jobid)){
					result.push_back (pair<string, ExprTree*>(jobid,tree->Copy()));
				}
			}
		}else{
			throw AdSyntaxException(__FILE__,__LINE__,
				METHOD,WMS_DAG_CHECK,"Ad node not yet initialized. Perform nodes expansion first");
		}
	}
	return result ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

std::vector<std::string> ExpDagAd::getNodes(){
	std::vector<std::string> result ;
	// Iterate over the NODES
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	for ( iter = begin ; iter!= end ; ++iter){
		result.push_back(iter->first);
	}
	return result;
}


/**
* This Method is mainly used by evaluate method
* This Static Method takes a Value instance as input and
* iterates over its values resolving and evaluating
* the classad remote paths
*/
ExprTree* ExpDagAd::EvaluateValue (Value val, ExprList* list ) {
	const ExprList *el ;
	if (val.IsListValue( el )){
		Value appVal;
		// 1) Evaluate the list
		// passed value is a list of elements
		vector<ExprTree*> vectList ;
		el->GetComponents(vectList) ;
		for ( unsigned int i = 0; i< vectList.size() ; i++){
			// Evaluate Elements of the list
			if (vectList[i]->Evaluate(appVal)){
				// Evaluation succeded
				if(!appVal.IsUndefinedValue()){
					// appending one expression to the other (if not undefined)
					vectList[i]=EvaluateValue(appVal,list)->Copy();
				}
			}
		}
		// 2) Check what happened so far (empty
		// flatten flag is active:
		if (list!=NULL){return list;}
		// One size vector: return one element
		else if ( vectList.size()==1 ){return vectList[0];}
		// more-than-one size vector: return list
		else { return ExprList::MakeExprList(vectList);}
	} else if (list!=NULL){
		// There is a flatten list to be appended
		list->push_back(Literal::MakeLiteral(val));
		return list ;
	} else {
		return Literal::MakeLiteral(val);
	}
}


/**
* Replace the desired string with the new one
* paying attention not to perform operation twice
* this method is used by orderNodes
*/
ExprTree* replaceExprvalue(ExprTree *tree, const std::string &src, const std::string dst){
	PrettyPrint  unp;
	unp.SetClassAdIndentation(0);
	unp.SetListIndentation(0);
	string buf;
	unp.Unparse(buf, tree);

	// Case Insensitive string representation
	const string lowSrc=glite_wms_jdl_toLower(src);
	const string lowDst=glite_wms_jdl_toLower(dst);
	string lowBuf=glite_wms_jdl_toLower(buf);

	// Using boost::algorithm to replace lowSrc with lowDst in lowBuf
	replace_all(lowBuf, lowSrc, lowDst);

	// delete tree;
	ClassAdParser par ;
	buf = lowBuf;
	return par.ParseExpression(buf, true);
}

bool hasExpression(const ExprTree *tree){
	PrettyPrint  unp;
	unp.SetClassAdIndentation(0);
	unp.SetListIndentation(0);
	string buffer ;
	// write tree inside buffer
	unp.Unparse(buffer, tree);
	switch (tree->GetKind()){
		case ExprTree::CLASSAD_NODE:
			// const ClassAd *classAd= static_cast<const classad::ClassAd*>(tree);
			// ClassAd case TBD TBimplemented
			AdSyntaxException(__FILE__,__LINE__,"hasExpression",WMS_DAG_CHECK,
				"ClassAd case: not allowed");
			// TBD
			return true;
			break;
		case ExprTree::LITERAL_NODE:
			return false;
			break;
		case ExprTree::EXPR_LIST_NODE:{
			const ExprList *nodeList = static_cast<const classad::ExprList*>(tree);
			ExprListIterator iter (nodeList);
			while(!iter.IsAfterLast()){
				// cp.Unparse( buffer,iter.CurrentExpr()) ;
				if (hasExpression(iter.CurrentExpr())){ return true; }
				// result.push_back(buffer);
				// buffer="";
				iter.NextExpr( );
			}
			// self iterate over the list
			break;
		}
		case ExprTree::ATTRREF_NODE:
			// i.e.: root.inputsandbox
		case ExprTree::OP_NODE:
			// i.e.: root.inputsandbox[0]
		case ExprTree::FN_CALL_NODE:
			// i.e.: TBD
			return true;
			break;
		default: // Should never arrive here
			AdSyntaxException(__FILE__,__LINE__,"hasExpression",WMS_DAG_CHECK,
				"hasExpression unreachable field reached");
			break;
	}
	// NO expression found so far
	return false;
}


/**
* Iterate over the nodes and order their names
* first nodes will be expression-free
* last nodes will need a further evaluation
* returned vector will contain ordered iterator to Nodes
* TBD at the moment Expression are only seeked inside ISB
*/
std::vector<DAGAd::node_iterator> ExpDagAd::orderNodes(){
	GLITE_STACK_TRY("ExpDagAd::orderNodes")
	DAGAd::node_iterator begin, end , iter;
	boost::tie ( begin, end )= dagad->nodes() ;
	ExprTree *isb =NULL;
	ClassAd *classAd = NULL ;
	Value val ;
	string s_tmp ;
	// TBD attr name custom
	// const string attr_name = JDL::INPUTSB ;
	vector<DAGAd::node_iterator> orderedNodes;
	bool expressionNode_b;
	// iterate over the classad nodes to replace OSB values and check for expression type
	for (iter = begin ; iter!= end ; iter++){
		expressionNode_b = false;
		classAd = new ClassAd (*(iter->second.description_ad()));
		isb = classAd->Lookup(JDL::INPUTSB); // NEW APPROACH
		if ( isb!=NULL ){
			if (hasExpression(isb)){
				expressionNode_b = true;
				// TBD check when evaluate is half successful:
				// note evaluated expression forgotten?
				isb=replaceExprvalue(isb, JDL::OUTPUTSB, JDL::OSB_DEST_URI); // output of replace directly inside Insert
				ExprTree* tmp_expr = isb->Copy(); //TBD Copy needed?
				classAd->Insert (JDL::INPUTSB, tmp_expr);
				// Replacing the node:
				DAGNodeInfo replacing_node (*classAd,"edg_jdl")  ;
				replacing_node.replace_description_ad( classAd ) ;
				dagad->replace_node(iter->first, replacing_node) ;
			}
		}
		if (expressionNode_b){orderedNodes.push_back(iter);}
		else {orderedNodes.insert(orderedNodes.begin(),iter);}
	}
	return orderedNodes;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

void ExpDagAd::checkSandBox( std::vector < std::pair<std::string , isb_value > >& isb , Ad& osb_nodes ){
	GLITE_STACK_TRY("ExpDagAd::checkSandBox");
	std::vector < std::pair<std::string , isb_value > >::iterator iter ;
	isb_value::iterator it_val ;
	string buffer , osb_node , osb_file ;
	bool osb_found ;
	vector <string> osb_files ;
	string finalMsg = "" ;
	string ISB_SEP = "_" ;
	// used for ExprTree parsing:
	ClassAdUnParser cp ;
	for (iter = isb.begin() ; iter!= isb.end() ; iter++){
		// Iterate over the nodes inputSandbox
		// The father id string is iter->first ;
		// The inputSandbox Exptree* value is iter->second
		for (it_val = iter->second.begin(); it_val != iter->second.end(); it_val++ ){
			// Now it_val points to a single ISB value in the form:
			// <node name>_<osb value>
			// saved as a ExprTree*
			buffer = "" ;
			cp.Unparse(buffer, (*it_val)->Copy() );
			int isb_sep = buffer.find( ISB_SEP );
			if ( isb_sep>(int)buffer.size() ){
				finalMsg+=iter->first + " -> separator not found\n" ;
			}else{
				//Split the inputSandbox into NODE - VALUE:
				osb_node = buffer.substr(0 ,isb_sep ) ;
				osb_file = buffer.substr(isb_sep+1 , buffer.size()-isb_sep-1) ;
				if (osb_nodes.hasAttribute(osb_node)){
					try{
						// Retrieve OutputSandbox of the NODE
						osb_found = false ;
						osb_files =osb_nodes.getStringValue(osb_node) ;
						// Look for the VALUE in the outputsandbox of the NODE:
						for ( unsigned int i = 0 ; i<osb_files.size() ; i++ ){
							if (osb_files[i]== osb_file){
								osb_found = true ;
							}
						}
						if (osb_found ){
							// outputSandbox found. Check Dependencies...
							if (!parent_child(*dagad , osb_node , iter->first ) )
								finalMsg+= iter->first + " -> failed dependency with " + buffer + "\n";
						} else {
							finalMsg+=iter->first+" -> unable to find '"+
							osb_file+"' in "+osb_node+" sandbox output files\n";
						}
					}catch (Exception &exc){
						cerr <<"WARNING!! check sandbox problem:" << exc.printStackTrace() <<endl ;
						finalMsg+=iter->first + " -> unable to retrieve " + osb_node + " output files\n" ;
					}
				}
			}
		}
	}
	if ( !finalMsg.empty() ){
		throw AdSyntaxException (__FILE__,__LINE__,METHOD,WMS_DAG_CHECK,finalMsg);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

// WARNING MANAGEMENT
bool  ExpDagAd::hasWarnings(){
	return warning_messages_v.size()!=0;
}
std::vector<std::string>  ExpDagAd::getWarnings(){
	return warning_messages_v;
}
void  ExpDagAd::addWarning(const std::string &msg){
	warning_messages_v.push_back(msg);
}
void ExpDagAd::addWarnings(const std::string &nodeName, Ad *ad){
	if (ad->hasWarnings()){
		std::vector<std::string> warnings=ad->getWarnings();
		std::vector<std::string>::iterator it = warnings.begin();
		std::vector<std::string>::iterator end = warnings.end();
		for (;it!=end; ++it){
			addWarning(nodeName+"-> "+*it);
		}
	}
}

} // jdl namespace
} // glite namespace

//EOF


