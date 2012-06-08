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

#ifndef GLITE_WMS_COMMON_CLIENT_JOBADEXCEPTIONS_H
#define GLITE_WMS_COMMON_CLIENT_JOBADEXCEPTIONS_H

#define GLITE_STACK_JDL_CATCH(exc_name)catch(exc_name &exc){exc.push_back(__FILE__,LINE,METHOD);throw;}
#define GLITE_STACK_JDL_CATCH_ALL() }\
GLITE_STACK_JDL_CATCH(AdSemanticMandatoryException) \
GLITE_STACK_JDL_CATCH(AdSemanticPathException) \
GLITE_STACK_JDL_CATCH(AdSemanticGroupException) \
GLITE_STACK_JDL_CATCH(AdMismatchException) \
GLITE_STACK_JDL_CATCH(AdFormatException) \
GLITE_STACK_JDL_CATCH(AdListException) \
GLITE_STACK_JDL_CATCH(AdEmptyException) \
GLITE_STACK_JDL_CATCH(AdExtractedException) \
GLITE_STACK_JDL_CATCH(glite::wmsutils::exception::Exception) \
catch(std::exception &ex){glite::wmsutils::exception::Exception \
exc(__FILE__,__LINE__,METHOD,0,"Standard exception: "+std::string(ex.what()));throw exc;}

/*
 * RequestAdExceptions.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */
#include "glite/wmsutils/exception/Exception.h"
namespace glite {
namespace jdl {

/**
 * RequestAdException
 * This Exception is thrown when a bad usage of the JobAd class is made
 * @ingroup Common
 * @version 0.1
 * @date 15 April 2002
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
*/

class RequestAdException : public glite::wmsutils::exception::Exception {
 public:
	const char* what() throw();
 protected:
	/**
	* Update all mandatory Exception Information
	*/
	RequestAdException (std::string file,
					int line,
					std::string method,
					int code,
					std::string exception_name) ;
	virtual ~RequestAdException() throw () {};
	std::string          error_description ;
};//End CLass  RequestAdException


/**
* AdClassAdException - raised when ClassAd error is checked during add/set methods
*/
class AdClassAdException   : public RequestAdException {
public:
  AdClassAdException (std::string file,
                                      int line,
                                     std::string method,
                                      int code ,
                                     std::string method_name ,
                                     std::string error_description = "");
};//End CLass  AdClassAdException



/**
* AdSyntaxException - raised when syntax error is checked during add/set methods
*/
class AdSyntaxException   : public RequestAdException {
public:
  AdSyntaxException (std::string file,
                                      int line,
                                     std::string method,
                                      int code ,
                                     std::string attr_name );
};//End CLass  AdSyntaxException



/**
* AdSemanticException - raised while checking the whole constructed JobAd with the check() method
*/
class AdSemanticException : public RequestAdException {
public:
  /**
   * Raised when mandatory attribute is missing, unable to find a specified path, wrong attribute coexistence
  */
  AdSemanticException (std::string file,
                                      int line,
                                     std::string method,
                                      int code,
                                     std::string exception_name );
};//End CLass  AdSemanticException

     /**
     * AdSemanticMandatoryException - raised when a mandatoty attribute is missing to the classAd
     */
     class AdSemanticMandatoryException : public AdSemanticException {
        public:
        /**
        * Raised when mandatory attribute is missing, unable to find a specified path, wrong attribute coexistence
        */
        AdSemanticMandatoryException (std::string file,
                                        int line,
                                       std::string method,
                                        int code,
                                       std::string attr_name );
     };//End CLass  AdSemanticMandatoryException


     /**
     * AdSemanticPathException - raised when a mandatoty attribute is missing to the classAd
     */
     class AdSemanticPathException : public AdSemanticException {
        public:
        /**
        * Raised when Path attribute is missing, unable to find a specified path, wrong attribute coexistence
        */
        AdSemanticPathException (std::string file,
                                        int line,
                                       std::string method,
                                        int code,
                                       std::string attr_name,
                                       std::string path_name );
     };//End CLass  AdSemanticPathException

     /**
     * AdSemanticGroupException - raised when a mandatoty attribute is missing to the classAd
     */
     class AdSemanticGroupException : public AdSemanticException {
        public:
        /**
        * Raised when Group attribute is missing, unable to find a specified path, wrong attribute coexistence
        */
        AdSemanticGroupException (std::string file,
                                        int line,
                                       std::string method,
                                        int code,
                                       std::string attrs_name );
     };//End CLass  AdSemanticGroupException

/**
*  AdAttributeException - raised when a not admitted value is added/set to the attribute
*/
class AdAttributeException : public RequestAdException {
   public:
      AdAttributeException (std::string file,
                                      int line,
                                     std::string method,
                                      int code,
                                     std::string exception_name );
};//End CLass  AdAttibuteException

   /**
   *  AdMismatchException - raised when a not admitted value is added/set to the jdl
   */
   class AdMismatchException : public AdAttributeException {
        public:
        /**
        * AdMismatchException  Constructor
        */
        AdMismatchException (std::string file,
                                        int line,
                                       std::string method,
                                        int code,
                                       std::string attr_name,
                                       std::string error_description = ""  );

   };//End CLass  AdMismatchException

   /**
   *   AdFormatException Class
   */
   class AdFormatException : public AdAttributeException {
        public:
        /**
        *  AdFormatException  Constructor
        */
         AdFormatException(std::string file,
                                        int line,
                                       std::string method,
                                        int code,
                                       std::string attr_name,
                                       std::string format ="");
   };//End CLass  AdFormatException
   /**
   *  AdListException - raised when an add method is made on a non-list attribute
   */
   class AdListException : public AdAttributeException {
        public:
        /**
        *  AdListException  Constructor
        */
         AdListException(std::string file,
                                        int line,
                                       std::string method,
                                        int code,
                                       std::string attr_name );

   };//End CLass  AdListException


   /**
   *  AdEmptyException - raised when an set method is made on a empty attribute
   */
   class AdEmptyException : public AdAttributeException {
        public:
        /**
        *  AdEmptyException  Constructor
        */
         AdEmptyException(std::string file,
                                        int line,
                                       std::string method,
                                        int code,
                                       std::string attr_name );
   };//End CLass  AdEmptyException

/**
* AdClassAdException - raised when ClassAd error is checked during add/set methods
*/
class AdExtractedException: public RequestAdException {
public:
	AdExtractedException (std::string file,
		int line,
		std::string method,
		int code,
		std::string error_description);
};//End CLass AdExtractedAdException

} // jdl namespace
} // glite namespace

#endif
