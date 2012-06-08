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

#include "JDLAttributes.h"
#include "RequestAdExceptions.h"
#include "exception_codes.h"
#include "extractfiles.h"
#include "classad_distribution.h"
#include <iostream>
#include <glob.h>
// Boost File System
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include <boost/scoped_ptr.hpp>
// fstat needed by getFileSize
#include <sys/stat.h>
namespace fs = boost::filesystem;

using namespace std ;
using namespace classad;
namespace glite {
namespace jdl {

// Static Variable definition:
const string ALLOWED_PROTOCOLS []={  "gridftp" , "rsm"} ;
const string WILDCARDS []={"*","[","]","{","}","?","$"} ;
const string FILE_PROT="file";


#ifdef WIN		// Windows Separator
const string SEPARATOR="\\";
#else   		// Linux-Unix Separator
const string SEPARATOR="/";
#endif
const string INPUT=SEPARATOR+"input"+SEPARATOR;

// MAX SIZEs initialisation (no upper limit)
unsigned int FileAd::maxFileSize_i=0;
unsigned int ExtractedAd::maxTotalSize_i=0;

/******************************************************************
 STATIC methods :   The following utility methods are used by globIt
*******************************************************************/

unsigned int getFileSize(const std::string &path){
	struct stat file_info;
	int hd = open(path.c_str(), O_RDONLY) ;
	if (hd < 0) {
			throw AdSemanticPathException (__FILE__,__LINE__,
				"extractfiles::getFileSize", WMS_JDLEMPTY,"",path);
	}
	fstat(hd, &file_info);
	close(hd) ;
	return file_info.st_size ;
}

/* Check if simple file already exists (and return true) and if not push it back into extracted (and return false)
* remote_protocol_b specify whether this is a remote server file (full file name comparison)
* or a local path (simple file name comparison)
*/
bool addPath (const string& path ,vector<string> &extracted){
	// Check if path has been repeated
	// simple paths must have different names unless remote protocol has been specified
	vector<string>::iterator iter ;
	// string simplePath= fs::path(path, fs::system_specific).leaf();  // boost 1.29
	string simplePath= fs::path(path, fs::native).leaf();  // upgrade to boost 1.32
	// TBD a map with all simple files can be used
	for ( iter=extracted.begin() ; iter != extracted.end() ; ++iter ) {
		// Compare simple names: (files will be stored in the same directory)
				// fs::path cp(*iter, fs::system_specific);  boost 1.29
		if ( simplePath == fs::path(*iter, fs::native).leaf() ){ // upgrade to boost 1.32
			return true;
		}
	}
	extracted.push_back(path);
	return false;
}
// Check if path has wildcards (true) or not (false)
bool hasWildCards(const string& path){
	for (int i = 0 ; i< 7; i++){
		if (path.find(WILDCARDS[i])!=string::npos){
			return true;
		}
	}
	return false;
}
// check and exploit ENV variable, return false if possible
bool checkEnv (const string& prot,string& path ) {
	// Check for Environment Variables:
	unsigned int offset = (prot.size()>0)?prot.size()+3:0;
	if (path.find("$") == offset ){
		unsigned int last_char = path.find(SEPARATOR, offset);
		if (last_char==string::npos){last_char =path.size();}
		// offset + 1   	skip '$' char
		// last_char -1 	skip '/' char
		char* environ=getenv(path.substr(offset+1,last_char-1).c_str());
		if (environ == NULL){return true;}
		path= string(environ)+path.substr(last_char,path.size()-last_char);
		// Reintrocude protocol when needed
		path=((prot.size()>0)?(prot+"://"):("")  )+  path;
	}else if (path.find("$")!=string::npos) {
		// Dollar found but in a wrong position
		return true ;
	}
	return false;
}
// Retrieve the protocol from a path, empty ("") string otherwise
const std::string getProtocol (const string& path){
	string::size_type pos = path.find("://");
	if (pos != string::npos){
		// Protocol Found
		return path.substr(0, pos);
	}
	// Protocol NOT Found
	return "";
}
void globl(vector<std::string>& matches, std::string const & pattern)
{
  glob_t glob_buffer;
  glob_buffer.gl_offs = 0;
  glob(pattern.c_str(), 0, 0, &glob_buffer);

  matches.insert(
    matches.end(),
    glob_buffer.gl_pathv,
    glob_buffer.gl_pathv + glob_buffer.gl_pathc
  );

  globfree(&glob_buffer);
}
/**
* exploit the path of a local file
* and push all matched files inside extracted vector
* return 0 in case of SUCCESS
* return WMS_JDLMANDATORY (path does not exists)
* or 	WMS_JDLDUPLICATE  (path already exists) in case of error
*/
int globIt (const string& prot,const string& path,vector<string> &extracted,ExtractedAd *extractedAd){
	// Check for actual File Existence on HDhasWildCards(const string& path){
	//glob_t  *pglob ;
	vector<string> vglob ;
	// Retrieve files from path
	int gl ;
	if (prot==""){
		globl( vglob, path.c_str());
	}else{
		globl( vglob, path.substr(prot.size() + 3,string::npos).c_str() );
	}
	if  ( vglob.size()==0 ) {
		return WMS_JDLMANDATORY;
	} // check if path exists
	// Retrieve the absolute current path
	string cwd = "";
	string buff ;
	long size ;
	size = pathconf(".", _PC_PATH_MAX);
	buff = (size_t)size ;
	if (buff != ""){ cwd = boost::filesystem::current_path().string(); }
	if (buff == ""){
		return WMS_JDLMANDATORY;
	}
	string abs = cwd ;
	for  (int i=0 ; i< vglob.size() ; i++)  {
		string attr_value = vglob[i] ;
		if (attr_value.find("."+SEPARATOR) ==0) {   attr_value = abs + attr_value.substr(1) ; }
		if (attr_value.find(SEPARATOR) !=0) { attr_value = abs +SEPARATOR+  attr_value ;  }
		// check if value is suitable and update extracted
		if (hasWildCards(attr_value)){
			// Evaluated file cannot contain WildCards
			return WMS_JDLMISMATCH;
		}
		if (addPath (FILE_PROT+"://"+attr_value , extracted )){
			return WMS_JDLDUPLICATE;
		}
		if(extractedAd){
			// filesAd active: append value
			extractedAd->addFileAd(FileAd(FILE_PROT,attr_value,getFileSize(attr_value)));
		}
	}
	// Release (if used) memory
	//free (pglob) ;
	//free (buff);
	return 0;
}

/******************************************************************
 STATIC method :   extractFiles
 Extract all files from a specified path
*******************************************************************/
bool extractFiles(const std::string& attr_name , std::vector<std::string>& paths ,
		std::vector<std::string> &extracted,checkType lookInto_b,
		const std::string &wmpURI, const std::string &isbURI,
		ExtractedAd *extractedAd){
	bool toBretrieved= false;
	for (unsigned int i= 0 ; i< paths.size() ; i++){
		toBretrieved = extractFiles(attr_name,paths[i],extracted,lookInto_b,wmpURI,isbURI,extractedAd)||toBretrieved;
	}
	return toBretrieved ;
}
/**
* Check and (if necessary) Extract all matching files from a given path
* possible lookInto_b values:
* EXISTENCE - CLIENT side: check local files & extract wildcards
* WMPROXY   - SERVER side: do not look for local existence
* TRANSFER  - retrieves only files to be transferred (exclude all remote-server paths)
		this value behaves as WMPROXY, but it does not append "INPUT" directory
* ONLYLOCAL - CLIENT side: retrieve only files that are actually stored in the local machine
*
**/
bool extractFiles(const string& attr_name, 
		  const string& _path, 
		  vector<string> &extracted,
		  checkType lookInto_b,
		  const std::string &wmpURI, 
		  const std::string &isbURI,
		  ExtractedAd *extractedAd )
{
  string path = _path;
  if(path.length()>1 && path.at(0) == '/')
    path = string("file://") + path;

  //  cout << "extractFiles - path=" << path << endl;
  string METHOD = "extractFiles(const string& path, const string& path, vector<string> &extracted)";
  string mpath= path;
  string prot=getProtocol(path);
  bool toBretrieved= false;

  if(lookInto_b== WMPROXY||lookInto_b== TRANSFER){
    // It's a Server (or Transfer) Access domain, never check existence
    if (wmpURI.empty()){
      if(lookInto_b== WMPROXY){
	throw AdSemanticMandatoryException(__FILE__,__LINE__,
					   METHOD,WMS_JDLMANDATORY,JDL::WMPISB_BASE_URI);
      } else{
	throw AdSemanticMandatoryException(__FILE__,__LINE__,
					   METHOD,WMS_JDLMANDATORY, "Destination Uri");
      }
    }
    if(prot==FILE_PROT){
      // UI local machine, strip simple address and append baseURI
      unsigned int offset=mpath.find_last_of(SEPARATOR);
      if (offset==string::npos) {offset=0;}
      else {offset+=1;}
      // Append wmpURI to simple file name:
      // On WMPROXY side append INPUT directory name
      if (lookInto_b==WMPROXY){mpath = wmpURI+INPUT+mpath.substr(offset,string::npos);}
      // On TRANSFER side wmpURI already contains input directory name
      else{mpath = wmpURI+SEPARATOR+mpath.substr(offset,string::npos);}
      toBretrieved = true ;
    }else if (prot==""){
      // NO protocol Found
      if (isbURI!=""){
	// Append ISBuri when present
	mpath =isbURI+SEPARATOR+mpath;
	toBretrieved = false;
      }else{
	
	unsigned int offset=mpath.find_last_of(SEPARATOR);
	if (offset==string::npos) {offset=0;}
	else {offset+=1;}				
	// On WMPROXY side append INPUT directory name
	if (lookInto_b==WMPROXY){mpath =wmpURI+INPUT+mpath.substr(offset,string::npos);}
	// On TRANSFER side wmpURI already contains input directory name
	else{mpath = wmpURI+SEPARATOR+mpath.substr(offset,string::npos);}
	toBretrieved = true ;
      }
    }else {
      // PROTOCOL SPECIFIED BUT DIFFERENT from file://
      toBretrieved = false;
    }
    // else leave already protocolled path unchanged
    // Try and Add the path
    if (  addPath(mpath, extracted)  ){
      throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
				     WMS_JDLDUPLICATE,attr_name,fs::path(mpath, fs::native).leaf());
    }
    // Wildcards are NOT allowed
    if (hasWildCards(mpath)){
      throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
				     WMS_JDLMISMATCH,attr_name,path);
    }
  }else if(lookInto_b== EXISTENCE||lookInto_b== ONLYLOCAL){    // either EXISTENCE  OR ONLYLOCAL
    // It's a Client Access domain
    bool tbGlobed = true;
    if (prot==FILE_PROT){
      // "file://" protocol specified, check existence
      toBretrieved = true ;
      tbGlobed=true ;
    } else if (prot !=""){
      // remote protocol specified, do not check existence (remote file)
      tbGlobed=false ;
      toBretrieved= false;
    } else{
      tbGlobed=(isbURI=="");
      toBretrieved=(isbURI=="");
    }
    if (tbGlobed){
      // Check for Environment Variables:
      if ( checkEnv (prot,mpath) ){
	throw AdSemanticPathException (__FILE__ , __LINE__ ,METHOD,
				       WMS_JDLMANDATORY, attr_name ,path);
      }
      int glob_code = globIt (prot,mpath, extracted, extractedAd);
      if (glob_code) {
	if (lookInto_b != ONLYLOCAL || glob_code != WMS_JDLDUPLICATE){
	  // ONLY LOCAL tag accepts multiple file name (global scopes TBD why?)
	  throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
					 glob_code,attr_name,path);
	}
      }
    }else if (lookInto_b==EXISTENCE){  // following files are not local
      // Try and add the path
      if (addPath (mpath, extracted)){
	throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
				       WMS_JDLDUPLICATE,attr_name,
				       fs::path(mpath, fs::native).leaf());
      }
      // wildcards are not allowed
      if (hasWildCards(mpath)){
	throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
				       WMS_JDLMISMATCH,attr_name,path);
      }
    }
  }else {
    // this case is just to prevent unwilling situation
    // the program should never arrive here
    throw AdSemanticPathException (__FILE__,__LINE__,METHOD,
				   WMS_JDLMISMATCH,
				   "extractFiles FATAL ERROR",
				   "UnexpectedlookInto_b TYPE");
  }
  return toBretrieved ;
}
/**
* Determinewhich files are going to be retrieved for a certain path
**/
void toBcopied (const std::string& attr_name , const std::string& path ,
		std::vector<std::pair < std::string, std::string> > &result,
		const std::string &wmpURI, const std::string &isbURI) {
	vector<string> extracted, remotExtracted ;
	// Extract LOCAL files:
	if (extractFiles(attr_name, path,extracted,EXISTENCE, wmpURI, isbURI)){
		for (unsigned int i = 0 ; i< extracted.size(); i++){
			// create a pair for each entry: source and destination files
			if (extractFiles(attr_name, extracted[i], remotExtracted, TRANSFER, wmpURI, isbURI)){
				result.push_back (pair< string, string>(extracted[i],remotExtracted.back())) ;
			}
		}
	}
}
/**
* Determinewhich files are going to be retrieved for a certain set of path
**/
void toBcopied(const std::string& attr_name , std::vector<std::string> paths ,
		std::vector<std::pair < std::string, std::string> > &result,
		const std::string &wmpURI, const std::string &isbURI){
	for (unsigned int i = 0 ; i< paths.size() ; i++){
		toBcopied (attr_name , paths[i] , result , wmpURI , isbURI) ;
	}
}
/**********************
*  FileAd Class
**********************/
FileAd::FileAd(const std::string& protocol,const std::string& file, unsigned int size){
	if (maxFileSize_i && size>maxFileSize_i){
		throw AdExtractedException(__FILE__,__LINE__,
			"FileAd::FileAd",
			WMS_JDLTOOMANY,file+": max size exceeded");
	}
	this->protocol=protocol;
	this->file=file;
	this->size=size;
}

/**********************
*  ExtractedAd Class
**********************/
// STATIC COPY METHOD (needed by constructors and copy methods)
void ExtractedAd::ExtractedAdCopy(const ExtractedAd& source, ExtractedAd* dest){
	dest->nodeName_s  = source.nodeName_s;
	dest->jobid_s     = source.jobid_s;
	dest->totalSize_i = source.totalSize_i;
	dest->maxJobFileSize_i = source.maxJobFileSize_i;
	dest->files_v     = source.files_v;
	dest->hasFiles_b  = source.hasFiles_b;
	std::vector<ExtractedAd*> resultChildren;
	std::vector<ExtractedAd*>::const_iterator it = source.children_v.begin() ;
	std::vector<ExtractedAd*>::const_iterator const end = source.children_v.end();
	for ( ; it!=end; it++){
		dest->children_v.push_back((*it)->Copy());
	}
}
// STATIC MAX SIZE METHOD
void ExtractedAd::setMaxTotalSize(unsigned int maxTotalSize){maxTotalSize_i=maxTotalSize;}
// Constructors:
ExtractedAd::ExtractedAd(){
	nodeName_s="";
	jobid_s="";
	totalSize_i=0;
	maxJobFileSize_i=0;
	hasFiles_b=false;
}
ExtractedAd::ExtractedAd(const ExtractedAd& extracted){
	ExtractedAdCopy(extracted, this);
}
void ExtractedAd::operator=(const ExtractedAd& extracted){
	ExtractedAdCopy(extracted, this);
}
// Main instance GET methods
const std::string  ExtractedAd::getNodeName(){ return nodeName_s;}
const std::string  ExtractedAd::getJobId(){ return jobid_s; }
const std::vector<FileAd> ExtractedAd::getFiles(){ return files_v;}
unsigned int ExtractedAd::getTotalSize(){return totalSize_i;}
unsigned long ExtractedAd::getMaxJobFileSize(){return maxJobFileSize_i;}
bool ExtractedAd::hasFiles(){return hasFiles_b;}
// Main instance SET methods
void ExtractedAd::setNodeName(const std::string& nodeName){ nodeName_s = nodeName;}
void ExtractedAd::setJobId(const std::string& jobid){jobid_s=jobid;}
void ExtractedAd::setFiles(const std::vector<FileAd>& files){
	// check quota
	std::vector<FileAd>::const_iterator it = files.begin();
	std::vector<FileAd>::const_iterator const end = files.end();
	for ( ; it != end ; it++){
		totalSize_i += it->size;
		
		// Check if the current file size is the highest
		if(it->size > maxJobFileSize_i) {
			// Set the new max job file size
			maxJobFileSize_i = it->size;
		}
	}
	if( maxTotalSize_i && totalSize_i>maxTotalSize_i){
		throw AdExtractedException(__FILE__,__LINE__,
			"ExtractedAd::setFiles",
			WMS_JDLTOOMANY,"Max total size files exceeded");
	}
	// update files
	files_v=files;
	hasFiles_b = hasFiles_b || totalSize_i;
}
/**
* this method may be called by the below addFileAd
*/
void ExtractedAd::addFileAd(const FileAd& file){

	totalSize_i += file.size;

	// Check if the current file size is the highest
	if(file.size > maxJobFileSize_i) {
		// Set the new max job file size
		maxJobFileSize_i = file.size;
	}
	
	
	if( maxTotalSize_i && totalSize_i>maxTotalSize_i){
		throw AdExtractedException(__FILE__,__LINE__,
			"ExtractedAd::addFileAd",
			WMS_JDLTOOMANY,"Max total size files exceeded");
	}
	files_v.push_back(file);
	hasFiles_b=true;
}
/**
* this method calls the above addFileAd
*/
void ExtractedAd::addFileAd(const string& path){
	string::size_type pos = path.find("://");
	if (pos != string::npos){
	  // Protocol Found: append file only when LOCAL
	  
	  //	  cout << "ExtractedAd::addFileAd(1) - path=" << path << endl;
	  
	  if (path.substr(0,pos)==FILE_PROT){
	    //	    cout << "ExtractedAd::addFileAd(2) - path=" << path << endl;
	    addFileAd (FileAd(FILE_PROT,path.substr(pos+3),getFileSize(path.substr(pos+3))));
	  }
	}else{
	  //	  cout << "ExtractedAd::addFileAd(3) - path=" << path << endl;
	  addFileAd(FileAd(FILE_PROT,path,getFileSize(path)));
	}
}
// children GET methods
std::vector<ExtractedAd*> ExtractedAd::getChildren(){return children_v;}
ExtractedAd* ExtractedAd::getNode(const std::string& nodeName){
	assert(! nodeName.empty());
	std::vector<ExtractedAd*>::const_iterator it = children_v.begin() ;
	std::vector<ExtractedAd*>::const_iterator const end = children_v.end();
	// a map may be more efficent
	for ( ; it != end ; it++){
		if ((*it)->getNodeName()==nodeName){return *it;}
	}
	// Unable to find node
	throw AdExtractedException(__FILE__,__LINE__,
		"ExtractedAd::getNode(const std::string& nodeName)",
		WMS_JDLEMPTY, "Unable to find node: "+nodeName);
;
}
ExtractedAd* ExtractedAd::getJobId(const std::string& jobid){
	assert(! jobid.empty());
	std::vector<ExtractedAd*>::iterator it = children_v.begin() ;
	std::vector<ExtractedAd*>::iterator const end = children_v.end();
	// a map may be more efficent
	for ( ; it != end ; it++){
		if ((*it)->getJobId()==jobid){return *it;}
	}
	// Unable to find node
	throw AdExtractedException(__FILE__,__LINE__,
		"ExtractedAd::getJobId(const std::string& jobid)",
		WMS_JDLEMPTY, "Unable to find jobid: "+jobid);
}
const std::vector<FileAd> ExtractedAd::getNodeNameFiles(const std::string& nodeName){
	return getNode(nodeName)->getFiles();
}
const std::vector<FileAd> ExtractedAd::getJobIdFiles(const std::string& jobid){
	return getJobId(jobid)->getFiles();
}
// children SET/ADD methods
void ExtractedAd::addNode(ExtractedAd* extracted){
	if (extracted->hasFiles()){
		totalSize_i += extracted->totalSize_i;
		
		// Check if the max job file size is the highest
		if(extracted->maxJobFileSize_i > maxJobFileSize_i) {
			// Set the new max job file size
			maxJobFileSize_i = extracted->maxJobFileSize_i;
		}
		
		hasFiles_b = hasFiles_b || extracted->hasFiles_b;
		children_v.push_back(extracted);
	}
}
void ExtractedAd::setNodeName(const std::string& nodeName,const std::string& jobid){
	getJobId(jobid)->setNodeName(nodeName);
}
void ExtractedAd::setJobId(const std::string& nodeName,const std::string& jobid){
	getNode(nodeName)->setJobId(jobid);
}
// copy Method
ExtractedAd* ExtractedAd::Copy(){
	ExtractedAd *result = new ExtractedAd();
	ExtractedAdCopy (*this, result );
	return result ;
}
} // jdl namespace
} // glite namespace

// EOF





