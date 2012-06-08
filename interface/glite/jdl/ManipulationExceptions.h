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

#ifndef GLITE_WMS_COMMON_REQUESTAD_MANIPULATIONEXCEPTIONS_H
#define GLITE_WMS_COMMON_REQUESTAD_MANIPULATIONEXCEPTIONS_H

#include <string>
#include <exception>

namespace glite { 
namespace jdl {

class ManipulationException : public std::exception {
public:
  explicit ManipulationException( const std::string &parameter );
  virtual ~ManipulationException( void ) throw();

  inline std::string parameter( void ) const { return this->me_parameter; }

  virtual const char *what( void ) const throw();
  virtual std::string reason( void ) const;

protected:
  std::string   me_parameter;

private:
  mutable std::string   me_reason;
};

class CannotGetAttribute : public ManipulationException {
public:
  explicit CannotGetAttribute( const std::string &parameter );
  virtual ~CannotGetAttribute( void ) throw();

  virtual std::string reason( void ) const;
};

class CannotSetAttribute : public ManipulationException {
public:
  explicit CannotSetAttribute( const std::string &parameter );
  virtual ~CannotSetAttribute( void ) throw();

  virtual std::string reason( void ) const;
};

class CannotRemoveAttribute : public ManipulationException {
public:
  explicit CannotRemoveAttribute( const std::string &parameter );
  virtual ~CannotRemoveAttribute( void ) throw();

  virtual std::string reason( void ) const;
};

} // jdl namespace
} // glite namespace

#endif /* GLITE_WMS_COMMON_REQUESTAD_MANIPULATIONEXCEPTIONS_H */

// Local Variables:
// mode: c++
// End:
