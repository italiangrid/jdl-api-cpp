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

#ifndef GLITE_WMS_COMMON_REQUESTAD_ADCONVERTER_H
#define GLITE_WMS_COMMON_REQUESTAD_ADCONVERTER_H
/*
 * AdConverter.h
 * Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
 * Contributors are mentioned in the code where appropriate.
 */
#include "Ad.h"
#include "DAGAd.h"
#include "collectionad.h"
#include "ExpDagAd.h"
#include "JdlAttributeList.h"
#include <classad_distribution.h>
namespace glite {
namespace jdl {

/**
* Used to design the dependency structure among the nodes of a dag.
* Each node specifies its name and all the nodes that directly depend on it.
* when the name is NULL this structure does not represent an actual node, but it lists all the nodes that don't depend on any other node.
*/
struct NodeStruct {

	/**Default Constructor*/
	NodeStruct();

	/**Name Constructor*/
	NodeStruct(std::string* name);
	
	/**Copy Constructor*/
	NodeStruct(const NodeStruct& node);
	
	/** Distructor */
	~NodeStruct();

	/** Operator = */
	NodeStruct& operator=(const NodeStruct& node);
	
	/** The name of the node */
	std::string* name ;

	/** The list of all the node that depend on this node (0-size vector if empty)*/
	std::vector< NodeStruct* > childrenNodes ;
	
private:

	/** Method to be invoked by the destructor and assign operator to free
	* allocated memory in childrenNodes vector
	*/
	void flushMemory(void);	
};


/**
 * AdConverter deifines a series of utiliteis as separate static methods that allow the user to convert a Jdl into several different classad representation.
 * it manages partitioner, collection and parametric jdls converting internally into an ExpDagAd clas instance.
 * It also provide a set of utilities to easily create valid jdl template for simple Jobs (even with jobtype different from "normal")
 * Dags or Collection of jobs;  just by specifing a few parameters.
 *
 * @brief utilities for converting classad expression into requestad known classes and to create JobAd/ExpDagAd templates instances
 *
 * @version 0.1
 * @date 2004
 * @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
*/
class AdConverter {
public:
	/**
	* Enum used to specify the Jobtype of a job
	* Notice: muliple job type can be obtained by bitwise '|' operator.
	* @see createJobTemplate*/
	enum jobtype {
		/*** Normal Jobs */
		ADCONV_JOBTYPE_NORMAL=1,
		/*** Parametric Jobs */
		ADCONV_JOBTYPE_PARAMETRIC =2,
		/***  Interactive Jobs */
		ADCONV_JOBTYPE_INTERACTIVE=4,
		/*** Mpi Jobs */
		ADCONV_JOBTYPE_MPICH=8,
		/*** PArtitionable Jobs */
		ADCONV_JOBTYPE_PARTITIONABLE=16,
		/*** Checkpointable Jobs */
		ADCONV_JOBTYPE_CHECKPOINTABLE =32
	};
	/**
	* Enum used to specify which attribute(s) are to be parametrised
	* Notice: muliple attributes can be obtained by bitwise '|' operator.
	* @see createStringParametricTemplate
	* @see createIntParametricTemplate
	*/
	enum attribute {
		/*** InputSandbox */
		ADCONV_ATTR_INPUTSB=1,
		/*** InputData */
		ADCONV_ATTR_INPUTDATA =2,
		/***  Arguments */
		ADCONV_ATTR_ARGUMENTS=4
	};

	/**@name Template creation:*/
	//@{
	/**
	* Create a valid JDL ready for submission.
	* @param type the jobtype of the job. Multiple jobtype can be specified toghether through the bitwise '|' operator  ( as specified in #jobtype)
	* @param executable the simple file name to be executed (if local) or the full path if stored in the remote machine. In the former case the full path of the file must be specified in the inputsandbox attribute
	* @param arguments a string representing the arguments (if needed) of the executable file (empty "" string if not needed)
	* @param requirements a string representing the expression describing all the Job requirements (which is an attribute of boolean type)
	* @param rank a string representing the expression for the rank (which is an attribute of double type) of the resource
	* @param vo the VirtualOrganisation name to be used
	* @return the JobAd template instance
	*/
	static JobAd* createJobTemplate (int type, const std::string &executable, const std::string &arguments,
					const std::string &requirements, const std::string &rank, const std::string &vo="" ) ;
	/** Create a valid Parametric
	* @param parametrised all the attributes that contains reference to a parameter.
	* @param parameters a vector containing all the parameters
	* @param requirements a string representing the expression describing all the Job requirements (which is an attribute of boolean type)
	* @param rank a string representing the expression for the rank (which is an attribute of double type) of the resource
	* @param vo the VirtualOrganisation name to be used
	* @return the JobAd of a parametric job
	*/
	static JobAd* createStringParametricTemplate(std::vector<std::string> parametrised, std::vector<std::string> parameters,
						const std::string &requirements, const std::string &rank, const std::string &vo="");
	// DEPRECATED
	static JobAd* createStringParametricTemplate(int parametrised ,std::vector<std::string> parameters ,
						const std::string &requirements, const std::string &rank , const std::string &vo="" ) ;
	/** Create a valid Parametric
	* @param parametrised all the attributes that contains reference to a parameter.
	* @param param_number the number of  different parameters to be created
	* @param param_start (default value is 0) the starting point where to begin to parametrise
	* @param param_step (default value is 1) the step between one parameter and the next one among param_start
	* @param requirements a string representing the expression describing all the Job requirements (which is an attribute of boolean type)
	* @param rank a string representing the expression for the rank (which is an attribute of double type) of the resource
	* @param vo the VirtualOrganisation name to be used
	* @return the JobAd of a parametric job  */
	static JobAd* createIntParametricTemplate(std::vector<std::string> parametrised, int param_number, int param_start,
						int param_step, const std::string &requirements, const std::string &rank,
						const std::string &vo="");
	// DEPRECATED
	static JobAd* createIntParametricTemplate(int parametrised, int param_number, int param_start, int param_step,
						const std::string &requirements, const std::string &rank, const std::string &vo="");
	/**
	* Create a valid template JDL for a Dag
	* @param dependencies the dependency structure of the dag: each node must list all the nodes that depends on it.
	* @param requirements a string representing the expression describing the requirements (which is an attribute of boolean type) for all the nodes of the dag
	* @param rank a string representing the expression for the rank (which is an attribute of double type) for all the nodes of the dag
	* @param vo the VirtualOrganisation name to be used for all the nodes of the dag
	* @return the ExpDagAd template istance
	*/
	static ExpDagAd* createDAGTemplate(NodeStruct dependencies, const std::string &requirements, const std::string &rank,
						const std::string &vo="");
	/**
	* Create a valid template JDL for a Collection of jobs
	* @param jobNumber the number of jobs to be created for the collection
	* @param requirements a string representing the expression describing the requirements (which is an attribute of boolean type) for all the jobs in the collection
	* @param rank a string representing the expression for the rank (which is an attribute of double type) for all the jobs in the collection
	* @param vo the VirtualOrganisation name to be used by all the jobs in the collection
	* @return the Collection created
	*/
	static CollectionAd* createCollectionTemplate (unsigned int jobNumber,const std::string &requirements, const std::string &rank,
					const std::string &vo="") ;
	/**
	* Load all the JDL files stored in a specified path and put them all inside a collection of jobs
	* @param path the path (including wildcards) where to look for JDL files to be added to the collection
	* @param vo the VirtualOrganisation name to be used by all the jobs in the collection
	* @return the Collection created
	*/
	static CollectionAd* createCollectionFromPath ( const std::string &path, const std::string &vo="");
	/**
	* Load all the JDL files stored in a specified path and create an Ad instance that represents a DagAd
	* with enmpty dependencies
	* @param path the path (including wildcards) where to look for JDL files to be added to the DagAd
	* @param vo the VirtualOrganisation name to be used by all the jobs in the collection
	* @return the Ad created
	*/
	static Ad* createDagAdFromPath (const std::string &path, const std::string &vo="");	
	/**
	* Load all the JDL files stored in a specified path and create an ExpDagAd instance
	* @param dependencies the dependency structure of the dag: each node must list all the nodes that depends on it.
	* @param path the path (including wildcards) where to look for JDL files to be added to the DagAd
	* @param vo the VirtualOrganisation name to be used by all the jobs in the collection
	* @return the ExpDagAd created
	*/
	static ExpDagAd* createDagAdFromPath (NodeStruct dependencies, const std::string &path, const std::string &vo="");
	//@}
	/**@name Ad conversion:*/
	//@{
	/**
	* utility that converts the jdl of a partitioner job into a DagAd
	* @param jdl string representing the classad of a partitioner job
	* @return the converted ExpDagAd instance
	*/
	static ExpDagAd* part2dag (  const std::string &jdl ) ;
	/**
	* utility that converts the jdl of a partitioner job into a DagAd
	* @param ad the ClassAd representing the JDL of a partitioner job
	* @return the converted ExpDagAd instance
	*/
	static ExpDagAd* part2dag ( Ad* ad ) ;
	/**
	* utility that converts the jdl of a collection into a DagAd
	* @param jdl string representing the classad of a collection of jobs
	* @return the converted ExpDagAd instance
	*/
	static ExpDagAd* collection2dag ( const std::string &jdl ) ;
	/**
	* utility that converts the jdl of a collection into a DagAd
	* @param ad the ClassAd representing the JDL of a collection of jobs
	* @return the converted ExpDagAd instance
	*/
	static ExpDagAd* collection2dag ( Ad* ad ) ;
	/**
	* utility that converts the jdl of a parametric job into a DagAd
	* @param jdl string representing the classad of a parametric job
	* @param maxCycles the max number of cycles over parameters to be done (0 means all)
	* @return the converted ExpDagAd instance
	*/
	static ExpDagAd* bulk2dag (const std::string &jdl, unsigned int maxCycles=0)  ;
	/**
	* utility that converts the jdl of a parametric job into a DagAd
	* @param ad the ClassAd representing the JDL of a parametric job
	* @param maxCycles_i the max number of cycles over parameters to be done (0 means all)
	* @return the converted ExpDagAd instance
	*/
	static ExpDagAd* bulk2dag (Ad* ad, unsigned int maxCycles_i=0) ;
	//@}

	/**@name Static Const String Values:*/
	/** */
	static const std::string VALUES ;
	static const std::string VALUE ;
	static const std::string NODE ;
	static const std::string SIMPLE_NODE_TYPE;
	static const std::string PARAMETRIC_PARAMETERS ;
	static const std::string PARAMETRIC_START;
	static const std::string PARAMETRIC_STEP ;
	static const std::string PARAMETER_VALUE ;
}; // end AdConverter class
} // jdl namespace
} // glite namespace

#endif
//EOF
