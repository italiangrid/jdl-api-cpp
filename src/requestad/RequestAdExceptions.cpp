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
*  filename  : RequestAdExceptions.cpp
*  author    : Alessandro Maraschini <alessandro.maraschini@datamat.it>
*  copyright : (C) 2002 by DATAMAT
***************************************************************************/
#include "RequestAdExceptions.h"
#include "exception_codes.h"
#include <iostream>
using namespace std ;
namespace glite {
namespace jdl {
/*********************************
*  RequestAdException
**********************************/
const char* RequestAdException::what() throw(){
	if (!error_message.empty()){return (error_message+error_description).c_str();}
	return (ancestor+error_description).c_str();
}
RequestAdException::RequestAdException (string file,
				int line,
				string method,
				int code,
				string exception_name):
Exception(file,line,method,code , exception_name ){};
/*********************************
*  AdClassAdException
**********************************/
AdClassAdException::AdClassAdException (string file,
				int line,
				string method,
				int code ,
				string method_name,
				std::string error_description ):
RequestAdException(file , line , method , code , "AdClassAdException"){
	error_message = method_name+ ": ClassAd returned syntax error";
	if (error_description!= "") error_message +=" for " + error_description ;
}
/*********************************
*  AdSyntaxException
**********************************/
AdSyntaxException::AdSyntaxException (string file,
				int line,
				string method,
				int code ,
				string attr_name ):
RequestAdException(file , line , method , code, "AdSyntaxException"){
	switch (code){
	case WMS_JDL_MEMBER:
		error_message = attr_name+ ": wrong usage of MultiAttribute method;";
		error_message +=" syntax is: Member/IsMember(Value,List)";
		break;
	case WMS_JDLPARSE:
		error_message = "The following parsing error(s) have been found:\n" + attr_name;
		break;
	case WMS_DAG_CHECK:
		error_message = "The following error(s) have been found while checking nodes:\n" + attr_name;
		break;
	default:
		error_message = attr_name+ ": syntax Error caught";
	}
}
/*********************************
*  AdSemanticException
**********************************/
AdSemanticException::AdSemanticException (string file,
				int line,
				string method,
				int code,
				string exception_name ):
RequestAdException(file , line , method , code  , exception_name){}
/*********************************
*  AdSemanticMandatoryException
**********************************/
AdSemanticMandatoryException::AdSemanticMandatoryException (string file,
					int line,
					string method,
					int code,
					string attr_name ):
AdSemanticException(file , line , method , code, "AdSemanticMandatoryException"){  // WMS_JDLMANDATORY err code
	error_message = attr_name + ": Jdl mandatory attribute is missing";
}
/*********************************
*  AdSemanticPathException
**********************************/
AdSemanticPathException::AdSemanticPathException (string file,
				int line,
				string method,
				int code,
				string attr_name,
				string path_name ):
AdSemanticException(file , line , method , code, "AdSemanticPathException"){
		if (attr_name!="") error_message = attr_name +": ";
		else error_message = "" ;
		switch (code){
			case  WMS_JDLDUPLICATE:
				error_message += "filename conflict found while extracting files."
					"The following file is repeated more than once: '" + path_name+"'";
				break;
			case  WMS_JDLMISMATCH:
				error_message += "filename conflict found while extracting files. "
					"The following file is not allowed: '" + path_name+"'";
				break;
			default: // WMS_JDLMANDATORY err code
				error_message += "Specified path '"+path_name+"' is missing";
			break;
		}
}
/*********************************
*  AdSemanticGroupException
**********************************/
AdSemanticGroupException::AdSemanticGroupException (string file,
					int line,
					string method,
					int code,
					string attrs_name ):
AdSemanticException(file , line , method , code, "AdSemanticGroupException"){ // WMS_JDLMANDATORY err code
	switch (code){
		case  WMS_JDLMANDATORY:
		error_message = attrs_name+ ": attributes group not complete, the attributes have to be specified all togheter";
		break;
		case WMS_JDLTOOMANY :
			error_message = attrs_name + ": no other attributes can be specified for this node";
		break;
	default: // WMS_JDLGROUP err code
		error_message = attrs_name+ ": wrong combination of values" ;
		break;
	}
}
/*********************************
*  AdAttributeException
**********************************/
AdAttributeException::AdAttributeException (string file,
				int line,
				string method,
				int code,
				string exception_name ):
RequestAdException(file , line , method , code  , exception_name){}
/*********************************
*  AdMismatchException
**********************************/
AdMismatchException::AdMismatchException (string file,
					int line,
					string method,
					int code,
					string attr_name,
					string error_description ):
AdAttributeException(file , line , method , code, "AdMismatchException"){  // WMS_JDLMISMATCH ,WMS_JDLSYN  err codes
		switch (code){
			case  WMS_JDLSYN:
				error_message = attr_name + ": wrong value caught for attribute" ;
				break;
			default:  // WMS_JDLMISMATCH
				error_message = attr_name + ": wrong type caught for attribute" ;
		}
		if (error_description!=""){error_message += " (" + error_description +")";}
}
/*********************************
*  AdFormatException
**********************************/
AdFormatException::AdFormatException(string file,
					int line,
					string method,
					int code,
					string attr_name,
					string format ):
AdAttributeException(file , line , method , code, "AdFormatException"){ // WMS_JDLMISMATCH err  code
	switch (code){
		case WMS_JDLMISMATCH:
			error_message = attr_name + ": wrong format caught for attribute" ;
			error_message += ". The right format is:\n'" +format+"'" ;
			break;
		default : // WMS_JOBADSCHEMA:
			error_message= "JobAd Schema constructor dimension exceeded" ;
	}
}
/*********************************
*  AdListException
**********************************/
AdListException::AdListException(string file,
					int line,
					string method,
					int code,
					string attr_name ):
AdAttributeException(file , line , method , code, "AdListException"){
	switch (code){
		case  WMS_JDLSYN:
			error_message = attr_name +": the attribute cannot be of list type";
		break;
			break;
		default: // EPERM error code
			error_message = attr_name +": the attribute is of list type, operation not allowed";
	}
}
/*********************************
*  AdEmptyException
**********************************/
AdEmptyException::AdEmptyException(string file,
					int line,
					string method,
					int code,
					string attr_name ):
AdAttributeException(file , line , method , code, "AdEmptyException"){
	error_message = attr_name + ": unable to complete the operation: the attribute" ;
	switch (code){
		case  WMS_JDLEMPTY:
			error_message += " has not been initialised yet";
			break;
		default:   // WMS_JDLFULL:
			error_message +=" has already been set";
			break;
	}
}
/*********************************
*  AdExtractedException
**********************************/
AdExtractedException::AdExtractedException (std::string file,
	int line,
	std::string method,
	int code ,
	std::string error_message):
RequestAdException(file, line, method, code, "AdExtractedException"){
	this->error_message = error_message;
}


} // jdl namespace
} // glite namespace
