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

///////////////////////////////////////////////////////////////
// Author: Simone Pellegrini
// Mail: simone.pellegrini@cnaf.infn.it
///////////////////////////////////////////////////////////////

#ifndef GLITE_WMS_COMMON_REQUESTAD_GRAMMAR_H
#define GLITE_WMS_COMMON_REQUESTAD_GRAMMAR_H


#include <dirent.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <fstream>
#include <stack>
#include <boost/scoped_ptr.hpp>

namespace glite {
namespace jdl {


struct jdl_grammar ;

class jdl_parser{
		//boost::scoped_ptr<glite::jdl::jdl_grammar> grammar ;
		boost::scoped_ptr<jdl_grammar> grammar ;
		std::stack<std::vector<std::string> *> stack;
	public:
		jdl_parser();

		void parseString(std::string str);

		void parseFile(std::string file_name);

		std::string open_file(const std::string &file_name);

		~jdl_parser();
};

} // jdl namespace
} // glite namespace
#endif

