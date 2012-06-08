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
*  filename  : JdlAttributeList.cpp
*  author    : Alessandro Maraschini <alessandro.maraschini@datamat.it>
*  copyright : (C) 2002 by DATAMAT
***************************************************************************/

// Boost File System
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/exception.hpp"

// Exception handling:
#include "RequestAdExceptions.h"
#include "JobAd.h"
#include "exception_codes.h"

// Default attribute values
#include "jdl_attributes.h"

// Header
#include "JdlAttributeList.h"

// Attribute names
#include "JDLAttributes.h"


namespace glite {
namespace jdl {
using namespace std ;
using namespace classad;

namespace fs = boost::filesystem;

/******************************************************************
 method : count
 Counts number of sub-string occurrences  in str
*******************************************************************/
int count(const string& strMain,const string& sep){
   int n=0,found ;
   int l;
   //string str=strMain ;
   l = sep.length();
   found = strMain.find(sep) ;
   while (found!= -1){
         found = strMain.find(sep , found + l) ;
         ++n ;
      }
   return n ;
};


/******************************************************************
 method :   sp
 field: string class
 used to create a checkString
*******************************************************************/
string sp(const string& separator)
  {
   const string sep = "_SEP_"  ;
   return sep + separator + sep ;
  }



/******************************************************************
 method :   isInt
 field: integer & string class
 check if str is an integer
*******************************************************************/
bool isInt (const string& str)
{
   int len, bCode,eCode;
   char code ;
   const char * strCh ;
   len = str.size() ;
   strCh = str.c_str();
   bCode= '0';
   eCode= '9';
   for (int i=0; i<len; i++){
      code=strCh[i];
      if ( (code < bCode) || (code >eCode) )  //It's not a digit number
         return false ;
   }
   return true ;
}


/******************************************************************
 method :   split
 field: string class
 Splits a string into a vector of substring
 maxLenght: max dimension of vector (the last item of the vector will be the lasting part)
 trough: if trough == 1 the separator will be copied at the end of the left-substring
*******************************************************************/
vector<string> split(const string& str, const string& sep, int maxLength =1000, int trough = 0 )
{
   vector<string> strList ;
   int n,l,end, begin;
   string tmpStr=str ;
   l= sep.length();
   // Optional trough variable indicates that the separator
   // string remain in the array string
   if (trough) trough = l ;
   n = count(tmpStr,sep);
   if (n>maxLength)  n = maxLength ;
   //n (or maxLength) is the number of separator to be found
   begin = 0;
   end = tmpStr.find(sep);
   for (int i=0; i<n; i++)
   {
      strList.push_back(  tmpStr.substr(begin,end +trough - begin)  ) ;
      begin = end + l ;
      end= tmpStr.find(sep, begin) ;
      //tmpStr=tmpStr.substr(end+l, str.size()   );
   }
   strList.push_back(tmpStr.substr(begin, tmpStr.length() - begin ) ) ;
   return strList ;
};


/******************************************************************
 method :   checkFormat
 field: string class
 Chek the format of a string
 The format should be given as:
       TYPE+sep+SEPARATOR+sep+TYPE+sep+SEPARATOR+sep+ TYPE +...
 Returns: 0 No Error
          1 Error Found
*******************************************************************/
bool checkFormat (const string& format, const string& str)
{
   string  type , separator, tmpStr=str ;
   vector<string> form ;
   int len, pos, i;
   const string sep = "_SEP_"  ;
   const string sepStr =  "$STR$"  ;
   const string sepInt =  "$INT$"  ;
   form =split (format,sep);
   len=form.size();
   for (i =1;i<len;i=i+2)  {
      separator = form[i];
      pos = tmpStr.find(separator);
      if (pos ==-1)
         //No required separator found
         return true ;
      else
         //Required Separator successfully found
         type   =  tmpStr.substr (0, pos);
         tmpStr =  tmpStr.substr( pos+separator.size() , tmpStr.size()  );
         if (form[i-1] == sepInt) {
             if (!isInt(type) )    return true ;
         }
      }
    type   =  tmpStr ;
    if (form[i-1] == sepInt){
        if (!isInt(type) )   return true ;
    }
   return false ;
}




JdlAttributeList::JdlAttributeList(){
// String Attributes:
stringAttrs.push_back(JDL::EXECUTABLE) ;
stringAttrs.push_back(JDL::ARGUMENTS) ;
stringAttrs.push_back(JDL::STDINPUT) ;
stringAttrs.push_back(JDL::STDOUTPUT);
stringAttrs.push_back(JDL::STDERROR);
stringAttrs.push_back(JDL::ENVIRONMENT);
stringAttrs.push_back(JDL::MYPROXY);
stringAttrs.push_back(JDL::JOBTYPE);
stringAttrs.push_back(JDL::INPUTDATA);
stringAttrs.push_back(JDL::DATA_ACCESS);
stringAttrs.push_back(JDL::REPLICA_CATALOG);
stringAttrs.push_back(JDL::OUTPUT_SE);
stringAttrs.push_back(JDL::USER_CONTACT);
stringAttrs.push_back(JDL::JOBID);
stringAttrs.push_back(JDL::CE_MATCH);
stringAttrs.push_back(JDL::CERT_SUBJ);
stringAttrs.push_back(JDL::CEID);
stringAttrs.push_back(JDL::SUBMIT_TO);
stringAttrs.push_back(JDL::HLR_LOCATION);
stringAttrs.push_back(JDL::LRMS_TYPE);
stringAttrs.push_back(JDL::VIRTUAL_ORGANISATION);
stringAttrs.push_back(JDL::SHHOST);
stringAttrs.push_back(JDL::SHPIPEPATH);
stringAttrs.push_back(JDL::INPUTSB);
stringAttrs.push_back(JDL::ISB_BASE_URI);
stringAttrs.push_back(JDL::WMPISB_BASE_URI);
stringAttrs.push_back(JDL::OUTPUTSB);
stringAttrs.push_back(JDL::OSB_BASE_DEST_URI);
stringAttrs.push_back(JDL::OSB_DEST_URI);
stringAttrs.push_back(JDL::PU_FILES_DEST_URI);
stringAttrs.push_back(JDL::JOB_PROVENANCE);
stringAttrs.push_back(JDL::DATA_CATALOG);
stringAttrs.push_back(JDL::STORAGE_INDEX);
stringAttrs.push_back(JDL::PROLOGUE);
stringAttrs.push_back(JDL::PROLOGUE_ARGUMENTS);
stringAttrs.push_back(JDL::EPILOGUE);
stringAttrs.push_back(JDL::EPILOGUE_ARGUMENTS);
stringAttrs.push_back(JDL::GLITE_WMS_UI_DAG_NODE_NAME);
stringAttrs.push_back(JDL::NODE_NAME);
// Integer Attributes:
// JDL::NODENUMB || CPUNUMBER,  JDL::SHPORT, JDL::RETRYCOUNT
intAttrs.push_back(JDL::NODENUMB );
intAttrs.push_back(JDL::CPUNUMBER);
intAttrs.push_back(JDL::SHPORT);
intAttrs.push_back(JDL::RETRYCOUNT);
intAttrs.push_back(JDL::SHALLOWRETRYCOUNT);
intAttrs.push_back(JDL::PARTITION_NUMBER);
intAttrs.push_back(JDL::PU_TIME_INTERVAL);
intAttrs.push_back(JDL::EXPIRY_TIME);
intAttrs.push_back(JDL::SMPGRANULARITY);
intAttrs.push_back(JDL::HOSTNUMBER);
// DoubleAttributes: RANK , JDL::CE_RANK
doubleAttrs.push_back(JDL::RANK);
doubleAttrs.push_back(JDL::CE_RANK);
// BooleanAttributes: JDL::REQUIREMENTS , JDL::FUZZY_RANK
boolAttrs.push_back(JDL::REQUIREMENTS);
boolAttrs.push_back(JDL::RANK);
boolAttrs.push_back(JDL::FUZZY_RANK);
boolAttrs.push_back(JDL::PU_FILE_ENABLE);
boolAttrs.push_back(JDL::SHORT_DEADLINE_JOB);
boolAttrs.push_back(JDL::ALLOW_ZIPPED_ISB);
boolAttrs.push_back(JDL::WHOLENODES);
// Ad Attributes: OUTPUTDATA
adAttrs.push_back(JDL::OUTPUTDATA);
adAttrs.push_back(JDL::DATA_REQUIREMENTS);
// ListAttributes: DL::USER_CONTACT, JDL::INPUTSB,  JDL::OUTPUTSB, JDL::ENVIRONMENT ,JDL::JOBTYPE,
// JDL::INPUTDATA ,  JDL::DATA_ACCESS , JDL::CE_MATCH, JDL::CE_RANK , DATA_REQUIREMENTS,OUTPUTDATA
listAttrs.push_back(JDL::USER_CONTACT);
listAttrs.push_back(JDL::INPUTSB);
listAttrs.push_back(JDL::OUTPUTSB);
listAttrs.push_back(JDL::ENVIRONMENT);
listAttrs.push_back(JDL::JOBTYPE);
listAttrs.push_back(JDL::INPUTDATA);
listAttrs.push_back(JDL::DATA_ACCESS);
listAttrs.push_back(JDL::CE_MATCH);
listAttrs.push_back(JDL::CE_RANK);
listAttrs.push_back(JDL::OUTPUTDATA);
listAttrs.push_back(JDL::DATA_REQUIREMENTS);
listAttrs.push_back(JDL::OSB_DEST_URI);

// Expr Attributes:  JDL::RANK, JDL::REQUIREMENTS
exprAttrs.push_back(JDL::RANK) ;
exprAttrs.push_back(JDL::REQUIREMENTS) ;
// To be Checked Attributes: RANK,REQUIREMENTS, INPUTSB, ENVIRONMENT, SHPORT, JOBTYPE, TYPE, PRE|POSTJOB
checkAttrs.push_back(JDL::RANK) ;
checkAttrs.push_back(JDL::REQUIREMENTS) ;
checkAttrs.push_back(JDL::INPUTSB) ;
checkAttrs.push_back(JDL::ENVIRONMENT) ;
checkAttrs.push_back(JDL::SHPORT) ;
checkAttrs.push_back(JDL::JOBTYPE) ;
checkAttrs.push_back(JDL::TYPE) ;
// Default attribute
defaultAttrs.resize ( MAX_ATTR ) ;
setDefault ( JOBTYPE_MPICH_REQ_RTE , JDL_JOBTYPE_MPICH_REQ_RTE ) ;
setDefault ( JOBTYPE_MPICH_REQ_CPU ,JDL_JOBTYPE_MPICH_REQ_CPU ) ;
setDefault ( JOBTYPE_MPICH_RANK_FREE , JDL_JOBTYPE_MPICH_RANK_FREE ) ;
setDefault ( REQ_DEFAULT , JDL_REQ_DEFAULT ) ;
setDefault ( RANK_DEFAULT , JDL_RANK_DEFAULT ) ;
}; //End cTor
void JdlAttributeList::setDefault ( Attr attr_name , const string& attr_value){
	defaultAttrs[attr_name] = attr_value ;
}  ;
bool  JdlAttributeList::findAttribute(const string& attr_name) {
   return   findAttr (attr_name , boolAttrs  )   ||
               findAttr (attr_name , intAttrs   )     ||
               findAttr (attr_name , stringAttrs)   ||
               findAttr (attr_name , doubleAttrs) ||
               findAttr (attr_name , adAttrs) ||
               findAttr (attr_name , exprAttrs  ) ;
};
bool compare (const string& src , const string& dst ) {
	if (  glite_wms_jdl_toLower(src) == glite_wms_jdl_toLower(dst)   )
		return true ;
	return false ;
}
bool  JdlAttributeList::findAttr(const string& attr_name, vector<string> lis)const {
	vector<string>::iterator it;
	for (it = lis.begin() ; it!=lis.end() ; ++it){
		if ( glite_wms_jdl_toLower(*it) == glite_wms_jdl_toLower(attr_name) ) {return true;}
	}
	return false;
}
bool JdlAttributeList::findTail(const string& value, vector<string> lis) const {
	vector<string>::iterator it;
	string file = "";
	for (it = lis.begin(); it!=lis.end(); ++it) {
		// fs::path cp(*it, fs::system_specific);  boost 1.29
		fs::path cp(*it, fs::native);  // upgrade to boost 1.32
		file = cp.leaf();
		if (file == value) { return true; }
	}
	return false;
}


/******************************************************************
 PRIVATE methods :  check<type> (string attr_name , <type> attr_value )
 verify if the couple attr_name /attr_value is valid
 where <type> could be:
 -int
 -double
 -bool
 -string
 -Ad
 -Expression
*******************************************************************/
void JdlAttributeList::checkExpr(const string& attr_name,const string&  attr_value)   {
JDLATTR_SET_METHOD("checkExpr(const string& attr_name,const string&  attr_value)");
//Check if the couple is ok... i.e. rank and requirements
if (   findAttribute(attr_name)   )
   if (  ! findExpr(attr_name)  )
		throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name) ;
};
void JdlAttributeList::checkInt(const string& attr_name, int attr_value)   {
JDLATTR_SET_METHOD("checkInt(const string& attr_name, int attr_value)");
if (   findAttribute(attr_name)   ){
	if ((!findInt(attr_name)) && (!findDouble(attr_name))){
		throw AdMismatchException (__FILE__, __LINE__, METHOD, WMS_JDLMISMATCH, attr_name) ;
	}else if(compare (attr_name, JDL::NODENUMB) && (attr_value<1)){
		throw AdMismatchException (__FILE__, __LINE__, METHOD, WMS_JDLSYN, 	attr_name , "value must be greater than 0") ;
	}else if(compare (attr_name, JDL::CPUNUMBER) && (attr_value<1)){
		throw AdMismatchException (__FILE__, __LINE__, METHOD, WMS_JDLSYN, 	attr_name , "value must be greater than 0") ;
	}else if(compare (attr_name, JDL::SHALLOWRETRYCOUNT)){
	 	if (attr_value<-1){
			throw AdMismatchException (__FILE__, __LINE__, METHOD, WMS_JDLSYN, 	attr_name ,
				"value must be greater than 0 (-1 to unset)") ;
		}		
	}else if(attr_value<0){
		throw AdMismatchException (__FILE__, __LINE__, METHOD, WMS_JDLSYN, 	attr_name , "value cannot be less than 0") ;
	}
}
};
void JdlAttributeList::checkDouble(const string& attr_name, const double& attr_value)   {
JDLATTR_SET_METHOD("checkDouble(const string& attr_name, const double& attr_value)");
if (   findAttribute(attr_name)   )
   if    ( ! findDouble(attr_name) )
            throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name) ;
};
void JdlAttributeList::checkBool(const string& attr_name, const bool& attr_value)   {
JDLATTR_SET_METHOD("checkBool(const string& attr_name, const bool& attr_value)");
if (   findAttribute(attr_name)   )
   if    ( ! findBool(attr_name)   )
            throw  AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name) ;
}

void checkDataRequirements(Ad ad){
	JDLATTR_SET_METHOD("checkDataRequirements(Ad ad)");
	/*
	DataRequirements semantic:
		- InputData   = [list of] <string>
		- DataCatalog = <string>
		- CatalogType = <string>
	*/
	try{
		// INPUTDATA: Mandatory
		ad.getStringValue(JDL::INPUTDATA);
		// DATA CATALOG TYPE: Mandatory
		ad.getString(JDL::DATA_CATALOG_TYPE);
		// DATA CATALOG: optional
		if (ad.hasAttribute(JDL::DATA_CATALOG)){
			ad.getString(JDL::DATA_CATALOG);
		}
	}catch (AdEmptyException &exc){
		// One attribute is missing
		throw AdSemanticGroupException (__FILE__,__LINE__,METHOD,WMS_JDLGROUP,JDL::DATA_REQUIREMENTS);
	}catch (AdMismatchException &exc){
		// wrong type for some attribute
		throw AdMismatchException (__FILE__,__LINE__,METHOD,WMS_JDLSYN,JDL::DATA_REQUIREMENTS,string(exc.what()));
	}
}
void JdlAttributeList::checkAd(const string& attr_name, ClassAd* attr_value)   {
	JDLATTR_SET_METHOD("checkAd(const string& attr_name, ClassAd* attr_value)");
	const string sepStr =  "$STR$"  ;
	ExprTree* tree ;
	Value val ;
	if(  (findAttribute(attr_name)) && (!findAd(attr_name)) ){
		throw  AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name) ;
	}else if (compare(attr_name,JDL::DATA_REQUIREMENTS)){
		checkDataRequirements(Ad(*attr_value));
	} else if (   compare (attr_name ,   JDL::OUTPUTDATA )   ){
		//     checked  Value = OD_OUTPUT_FILE
		tree = attr_value->Lookup ( JDL::OD_OUTPUT_FILE );
		if ( tree == NULL)
			throw AdSemanticMandatoryException ( __FILE__ , __LINE__ ,METHOD,
				WMS_JDLSYN ,JDL::OUTPUTDATA+"." +JDL::OD_OUTPUT_FILE ) ;
		// if (  !attr_value->EvaluateAttr(JDL::OD_OUTPUT_FILE , val )  )
		if (  !attr_value->EvaluateExpr(tree , val )  )
			throw AdClassAdException (__FILE__ , __LINE__ ,METHOD,
				WMS_JDLSYN , "ClassAd::EvaluateExpr");
		if (  val.IsListValue() )
			throw AdListException( __FILE__ , __LINE__ ,
				METHOD,WMS_JDLSYN , JDL::OUTPUTDATA + "."  + JDL::OD_OUTPUT_FILE) ;
		else if ( ! val.IsStringValue()  )
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD,
				WMS_JDLMISMATCH , JDL::OUTPUTDATA+"." +JDL::OD_OUTPUT_FILE);
		//  checked Value = OD_LOGICAL_FILENAME
		tree = attr_value->Lookup ( JDL::OD_LOGICAL_FILENAME );
		if ( tree != NULL){
			// if (!attr_value->EvaluateAttr(JDL::OD_LOGICAL_FILENAME , val ))
			if (  !attr_value->EvaluateExpr(tree , val )  )
			throw AdClassAdException (__FILE__ , __LINE__ ,METHOD,
				WMS_JDLSYN , "ClassAd::EvaluateExpr");
			string lfn ;
			if (  val.GetType() == Value::LIST_VALUE  )
				throw AdListException( __FILE__ , __LINE__ ,METHOD,
					WMS_JDLSYN , JDL::OUTPUTDATA + "."  + JDL::OD_LOGICAL_FILENAME) ;
			else if (  !val.IsStringValue( lfn  )  )
				throw AdMismatchException (__FILE__ , __LINE__ ,METHOD,
					WMS_JDLMISMATCH , JDL::OUTPUTDATA + "."  + JDL::OD_LOGICAL_FILENAME );
				vector<string> vec = split (lfn , ":") ;
				if (vec[0] != "lfn")
					throw AdFormatException (__FILE__ , __LINE__ ,METHOD,
						WMS_JDLMISMATCH , attr_name , "lfn:<value>") ;
				if (checkFormat(  sepStr+sp(":")+ sepStr , lfn) )
					throw AdFormatException (__FILE__ , __LINE__ ,METHOD,
						WMS_JDLMISMATCH , attr_name , "lfn:<value>") ;
		}
	}
}

void JdlAttributeList::checkString(const string& attr_name, const string& attr_value){
JDLATTR_SET_METHOD("checkString(const string& attr_name, const string& attr_value)");
	if (findAttribute(attr_name)){
		//The attribute name exists:
		if ((!findString(attr_name))&&(!findExpr(attr_name))){
			throw AdMismatchException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH , attr_name) ;
		}
		string format;
		vector<string> vec ;
		const string sepStr =  "$STR$"  ;
		const string sepInt =  "$INT$"  ;
		//Ce_id Check
		if (  compare (attr_name , JDL::CEID ) || compare (attr_name  , JDL::SUBMIT_TO ) ){
			format=sepStr+sp(":")+ sepInt+ sp("/") +sepStr +sp("-") +sepStr +sp("-") +sepStr ;
			if (checkFormat(format, attr_value))
				throw AdFormatException (__FILE__, __LINE__, METHOD, WMS_JDLMISMATCH,
					attr_name, "<full-hostname>:<port-number>/jobmanager-<service>-<queuename>");
		}
		//ReplicaCatalog Check
		else if ( compare (attr_name ,  JDL::REPLICA_CATALOG  )){
			format=sepStr+sp("://")+ sepStr+ sp(":") +sepInt +sp("/") +sepStr;
			if (checkFormat(format , attr_value) )
				throw  AdFormatException (__FILE__, __LINE__, METHOD, WMS_JDLMISMATCH,
				attr_name, "<protocol>://<address>:<port>/<DN>") ;
		}
		//Environment Check
		else if (compare (attr_name ,   JDL::ENVIRONMENT)){
			format=sepStr+sp("=")+ sepStr ;
			if (checkFormat(format , attr_value) )
				throw AdFormatException (__FILE__, __LINE__, METHOD, WMS_JDLMISMATCH,
				attr_name, "<variable>=<value>") ;
		}
		//InputData Check
		else if (compare (attr_name ,   JDL::INPUTDATA) ){
			vec = split (attr_value , ":") ;
			if ( (vec[0] != "lfn")&&(vec[0] != "guid")&&(vec[0] != "si-lfn")&&(vec[0] != "si-guid") )
				throw AdFormatException (__FILE__, __LINE__, METHOD, WMS_JDLMISMATCH,
					attr_name, "lfn | guid | si-lfn | si-guid :<value>");
			format=sepStr+sp(":")+ sepStr ;
			if (checkFormat(format , attr_value) )
				throw AdFormatException (__FILE__, __LINE__, METHOD, WMS_JDLMISMATCH,
					attr_name, "lfn | guid | si-lfn | si-guid :<value>");
		}
		//UserContact Check
		else if ( compare (attr_name ,   JDL::USER_CONTACT) ){
			if ( count (attr_value , "@" )  != 1 )
				throw AdFormatException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH ,
					attr_name , "<user>@<host name>") ;
		}else if ( compare (attr_name ,   JDL::STDOUTPUT) ){
				//StdOutput Check
				if (  attr_value.find("..") ==0  )
					throw AdFormatException (__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH ,
						attr_name , "<absolute path>|<directory relative path>") ;
		}else if(compare( attr_name , JDL::STDOUTPUT) ||
			compare( attr_name  , JDL::STDINPUT)  ||
			compare (attr_name  , JDL::EXECUTABLE)||
			compare (attr_name  , JDL::STDERROR)){
				// WildCards check
					const string wildcards  [JDL_ARRAY] = {"*","{","}","[","]","?"};
					for (int i = 0  ;  i < 6 ; i++ ){
						if(attr_value.find(wildcards[i])<attr_value.size()){
							throw AdFormatException(__FILE__,__LINE__,METHOD,WMS_JDLMISMATCH,
								attr_name ,"wildcards not allowed");
						}
					}
		} else if(compare (attr_name ,JDL::ISB_BASE_URI)||compare (attr_name ,JDL::WMPISB_BASE_URI)){
				format=sepStr+sp("://")+ sepStr ;
				if (checkFormat(format , attr_value) ){
					throw AdFormatException(__FILE__ , __LINE__ ,METHOD, WMS_JDLMISMATCH,
						attr_name,"protocol://address") ;
				}
			}
	} // end if findAttribute
};

} // jdl namespace
} // glite namespace
