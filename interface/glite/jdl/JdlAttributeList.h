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

#ifndef GLITE_WMS_COMMON_REQUESTAD_JDLATTRIBUTELIST_H
#define GLITE_WMS_COMMON_REQUESTAD_JDLATTRIBUTELIST_H
/*
 * JdlAttributeList.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 *
 */
#include <list>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <classad_distribution.h>

#define JDL_ARRAY 30
#define JDLATTR_SET_METHOD(method) string METHOD = method

namespace glite {
namespace jdl {

/**
* JobAd Manipulation attribute class
* This class allow the user to know the names of all Jobad attributes and
* it is used principally by JobAd in order to perform the requested checks needed
* ro prepare for submission
*/
class  JdlAttributeList{
public:
    //Constuctor
    JdlAttributeList();
    virtual ~JdlAttributeList() throw() {};

    /**
    * Find the specified attribute among boolean values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findBool(const std::string& attr_name)    {return findAttr (attr_name , boolAttrs  );   };
    /**  
    * Find the specified attribute among integer values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findInt(const std::string& attr_name)       {return findAttr (attr_name , intAttrs   );   };
    /**  
    * Find the specified attribute among string values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findString(const std::string& attr_name)  {return findAttr (attr_name , stringAttrs);   };
    /**  
    * Find the specified attribute among double values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findDouble(const std::string& attr_name){return findAttr (attr_name , doubleAttrs);   };
    /**  
    * Find the specified attribute among Ad values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findAd(const std::string& attr_name)      {return findAttr (attr_name , adAttrs);   };
    /**  
    * Find the specified attribute among list values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findList(const std::string& attr_name)     {return findAttr (attr_name , listAttrs  );   };
    /**  
    * Find the specified attribute among expression values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findExpr(const std::string& attr_name)   {return findAttr (attr_name , exprAttrs  );   };
    /**
    * Find the specified attribute among to-be-checked values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findCheck(const std::string& attr_name){ return findAttr (attr_name , checkAttrs  );   };
    /**
    * Find the specified attribute among all known values
    * @param attr_name the name of the attribute to be found
    * @return true if found, false otherwise
    */
    bool  findAttribute(const std::string& attr_name) ;
    /**
    * Find the specified attribute among all known values.
    * Case INSENSITIVE
    * @param attr_name the name of the attribute to be found
    * @param values the set of values to be looked up to
    * @return true if found, false otherwise
    */
    bool  findAttr (const std::string& attr_name , std::vector<std::string>  values) const ;
    /**
    * Find the specified attribute among the provided list.
    * case SENSITIVE, attr_name can be just the tail of the value
    * @param attr_name the name of the attribute to be found
    * @param values the set of values to be looked up to
    * @return true if found, false otherwise
    */
    bool  findTail (const std::string& attr_name , std::vector<std::string>  values) const ;
                       /**@name Check Methods*/
 //@{
     /**Check if the couple attribute/value is admitted
     * @param attr_name - the name of the attribute
     * @param attr_value - the value of the attribute
     * @exception AdMismatchException - The type of value is not allowed for the specified attribute name     */
     void checkInt(const std::string& attr_name, int attr_value)  ;
     /**Check if the couple attribute/value is admitted
     * @param attr_name - the name of the attribute
     * @param attr_value - the value of the attribute
     * @exception AdMismatchException - The type of value is not allowed for the specified attribute name     */
     void checkDouble(const std::string& attr_name, const double& attr_value)  ;
     /**Check if the couple attribute/value is admitted
     * @param attr_name - the name of the attribute
     * @param attr_value - the value of the attribute
     * @exception AdMismatchException - The type of value is not allowed for the specified attribute name     */
     void checkBool(const std::string& attr_name, const bool& attr_value)    ;
     /**Check if the couple attribute/value is admitted
     * @param attr_name - the name of the attribute
     * @param attr_value - the value of the attribute
     * @exception AdMismatchException - The type of value is not allowed for the specified attribute name     */
     void checkString(const std::string& attr_name, const std::string& attr_value) ;
     /**Check if the couple attribute/value is admitted
     * @param attr_name - the name of the attribute
     * @param attr_value - the value of the attribute
     * @exception AdMismatchException - The type of value is not allowed for the specified attribute name     */
     void checkAd(const std::string& attr_name, classad::ClassAd* attr_value) ;
     /**Check if the couple attribute/value is admitted
     * @param attr_name - the name of the attribute
     * @param attr_value - the value of the attribute
     * @exception AdMismatchException - The type of value is not allowed for the specified attribute name
     * @exception AdFormatException - The type of value is not allowed for the specified attribute name     */
     void checkExpr(const std::string& attr_name, const std::string& attr_value)  ;

     /** Defatul attribute list */
     enum Attr {
        JOBTYPE_MPICH_REQ_RTE,
        JOBTYPE_MPICH_REQ_CPU,
        JOBTYPE_MPICH_RANK_FREE,
        REQ_DEFAULT,
        RANK_DEFAULT,
        MAX_ATTR
     } ;
     /**
     * Set the value for a default attribute
     *@param attr_name the attribute to be set
     *@param attr_value the string representation of the value to be set
     */
     void setDefault ( Attr attr_name , const std::string& attr_value)  ;

 private:
    std::vector<std::string> defaultAttrs ;
    std::vector<std::string> stringAttrs ;
    std::vector<std::string>  intAttrs ;
    std::vector<std::string>  doubleAttrs;
    std::vector<std::string>  boolAttrs;
    std::vector<std::string>  adAttrs;
    std::vector<std::string>  listAttrs;
    std::vector<std::string>  exprAttrs;
    std::vector<std::string>  checkAttrs;
    // JobAd is allowed to access to all JdlAttributeList members
    friend class JobAd ;
};

} // jdl namespace
} // glite namespace

#endif



