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

#include "ManipulationExceptions.h"

using namespace std;

namespace glite { 
namespace jdl {

ManipulationException::ManipulationException( const string &parameter ) : exception(), me_parameter( parameter ), me_reason()
{}

ManipulationException::~ManipulationException( void ) throw()
{}

const char *ManipulationException::what( void ) const throw()
{
  this->me_reason.assign( "RequestAd module: " );
  this->me_reason.append( this->reason() );

  return this->me_reason.c_str();
}

string ManipulationException::reason( void ) const
{
  string     error( "Error while manipulating ClassAd parameter: " );

  error.append( this->me_parameter );

  return error;
}

CannotGetAttribute::CannotGetAttribute( const string &parameter ) : ManipulationException( parameter )
{}

CannotGetAttribute::~CannotGetAttribute( void ) throw()
{}

string CannotGetAttribute::reason( void ) const
{
  string    error( "Error while extracting ClassAd parameter: " );

  error.append( this->me_parameter );

  return error;
}

CannotSetAttribute::CannotSetAttribute( const string &parameter ) : ManipulationException( parameter )
{}

CannotSetAttribute::~CannotSetAttribute( void ) throw()
{}

string CannotSetAttribute::reason( void ) const
{
  string     error( "Error while setting ClassAd parameter: " );

  error.append( this->me_parameter );

  return error;
}

CannotRemoveAttribute::CannotRemoveAttribute( const string &parameter ) : ManipulationException( parameter )
{}

CannotRemoveAttribute::~CannotRemoveAttribute( void ) throw()
{}

string CannotRemoveAttribute::reason( void ) const
{
  string     error( "Error while removing ClassAd parameter: " );

  error.append( this->me_parameter );

  return error;
}

} // jdl namespace
} // glite namespace
