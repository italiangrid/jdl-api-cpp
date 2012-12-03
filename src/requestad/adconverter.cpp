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
*  filename  : adconverter.cpp
*  author    : Alessandro Maraschini <alessandro.maraschini@datamat.it>
*  copyright : (C) 2004 by DATAMAT
***************************************************************************/
#include "adconverter.h"
#include "JobAd.h"
#include "jdl_attributes.h"
#include "JDLAttributes.h"
#include "PrivateAttributes.h"  // ZIPPED_ISB needed
#include "RequestAdExceptions.h"
#include "DAGAdManipulation.h"
#include "exception_codes.h"
#include "grammar.h"
#include "glite/wmsutils/classads/classad_utils.h"
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <glob.h>
using namespace classad ;
using namespace glite::wmsutils::classads ;
using namespace std ;
namespace fs = boost::filesystem;

namespace glite {
namespace jdl {
const string AdConverter::VALUES = "Parameters" ;
const string AdConverter::PARAMETER_VALUE = "ParameterValue" ;
const string AdConverter::PARAMETRIC_START="ParameterStart";
const string AdConverter::PARAMETRIC_STEP ="ParameterStep";
const string AdConverter::VALUE = "_PARAM_" ;
const string AdConverter::NODE = "Node_" ;
const string AdConverter::SIMPLE_NODE_TYPE= "edg-jdl" ;
const int DEFAULT_STEPS=4;

/*********************************************
*  replace the old string with the new one
*********************************************/
string replace ( const string& source , const string& s_old ,const string& s_new ) {
	string result = source ;
	while (result.find (s_old )<result.length()){
		result.replace (  result.find (s_old )  , s_old.length() , s_new );
	}
	return result ;
}

/*********************************************
*  Check Dagad syntax unallowed node names
*********************************************/
string checkNodeName(const string &nodeName){
	string result= replace(nodeName,".","_");
	result=replace(result,"/","I");
	result=replace(result,"*","-");
	result=replace(result,"$","_S_");
	// Eventually return result
	return result;
}

/*********************************************
* list2nodes - create dagad nodes attribute from a list of classads
* Used by createDagAdFromPath & collection2dag
*********************************************/
void list2nodes (ClassAd &nodes, std::vector<ExprTree*> list){
	GLITE_STACK_TRY("AdConverter::collection2dag");
	Value val;
	for (unsigned int i = 0 ; i < list.size() ; i++){
		if ( list[i]->GetKind() != ExprTree::CLASSAD_NODE ){
			throw AdMismatchException (__FILE__,__LINE__ ,
				METHOD,WMS_JDLMISMATCH,DAGAd::Attributes::NODES);
		}
		// Parsing / Initialising Node Name
		string nodeName = "";
		ClassAd * node = static_cast<classad::ClassAd*>(list[i]);
		if (node->Lookup (JDL::NODE_NAME)){
			(node->Lookup(JDL::NODE_NAME))->Evaluate(val);
			node->Remove(JDL::NODE_NAME);
			if (val.IsStringValue(nodeName)){
				// Cut classads unallowed char
				nodeName = checkNodeName(nodeName);
			}else{
				nodeName=AdConverter::NODE +  boost::lexical_cast<std::string>(i);
			}
			// If this point is reached nodeName is definitely a string
		}else{
			nodeName=AdConverter::NODE +  boost::lexical_cast<std::string>(i);
		}
		// Build the node with its mandatory attributes (description, node_type, nodeName)
		ClassAd nod ;
		nod.Insert (DAGAd::Attributes::DESCRIPTION_AD , node->Copy());
		val.SetStringValue(AdConverter::SIMPLE_NODE_TYPE);
		nod.Insert (DAGAd::Attributes::NODE_TYPE , Literal::MakeLiteral (val)) ;
		if (nodes.Lookup(nodeName)){
			// The NodeName already exists
			throw AdEmptyException (__FILE__, __LINE__, METHOD,
				WMS_JDLFULL,"Duplicated " + JDL::NODE_NAME +"("+nodeName+ ")");
		}
		nodes.Insert (nodeName, nod.Copy() ) ;
	}
	// Final Checks:
	if (!nodes.size()){
		// no nodes created
		throw AdEmptyException (__FILE__, __LINE__, METHOD,
			WMS_JDLEMPTY,DAGAd::Attributes::NODES);
	}
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}

/*********************************************
*NodeStruct default constructor
*********************************************/
NodeStruct::NodeStruct()
{
  // Reset the Node name
  this->name = NULL;
}

/*********************************************
*NodeStruct default constructor
*********************************************/
NodeStruct::NodeStruct(std::string* name){
  // Set the Node name
  this->name = name;
};

/******************************************************************
*NodeStruct copy constructor
*******************************************************************/
NodeStruct::NodeStruct(const NodeStruct &node)
{
  // Copy the Node name 
  name = node.name;

  // Retrieve the children vector
  std::vector<NodeStruct*> tempChildrenNodes = node.childrenNodes;

  // Retrieve the Iterator of the children and the last child	
  std::vector<NodeStruct*>::iterator childrenIterator =  tempChildrenNodes.begin();
  std::vector<NodeStruct*>::iterator lastChild = tempChildrenNodes.end();

  // Scan all the available children and copy the Vector
  while(childrenIterator < lastChild)
  {
    // Create a new Child
    NodeStruct* newChild = new NodeStruct();

    // Copy the child		
    *newChild = *((NodeStruct *)*childrenIterator);
    
    // Add the new Child to the vector
    childrenNodes.push_back(newChild);
  
    // Move to the next child
    childrenIterator++;
  }

}

/******************************************************************
 *NodeStruct destructor
*******************************************************************/
NodeStruct::~NodeStruct()
{
  // Free the memory allocated
  flushMemory();
}

/******************************************************************
 *NodeStruct operator=
*******************************************************************/
NodeStruct& NodeStruct::operator=(const NodeStruct& node)
{ 
  // Perform the assign if the node is NOT 'this'
  if (this != &node) {

    // Free the memory allocated
    flushMemory();
  
    // Copy the Node name 
    name = node.name;

    // Retrieve the children vector
    std::vector<NodeStruct*> tempChildrenNodes = node.childrenNodes;

    // Retrieve the Iterator of the children and the last child	
    std::vector<NodeStruct*>::iterator childrenIterator =  tempChildrenNodes.begin();
    std::vector<NodeStruct*>::iterator lastChild = tempChildrenNodes.end();

    // Scan all the available children and copy the Vector
    while(childrenIterator < lastChild)
    {
      // Create a new Child
      NodeStruct* newChild = new NodeStruct();

      // Copy the child		
      *newChild = *((NodeStruct *)*childrenIterator);
    
      // Add the new Child to the vector
      childrenNodes.push_back(newChild);
    
      // Move to the next child
      childrenIterator++;
    }

  }
  
  // Return the copied Node
  return *this; 
}

/******************************************************************
 *NodeStruct flushMemory method
*******************************************************************/
void NodeStruct::flushMemory(void)
{
  // Check if the Job has children
  if(childrenNodes.size() > 0) {
    // Retrieve the Iterator of the children and the last child	
    std::vector<NodeStruct*>::iterator childrenIterator = childrenNodes.begin();
    std::vector<NodeStruct*>::iterator lastChild = childrenNodes.end();

    // Scan all the available children and free the memory
    while(childrenIterator < lastChild)
    {
      // Retrieve a child	   
      NodeStruct *currentChild = (NodeStruct *)*childrenIterator;

      // Delete the current child
      delete(currentChild);
    
      // Move to the next child
      childrenIterator++;
    }

  } 
  
  // Clean the vector
  childrenNodes.clear();

}


/*********************************************
*   createJobTemplate
*********************************************/
JobAd* AdConverter::createJobTemplate ( int  type , const std::string &executable, const std::string &arguments,
	const std::string &requirements, const std::string &rank , const std::string &vo ){

	GLITE_STACK_TRY("AdConverter::createJobTemplate") ;
	// Initialise JobAd:
	JobAd *jobad = new JobAd () ;
	jobad->setAttribute( JDL::EXECUTABLE , executable );
	if (arguments!= "" ) jobad->setAttribute( JDL::ARGUMENTS , arguments ) ;
	if (vo!="") jobad->setAttribute( JDL::VIRTUAL_ORGANISATION , vo ) ;
	jobad->setAttributeExpr( JDL::RANK , rank );
	jobad->setAttributeExpr( JDL::REQUIREMENTS , requirements );
	// check The Jobtype
	if ( type & ADCONV_JOBTYPE_PARAMETRIC ) {
			vector<std::string> parametrised;
			parametrised.push_back(JDL::ARGUMENTS);
			parametrised.push_back(JDL::STDINPUT);
			// Special case: merge existing attriubtes with created ones
			jobad->merge(*createIntParametricTemplate(parametrised,DEFAULT_STEPS,0,1,requirements,rank,vo));
	}
	if ( type & ADCONV_JOBTYPE_PARTITIONABLE ){
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH ,
			JDL::JOBTYPE, "Partitionable jobs have been deprecated!" );
		/*
		jobad->addAttribute (JDL::JOBTYPE, string(JDL_JOBTYPE_PARTITIONABLE));
		jobad->setAttribute (JDL::CHKPT_CURRENTSTEP, 0);
		jobad->setAttribute (JDL::CHKPT_STEPS, DEFAULT_STEPS);
		JobAd prepost = *jobad;
		prepost.addAttribute(JDL::JOBTYPE, string(JDL_JOBTYPE_CHECKPOINTABLE ));
		jobad->setAttribute(JDL::POSTJOB, &prepost);
		jobad->setAttribute(JDL::PREJOB, &prepost);
		*/
	}
	if ( type & ADCONV_JOBTYPE_CHECKPOINTABLE ){
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH ,
			JDL::JOBTYPE, "Checkpointable jobs have been deprecated!" );
		/*
		jobad->addAttribute (  JDL::JOBTYPE  , string(JDL_JOBTYPE_CHECKPOINTABLE )  ) ;
		jobad->setAttribute (JDL::CHKPT_CURRENTSTEP , 0 ) ;
		jobad->setAttribute (JDL::CHKPT_STEPS ,  DEFAULT_STEPS ) ;
		*/
	}
	if ( type & ADCONV_JOBTYPE_INTERACTIVE ) {
		jobad->addAttribute (  JDL::JOBTYPE  , string(JDL_JOBTYPE_INTERACTIVE )  ) ;
		jobad->addAttribute ( JDL::SHPORT  , 0 ) ;
	}
	if ( type & ADCONV_JOBTYPE_MPICH ) {
		jobad->addAttribute (  JDL::JOBTYPE  , string(JDL_JOBTYPE_MPICH )  ) ;
		jobad->addAttribute (  JDL::CPUNUMBER, 2 ) ;
	}
	return jobad ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*********************************************
*  PARAMETRIC JOBS
*********************************************/
JobAd* createParametricTemplate (std::vector<std::string> parametrised ,const std::string &requirements,
	const std::string &rank , const std::string &vo ) {

	JobAd *parametric = new JobAd() ;
	// Add parametrised attributes:
	for (unsigned int i = 0 ; i< parametrised.size() ; i++){
		parametric->setAttribute (parametrised[i], AdConverter::VALUE);
	}
	// Add default attributes:
	parametric->setAttributeExpr( JDL::REQUIREMENTS , requirements );
	parametric->setAttributeExpr( JDL::RANK , rank );
	if (vo!="") parametric->setAttribute( JDL::VIRTUAL_ORGANISATION , vo ) ;
	parametric->addAttribute (JDL::JOBTYPE, string(JDL_JOBTYPE_PARAMETRIC));
	return parametric ;
}
// DEPRECATED
JobAd* createParametricTemplate (int parametrised ,const std::string &requirements,
	const std::string &rank , const std::string &vo ) {

	JobAd *parametric = new JobAd() ;
	// Add parametrised attributes:
	if (parametrised & AdConverter::ADCONV_ATTR_INPUTSB) {
		parametric->setAttribute (JDL::INPUTSB,AdConverter::VALUE);
	}if (parametrised &AdConverter::ADCONV_ATTR_INPUTDATA) {
		parametric->setAttribute (JDL::INPUTDATA,AdConverter::VALUE);
	}if (parametrised &AdConverter::ADCONV_ATTR_ARGUMENTS) {
		parametric->setAttribute (JDL::ARGUMENTS,AdConverter::VALUE);
	}
	// Add default attributes:
	parametric->setAttributeExpr( JDL::REQUIREMENTS , requirements );
	parametric->setAttributeExpr( JDL::RANK , rank );
	if (vo!="") parametric->setAttribute( JDL::VIRTUAL_ORGANISATION , vo ) ;
	return parametric ;
}
JobAd* AdConverter::createStringParametricTemplate( std::vector<std::string> parametrised,
	std::vector<std::string> parameters , const std::string &requirements,
	const std::string &rank , const std::string &vo ) {

	JobAd *parametric = createParametricTemplate (parametrised , requirements, rank , vo );
	for (unsigned int i = 0 ; i< parameters.size() ; i++) {
		parametric->addAttribute (VALUES , parameters[i] );
	}
	return parametric ;
}
// DEPRECATED
JobAd* AdConverter::createStringParametricTemplate(int parametrised, std::vector<std::string> parameters,
	const std::string &requirements, const std::string &rank , const std::string &vo ) {

	JobAd *parametric = createParametricTemplate (parametrised , requirements, rank , vo );
	for (unsigned int i = 0 ; i< parameters.size() ; i++) {
		parametric->addAttribute (VALUES , parameters[i] );
	}
	return parametric ;
}
JobAd* AdConverter::createIntParametricTemplate(std::vector<std::string> parametrised, int param_number,
	int param_start , int param_step , const std::string &requirements,
	const std::string &rank , const std::string &vo ) {

	JobAd *parametric = createParametricTemplate (parametrised , requirements, rank , vo );
	parametric->setAttribute(VALUES , param_number);
	parametric->setAttribute(PARAMETRIC_START , param_start);
	// Division by zero not allowed
	if (param_step == 0) {
		throw AdSyntaxException (__FILE__,__LINE__,"createIntParametricTemplate",
				WMS_JDLPARSE , "JDL Attribute ParameterStep must be different from zero, division by zero not allowed");
	} else {
		parametric->setAttribute(PARAMETRIC_STEP , param_step);
	}
	return parametric ;
}
// DEPRECATED
JobAd* AdConverter::createIntParametricTemplate( int parametrised ,int param_number , int param_start , int param_step , const std::string &requirements, const std::string &rank , const std::string &vo ) {
	JobAd *parametric = createParametricTemplate (parametrised , requirements, rank , vo );
	parametric->setAttribute(VALUES , param_number);
	parametric->setAttribute(PARAMETRIC_START , param_start);
	parametric->setAttribute(PARAMETRIC_STEP , param_step);
	return parametric ;
}
/*********************************************
*  static method: addDependencies
*********************************************/
void addDependencies (DAGAd *p_dag , string *name, std::vector< NodeStruct* > childrenNodes ){
	for (unsigned int i = 0 ; i<childrenNodes.size() ; i++) {
		if (name) {p_dag->add_dependency ( *name , *(childrenNodes[i]->name));}
		if (childrenNodes[i]->name){
			addDependencies ( p_dag ,  childrenNodes[i]->name , childrenNodes[i]->childrenNodes) ;
		}
	}
}
/*********************************************
*  static method: addNodes
*********************************************/
void addNodes (DAGAd *p_dag , const ClassAd &node,NodeStruct *dependencies){
	if ( dependencies->name!=NULL ) {
		// node name not NULL
		p_dag->add_node (*(dependencies->name)  , DAGNodeInfo ( *( static_cast<classad::ClassAd*>(node.Copy()))  )  );
	}
	for (unsigned int i = 0 ; i<dependencies->childrenNodes.size() ; i++) {
		if (dependencies->childrenNodes[i]){
			addNodes (p_dag ,node ,dependencies->childrenNodes[i]) ;
		}
	}
}
/*********************************************
*   createDAGTemplate
*********************************************/
ExpDagAd* AdConverter::createDAGTemplate ( NodeStruct dependencies , const std::string &requirements,
	const std::string &rank , const std::string &vo ){

	GLITE_STACK_TRY("AdConverter::createDAGTemplate") ;
	// simple NodeAd template
	Ad ad ;
	Value val ;
	ad.setAttributeExpr( JDL::RANK , rank );
	ad.setAttributeExpr( JDL::REQUIREMENTS , requirements );
	ad.setAttribute (JDL::EXECUTABLE , string("<put executable path>") ) ;

	// Create a node to be copied n times (one for each node)
	ClassAd node = *ad.ad();
	val.SetStringValue ( SIMPLE_NODE_TYPE  ) ;
	node.Insert ( DAGAd::Attributes::NODE_TYPE , Literal::MakeLiteral (val)  ) ;
	node.Insert ( DAGAd::Attributes::DESCRIPTION_AD ,  (ad.ad())->Copy() );

	DAGAd *p_dag = new DAGAd( ) ;
	if (!dependencies.childrenNodes.size()){
		// No nodes /dependencies require
		throw AdSyntaxException (__FILE__,__LINE__,METHOD,WMS_JDLSYN,"Empty NodeStruct given");
	}
	addNodes (p_dag , node, &dependencies );
	addDependencies ( p_dag , dependencies.name , dependencies.childrenNodes );
	if (vo!="") set_virtual_organisation ( *p_dag , vo ) ;
	return new ExpDagAd(p_dag) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*********************************************
* createCollection: given an exprlist
*********************************************/
CollectionAd* createCollection (ExprList *list, const std::string &vo) {
	const string COLLECTION_TYPE = "collection" ;
	// Insert the nodes
	CollectionAd *collection = new CollectionAd ();
	collection->setAttributeExpr ( DAGAd::Attributes::NODES , list );
	// insert the Type = "Collection"
	collection->setAttribute ( JDL::TYPE , COLLECTION_TYPE) ;
	// Insert the VirtualOrganisation
	if (vo!="") collection->setAttribute ( JDL::VIRTUAL_ORGANISATION , vo ) ;
	return collection;
}
/*********************************************
* createCollectionTemplate
*********************************************/
CollectionAd* AdConverter::createCollectionTemplate ( unsigned int jobNumber ,const std::string &requirements,
	const std::string &rank , const std::string &vo ){
	GLITE_STACK_TRY("AdConverter::createCollectionTemplate");
	NodeAd jobad ; // is a job template and will be copied n times
	if (vo!="") jobad.setAttribute( JDL::VIRTUAL_ORGANISATION , vo ) ;
	jobad.setAttributeExpr( JDL::RANK , rank );
	jobad.setAttributeExpr( JDL::REQUIREMENTS , requirements );
	jobad.setAttribute (JDL::EXECUTABLE,string("<put executable path>"));
	ExprList *list = new ExprList ();
	Value val;
	for (unsigned int i = 0 ; i < jobNumber ; i++){
		// Inserting Node Name
		ClassAd * ad = jobad.ad();
		val.SetStringValue (AdConverter::NODE+boost::lexical_cast<std::string>(i));
		ad->Insert(JDL::NODE_NAME, Literal::MakeLiteral (val));
		list->push_back (ad);
	}
	return createCollection (list ,vo ) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*********************************************
* loadAdsFromPath: extract all files corresponding to the given
* regular expression, and for each corresponding value try and load a classad
* return the list (as an ExprList) of all classads loaded/created
*********************************************/
ExprList* loadAdsFromPath ( const std::string &path ){
	GLITE_STACK_TRY("loadAdsFromPath");
	ExprList *list = new ExprList () ;  // will contain all successfully parsed classads
	glob_t *pglob ;
	NodeAd jobad ;
	pglob = (glob_t *) malloc (sizeof(glob_t)) ;
	// Retrieve files from regular expression path:
	int gl = glob(path.c_str(),GLOB_ERR,NULL,pglob);
	if (gl!=0) {
		 throw AdSemanticPathException (__FILE__ , __LINE__ ,
		 	"loadAdsFromPath ( const std::string &path )", WMS_JDLMISMATCH, "path" , path);
	}
	for (unsigned int i=0 ; i< pglob->gl_pathc ; i++){
		try{
			jobad.clear() ;
			// Try load & parse classad:
			jobad.fromFile (pglob->gl_pathv[i]);
			// Inserting NodeName (if necessary):
			if (!jobad.hasAttribute(JDL::NODE_NAME)){
				// fs::path cp(pglob->gl_pathv[i], fs::system_specific);  // boost 1.29
				fs::path cp(pglob->gl_pathv[i], fs::native);  // upgrade to boost 1.32

				jobad.setAttribute(JDL::NODE_NAME, checkNodeName(AdConverter::NODE + cp.leaf()));
			}
			list->push_back ( jobad.ad()  ) ;
		}catch (glite::wmsutils::classads::CannotParseClassAd  &exc) {
			// It is not a classad
			jobad.addWarning("No valid ClassAd found in the path specified");
		}
	}
	// Final Checks:
	if (!list->size()){
		jobad.addWarning("The path specified is empty");
		throw AdSemanticPathException (__FILE__ , __LINE__,
			METHOD, WMS_JDLMANDATORY,"",path); 
	}
	return list ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*********************************************
* createCollectionFromPath
*********************************************/
CollectionAd* AdConverter::createCollectionFromPath ( const std::string &path, const std::string &vo ) {
	GLITE_STACK_TRY("AdConverter::createCollectionFromPath");
	return createCollection ( loadAdsFromPath ( path )  ,vo  ) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*********************************************
* createDagAdFromPath - as an Ad instance, with empty dependency
*********************************************/
Ad* AdConverter::createDagAdFromPath (const std::string &path, const std::string &vo){
	ClassAd nodes ;
	std::vector<ExprTree*> exprTreeVect;
	// Parse the path and load all matching classads into exprTreeVect:
	loadAdsFromPath(path)->GetComponents(exprTreeVect);
	// Create the dag NODES attribute from the list of classads:
	list2nodes(nodes,exprTreeVect);
	// Insert Empty Dependencies (exception thrown otherwise)
	nodes.Insert ( DAGAd::Attributes::DEPENDENCIES , new ExprList () ) ;
	// Create an Ad instance which represents the dag
	Ad *dagad = new Ad();
	dagad->setAttributeExpr(DAGAd::Attributes::NODES, nodes.Copy());
	dagad->setAttribute(JDL::TYPE,JDL_TYPE_DAG);
	if (vo!=""){dagad->setAttribute(JDL::VIRTUAL_ORGANISATION,vo);}
	return dagad;
}
/*********************************************
* createDagAdFromPath - as a ExpDagAd instance, with specified dependency
*********************************************/
ExpDagAd* AdConverter::createDagAdFromPath (NodeStruct dependencies, const std::string &path, const std::string &vo){
	DAGAd *p_dag = new DAGAd(*(createDagAdFromPath(path,vo)->ad()));
	addDependencies ( p_dag , dependencies.name , dependencies.childrenNodes );
	return new ExpDagAd (p_dag);
}

/*********************************************
* static method: Expr2List
* Parses an expression and generate a list of string values
* it works even if it is a list of int (for parametric jobs)
* WARNING: this method is recoursive
* used by splitBulkAttribute, splitIsbAttribute, removeBulkAttribute, bulk2dag
*********************************************/
void Expr2List (const classad::ExprTree *param, std::vector<string> &result, bool flatten=false){
	Value val ;
	PrettyPrint  cp ;
	string buffer="" ;
	const ExprList *el;
	int i_param;
	string s_param;
	if (param ==NULL){
		throw AdEmptyException(__FILE__,__LINE__,"Expr2List",WMS_JDLEMPTY,AdConverter::VALUES);
	}
	if  (param->Evaluate (val)){
		if (  val.IsListValue(el) ){
			// It is a list: iterate over its values recoursively
			ExprListIterator iter (el);
			while(!iter.IsAfterLast()){
				// Checks if the current Expr in the list is an integer
				Value tmp ;
				iter.CurrentExpr()->Evaluate(tmp) ;
				if( tmp.IsIntegerValue()) {
					// Converts the int in the list in a string: append the result
					cp.Unparse( buffer, iter.CurrentExpr() );
					result.push_back(buffer) ;
					buffer="" ;
				} else {
					// Recoursive call
					Expr2List(iter.CurrentExpr(),result, flatten);
				}
				iter.NextExpr( );
			}
		}else if (val.IsIntegerValue(i_param)){
			// It's an integer: append the result (converted into a string)
			for (int i = 0 ; i< i_param; i++){
				result.push_back( boost::lexical_cast<std::string>(i) );
			}
		}else if (flatten && val.IsStringValue(s_param)){
			// It's only a string (not flattened): append to result
			result.push_back(s_param);
		}else{
			// It's either a string flattened or anything else: append its string representation
			cp.Unparse( buffer, param );
			result.push_back(buffer) ;
			buffer="" ;
		}
	} else{
		// The expression is not evaluated
	}
}
/*********************************************
* removeInt return the value corresponding to the specified attribute for a given Ad instance
* if present, definitely remove the attribute
* if not present, just return default value
*********************************************/
int removeInt (Ad *ad , const string& attr_name , int default_value ){
	int result = default_value ;
	if (ad->hasAttribute (attr_name)){
		result = ad->getInt( attr_name);
		ad->delAttribute(attr_name) ;
	}
	return result ;
}
/*********************************************
* splitBulkAttribute separate the attribute into parametrized and not
* adParametric collects parametrized (i.e. contain _PARAM_) value(s)
* adStatic collects static (i.e. do not contain _PARAM_)  value(s)
* if paramAllowed is false, the specified attribute SHOULD be static: Warning appended
*********************************************/
void splitBulkAttribute(const std::string & attr_name, Ad *adParametric, Ad * adStatic, bool paramAllowed=true){
	if (!adParametric->hasAttribute (attr_name) ) {return;}
	std::vector<string> values;
	// Parses the attribute and generate a list of string values
	Expr2List(adParametric->delAttribute(attr_name), values,true);
	bool listv=(values.size()>1);  // indicate whether to set or to add
	for (unsigned int i = 0;i<values.size(); i++){
		if(values[i].find(AdConverter::VALUE)==string::npos){
			// parameter NOT found, store in the adStatic
			if (listv){adStatic->addAttribute(attr_name, values[i]);}
			else {adStatic->setAttribute(attr_name, values[i]);}
		}else{
			// Parameter found, leave in the list
			if (listv){adParametric->addAttribute(attr_name, values[i]);}
			else {adParametric->setAttribute(attr_name, values[i]);}
		}
	}

	if (!paramAllowed && adParametric->hasAttribute(attr_name)){
		// This attribute SHOULDN'T be parametric: Warning Appended
		adStatic->addWarning(attr_name+": Found parametric value for non-parametric attribute");
	}
}

/*********************************************
* splitIsbAttribute separate InputSandbox attribute into parametric, static and path-parametrized
* ISB_BASE_URI value will affect this selection with the following logic:
* adParametric collects:
	- parametrized ISB simple name (path not parametrized) AND non-parametrized ISB_BASE_URI
* adStatic collects:
	- non-parametrized ISB AND non-parametrized ISB_BASE_URI
* adPathametric collects:
	- non-parametrized ISB  AND parametrized ISB_BASE_URI
	- parametrized ISB path AND non-parametrized ISB_BASE_URI
*********************************************/
void splitIsbAttribute(Ad *adParametric, Ad *adStatic, Ad *adPathametric){
	const string attr_name = JDL::INPUTSB;
	splitBulkAttribute(JDL::ISB_BASE_URI,adParametric,adStatic);
	const bool parametricISBbaseUri = adParametric->hasAttribute(JDL::ISB_BASE_URI);
	if (!adParametric->hasAttribute (attr_name)) {return;}
	std::vector<string> values;
	std::vector<string>::iterator values_it;
	string value;
	// Parses the attribute and generate a list of string values
	Expr2List(adParametric->delAttribute(attr_name), values,true);
	bool listv=(values.size()>1);
	for (values_it=values.begin();values_it!=values.end();values_it++){
		if(values_it->find(AdConverter::VALUE)==string::npos){
			// parameter NOT found inside ISB
			if (parametricISBbaseUri){
				// files with static name and dynamic path: store in adPathametric
				if (listv){adPathametric->addAttribute(attr_name, *values_it);}
				else {adPathametric->setAttribute(attr_name, *values_it);}
			}else{
				// store in adStatic
				if (listv){adStatic->addAttribute(attr_name, *values_it);}
				else {adStatic->setAttribute(attr_name, *values_it);}
			}
		}else{
			// Parameter found, can be of different kind:
			if (parametricISBbaseUri ||
			fs::path(*values_it, fs::native).leaf().find(AdConverter::VALUE)==string::npos){
				// Paramaeter NOT found inside LEAF
				// files with same name but dynamic path: pathametric will contain it
				if (listv){adPathametric->addAttribute(attr_name, *values_it);}
				else {adPathametric->setAttribute(attr_name, *values_it);}
			}else{
				// Paramaeter FOUND inside LEAF (and ISB uri NOT dynamic):
				// files with different name (but SAME path): parametric will contain it
				if (listv){adParametric->addAttribute(attr_name, *values_it);}
				else {adParametric->setAttribute(attr_name, *values_it);}
			}
		}
	}
}


/*********************************************
* Pop a value from an attribute
* i.e.: remove the "parametric" value from a list of jobtype attribute
*********************************************/
bool removeBulkAttribute(const std::string & attr_name, Ad *adParametric, const std::string strTBremoved){
	if(!adParametric->hasAttribute (attr_name)){return true;}
	std::vector<string> values;
	bool keepLook=true;
	Expr2List(adParametric->delAttribute(attr_name), values,true);
	for (unsigned int i = 0;i<values.size(); i++){
		if(    (glite_wms_jdl_toLower(values[i]).find(strTBremoved)!=string::npos)   ){
			// strTBremoved value FOUND! do not re-insert
			keepLook= false;
		}else{
			// it's not the strTBremoved value: re-insert as before
			adParametric->addAttribute(attr_name, values[i]);
		}
	}
	return keepLook;
}
/*********************************************
* Append a referring expression to the rootNode
* i.e.: a node pointing to the root inputSandbox root.inputSandbox[offset+dim]
********************************************/
int appendReference(ExprList *nodeList, int offset,const int dim){
	for (int i=0;i<dim;i++){
		ClassAdParser par ;
		string attr_value="root.inputsandbox["+boost::lexical_cast<std::string>(i+offset)+"]";
		nodeList->push_back(par.ParseExpression(attr_value, true));
	}
	return offset+dim;
}

/*********************************************
* Append the tree Expression to the existing ExprList expression
* i.e.: the delAttribute of an ISB can be appended to a general epxList
********************************************/
void appendTrees(ExprTree* tree,ExprList *exprList){
	if( (tree==NULL)||(exprList==NULL) ){
		throw AdClassAdException (__FILE__,__LINE__,"appendTrees",
				WMS_JDLMISMATCH,"NULL ExprList",DAGAd::Attributes::NODES);
	}
	switch (tree->GetKind()){
		case ExprTree::LITERAL_NODE:
  		case ExprTree::CLASSAD_NODE:
			exprList->push_back(tree->Copy());
			break;
		case ExprTree::EXPR_LIST_NODE:{
			ExprList *el = static_cast<classad::ExprList*>(tree);
			std::vector<ExprTree *> list;
			el->GetComponents(list);
			for (unsigned int i =0;i< list.size();i++){exprList->push_back(list[i]->Copy());}
			break;
		}
		default:
			throw AdMismatchException (__FILE__,__LINE__,"appendTrees",
				WMS_JDLMISMATCH,DAGAd::Attributes::NODES);
			break;
	}
}


ExpDagAd* AdConverter::bulk2dag (const std::string &ad, unsigned int maxCycles_i){
	return bulk2dag(new Ad(ad));
}


ExpDagAd* AdConverter::bulk2dag (Ad* adOriginal, unsigned int maxCycles_i){
	GLITE_STACK_TRY("AdConverter::bulk2dag");
	/*
	* Ad instance will be repeated several times,
	* once per attribute.
	* Some (inherited) attributes might be placed only at root/dag/father level
	* This is true when they do not contain the parameter
	*/
	// Make a copy (will be modified) of the given pointer (will remain unchanged):
	Ad* adParametric = new Ad(*adOriginal);
	Ad adStatic, adPathametric;
	ClassAd nodes ;
	// ClassAd dagad ; used adStatic directly
	Value val ;
	string buffer ;
	std::vector<ExprTree*> list ;

	// Remove parametric expression from JobType
	if(removeBulkAttribute(JDL::JOBTYPE,adParametric,JDL_JOBTYPE_PARAMETRIC)){
		throw   AdSemanticGroupException(__FILE__ , __LINE__ ,
				METHOD,WMS_JDLGROUP,"JobType!=\"parametric\" for parametric jobs") ;
	}
	// Look for (and remove) start/step attributes (if not present, default given)
	unsigned int start = removeInt(adParametric,PARAMETRIC_START,0);
	unsigned int step  = removeInt(adParametric,PARAMETRIC_STEP,1);
	// Division by zero not allowed
	if (step == 0) {
		throw AdSyntaxException (__FILE__,__LINE__,
				"bulk2dag",WMS_JDLPARSE , "JDL Attribute ParameterStep must be different from zero, division by zero not allowed");
	}
	/*
	* InputSsandbox Approach: separate static, dynamic and path-dynamic values
	* ISB files will be all listed in the main dag attribute
	* ISB nodes will refer to root.ISB attribute
	* adStatic will have all static (NO PARAM FOUND) ISBs (all strings)
	*/
	splitIsbAttribute(adParametric, &adStatic, &adPathametric);
	// this flags tell whether is worth proceeding with dynamic isb
	bool isbDynamic = adParametric->hasAttribute(JDL::INPUTSB);
	bool isbStatic  = adStatic.hasAttribute(JDL::INPUTSB);
	// Special Path-a-metrized case: ISB values are found
	// either inside ISB_BASE_URI or inside ISB path name:
	bool   isbPatham_b=false;
	string isbPatham_s;  //This string will contain path-dynamic value(s) expression
	if (adPathametric.hasAttribute(JDL::INPUTSB)){
		isbPatham_b=true;
		isbPatham_s=adPathametric.toString();
	}
	// dimension of Dynamic values
	const int isbDim = isbDynamic?(adParametric->getStringValue(JDL::INPUTSB)).size():0;
	// dimension of Static values
	const int issDim = isbStatic?(adStatic.getStringValue(JDL::INPUTSB)).size():0;
	// offset to append expressions (static referencies first)
	int isbOffset = issDim;
	// isbList will include all the dynamic value to be inserted at dag (root/father) level
	ExprList *isbList = new ExprList();
	if (isbStatic){
		appendTrees(adStatic.delAttribute(JDL::INPUTSB), isbList);
	}
	// Special attribute NodesCollocation: must be static and boolean
	if (adParametric->hasAttribute(JDL::NODES_COLLOCATION)){
		adStatic.setAttribute(JDL::NODES_COLLOCATION, adParametric->getBool(JDL::NODES_COLLOCATION));
		adParametric->delAttribute(JDL::NODES_COLLOCATION);
	}
	// Separate inheriting values from parametric ones
	// it DOES NOT make any sense to have parametric inheriting attributes -> last argument set to false
	splitBulkAttribute(JDL::VIRTUAL_ORGANISATION,adParametric,&adStatic, false);
	splitBulkAttribute(JDL::HLR_LOCATION,adParametric,&adStatic, false);
	splitBulkAttribute(JDL::MYPROXY,adParametric,&adStatic, false);
	splitBulkAttribute(JDL::LB_ADDRESS,adParametric,&adStatic, false);
	splitBulkAttribute(JDL::ALLOW_ZIPPED_ISB,adParametric,&adStatic, false);
	splitBulkAttribute(JDLPrivate::ZIPPED_ISB,adParametric,&adStatic, false);
	//Add the used parameter to the Environment
	adParametric->addAttribute(JDL::ENVIRONMENT, PARAMETER_VALUE+"="+VALUE);
	// Iterate over the parametric values and replacing parameter
	std::vector<string> iters;
	Expr2List(adParametric->delAttribute(VALUES), iters, true);
	// BUFFER will contain the string representation of the parametrized JDL
	buffer = adParametric->toString() ;
	ExprList *nodeList =NULL;
	ClassAd  *node =NULL;
	// maxCycles_i determine how many parameters can be evaluated
	// 0 means ALL
	if (maxCycles_i==0){ maxCycles_i=iters.size();}
	for ( unsigned int i = start;i <= maxCycles_i;i+=step){
		// Generate the node by replacing parameter
		try {
			node = parse_classad(replace(buffer,VALUE,iters[i]));
		}catch(std::exception &exc){
			jdl_parser parser;
			parser.parseString ( replace(buffer,VALUE,iters[i]) ) ;
			// Remap Exception: classad_utils throws a std::exception
			throw AdSyntaxException (__FILE__,__LINE__,"bulk2dag",
			WMS_JDLPARSE , string(exc.what()));
		}
		// Generate new ISB LIST
		nodeList =new ExprList ();
		// INPUTSB approach: append dynamic values
		// (remove possible ISB attribute from node)
		if (isbDynamic){
			// InputSandbox attribute is ready
			// move inputSandbox from node to dag
			appendTrees(node->Remove (JDL::INPUTSB),isbList);
			// append link from dag to node
			isbOffset=appendReference(nodeList,isbOffset,isbDim);
		}
		// INPUTSB approach: append static values
		if (isbStatic){
			appendReference(nodeList,0,issDim);
		}
		// INPUTSB approach: append special case pathametrized values
		// references will not be done in this case
		if (isbPatham_b) {
			ClassAd  *tmpNode;
			try {
				 tmpNode = parse_classad(replace(isbPatham_s,VALUE,iters[i]));
			}catch(std::exception &exc){
				jdl_parser parser;
				parser.parseString ( replace(isbPatham_s,VALUE,iters[i])) ;
				// Remap Exception: classad_utils throws a std::exception
				throw AdSyntaxException (__FILE__,__LINE__,"bulk2dag",
				WMS_JDLPARSE , string(exc.what()));
			}
			ExprTree *tmpTree = tmpNode->Lookup(JDL::INPUTSB);
			if (tmpTree){
			switch (tmpTree->GetKind()){
				case ExprTree::LITERAL_NODE:
					nodeList->push_back(tmpTree->Copy());
					break;
				case ExprTree::EXPR_LIST_NODE:{
					classad::ExprList* el = static_cast<classad::ExprList*>(tmpTree);
					std::vector<ExprTree*> list;
					std::vector<ExprTree*>::iterator list_it;
					el->GetComponents(list);
					for (list_it=list.begin();list_it<list.end();list_it++){
						if ((*list_it)->GetKind() != ExprTree::LITERAL_NODE){
							throw AdMismatchException (__FILE__,__LINE__,"AdConverter::bulk2dag",
								WMS_JDLMISMATCH,JDL::INPUTSB);
						}
						nodeList->push_back((*list_it)->Copy());
					}
					break;
				}
				default:
					break;
					throw AdMismatchException (__FILE__,__LINE__,"AdConverter::bulk2dag",
						WMS_JDLMISMATCH,JDL::INPUTSB);
					break;
			}}  //end switch & (tmpTree)
		}
		// put back ALL created ISB expressions:
		// (only when needed)
		if ( nodeList->size() ){
			node->Insert(JDL::INPUTSB, nodeList);
		}
		// First Step approach
		if ( i==start ){
			// Insert DagAd common Attributes (made only once)
			// This is to be done when cycling because those
			// values might be parametric
			if (node->Lookup(JDL::RANK) !=NULL ){
				adStatic.setAttributeExpr(JDL::RANK,node->Remove(JDL::RANK));
			}
			if (node->Lookup(JDL::REQUIREMENTS) !=NULL){
				adStatic.setAttributeExpr(JDL::REQUIREMENTS,node->Remove(JDL::REQUIREMENTS));
			}
		}
		// Eventually add the built node into the list of nodes
		ClassAd *nodescription=new ClassAd();
		nodescription->Insert(DAGAd::Attributes::DESCRIPTION_AD,node);
		// node type (mandatory)
		val.SetStringValue(SIMPLE_NODE_TYPE);
		nodescription->Insert(DAGAd::Attributes::NODE_TYPE,Literal::MakeLiteral(val));
		if ( nodes.Lookup(NODE + iters[i]) == NULL ) {
			nodes.Insert(checkNodeName(NODE + iters[i]),nodescription);
		} else {
			// The NodeName already exists
			throw AdEmptyException (__FILE__, __LINE__, METHOD,
				WMS_JDLFULL,"Duplicated " + JDL::NODE_NAME +"("+NODE + iters[i]+ ")");
		}
	}
	if (!nodes.size()){
		// no nodes created
		throw AdEmptyException (__FILE__,__LINE__,METHOD,WMS_JDLEMPTY,DAGAd::Attributes::NODES);
	}
	// *******************************
	// Parametric Parsing Finish
	// now create the dagad and return
	// *******************************
	// Set Empty Dependencies
	nodes.Insert (DAGAd::Attributes::DEPENDENCIES, new ExprList());
	// Set created nodes
	adStatic.setAttributeExpr(DAGAd::Attributes::NODES, nodes.Copy());
	// Set Type
	adStatic.setAttribute(JDL::TYPE, JDL_TYPE_DAG);
	// Set Isb created value (if necessary)
	if (isbList->size()){
		adStatic.setAttributeExpr(JDL::INPUTSB, isbList->Copy());
	}
	ExpDagAd *dagad= new ExpDagAd (new DAGAd( *(adStatic.ad()) ));
	// Append warnings (if present):
	if (adStatic.hasWarnings()){
		vector<string> warnings=adStatic.getWarnings();
		vector<string>::iterator it = warnings.begin();
		vector<string>::iterator const end = warnings.end();
		for (; it != end ; it++){ dagad->addWarning(*it); }
	}
	delete (isbList) ;
	return dagad;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*********************************************
* collection2dag
*********************************************/
ExpDagAd* AdConverter::collection2dag ( const std::string &ad ){
	return collection2dag(new Ad(ad));
}
ExpDagAd* AdConverter::collection2dag ( Ad *adOriginal ){
	GLITE_STACK_TRY("AdConverter::collection2dag");
	Ad* dagad = new Ad(*adOriginal);
	ClassAd nodes ;
	std::vector<ExprTree*> list ;
	const ExprList *el;
	Value val ;
	// if (dagad->hasAttribute (JDL::TYPE ,  JDL_TYPE_DAG )
	// Check ad of proper type and other attributes...
	ExprTree* collection_nodes=dagad->delAttribute(DAGAd::Attributes::NODES);
	if (collection_nodes == NULL){
		throw AdEmptyException (__FILE__ , __LINE__ ,"collection2dag",   WMS_JDLEMPTY , DAGAd::Attributes::NODES );
	}
	if  (collection_nodes->Evaluate ( val ) ){
		if (val.IsListValue (el ) ){
			// It is a list:create nodes
			el->GetComponents (list);
			list2nodes(nodes, list);
		}else {
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD,
				WMS_JDLMISMATCH , DAGAd::Attributes::NODES );
		}
	}else {
		throw AdClassAdException(__FILE__,__LINE__,METHOD,
			WMS_JDLMISMATCH,"ClassAd::EvaluateExpr",DAGAd::Attributes::NODES);
	}
	// Create the proper dagad and return
	nodes.Insert ( DAGAd::Attributes::DEPENDENCIES , new ExprList () ) ;
	dagad->setAttributeExpr ( DAGAd::Attributes::NODES   ,   nodes.Copy() ) ;
	// Replace "collection" type with "dag" type
	dagad->delAttribute(JDL::TYPE) ;
	dagad->setAttribute(JDL::TYPE,JDL_TYPE_DAG ) ;
	return new ExpDagAd(new DAGAd(*(dagad->ad()))) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
} // jdl namespace
} // glite namespace

