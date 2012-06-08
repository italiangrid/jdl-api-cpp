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

#ifndef GLITE_WMS_COMMON_REQUESTAD_EXTRACTFILES_H
#define GLITE_WMS_COMMON_REQUESTAD_EXTRACTFILES_H
/*
* extractfiles.h
* Copyright (c) 2001 The European Datagrid Project - IST programme, all rights reserved.
* Contributors are mentioned in the code where appropriate.
*/

namespace glite {
namespace jdl {

	/**
	* FileAd represent a single file name entry
	*/
	struct FileAd {
		/** Default Constructor */
		FileAd(const std::string& protocol,const std::string& file, unsigned int size);
		/** Protocol */
		std::string protocol;
		/** absolute path for file*/
		std::string file;
		/** size (in Kb)*/
		unsigned int size;
		// STATIC METHOD
		/**
		* Set the max possible size for a single file
		* @param maxFileSize the value (in Kb) of biggest possible file
		*/
		inline static void setMaxFileSize(unsigned int maxFileSize){maxFileSize_i=maxFileSize;}
		private:
		static unsigned int maxFileSize_i;
	};
	/**
	* ExtractedAd represent all the extracted files for a certain job/node/dag etc
	* each FilesAd instance can have recoursively children of any kind
	*/
	class ExtractedAd{
	/**@name Constructors/Destructors/Copy*/ //@{
		public:
		/** Default Constructor */
		ExtractedAd() ;
		/** Copy Constructor */
		ExtractedAd(const ExtractedAd& jobad);
		/** Operator "=" performs a deep copy of the instance
		* @param extractedAd the source instance to be copied
		*/
		virtual void operator=(const ExtractedAd& extractedAd);
		/** Static method: Copy Constructor
		* @param source the instance to be copied
		* @param dest the pointer which will be filled with source values
		*/
		static void ExtractedAdCopy(const ExtractedAd& source, ExtractedAd* dest);
		/**Default Destructor   */
		virtual ~ExtractedAd() throw(){};
		/**
		* Deep copy the instance, including all its internal pointers.
		* This has to be done when the copied instance is supposed to survive outside the executing scope
		* @return the identical copy of the instance, with new allocated memory
		*/
		ExtractedAd* Copy();
	//@}


	/**@name SET/ADD Methods*/ //@{
		/** static method:
		* set the max possible size for the total of files contained inside instance
		* @param maxTotalSize the value (in Kb) of max total size of files contained
		*/
		static void setMaxTotalSize(unsigned int maxTotalSize);
		/**
		* Set the nodeName for the current instance
		* @param nodeName the value of the node to be set
		*/
		void setNodeName(const std::string& nodeName);
		/**
		* Set the nodeName for the specified jobid if present, raises exception otherwise
		* @param nodeName the value of the node to be set
		* @param jobid the jobid of the Node where to set the node name
		*/
		void setNodeName(const std::string& nodeName,const std::string& jobid);
		/**
		* Set the job id for the current instance
		* @param jobid the value of the job id to be set
		*/
		void setJobId(const std::string& jobid);
		/**
		* Set the jobid for the specified nodeName if present, raises exception otherwise
		* @param jobid the value of the jobid to be set
		* @param nodeName the name of the Node where to insert the jobid
		*/
		void setJobId(const std::string& nodeName,const std::string& jobid);

		/**
		* Set the files for the current instance
		* @param files the vector of files for the instance
		*/
		void setFiles(const std::vector<FileAd>& files);
		/**
		* Add a single File
		* @param file the file to be added
		*/
		void addFileAd(const FileAd& file);
		/**
		* Add a single File
		* @param path the path of the file to be added
		*/
		void addFileAd(const std::string& path);
		/**
		* Add a new Node to the children of the instance
		* @param extracted the ExtractedAd node to be added
		*/
		void addNode(ExtractedAd* extracted);
	//@}


	/**@name GET Methods*/ //@{

		// Main instance GET methods
		/**Retrieve the name of the node (if the instance represents a node)
		* @return the name of the node, empty string if not set
		*/
		const std::string  getNodeName();
		/**Retrieve the jobid
		* @return the jobid string representation, empty string if not set
		*/
		const std::string  getJobId();
		/**Retrieve only the files listed (without computing children files)
		* @return a vector containig all FilesAd listed
		*/
		const std::vector<FileAd> getFiles();
		/** Retrieve the total amount of size for files listed in the whole instance (computing children files too)
		* @return the size (in Kb)
		*/
		unsigned int getTotalSize();
		/** Retrieve the highest file size from the ones listed in the whole instance (computing children files too)
		* @return the size (in Kb)
		*/
		unsigned long getMaxJobFileSize();
		/**
		* Retrieve extracted instance for a specified node if present, raises exception otherwise
		* @param nodeName the value of the node to be retrieved
		* @return a pointer to the desired node ExtractedAd instance
		*/
		ExtractedAd* getNode (const std::string& nodeName);
		/**
		* Retrieve  extracted instance for a specified jobid if present, raises exception otherwise
		* @param jobid the value of the jobid to be retrieved
		* @return a pointer to the desired jobid ExtractedAd instance
		*/
		ExtractedAd* getJobId(const std::string& jobid);
		/**
		* Retrieve all children ExtractedAd for this instance, empty vector if no children found
		* @return a vector containing all pointers to the instance ExtractedAd children
		*/
		std::vector<ExtractedAd*> getChildren();
		/**
		* Retrieve all files for a specified node if present, raises exception otherwise
		* @param nodeName the value of the node to be retrieved
		* @return a pointer to the desired node ExtractedAd instance
		*/
		const std::vector<FileAd> getNodeNameFiles(const std::string& nodeName);
		/**
		* Retrieve all files for a specified node if present, raises exception otherwise
		* @param jobid the value of the jobid to be retrieved
		* @return a pointer to the desired node ExtractedAd instance
		*/
		const std::vector<FileAd> getJobIdFiles(const std::string& jobid);
		/**
		* Determine whether the instance or its children contain at least one file
		* @return true when at least one file has been specified inside the instance or its children,
		* false otherwise
		*/
		bool hasFiles();
	//@}
		private:
			// mapping nodeNames and jobids
			// std::map<std::string,ExtractedAd*> nodesMapppy ; // TBD
			std::string nodeName_s;
			std::string jobid_s;
			std::vector<FileAd>   files_v;
			std::vector<ExtractedAd*> children_v;
			unsigned int totalSize_i;
			unsigned long maxJobFileSize_i;
			static unsigned int maxTotalSize_i;
			bool hasFiles_b;
	};

	/**
	*
	* @brief Provides a method for extracting files from a specified path
	*
	* @version 0.1
	* @date April 2005
	* @author Alessandro Maraschini <alessandro.maraschini@datamat.it>
	*/
	enum checkType {
		EXISTENCE, /** check if file is actually stored on local machine */
		WMPROXY,   /** create extract files on server side*/
		TRANSFER,  /** create extract files from path and destination URI*/
		ONLYLOCAL  /** create extract files only from local path */
	};
	/**
	* Following the classad rules this method parses the specified path and
	* extract/transform it filling all the resulting matching files depending on called parameter
	*@param attr_name the name of the attribute that is beeing parsed
	*@param path the string representation of the path to be parsed
	*@param extracted a vector where to append matching results
	*@param lookInto_b specify whether to use the client-side ruling approach (true) or the server one (false)
	*@param wmpURI the string representation of the wmproxy Destination URI (needed for server side, empty "" string otherwise)
	*@param isbURI the string representation of the InputSandboxDestUri attribute (if provided, empty "" string otherwise)
	*@param extractedAd matched files for globbing
	*@return whether the file is stored (or to be stored) on server side (true), that means whether wmpURI has been appended
	*/
	bool extractFiles(const std::string& attr_name , const std::string& path ,
		std::vector<std::string> &extracted,checkType lookInto_b,
		const std::string &wmpURI, const std::string &isbURI,ExtractedAd *extractedAd=NULL) ;
	/**
	* Following the classad rules this method parses the specified paths and
	* extract/transform them filling all the resulting matching files depending on called parameter
	*@param attr_name the name of the attribute that is beeing parsed
	*@param paths the strings representation of all the paths to be parsed
	*@param extracted a vector where to append matching results
	*@param lookInto_b specify whether to use the client-side ruling approach (true) or the server one (false)
	*@param wmpURI the string representation of the wmproxy Destination URI (needed for server side, empty "" string otherwise)
	*@param isbURI the string representation of the InputSandboxDestUri attribute (if provided, empty "" string otherwise)
        *@param extractedAd matched files for globbing
	*@return whether the file is stored (or to be stored) on server side (true), that means whether wmpURI has been appended
	*/
	bool extractFiles(const std::string& attr_name , std::vector<std::string>& paths ,
		std::vector<std::string> &extracted,checkType lookInto_b,
		const std::string &wmpURI, const std::string &isbURI,ExtractedAd *extractedAd=NULL);

	/**
	* Following the classad rules this method parses the specified path and
	* returns, if necessary, all the files that are to be transfered on remote machine
	*@param attr_name the name of the attribute that is beeing parsed
	*@param path the string representation of the path to be parsed
	*@param result list of source/destination pairs
	*@param wmpURI the string representation of the wmproxy Destination URI (needed for server side, empty "" string otherwise)
	*@param isbURI the string representation of the InputSandboxDestUri attribute (if provided, empty "" string otherwise)
	*@return a vector of pairs. Each pair contains the source and the target string file representation
	*/
	void toBcopied(const std::string& attr_name , const std::string& path ,
		std::vector<std::pair < std::string, std::string> > &result,
		const std::string &wmpURI, const std::string &isbURI);
	/**
	* This method iteratively calls its omonimous toBcopied method for each of its path contained in paths
	*@param attr_name the name of the attribute that is beeing parsed
	*@param paths the string representation of all the paths to be analised
	*@param result list of source/destination pairs
	*@param wmpURI the string representation of the wmproxy Destination URI (needed for server side, empty "" string otherwise)
	*@param isbURI the string representation of the InputSandboxDestUri attribute (if provided, empty "" string otherwise)
	*@result a vector of pairs. Each pair contains the source and the target string file representation
	*/
	void toBcopied(const std::string& attr_name , std::vector<std::string> paths ,
		std::vector<std::pair < std::string, std::string> > &result,
		const std::string &wmpURI, const std::string &isbURI);
	/**
	* Determine whether a specified string contains or not any possible wildCard
	@ param path the string to be parsed
	@ return true when at least one wildcard has been found, false otherwise
	*/
	bool hasWildCards(const std::string& path);
} // jdl namespace
} // glite namespace
#endif
//EOF
