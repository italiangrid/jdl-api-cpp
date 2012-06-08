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

#include "collectionad.h"
#include "adconverter.h"
#include "RequestAdExceptions.h"
#include "JDLAttributes.h"
#include "DAGAd.h"
#include "NodeAd.h"
#include "jdl_attributes.h"
#include "exception_codes.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "boost/filesystem/path.hpp"
using namespace std ;
using namespace classad;
namespace fs = boost::filesystem;
namespace glite {
namespace jdl {
	const string NODE = "Node_" ;
		/** Constructory by Classad */
	CollectionAd::CollectionAd( const classad::ClassAd& classAd ):Ad(classAd){
		lookInto_b=EXISTENCE;
		toBretrieved=false;
		defaultRank=defaultReq=NULL;
		extractedAd=NULL;
		warning_messages_v.resize(0);
	}
	CollectionAd::CollectionAd( const std::string &classAd_str ):Ad(classAd_str){
		lookInto_b=EXISTENCE;
		toBretrieved=false;
		defaultRank=defaultReq=NULL;
		extractedAd=NULL;
		warning_messages_v.resize(0);
	}
	/** Default constructor */
	CollectionAd::CollectionAd():Ad() {
		lookInto_b=EXISTENCE;
		toBretrieved=false;
		defaultRank=defaultReq=NULL;
		extractedAd=NULL;
		warning_messages_v.resize(0);		
	}
	/**
	* CollectionAd constructors and methods
	**/
	CollectionAd::~CollectionAd() throw(){};
	void CollectionAd::operator=(const CollectionAd& collect) {
		GLITE_STACK_TRY("CollectionAd::operator=(const CollectionAd& collect)") ;
		vector< pair< string, ExprTree *> > vect ;
		collect.GetComponents(vect ) ;
		vector< pair< string, ExprTree *> >::iterator it = vect.begin();
		vector< pair< string, ExprTree *> >::iterator const  end = vect.end();
		lookInto_b=collect.lookInto_b;
		toBretrieved=collect.toBretrieved;
		defaultRank=collect.defaultRank;
		defaultReq=collect.defaultReq;
		extractedAd=collect.extractedAd;
		warning_messages_v = collect.warning_messages_v;
		for(; it!=end;++it){
			Insert (it->first,it->second->Copy());
		}
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}
	/** static insight private methods for checkNoding
	* This method is called by evaluateNode(ClassAd *jobad, const string& attr_name , bool flatten)
	* which is called by evaluateNodes(CollectionAd *collect)
	*/
	ExprTree* EvaluateNode (Value val, ExprList* list ) {
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
						vectList[i]=EvaluateNode(appVal,list)->Copy();
					} else {
						vectList[i]=vectList[i]->Copy();
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
	/*
	* This method evaluates the attributes of the nodes of a dag
	* For instance resolve nodes reference to father such as root.inputsandbox[0]
	* flatten make sure all values become one plain big list
	* @see checkIsb method
	* this method is called by evaluateNodes(CollectionAd *collect)
	*/
	void evaluateNode(ClassAd *nodead, const string& attr_name , bool flatten ){
		GLITE_STACK_TRY("CollectionAd::evaluate")
		Value val ;
		// Retrieve required Value
		ExprTree *isb=nodead->Lookup(attr_name) ;
		if ( isb!=NULL ){
			if (isb->Evaluate(val)){
				if (!val.IsUndefinedValue()){
					// Replacing the node:
					nodead->Insert (attr_name, EvaluateNode(val,flatten?new ExprList():NULL));
				}
			}
		}
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}

	/**
	* Static method: for each node evaluates the expression for ISB
	* this assure in the future ISB will only have pure STRINGS
	**/
	void evaluateNodes(CollectionAd *collect){
		Value val;
		ClassAd *classAd;
		std::vector<ExprTree*> list ;
		ExprTree* collection_nodes=collect->lookUp(DAGAd::Attributes::NODES);
		if (collection_nodes == NULL){
			throw AdEmptyException (__FILE__ , __LINE__ ,"evaluateNodes",   WMS_JDLEMPTY , DAGAd::Attributes::NODES );
		}
		if  (collection_nodes->GetKind()== ExprTree::EXPR_LIST_NODE){
			ExprList* el = static_cast<classad::ExprList*>(collection_nodes);
			el->GetComponents (list);
			string nodeName;
			vector<ExprTree*>::iterator it = list.begin();
			vector<ExprTree*>::iterator const  end = list.end();
			for(; it!=end;++it){
				(*it)->Evaluate(val);
				if (val.IsClassAdValue()){
					classAd=static_cast<classad::ClassAd*>(*it);
					evaluateNode (classAd,JDL::INPUTSB, true);
				}
			}
		}
	}


	/**
	* Static Method: loading a NodeAd from file (if "File" attribute was specified)
	* leaving NodeAd untouched otherwise
	*/
	void expandNode(NodeAd &nodead){
		string nv ="";  // NODE_NAME value
		if (nodead.hasAttribute(JDL::NODE_FILE)){
			// size can be either 2 (NodeName + File) or 1 (File)
			switch (nodead.ad()->size()){
				case 2:
					// NodeName and File attributes case
					if ( nodead.hasAttribute(JDL::NODE_NAME) ) {
						nv = nodead.getString(JDL::NODE_NAME);
					} else{
						// NodeName is missing
						throw AdSemanticGroupException (__FILE__, __LINE__,
							"CollectionAd::expandNode(nodead)", WMS_JDLTOOMANY,
							string(JDL::NODE_FILE +", "+ JDL::NODE_NAME) );
					}
					break;
				case 1:
					// only File attribute case
					break;
				default:
					throw AdSemanticGroupException (__FILE__, __LINE__,
							"CollectionAd::expandNode(nodead)", WMS_JDLTOOMANY,
							string(JDL::NODE_FILE +", "+ JDL::NODE_NAME) );
			}
			// NODE_FILE is definitely present
			// Load NodeAd From File
			string fpath =nodead.getString(JDL::NODE_FILE);
			nodead.clear();
			nodead.fromFile(fpath);
			// remove possible previous present NodeName:
			if (nodead.hasAttribute(JDL::NODE_NAME)){
				nodead.delAttribute(JDL::NODE_NAME);
			}
			if (nv!=""){
				nodead.setAttribute(JDL::NODE_NAME, string(nv));
			}
		}
	}

	/**
	* Static Method: Check The ISB value for a Node and if necessary modify/extract change it
	* return the created list of expressions
	* Notice: At this step alll ISB values must be string: see evaluateNode method
	**/
	void checkIsb(NodeAd &nodead, vector<string> &extracted,
		bool &toBretrieved, checkType lookInto_b,
		ExtractedAd* rootExtractedAd,ExtractedAd* nodeExtractedAd){
		ExprList *nodeList = NULL;               // INPUTSANDBOX Management
		if (nodead.hasAttribute(JDL::INPUTSB)){
			std::vector<std::string> fakeextracted ; //This variable checks wheter there are files to be extracted
			nodeList = new ExprList();
			ClassAdParser par ;
			// At this step alll ISB values must be string: see evaluateNode method
			std::vector<std::string> isbValues=nodead.getStringValue(JDL::INPUTSB);
			// If the InputSandbox is empty, do not delete, no inheritance from parent
			if (isbValues.size() > 0){
				nodead.delAttribute(JDL::INPUTSB);
			}
			// Cycling over node values:
			bool isbfound_b;
			string leaf;
			Value val;
			unsigned int offset=extracted.size();
			const string wmpURI=   (nodead.hasAttribute(JDL::WMPISB_BASE_URI))?(nodead.getString(JDL::WMPISB_BASE_URI)):"";
			const string isbURI=   (nodead.hasAttribute(JDL::ISB_BASE_URI))   ?(nodead.getString(JDL::ISB_BASE_URI)   ):"";
			vector<std::string>::iterator it = isbValues.begin();
			vector<std::string>::iterator const  end = isbValues.end();
			// Iterate over ISB files of the node.
			// Each entry will be glob-expanded
			// Each matched file will be checked and stored in the proper location
			// when possible, all file will be referenced from the father's ISB
			// (with the "root.inputsandbox" reference)
			for(; it!=end;++it){
			
				if( it->at(0) != '/' && (it->find( "file://", 0) == string::npos) ) {
				  if(!isbURI.empty() ) continue;
				}
			
				toBretrieved=extractFiles(JDL::INPUTSB,*it,fakeextracted,lookInto_b,wmpURI,isbURI)||toBretrieved;
				isbfound_b=false ;
				leaf=fs::path(*it, fs::native).leaf();  // boost 1.32
				// Cycling over already found values:
				for (unsigned int j=0; j<offset;j++){
					if (*it == extracted[j]){
						// already defined value: replace with the already exising ( inside extracted) reference
						nodeList->push_back(
						par.ParseExpression("root.inputsandbox["
							+boost::lexical_cast<std::string>(j)+"]", true));
						isbfound_b=true;
						break;
					}else if (fs::path(extracted[j],fs::native).leaf() == leaf){
						// Path with same name cannot be stored in the same ISB
						// No reference will be applied, pure string used
						isbfound_b=true;
						val.SetStringValue(*it);
						nodeExtractedAd->addFileAd(*it);
						nodeList->push_back(Literal::MakeLiteral(val));
					}
				}
				if (!isbfound_b){
					// value not found: appending to extracted
					// and incrementing offset
					nodeList->push_back(
						par.ParseExpression("root.inputsandbox["
							+boost::lexical_cast<std::string>(offset++)+"]", true));
					extracted.push_back(*it);
					rootExtractedAd->addFileAd(*it);
				}
			}
		}
		if (nodeList && nodeList->size()){
			nodead.setAttributeExpr(JDL::INPUTSB,nodeList);
		}
	}

	/** Check the Specified NODE
	* Assuming each node is a NodeAd
	* in principle and in future might be anything(DagAd, collection partitioner...)
	*/
	void CollectionAd::checkNode(NodeAd &nodead,std::vector<std::string> &extracted){
		GLITE_STACK_TRY("CollectionAd::checkNode(ClassAd *classAd,std::vector<std::string> &extracted)");
		// Check JobType
		if (nodead.hasAttribute(JDL::JOBTYPE, JDL_JOBTYPE_PARAMETRIC)){
			// jobType Parametric not allowed
			throw AdSemanticGroupException (__FILE__, __LINE__,
			METHOD, WMS_JDLSYN, string(JDL_JOBTYPE_PARAMETRIC) +" inside collection");
		}
		// check/set default Values (Rank /Requirements)
		if (defaultRank){ nodead.setDefaultRank(defaultRank);}
		if (defaultReq) { nodead.setDefaultReq(defaultReq);}
		// check The Job (without restoring its values)
		ExtractedAd *nodeExtractedAd = new ExtractedAd();
		nodead.check(false);
		// Check ISB value and move common file into root.inputsandbox attribute
		checkIsb(nodead,extracted,toBretrieved,lookInto_b, extractedAd, nodeExtractedAd);
		if (nodead.hasAttribute(JDL::JOBID)){ nodeExtractedAd->setJobId(nodead.getString(JDL::JOBID)); }
		if (nodead.hasAttribute(JDL::NODE_NAME)){nodeExtractedAd->setNodeName(nodead.getString(JDL::NODE_NAME));}
		extractedAd->addNode(nodeExtractedAd);
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}

	/**
	* if necessary inherit the specified attribute and expression into the nodead
	*/
	void inherit (NodeAd &nodead,const string &attrName, ExprTree* tree){
		if ( !nodead.hasAttribute(attrName) && tree){
			nodead.setAttributeExpr(attrName, tree->Copy());
		}
	}
	/**
	* check the nodeName (if already existing)
	* If necessary create a new one fom the given integer (which is incremented therefore)
	*/
	void insertNodeName (NodeAd &nodead,unsigned int &i){
		if (nodead.hasAttribute(JDL::NODE_NAME)){
			// this line is just checking the type
			nodead.getType(JDL::NODE_NAME);
		} else {
			// Insert automatic node name (custom was not found):
			nodead.setAttribute(JDL::NODE_NAME, NODE+boost::lexical_cast<std::string>(i));
			// increment nodeName int variable
			i+=1;
		}
	}

	void CollectionAd::checkNodes(CollectionAd *collect,std::vector<std::string> &extracted){
		GLITE_STACK_TRY("CollectionAd::checkNodes(CollectionAd &collect)") ;
		Value val;
		ClassAd *classAd;
		std::vector<ExprTree*> list ;
		ExprTree* collection_nodes=collect->lookUp(DAGAd::Attributes::NODES);
		if (collection_nodes == NULL){
			throw AdEmptyException (__FILE__ , __LINE__ ,"checkNodes",   WMS_JDLEMPTY , DAGAd::Attributes::NODES );
		}
		if  (collection_nodes->GetKind()==ExprTree::EXPR_LIST_NODE){
				// It is a list: iterate over its values
				// old approach used to call IsListValue (el)
				ExprList* el = static_cast<classad::ExprList*>(collection_nodes);
				// Rank & Requirements inheritance
				ExprTree* colRank = collect->lookUp(JDL::RANK);
				ExprTree* colReq  = collect->lookUp(JDL::REQUIREMENTS);
				ExprTree* colPer  = collect->lookUp(JDL::PU_FILE_ENABLE);
				el->GetComponents (list);
				string finalExc ="" ;
				vector<ExprTree*>::iterator it = list.begin();
				vector<ExprTree*>::iterator const  end = list.end();
				unsigned int i=0;
				// Iterate over the nodes:
				for(; it!=end;++it){
					if ((*it)->GetKind()==ExprTree::CLASSAD_NODE){
						classAd=static_cast<classad::ClassAd*>(*it);
						// Create NodeAd instance
						NodeAd nodead(*static_cast<classad::ClassAd*>(*it));
						nodead.setLocalAccess(lookInto_b==EXISTENCE?true:false);
						// parse file (if JDL not yet expanded)
						expandNode(nodead);
						// Rank & Requirements inheritance
						inherit(nodead, JDL::RANK, colRank);
						inherit(nodead, JDL::REQUIREMENTS, colReq);
						inherit(nodead, JDL::PU_FILE_ENABLE, colPer);
						// Parse (and if necessary create) the Node Name
						insertNodeName(nodead, i);
						// Check the single node (NodeName is already present as a string)
						try{
							checkNode (nodead,extracted);
							// update current collection
							classAd->CopyFrom( *(nodead.ad()) );
						} catch ( RequestAdException &exc ){
							if (finalExc!="") { finalExc += "\n"; }
							finalExc +=nodead.getString(JDL::NODE_NAME)
								 +"  - "+string(exc.what());
						}
					}else {
						throw AdMismatchException (__FILE__,__LINE__ ,
						METHOD,WMS_JDLMISMATCH,DAGAd::Attributes::NODES);
					}
				}
				if (!finalExc.empty()){
					throw AdSyntaxException ( __FILE__ , __LINE__ ,
					METHOD,WMS_DAG_CHECK,finalExc );
				}
		}else {
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , DAGAd::Attributes::NODES );
		}
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}
	void CollectionAd::setLocalAccess(bool lookInto){
		lookInto_b = lookInto?EXISTENCE:WMPROXY;
	}
	void CollectionAd::setDefaultRank (classad::ExprTree *attr_value ){
		if (attr_value!=NULL){ defaultRank=attr_value->Copy();}
		else{ throw  AdClassAdException (__FILE__ , __LINE__ ,
			" CollectionAd::setDefaultRank (const string& attr_value)", WMS_JDLSYN , "Empty Expression");
		}
	}
	void CollectionAd::setDefaultReq   (classad::ExprTree *attr_value ){
		if (attr_value!=NULL){ defaultReq=attr_value->Copy();}
		else{ throw  AdClassAdException (__FILE__ , __LINE__ ,
			" CollectionAd::setDefaultReq (const string& attr_value)", WMS_JDLSYN , "Empty Expression");
		}
	}
	CollectionAd* CollectionAd::check(){
		GLITE_STACK_TRY("CollectionAd::check()") ;
		// Clone the collection (all operations will be applied to the result instance)
		CollectionAd *collect = new CollectionAd(*(ad())) ;
		collect->lookInto_b=lookInto_b;
		extractedAd=new ExtractedAd();
		if (hasAttribute(JDL::JOBID)){
			extractedAd->setJobId(getString(JDL::JOBID));
		}
		// TYPE
		if (collect->hasAttribute(JDL::TYPE)){
			if(glite_wms_jdl_toLower(collect->getString(JDL::TYPE))!=JDL_TYPE_COLLECTION){
				throw AdSyntaxException (__FILE__ , __LINE__ ,METHOD,   WMS_JDLSYN ,  JDL::TYPE );
			}
		}else { collect->setAttribute(JDL::TYPE,JDL_TYPE_COLLECTION); }
		// INPUT SANDBOX CHECK
		// Extract ISB values: this values will be inserted eventually
		std::vector<std::string> extracted; //the vector is empty now
		// Evaluate possible remote Expression inside Nodes
		evaluateNodes(collect);
		// Manage ISB at collection (father) level
		if (collect->hasAttribute(JDL::INPUTSB)){
			const string wmpURI=   (hasAttribute(JDL::WMPISB_BASE_URI))?(getString(JDL::WMPISB_BASE_URI)):"";
			const string isbURI=   (hasAttribute(JDL::ISB_BASE_URI))   ?(getString(JDL::ISB_BASE_URI)   ):"";
			vector<string> isbox = collect->getStringValue(JDL::INPUTSB);
			for (unsigned int i=0; i< isbox.size();i++){
				toBretrieved=extractFiles(JDL::INPUTSB, isbox[i],extracted,
					lookInto_b,wmpURI,isbURI,extractedAd)||toBretrieved;
			}
			collect->delAttribute(JDL::INPUTSB);
		}
		// Iterate and check over its nodes
		checkNodes(collect, extracted);
		collect->toBretrieved =toBretrieved || collect->toBretrieved;
		// Switch pointer
		collect->extractedAd = extractedAd;
		extractedAd=NULL;
		// replace old ISB values with the extracted ones...
		for(unsigned int i=0; i< extracted.size();i++){
			collect->addAttribute(JDL::INPUTSB, extracted[i]) ;
		}
		return collect;
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}
	std::string CollectionAd::toSubmissionString(){
		return check()->toString();
	}

        map<std::string ,std::vector< std::string > >
        CollectionAd::getNodeStringValuesMap (const std::string &attr_name){
		GLITE_STACK_TRY("CollectionAd::getNodeStringValues (const std::string &attr_name)");
		map<std::string ,std::vector< std::string > > result ;
		const ExprList *el;
		std::vector<ExprTree*> list ;
		ExprTree* collection_nodes=lookUp(DAGAd::Attributes::NODES);
		if (collection_nodes == NULL){
			throw AdEmptyException (__FILE__ , __LINE__ ,"Expr2List",   WMS_JDLEMPTY , DAGAd::Attributes::NODES );
		}

		if (collection_nodes->GetKind()==ExprTree::EXPR_LIST_NODE){
			el = static_cast<classad::ExprList*>(collection_nodes);
			// It is a list: iterate over its values
			el->GetComponents (list);
			vector<ExprTree*>::iterator it = list.begin();
			vector<ExprTree*>::iterator const  end = list.end();
			for(; it!=end;++it){
				if ((*it)->GetKind()==ExprTree::CLASSAD_NODE){
					NodeAd ad(*(static_cast<classad::ClassAd*>(*it)));
					try{
							result.insert(make_pair(
								ad.getString(JDL::NODE_NAME),
								ad.getStringValue(attr_name)
							));
					}catch (AdEmptyException &exc){
							// either nodeName not yet initialised
							// or attribute not present: do nothing
						}
				}else {
					throw AdMismatchException (__FILE__,__LINE__ ,
						METHOD,WMS_JDLMISMATCH,DAGAd::Attributes::NODES);
				}
			}
		}else   throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , DAGAd::Attributes::NODES );
		// Once the cycle is over, return the gathered entries:
		return result;
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}

	std::vector< std::pair<std::string,std::vector< std::string > > >
	CollectionAd::getNodeStringValues (const std::string &attr_name){
		GLITE_STACK_TRY("CollectionAd::getNodeStringValues (const std::string &attr_name)");
		std::vector< std::pair<std::string,std::vector< std::string > > > result ;
		const ExprList *el;
		std::vector<ExprTree*> list ;
		ExprTree* collection_nodes=lookUp(DAGAd::Attributes::NODES);
		if (collection_nodes == NULL){
			throw AdEmptyException (__FILE__ , __LINE__ ,"Expr2List",   WMS_JDLEMPTY , DAGAd::Attributes::NODES );
		}

		if (collection_nodes->GetKind()==ExprTree::EXPR_LIST_NODE){
			el = static_cast<classad::ExprList*>(collection_nodes);
			// It is a list: iterate over its values
			el->GetComponents (list);
			vector<ExprTree*>::iterator it = list.begin();
			vector<ExprTree*>::iterator const  end = list.end();
			for(; it!=end;++it){
				if ((*it)->GetKind()==ExprTree::CLASSAD_NODE){
					NodeAd ad(*(static_cast<classad::ClassAd*>(*it)));
					try{
						result.push_back (
							std::pair<std::string,std::vector< std::string > >(
								ad.getString(JDL::NODE_NAME),
								ad.getStringValue(attr_name)
								)
						);
					}catch (AdEmptyException &exc){
						// Attribute not present, do nothing
					}
				}else {
					throw AdMismatchException (__FILE__,__LINE__ ,
						METHOD,WMS_JDLMISMATCH,DAGAd::Attributes::NODES);
				}
			}
		}else {
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , DAGAd::Attributes::NODES );
		}

		// Once the cycle is over, return the gathered entries:
		return result;
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}
	std::vector< std::string > CollectionAd::getNodeStringValue (const std::string &node, const std::string &attr_name){
		GLITE_STACK_TRY("CollectionAd::getNodeStringValue (const std::string &node, const std::string &attr_name)");
		const ExprList *el;
		std::vector<ExprTree*> list ;
		ExprTree* collection_nodes=lookUp(DAGAd::Attributes::NODES);
		if (collection_nodes == NULL){
			throw AdEmptyException (__FILE__ , __LINE__ ,"Expr2List",   WMS_JDLEMPTY , DAGAd::Attributes::NODES );
		}
		if (collection_nodes->GetKind()==ExprTree::EXPR_LIST_NODE){
				// It is a list: iterate over its values
				el = static_cast<classad::ExprList*>(collection_nodes);
				el->GetComponents (  list );
				vector<ExprTree*>::iterator it = list.begin();
				vector<ExprTree*>::iterator const  end = list.end();
				for(; it!=end;++it){
					if ((*it)->GetKind()==ExprTree::CLASSAD_NODE){
						NodeAd ad(*(static_cast<classad::ClassAd*>(*it)));
						if (ad.getString(JDL::NODE_NAME)==node){
							return ad.getStringValue(attr_name);
						}
					}else {
						throw AdMismatchException (__FILE__,__LINE__ ,
							METHOD,WMS_JDLMISMATCH,DAGAd::Attributes::NODES);
					}
				}
		}else {
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , DAGAd::Attributes::NODES );
		}
		// If this point reached, unable to find any matching node
		throw AdEmptyException (__FILE__,__LINE__,METHOD,WMS_JDLEMPTY,DAGAd::Attributes::NODES);
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}

	ExtractedAd* CollectionAd::getExtractedAd(){
		if (extractedAd==NULL){
			return check()->getExtractedAd();
		}
		return extractedAd;
	}


	// Node user management:
	void CollectionAd::addNode(Ad node){
		GLITE_STACK_TRY("CollectionAd::getNodeStringValue (const std::string &node, const std::string &attr_name)");
		Value val;
		ExprList *el;
		std::vector<ExprTree*> list ;
		ExprTree* collection_nodes=lookUp(DAGAd::Attributes::NODES);
		if (!collection_nodes){
			// collection is still empty: fill first node
			el = new ExprList();
			el->push_back(node.ad());
			Insert (DAGAd::Attributes::NODES,el);
		}else if  (collection_nodes->Evaluate ( val ) ){
			if (val.IsListValue (el)){
				// It is a list: append new Node
				el->push_back(node.ad());
			}else {
				throw AdMismatchException (__FILE__ , __LINE__ ,METHOD,
					WMS_JDLMISMATCH , DAGAd::Attributes::NODES );
			}
		}else throw AdClassAdException(__FILE__,__LINE__,METHOD,WMS_JDLMISMATCH,"ClassAd::EvaluateExpr",DAGAd::Attributes::NODES);
		GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
	}

} // jdl namespace
} // glite namespace

// EOF
