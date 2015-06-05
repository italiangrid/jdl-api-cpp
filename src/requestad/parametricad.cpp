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

#include "parametricad.h"
#include "JdlAttributeList.h"
#include "JDLAttributes.h"
#include "RequestAdExceptions.h"
#include "exception_codes.h"
#include "extractfiles.h"
#include <iostream>
using namespace std ;
using namespace classad;
namespace glite {
namespace jdl {
/*************
* CONSTRUCTORS
**************/
ParametricAd::ParametricAd(const ParametricAd& ParametricAd){
	GLITE_STACK_TRY("ParametricAd::ParametricAd(const ParametricAd&)") ;
	fromJobAd(ParametricAd);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
void ParametricAd::operator=(const ParametricAd& ParametricAd){
	GLITE_STACK_TRY("ParametricAd::operator=(const ParametricAd& ParametricAd)") ;
	fromJobAd(ParametricAd);
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
ParametricAd::~ParametricAd() throw(){}
/*************
* SET/INSERT/ADD
**************/
void ParametricAd::insertAttribute(const std::string& attr_name ,ExprTree* tree){
	if (    glite_wms_jdl_toLower (attr_name)== glite_wms_jdl_toLower(JDL::INPUTSB)  ){
		Insert (attr_name  , tree)  ;
		ExprTree* tmp_expr = tree->Copy();
		user.Insert (attr_name  , tmp_expr) ;
	} else  JobAd::insertAttribute(attr_name ,tree);
}
void ParametricAd::addUserTag ( const std::string& attr_name,  const std::string& attr_value){
	ExprTree* tree = Lookup ( JDL::USERTAGS  ) ;
	if ( tree ==NULL){
		// UserTags attribute has still to be created
		ClassAd ad ;
		ad.InsertAttr ( attr_name , attr_value ) ;
		ExprTree* tmp_expr = ad.Copy();
		Insert ( JDL::USERTAGS  , tmp_expr ) ;
	}else{
		// Already Existing UserTags attribute
		if (  tree->GetKind () == classad::ExprTree::CLASSAD_NODE  )
			((ClassAd*)tree)->InsertAttr ( attr_name , attr_value  ) ;
	}
}
/*************
* GET
**************/
std::vector<classad::ExprTree*> ParametricAd::getRemoteSandbox(){return inputRemotes;}
std::vector<std::string>  ParametricAd::getStringValue(const std::string& attr_name){
	if( (glite_wms_jdl_toLower(attr_name) == glite_wms_jdl_toLower(JDL::INPUTSB))){
		return getISBStrings();
	}else {
		return Ad::getStringValue(attr_name);
	}
}
std::vector<std::string> ParametricAd::getISBStrings(){
	GLITE_STACK_TRY("ParametricAd::getISBStrings()");
	// This vector contains all ISB string Values
	vector<string> inputFiles ;
	ExprTree* isbTree = Lookup (JDL::INPUTSB);
	if (!isbTree){ /* No inputFiles found: return */ return inputFiles; }
	Value val ;
	string isb ;
	EvaluateExpr(isbTree,val);
	switch (val.GetType()){
		case Value::UNDEFINED_VALUE:
			// Single Undefined (expression) value
			break;
		case Value::STRING_VALUE:
			// ISB consists on a single (String) value
			val.IsStringValue(isb);
			inputFiles.push_back(isb);
			break;
		case Value::LIST_VALUE:{
			// ISB is a list of (possible) mixed (string&expresssion) values
			const ExprList *el;
			val.IsListValue(el);
			vector<ExprTree*> vectList;
			el->GetComponents(vectList);
			for ( unsigned int i = 0; i< vectList.size() ; i++){
				if (vectList[i]->GetKind()!=ExprTree::LITERAL_NODE){
					// not a literal node
				}else if (vectList[i]->Evaluate(val)){
					switch (val.GetType()){
						case Value::STRING_VALUE:
							val.IsStringValue( isb ) ;
							inputFiles.push_back (isb) ;
							break;
						case Value::UNDEFINED_VALUE:
							// It's an Expression evaluated
							break;
						default:
							throw AdMismatchException (__FILE__,__LINE__,
							METHOD,WMS_JDLMISMATCH , JDL::INPUTSB );
					}
				}
				val.Clear() ;
			}
		}
		break;
		default:
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , JDL::INPUTSB );
			break;
	}
	return inputFiles ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
/*************
* CHECK
**************/
void ParametricAd::checkSpecials() {
}
void ParametricAd::checkSyntax(const std::string& attr_name , classad::Value attr_value ){
	if( (glite_wms_jdl_toLower(attr_name) == glite_wms_jdl_toLower(JDL::INPUTSB))
		&&(attr_value.GetType()==Value::UNDEFINED_VALUE)  ){
			// do nothing, value admitted
	}else {
		JobAd::checkSyntax(attr_name,attr_value);
	}
}
void ParametricAd::checkInputSandbox(std::vector<std::string>& extracted){
	GLITE_STACK_TRY("ParametricAd::checkInputSandbox(std::vector<std::string>&)");
	// This vector contains all ISB string extracted Values
	unsigned int iter_i = extracted.size();
	// This Vector will replace the old InputSanbox with the extracted values
	vector<ExprTree*> isVect ;
	ExprTree* isbTree = Lookup (JDL::INPUTSB);
	if (!isbTree){ /* No inputFiles found: return */ return; }
	// These variables are needed when extracting
	const string wmpURI = (hasAttribute(JDL::WMPISB_BASE_URI))? (getString(JDL::WMPISB_BASE_URI)):"";
	const string isbURI=   (hasAttribute(JDL::ISB_BASE_URI))  ? (getString(JDL::ISB_BASE_URI)   ):"";
	Value val ;
	string isb ;
	EvaluateExpr(isbTree,val);
	inputRemotes.clear();
	switch ( val.GetType() ){
		case Value::UNDEFINED_VALUE:
			inputRemotes.push_back(isbTree->Copy());
			isVect.push_back(isbTree->Copy());
			break;
		case Value::STRING_VALUE:
			val.IsStringValue(isb);
			toBretrieved=extractFiles (JDL::INPUTSB, isb, extracted,
				lookInto_b,wmpURI,isbURI,extractedAd.get()) || toBretrieved;
			// put the extracted files back into the InputSandbox attribute
			for(;iter_i<extracted.size();iter_i++){	// Iterate ONLY over new value(s)
				val.SetStringValue(extracted[iter_i]);	// create classad Value
				isVect.push_back(Literal::MakeLiteral(val));	// Update ISB value
			}
			break;
		case Value::LIST_VALUE:{
			const ExprList *el;
			val.IsListValue( el );
			vector<ExprTree*> vectList ;
			el->GetComponents(vectList) ;
			for ( unsigned int i = 0; i< vectList.size() ; i++){
				if (vectList[i]->GetKind()!=ExprTree::LITERAL_NODE){
					// not a literal node
					inputRemotes.push_back( vectList[i]->Copy() );
					isVect.push_back(vectList[i]->Copy());
				}
				else if (vectList[i]->Evaluate(val)){
					switch (val.GetType()){
						case Value::STRING_VALUE:
							val.IsStringValue(isb);
							toBretrieved=extractFiles (JDL::INPUTSB, isb, extracted,
								lookInto_b,wmpURI,isbURI,extractedAd.get()) || toBretrieved;
							// put the extracted files back into the InputSandbox attribute
							for(;iter_i<extracted.size();iter_i++){	// Iterate ONLY over new value(s)
								val.SetStringValue(extracted[iter_i]);	// create classad Value
								isVect.push_back(Literal::MakeLiteral(val));	// Update ISB value
							}
							break;
						case Value::UNDEFINED_VALUE:
							// It's an Expression evaluated
							inputRemotes.push_back( vectList[i]->Copy() );
							isVect.push_back(vectList[i]->Copy());
							break;
						default:
							throw AdMismatchException (__FILE__,__LINE__,
							METHOD,WMS_JDLMISMATCH , JDL::INPUTSB );
					}
				}else{
					// It's an Expression not evaluated, leave it unchanged
					inputRemotes.push_back( vectList[i]->Copy() );
					isVect.push_back(vectList[i]->Copy());
				}
				val.Clear() ;
			}
		}
		break;
		default:
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , JDL::INPUTSB );
			break;
	}
	classad:ExprTree* tmp_expr = ExprList::MakeExprList(isVect);
	Insert (JDL::INPUTSB , tmp_expr) ;
	GLITE_STACK_JDL_CATCH_ALL() ; //Exiting from method: remove line from stack trace
}
} // jdl namespace
} // glite namespace

// EOF
