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

#include <classad_distribution.h>

#include "glite/wmsutils/classads/classad_utils.h"

#include "ManipulationExceptions.h"
#include "PrivateAdManipulation.h"
#include "PrivateAttributes.h"

using namespace glite::wmsutils::classads;

namespace glite {
namespace jdl {


void set_transfer_executable( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFER, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_TRANSFER );
  return;
}

bool get_transfer_executable( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDLPrivate::CONDOR_TRANSFER, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFER );
  return value;
}

void remove_transfer_executable( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_TRANSFER );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_TRANSFER );
  return;
}

std::string unparse_transfer_executable( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFER );
  unparser.Unparse( value, tree );
  return value;
}

void set_transfer_executable( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFER, value );
  return;
}

bool get_transfer_executable( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDLPrivate::CONDOR_TRANSFER, value );
  return value;
}

void remove_transfer_executable( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_TRANSFER );
  return;
}

std::string unparse_transfer_executable( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_copy_to_spool( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_COPYTOSPOOL, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_COPYTOSPOOL );
  return;
}

bool get_copy_to_spool( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDLPrivate::CONDOR_COPYTOSPOOL, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_COPYTOSPOOL );
  return value;
}

void remove_copy_to_spool( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_COPYTOSPOOL );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_COPYTOSPOOL );
  return;
}

std::string unparse_copy_to_spool( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_COPYTOSPOOL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_COPYTOSPOOL );
  unparser.Unparse( value, tree );
  return value;
}

void set_copy_to_spool( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_COPYTOSPOOL, value );
  return;
}

bool get_copy_to_spool( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDLPrivate::CONDOR_COPYTOSPOOL, value );
  return value;
}

void remove_copy_to_spool( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_COPYTOSPOOL );
  return;
}

std::string unparse_copy_to_spool( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_COPYTOSPOOL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_stream_output( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::STREAM_OUTPUT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::STREAM_OUTPUT );
  return;
}

bool get_stream_output( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDLPrivate::STREAM_OUTPUT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::STREAM_OUTPUT );
  return value;
}

void remove_stream_output( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::STREAM_OUTPUT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::STREAM_OUTPUT );
  return;
}

std::string unparse_stream_output( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::STREAM_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::STREAM_OUTPUT );
  unparser.Unparse( value, tree );
  return value;
}

void set_stream_output( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::STREAM_OUTPUT, value );
  return;
}

bool get_stream_output( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDLPrivate::STREAM_OUTPUT, value );
  return value;
}

void remove_stream_output( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::STREAM_OUTPUT );
  return;
}

std::string unparse_stream_output( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::STREAM_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_stream_error( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::STREAM_ERROR, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::STREAM_ERROR );
  return;
}

bool get_stream_error( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDLPrivate::STREAM_ERROR, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::STREAM_ERROR );
  return value;
}

void remove_stream_error( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::STREAM_ERROR );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::STREAM_ERROR );
  return;
}

std::string unparse_stream_error( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::STREAM_ERROR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::STREAM_ERROR );
  unparser.Unparse( value, tree );
  return value;
}

void set_stream_error( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::STREAM_ERROR, value );
  return;
}

bool get_stream_error( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDLPrivate::STREAM_ERROR, value );
  return value;
}

void remove_stream_error( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::STREAM_ERROR );
  return;
}

std::string unparse_stream_error( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::STREAM_ERROR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_notification( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::NOTIFICATION, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::NOTIFICATION );
  return;
}

std::string get_notification( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::NOTIFICATION, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::NOTIFICATION );
  return value;
}

void remove_notification( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::NOTIFICATION );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::NOTIFICATION );
  return;
}

std::string unparse_notification( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::NOTIFICATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::NOTIFICATION );
  unparser.Unparse( value, tree );
  return value;
}

void set_notification( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::NOTIFICATION, value );
}

std::string get_notification( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::NOTIFICATION, value );
  return value;
}

void remove_notification( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::NOTIFICATION );
  return;
}

std::string unparse_notification( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::NOTIFICATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_log( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_LOG, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_LOG );
  return;
}

std::string get_log( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_LOG, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_LOG );
  return value;
}

void remove_log( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_LOG );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_LOG );
  return;
}

std::string unparse_log( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_LOG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_LOG );
  unparser.Unparse( value, tree );
  return value;
}

void set_log( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_LOG, value );
}

std::string get_log( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_LOG, value );
  return value;
}

void remove_log( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_LOG );
  return;
}

std::string unparse_log( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_LOG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_OUTPUT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_OUTPUT );
  return;
}

std::string get_output( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_OUTPUT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_OUTPUT );
  return value;
}

void remove_output( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_OUTPUT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_OUTPUT );
  return;
}

std::string unparse_output( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_OUTPUT );
  unparser.Unparse( value, tree );
  return value;
}

void set_output( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_OUTPUT, value );
}

std::string get_output( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_OUTPUT, value );
  return value;
}

void remove_output( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_OUTPUT );
  return;
}

std::string unparse_output( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_error( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_ERROR, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_ERROR );
  return;
}

std::string get_error( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_ERROR, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_ERROR );
  return value;
}

void remove_error( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_ERROR );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_ERROR );
  return;
}

std::string unparse_error( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_ERROR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_ERROR );
  unparser.Unparse( value, tree );
  return value;
}

void set_error( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_ERROR, value );
}

std::string get_error( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_ERROR, value );
  return value;
}

void remove_error( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_ERROR );
  return;
}

std::string unparse_error( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_ERROR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_error_( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_ERROR_, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_ERROR_ );
  return;
}

std::string get_error_( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_ERROR_, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_ERROR_ );
  return value;
}

void remove_error_( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_ERROR_ );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_ERROR_ );
  return;
}

std::string unparse_error_( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_ERROR_ );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_ERROR_ );
  unparser.Unparse( value, tree );
  return value;
}

void set_error_( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_ERROR_, value );
}

std::string get_error_( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_ERROR_, value );
  return value;
}

void remove_error_( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_ERROR_ );
  return;
}

std::string unparse_error_( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_ERROR_ );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_x509_user_proxy( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::USERPROXY, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::USERPROXY );
  return;
}

std::string get_x509_user_proxy( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::USERPROXY, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::USERPROXY );
  return value;
}

void remove_x509_user_proxy( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::USERPROXY );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::USERPROXY );
  return;
}

std::string unparse_x509_user_proxy( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::USERPROXY );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::USERPROXY );
  unparser.Unparse( value, tree );
  return value;
}

void set_x509_user_proxy( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::USERPROXY, value );
}

std::string get_x509_user_proxy( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::USERPROXY, value );
  return value;
}

void remove_x509_user_proxy( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::USERPROXY );
  return;
}

std::string unparse_x509_user_proxy( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::USERPROXY );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_submit_event_notes( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::SUBMITEVENTNOTES, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::SUBMITEVENTNOTES );
  return;
}

std::string get_submit_event_notes( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::SUBMITEVENTNOTES, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::SUBMITEVENTNOTES );
  return value;
}

void remove_submit_event_notes( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::SUBMITEVENTNOTES );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::SUBMITEVENTNOTES );
  return;
}

std::string unparse_submit_event_notes( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::SUBMITEVENTNOTES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::SUBMITEVENTNOTES );
  unparser.Unparse( value, tree );
  return value;
}

void set_submit_event_notes( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::SUBMITEVENTNOTES, value );
}

std::string get_submit_event_notes( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::SUBMITEVENTNOTES, value );
  return value;
}

void remove_submit_event_notes( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::SUBMITEVENTNOTES );
  return;
}

std::string unparse_submit_event_notes( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::SUBMITEVENTNOTES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_submit_event_user_notes( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::SUBMITEVENTUSERNOTES, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::SUBMITEVENTUSERNOTES );
  return;
}

std::string get_submit_event_user_notes( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::SUBMITEVENTUSERNOTES, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::SUBMITEVENTUSERNOTES );
  return value;
}

void remove_submit_event_user_notes( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::SUBMITEVENTUSERNOTES );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::SUBMITEVENTUSERNOTES );
  return;
}

std::string unparse_submit_event_user_notes( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::SUBMITEVENTUSERNOTES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::SUBMITEVENTUSERNOTES );
  unparser.Unparse( value, tree );
  return value;
}

void set_submit_event_user_notes( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::SUBMITEVENTUSERNOTES, value );
}

std::string get_submit_event_user_notes( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::SUBMITEVENTUSERNOTES, value );
  return value;
}

void remove_submit_event_user_notes( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::SUBMITEVENTUSERNOTES );
  return;
}

std::string unparse_submit_event_user_notes( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::SUBMITEVENTUSERNOTES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox_path( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::INPUT_SANDBOX_PATH, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::INPUT_SANDBOX_PATH );
  return;
}

std::string get_input_sandbox_path( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::INPUT_SANDBOX_PATH, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::INPUT_SANDBOX_PATH );
  return value;
}

void remove_input_sandbox_path( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::INPUT_SANDBOX_PATH );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::INPUT_SANDBOX_PATH );
  return;
}

std::string unparse_input_sandbox_path( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::INPUT_SANDBOX_PATH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::INPUT_SANDBOX_PATH );
  unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox_path( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::INPUT_SANDBOX_PATH, value );
}

std::string get_input_sandbox_path( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::INPUT_SANDBOX_PATH, value );
  return value;
}

void remove_input_sandbox_path( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::INPUT_SANDBOX_PATH );
  return;
}

std::string unparse_input_sandbox_path( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::INPUT_SANDBOX_PATH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox_path( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::OUTPUT_SANDBOX_PATH, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::OUTPUT_SANDBOX_PATH );
  return;
}

std::string get_output_sandbox_path( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::OUTPUT_SANDBOX_PATH, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::OUTPUT_SANDBOX_PATH );
  return value;
}

void remove_output_sandbox_path( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::OUTPUT_SANDBOX_PATH );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::OUTPUT_SANDBOX_PATH );
  return;
}

std::string unparse_output_sandbox_path( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::OUTPUT_SANDBOX_PATH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::OUTPUT_SANDBOX_PATH );
  unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox_path( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::OUTPUT_SANDBOX_PATH, value );
}

std::string get_output_sandbox_path( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::OUTPUT_SANDBOX_PATH, value );
  return value;
}

void remove_output_sandbox_path( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::OUTPUT_SANDBOX_PATH );
  return;
}

std::string unparse_output_sandbox_path( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::OUTPUT_SANDBOX_PATH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_globus_scheduler( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_GLOBUS_SCHEDULER, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  return;
}

std::string get_globus_scheduler( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GLOBUS_SCHEDULER, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  return value;
}

void remove_globus_scheduler( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  return;
}

std::string unparse_globus_scheduler( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  unparser.Unparse( value, tree );
  return value;
}

void set_globus_scheduler( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_GLOBUS_SCHEDULER, value );
}

std::string get_globus_scheduler( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GLOBUS_SCHEDULER, value );
  return value;
}

void remove_globus_scheduler( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  return;
}

std::string unparse_globus_scheduler( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GLOBUS_SCHEDULER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_grid_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_GRID_TYPE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_GRID_TYPE );
  return;
}

std::string get_grid_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GRID_TYPE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_GRID_TYPE );
  return value;
}

void remove_grid_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_GRID_TYPE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_GRID_TYPE );
  return;
}

std::string unparse_grid_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GRID_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_GRID_TYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_grid_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_GRID_TYPE, value );
}

std::string get_grid_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GRID_TYPE, value );
  return value;
}

void remove_grid_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_GRID_TYPE );
  return;
}

std::string unparse_grid_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GRID_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_job_universe( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  return;
}

int get_remote_job_universe( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  return value;
}

void remove_remote_job_universe( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  return;
}

std::string unparse_remote_job_universe( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_job_universe( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE, value );
  return;
}

int get_remote_job_universe( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE, value );
  return value;
}

void remove_remote_job_universe( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  return;
}

std::string unparse_remote_job_universe( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_JOBUNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_sub_universe( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  return;
}

std::string get_remote_sub_universe( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  return value;
}

void remove_remote_sub_universe( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  return;
}

std::string unparse_remote_sub_universe( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_sub_universe( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE, value );
}

std::string get_remote_sub_universe( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE, value );
  return value;
}

void remove_remote_sub_universe( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  return;
}

std::string unparse_remote_sub_universe( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_SUBUNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_job_grid_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  return;
}

std::string get_remote_job_grid_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  return value;
}

void remove_remote_job_grid_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  return;
}

std::string unparse_remote_job_grid_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_job_grid_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE, value );
}

std::string get_remote_job_grid_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE, value );
  return value;
}

void remove_remote_job_grid_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  return;
}

std::string unparse_remote_job_grid_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_JOBGRIDTYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_daemon_unique_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  return;
}

std::string get_daemon_unique_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  return value;
}

void remove_daemon_unique_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  return;
}

std::string unparse_daemon_unique_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  unparser.Unparse( value, tree );
  return value;
}

void set_daemon_unique_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME, value );
}

std::string get_daemon_unique_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME, value );
  return value;
}

void remove_daemon_unique_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  return;
}

std::string unparse_daemon_unique_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_DAEMON_UNIQUE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_condor_requirements( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REQUIREMENTS, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REQUIREMENTS );
  return;
}

std::string get_condor_requirements( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REQUIREMENTS, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REQUIREMENTS );
  return value;
}

void remove_condor_requirements( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REQUIREMENTS );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REQUIREMENTS );
  return;
}

std::string unparse_condor_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REQUIREMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_condor_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REQUIREMENTS, value );
}

std::string get_condor_requirements( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REQUIREMENTS, value );
  return value;
}

void remove_condor_requirements( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REQUIREMENTS );
  return;
}

std::string unparse_condor_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_requirements( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  return;
}

std::string get_remote_requirements( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  return value;
}

void remove_remote_requirements( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  return;
}

std::string unparse_remote_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS, value );
}

std::string get_remote_requirements( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS, value );
  return value;
}

void remove_remote_requirements( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  return;
}

std::string unparse_remote_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_env( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_ENV, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_ENV );
  return;
}

std::string get_remote_env( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_ENV, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_ENV );
  return value;
}

void remove_remote_env( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_ENV );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_ENV );
  return;
}

std::string unparse_remote_env( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_ENV );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_ENV );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_env( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_ENV, value );
}

std::string get_remote_env( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_ENV, value );
  return value;
}

void remove_remote_env( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_ENV );
  return;
}

std::string unparse_remote_env( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_ENV );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_queue( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  return;
}

std::string get_remote_remote_queue( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  return value;
}

void remove_remote_remote_queue( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  return;
}

std::string unparse_remote_remote_queue( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_queue( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE, value );
}

std::string get_remote_remote_queue( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE, value );
  return value;
}

void remove_remote_remote_queue( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  return;
}

std::string unparse_remote_remote_queue( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_QUEUE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_grid_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  return;
}

std::string get_remote_remote_grid_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  return value;
}

void remove_remote_remote_grid_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  return;
}

std::string unparse_remote_remote_grid_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_grid_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE, value );
}

std::string get_remote_remote_grid_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE, value );
  return value;
}

void remove_remote_remote_grid_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  return;
}

std::string unparse_remote_remote_grid_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_GRID_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_job_universe( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  return;
}

int get_remote_remote_job_universe( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  return value;
}

void remove_remote_remote_job_universe( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  return;
}

std::string unparse_remote_remote_job_universe( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_job_universe( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE, value );
  return;
}

int get_remote_remote_job_universe( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE, value );
  return value;
}

void remove_remote_remote_job_universe( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  return;
}

std::string unparse_remote_remote_job_universe( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_JOB_UNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_requirements( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  return;
}

std::string get_remote_remote_requirements( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  return value;
}

void remove_remote_remote_requirements( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  return;
}

std::string unparse_remote_remote_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS, value );
}

std::string get_remote_remote_requirements( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS, value );
  return value;
}

void remove_remote_remote_requirements( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  return;
}

std::string unparse_remote_remote_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_file_system_domain( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  return;
}

std::string get_remote_remote_file_system_domain( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  return value;
}

void remove_remote_remote_file_system_domain( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  return;
}

std::string unparse_remote_remote_file_system_domain( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_file_system_domain( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN, value );
}

std::string get_remote_remote_file_system_domain( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN, value );
  return value;
}

void remove_remote_remote_file_system_domain( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  return;
}

std::string unparse_remote_remote_file_system_domain( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_FILE_SYSTEM_DOMAIN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_uid_system_domain( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  return;
}

std::string get_remote_remote_uid_system_domain( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  return value;
}

void remove_remote_remote_uid_system_domain( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  return;
}

std::string unparse_remote_remote_uid_system_domain( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_uid_system_domain( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN, value );
}

std::string get_remote_remote_uid_system_domain( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN, value );
  return value;
}

void remove_remote_remote_uid_system_domain( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  return;
}

std::string unparse_remote_remote_uid_system_domain( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_UID_SYSTEM_DOMAIN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_should_transfer_files( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  return;
}

std::string get_remote_remote_should_transfer_files( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  return value;
}

void remove_remote_remote_should_transfer_files( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  return;
}

std::string unparse_remote_remote_should_transfer_files( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_should_transfer_files( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES, value );
}

std::string get_remote_remote_should_transfer_files( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES, value );
  return value;
}

void remove_remote_remote_should_transfer_files( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  return;
}

std::string unparse_remote_remote_should_transfer_files( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_SHOULD_TRANSFER_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  return;
}

std::string get_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  return value;
}

void remove_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  return;
}

std::string unparse_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT, value );
}

std::string get_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT, value );
  return value;
}

void remove_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  return;
}

std::string unparse_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_WHEN_TO_TRANSFER_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_nodenumber( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  return;
}

int get_remote_remote_nodenumber( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  return value;
}

void remove_remote_remote_nodenumber( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  return;
}

std::string unparse_remote_remote_nodenumber( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_nodenumber( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER, value );
  return;
}

int get_remote_remote_nodenumber( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER, value );
  return value;
}

void remove_remote_remote_nodenumber( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  return;
}

std::string unparse_remote_remote_nodenumber( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_NODENUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_stagecmd( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  return;
}

bool get_remote_remote_stagecmd( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  return value;
}

void remove_remote_remote_stagecmd( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  return;
}

std::string unparse_remote_remote_stagecmd( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_stagecmd( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD, value );
  return;
}

bool get_remote_remote_stagecmd( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD, value );
  return value;
}

void remove_remote_remote_stagecmd( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  return;
}

std::string unparse_remote_remote_stagecmd( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_STAGECMD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_edg_jobid( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  return;
}

std::string get_remote_remote_edg_jobid( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  return value;
}

void remove_remote_remote_edg_jobid( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  return;
}

std::string unparse_remote_remote_edg_jobid( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_edg_jobid( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID, value );
}

std::string get_remote_remote_edg_jobid( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID, value );
  return value;
}

void remove_remote_remote_edg_jobid( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  return;
}

std::string unparse_remote_remote_edg_jobid( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_JOBID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_user_subject_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  return;
}

std::string get_remote_remote_user_subject_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  return value;
}

void remove_remote_remote_user_subject_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  return;
}

std::string unparse_remote_remote_user_subject_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_user_subject_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT, value );
}

std::string get_remote_remote_user_subject_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT, value );
  return value;
}

void remove_remote_remote_user_subject_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  return;
}

std::string unparse_remote_remote_user_subject_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_SUBJECT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_ceid( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  return;
}

std::string get_remote_remote_ceid( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  return value;
}

void remove_remote_remote_ceid( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  return;
}

std::string unparse_remote_remote_ceid( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_ceid( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID, value );
}

std::string get_remote_remote_ceid( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID, value );
  return value;
}

void remove_remote_remote_ceid( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  return;
}

std::string unparse_remote_remote_ceid( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_CEID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_voms_fqan( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  return;
}

std::string get_remote_remote_voms_fqan( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  return value;
}

void remove_remote_remote_voms_fqan( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  return;
}

std::string unparse_remote_remote_voms_fqan( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_voms_fqan( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN, value );
}

std::string get_remote_remote_voms_fqan( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN, value );
  return value;
}

void remove_remote_remote_voms_fqan( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  return;
}

std::string unparse_remote_remote_voms_fqan( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_VOMS_FQAN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_virtual_organisation( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  return;
}

std::string get_remote_remote_virtual_organisation( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  return value;
}

void remove_remote_remote_virtual_organisation( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  return;
}

std::string unparse_remote_remote_virtual_organisation( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_virtual_organisation( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION, value );
}

std::string get_remote_remote_virtual_organisation( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION, value );
  return value;
}

void remove_remote_remote_virtual_organisation( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  return;
}

std::string unparse_remote_remote_virtual_organisation( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_VIRTUAL_ORGANISATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_ce_requirements( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  return;
}

std::string get_remote_remote_ce_requirements( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  return value;
}

void remove_remote_remote_ce_requirements( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  return;
}

std::string unparse_remote_remote_ce_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_ce_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS, value );
}

std::string get_remote_remote_ce_requirements( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS, value );
  return value;
}

void remove_remote_remote_ce_requirements( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  return;
}

std::string unparse_remote_remote_ce_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_CE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_schedd( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_SCHEDD, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  return;
}

std::string get_remote_schedd( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_SCHEDD, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  return value;
}

void remove_remote_schedd( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  return;
}

std::string unparse_remote_schedd( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_schedd( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_SCHEDD, value );
}

std::string get_remote_schedd( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_SCHEDD, value );
  return value;
}

void remove_remote_schedd( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  return;
}

std::string unparse_remote_schedd( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_SCHEDD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_schedd( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  return;
}

std::string get_remote_remote_schedd( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  return value;
}

void remove_remote_remote_schedd( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  return;
}

std::string unparse_remote_remote_schedd( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_schedd( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD, value );
}

std::string get_remote_remote_schedd( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD, value );
  return value;
}

void remove_remote_remote_schedd( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  return;
}

std::string unparse_remote_remote_schedd( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_SCHEDD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_pool( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  return;
}

std::string get_remote_remote_pool( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  return value;
}

void remove_remote_remote_pool( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  return;
}

std::string unparse_remote_remote_pool( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_remote_pool( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL, value );
}

std::string get_remote_remote_pool( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL, value );
  return value;
}

void remove_remote_remote_pool( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  return;
}

std::string unparse_remote_remote_pool( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_REMOTE_POOL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_globus_resource( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_GLOBUS_RESOURCE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  return;
}

std::string get_globus_resource( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GLOBUS_RESOURCE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  return value;
}

void remove_globus_resource( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  return;
}

std::string unparse_globus_resource( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  unparser.Unparse( value, tree );
  return value;
}

void set_globus_resource( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_GLOBUS_RESOURCE, value );
}

std::string get_globus_resource( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GLOBUS_RESOURCE, value );
  return value;
}

void remove_globus_resource( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  return;
}

std::string unparse_globus_resource( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GLOBUS_RESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remote_globus_resource( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  return;
}

std::string get_remote_globus_resource( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  return value;
}

void remove_remote_globus_resource( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  return;
}

std::string unparse_remote_globus_resource( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  unparser.Unparse( value, tree );
  return value;
}

void set_remote_globus_resource( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE, value );
}

std::string get_remote_globus_resource( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE, value );
  return value;
}

void remove_remote_globus_resource( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  return;
}

std::string unparse_remote_globus_resource( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_REMOTE_GLOBUS_RESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_site_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_SITE_NAME, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_SITE_NAME );
  return;
}

std::string get_site_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SITE_NAME, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_SITE_NAME );
  return value;
}

void remove_site_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_SITE_NAME );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_SITE_NAME );
  return;
}

std::string unparse_site_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SITE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_SITE_NAME );
  unparser.Unparse( value, tree );
  return value;
}

void set_site_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_SITE_NAME, value );
}

std::string get_site_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SITE_NAME, value );
  return value;
}

void remove_site_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_SITE_NAME );
  return;
}

std::string unparse_site_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SITE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_initial_dir( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_INITIAL_DIR, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_INITIAL_DIR );
  return;
}

std::string get_initial_dir( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_INITIAL_DIR, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_INITIAL_DIR );
  return value;
}

void remove_initial_dir( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_INITIAL_DIR );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_INITIAL_DIR );
  return;
}

std::string unparse_initial_dir( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_INITIAL_DIR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_INITIAL_DIR );
  unparser.Unparse( value, tree );
  return value;
}

void set_initial_dir( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_INITIAL_DIR, value );
}

std::string get_initial_dir( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_INITIAL_DIR, value );
  return value;
}

void remove_initial_dir( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_INITIAL_DIR );
  return;
}

std::string unparse_initial_dir( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_INITIAL_DIR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_site_gatekeeper( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_SITE_GATEKEEPER, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  return;
}

std::string get_site_gatekeeper( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SITE_GATEKEEPER, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  return value;
}

void remove_site_gatekeeper( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  return;
}

std::string unparse_site_gatekeeper( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  unparser.Unparse( value, tree );
  return value;
}

void set_site_gatekeeper( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_SITE_GATEKEEPER, value );
}

std::string get_site_gatekeeper( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SITE_GATEKEEPER, value );
  return value;
}

void remove_site_gatekeeper( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  return;
}

std::string unparse_site_gatekeeper( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SITE_GATEKEEPER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_should_transfer_files( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  return;
}

std::string get_should_transfer_files( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  return value;
}

void remove_should_transfer_files( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  return;
}

std::string unparse_should_transfer_files( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  unparser.Unparse( value, tree );
  return value;
}

void set_should_transfer_files( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES, value );
}

std::string get_should_transfer_files( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES, value );
  return value;
}

void remove_should_transfer_files( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  return;
}

std::string unparse_should_transfer_files( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SHOULD_TRANSFER_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  return;
}

std::string get_when_to_transfer_output( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  return value;
}

void remove_when_to_transfer_output( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  return;
}

std::string unparse_when_to_transfer_output( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  unparser.Unparse( value, tree );
  return value;
}

void set_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT, value );
}

std::string get_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT, value );
  return value;
}

void remove_when_to_transfer_output( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  return;
}

std::string unparse_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_WHEN_TO_TRANSFER_OUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_periodic_hold( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_PERIODIC_HOLD, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_PERIODIC_HOLD );
  return;
}

std::string get_periodic_hold( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_PERIODIC_HOLD, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_PERIODIC_HOLD );
  return value;
}

void remove_periodic_hold( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_PERIODIC_HOLD );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_PERIODIC_HOLD );
  return;
}

std::string unparse_periodic_hold( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_PERIODIC_HOLD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_PERIODIC_HOLD );
  unparser.Unparse( value, tree );
  return value;
}

void set_periodic_hold( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_PERIODIC_HOLD, value );
}

std::string get_periodic_hold( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_PERIODIC_HOLD, value );
  return value;
}

void remove_periodic_hold( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_PERIODIC_HOLD );
  return;
}

std::string unparse_periodic_hold( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_PERIODIC_HOLD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_periodic_remove( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_PERIODIC_REMOVE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  return;
}

std::string get_periodic_remove( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_PERIODIC_REMOVE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  return value;
}

void remove_periodic_remove( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  return;
}

std::string unparse_periodic_remove( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  unparser.Unparse( value, tree );
  return value;
}

void set_periodic_remove( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_PERIODIC_REMOVE, value );
}

std::string get_periodic_remove( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_PERIODIC_REMOVE, value );
  return value;
}

void remove_periodic_remove( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  return;
}

std::string unparse_periodic_remove( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_PERIODIC_REMOVE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_transfer_input_files( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  return;
}

std::string get_transfer_input_files( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  return value;
}

void remove_transfer_input_files( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  return;
}

std::string unparse_transfer_input_files( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  unparser.Unparse( value, tree );
  return value;
}

void set_transfer_input_files( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES, value );
}

std::string get_transfer_input_files( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES, value );
  return value;
}

void remove_transfer_input_files( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  return;
}

std::string unparse_transfer_input_files( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFER_INPUT_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_transfer_output_files( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  return;
}

std::string get_transfer_output_files( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  return value;
}

void remove_transfer_output_files( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  return;
}

std::string unparse_transfer_output_files( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  unparser.Unparse( value, tree );
  return value;
}

void set_transfer_output_files( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES, value );
}

std::string get_transfer_output_files( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES, value );
  return value;
}

void remove_transfer_output_files( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  return;
}

std::string unparse_transfer_output_files( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFER_OUTPUT_FILES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_transfer_output( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFEROUTPUT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  return;
}

std::string get_transfer_output( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_TRANSFEROUTPUT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  return value;
}

void remove_transfer_output( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  return;
}

std::string unparse_transfer_output( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  unparser.Unparse( value, tree );
  return value;
}

void set_transfer_output( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_TRANSFEROUTPUT, value );
}

std::string get_transfer_output( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_TRANSFEROUTPUT, value );
  return value;
}

void remove_transfer_output( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  return;
}

std::string unparse_transfer_output( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_TRANSFEROUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_globus_rsl( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_GLOBUS_RSL, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_GLOBUS_RSL );
  return;
}

std::string get_globus_rsl( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GLOBUS_RSL, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_GLOBUS_RSL );
  return value;
}

void remove_globus_rsl( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_GLOBUS_RSL );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_GLOBUS_RSL );
  return;
}

std::string unparse_globus_rsl( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GLOBUS_RSL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_GLOBUS_RSL );
  unparser.Unparse( value, tree );
  return value;
}

void set_globus_rsl( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_GLOBUS_RSL, value );
}

std::string get_globus_rsl( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_GLOBUS_RSL, value );
  return value;
}

void remove_globus_rsl( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_GLOBUS_RSL );
  return;
}

std::string unparse_globus_rsl( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_GLOBUS_RSL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_user_subject_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_SUBJECT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_SUBJECT );
  return;
}

std::string get_user_subject_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SUBJECT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_SUBJECT );
  return value;
}

void remove_user_subject_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_SUBJECT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_SUBJECT );
  return;
}

std::string unparse_user_subject_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SUBJECT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_SUBJECT );
  unparser.Unparse( value, tree );
  return value;
}

void set_user_subject_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_SUBJECT, value );
}

std::string get_user_subject_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SUBJECT, value );
  return value;
}

void remove_user_subject_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_SUBJECT );
  return;
}

std::string unparse_user_subject_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SUBJECT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_universe( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_UNIVERSE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_UNIVERSE );
  return;
}

std::string get_universe( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_UNIVERSE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_UNIVERSE );
  return value;
}

void remove_universe( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_UNIVERSE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_UNIVERSE );
  return;
}

std::string unparse_universe( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_UNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_UNIVERSE );
  unparser.Unparse( value, tree );
  return value;
}

void set_universe( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_UNIVERSE, value );
}

std::string get_universe( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_UNIVERSE, value );
  return value;
}

void remove_universe( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_UNIVERSE );
  return;
}

std::string unparse_universe( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_UNIVERSE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_condor_submit_file( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CONDOR_SUBMIT_FILE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CONDOR_SUBMIT_FILE );
  return;
}

std::string get_condor_submit_file( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SUBMIT_FILE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CONDOR_SUBMIT_FILE );
  return value;
}

void remove_condor_submit_file( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CONDOR_SUBMIT_FILE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CONDOR_SUBMIT_FILE );
  return;
}

std::string unparse_condor_submit_file( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SUBMIT_FILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CONDOR_SUBMIT_FILE );
  unparser.Unparse( value, tree );
  return value;
}

void set_condor_submit_file( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CONDOR_SUBMIT_FILE, value );
}

std::string get_condor_submit_file( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CONDOR_SUBMIT_FILE, value );
  return value;
}

void remove_condor_submit_file( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CONDOR_SUBMIT_FILE );
  return;
}

std::string unparse_condor_submit_file( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CONDOR_SUBMIT_FILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_edg_dagid( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::DAGID, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::DAGID );
  return;
}

std::string get_edg_dagid( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::DAGID, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::DAGID );
  return value;
}

void remove_edg_dagid( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::DAGID );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::DAGID );
  return;
}

std::string unparse_edg_dagid( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::DAGID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::DAGID );
  unparser.Unparse( value, tree );
  return value;
}

void set_edg_dagid( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::DAGID, value );
}

std::string get_edg_dagid( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::DAGID, value );
  return value;
}

void remove_edg_dagid( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::DAGID );
  return;
}

std::string unparse_edg_dagid( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::DAGID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_perusal_list_file_uri( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::PU_LIST_FILE_URI, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::PU_LIST_FILE_URI );
  return;
}

std::string get_perusal_list_file_uri( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::PU_LIST_FILE_URI, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::PU_LIST_FILE_URI );
  return value;
}

void remove_perusal_list_file_uri( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::PU_LIST_FILE_URI );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::PU_LIST_FILE_URI );
  return;
}

std::string unparse_perusal_list_file_uri( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::PU_LIST_FILE_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::PU_LIST_FILE_URI );
  unparser.Unparse( value, tree );
  return value;
}

void set_perusal_list_file_uri( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::PU_LIST_FILE_URI, value );
}

std::string get_perusal_list_file_uri( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::PU_LIST_FILE_URI, value );
  return value;
}

void remove_perusal_list_file_uri( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::PU_LIST_FILE_URI );
  return;
}

std::string unparse_perusal_list_file_uri( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::PU_LIST_FILE_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_zipped_isb( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDLPrivate::ZIPPED_ISB, l );
  if( !res ) throw CannotSetAttribute( JDLPrivate::ZIPPED_ISB );
  return;
}

void get_zipped_isb( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDLPrivate::ZIPPED_ISB, l );
  if( !res ) throw CannotGetAttribute( JDLPrivate::ZIPPED_ISB );
  return;
}

void remove_zipped_isb( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::ZIPPED_ISB );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::ZIPPED_ISB );
  return;
}

std::string unparse_zipped_isb( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::ZIPPED_ISB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::ZIPPED_ISB );
  unparser.Unparse( value, tree );
  return value;
}

void set_zipped_isb( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDLPrivate::ZIPPED_ISB, l );
  return;
}

void get_zipped_isb( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDLPrivate::ZIPPED_ISB, l );
  return;
}

void remove_zipped_isb( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::ZIPPED_ISB );
  return;
}

std::string unparse_zipped_isb( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::ZIPPED_ISB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_edg_previous_matches( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDLPrivate::EDG_PREVIOUS_MATCHES, l );
  if( !res ) throw CannotSetAttribute( JDLPrivate::EDG_PREVIOUS_MATCHES );
  return;
}

void get_edg_previous_matches( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDLPrivate::EDG_PREVIOUS_MATCHES, l );
  if( !res ) throw CannotGetAttribute( JDLPrivate::EDG_PREVIOUS_MATCHES );
  return;
}

void remove_edg_previous_matches( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::EDG_PREVIOUS_MATCHES );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::EDG_PREVIOUS_MATCHES );
  return;
}

std::string unparse_edg_previous_matches( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::EDG_PREVIOUS_MATCHES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::EDG_PREVIOUS_MATCHES );
  unparser.Unparse( value, tree );
  return value;
}

void set_edg_previous_matches( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDLPrivate::EDG_PREVIOUS_MATCHES, l );
  return;
}

void get_edg_previous_matches( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDLPrivate::EDG_PREVIOUS_MATCHES, l );
  return;
}

void remove_edg_previous_matches( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::EDG_PREVIOUS_MATCHES );
  return;
}

std::string unparse_edg_previous_matches( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::EDG_PREVIOUS_MATCHES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_really_running_token( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::REALLY_RUNNING_TOKEN, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::REALLY_RUNNING_TOKEN );
  return;
}

std::string get_really_running_token( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::REALLY_RUNNING_TOKEN, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::REALLY_RUNNING_TOKEN );
  return value;
}

void remove_really_running_token( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::REALLY_RUNNING_TOKEN );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::REALLY_RUNNING_TOKEN );
  return;
}

std::string unparse_really_running_token( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::REALLY_RUNNING_TOKEN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::REALLY_RUNNING_TOKEN );
  unparser.Unparse( value, tree );
  return value;
}

void set_really_running_token( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::REALLY_RUNNING_TOKEN, value );
}

std::string get_really_running_token( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::REALLY_RUNNING_TOKEN, value );
  return value;
}

void remove_really_running_token( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::REALLY_RUNNING_TOKEN );
  return;
}

std::string unparse_really_running_token( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::REALLY_RUNNING_TOKEN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_getenv( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::GETENV, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::GETENV );
  return;
}

bool get_getenv( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDLPrivate::GETENV, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::GETENV );
  return value;
}

void remove_getenv( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::GETENV );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::GETENV );
  return;
}

std::string unparse_getenv( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::GETENV );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::GETENV );
  unparser.Unparse( value, tree );
  return value;
}

void set_getenv( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::GETENV, value );
  return;
}

bool get_getenv( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDLPrivate::GETENV, value );
  return value;
}

void remove_getenv( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::GETENV );
  return;
}

std::string unparse_getenv( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::GETENV );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_remove_kill_sig( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::REMOVE_KILL_SIG, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::REMOVE_KILL_SIG );
  return;
}

std::string get_remove_kill_sig( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::REMOVE_KILL_SIG, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::REMOVE_KILL_SIG );
  return value;
}

void remove_remove_kill_sig( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::REMOVE_KILL_SIG );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::REMOVE_KILL_SIG );
  return;
}

std::string unparse_remove_kill_sig( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::REMOVE_KILL_SIG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::REMOVE_KILL_SIG );
  unparser.Unparse( value, tree );
  return value;
}

void set_remove_kill_sig( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::REMOVE_KILL_SIG, value );
}

std::string get_remove_kill_sig( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::REMOVE_KILL_SIG, value );
  return value;
}

void remove_remove_kill_sig( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::REMOVE_KILL_SIG );
  return;
}

std::string unparse_remove_kill_sig( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::REMOVE_KILL_SIG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_voms_fqan( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::VOMS_FQAN, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::VOMS_FQAN );
  return;
}

std::string get_voms_fqan( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::VOMS_FQAN, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::VOMS_FQAN );
  return value;
}

void remove_voms_fqan( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::VOMS_FQAN );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::VOMS_FQAN );
  return;
}

std::string unparse_voms_fqan( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::VOMS_FQAN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::VOMS_FQAN );
  unparser.Unparse( value, tree );
  return value;
}

void set_voms_fqan( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::VOMS_FQAN, value );
}

std::string get_voms_fqan( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::VOMS_FQAN, value );
  return value;
}

void remove_voms_fqan( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::VOMS_FQAN );
  return;
}

std::string unparse_voms_fqan( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::VOMS_FQAN );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_default_node_retry_count( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::DEFAULT_NODE_RETRYCOUNT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  return;
}

int get_default_node_retry_count( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDLPrivate::DEFAULT_NODE_RETRYCOUNT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  return value;
}

void remove_default_node_retry_count( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  return;
}

std::string unparse_default_node_retry_count( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  unparser.Unparse( value, tree );
  return value;
}

void set_default_node_retry_count( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::DEFAULT_NODE_RETRYCOUNT, value );
  return;
}

int get_default_node_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDLPrivate::DEFAULT_NODE_RETRYCOUNT, value );
  return value;
}

void remove_default_node_retry_count( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  return;
}

std::string unparse_default_node_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::DEFAULT_NODE_RETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_default_node_shallow_retry_count( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  return;
}

int get_default_node_shallow_retry_count( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  return value;
}

void remove_default_node_shallow_retry_count( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  return;
}

std::string unparse_default_node_shallow_retry_count( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  unparser.Unparse( value, tree );
  return value;
}

void set_default_node_shallow_retry_count( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT, value );
  return;
}

int get_default_node_shallow_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT, value );
  return value;
}

void remove_default_node_shallow_retry_count( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  return;
}

std::string unparse_default_node_shallow_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::DEFAULT_NODE_SHALLOWRETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_ce_application_dir( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CE_APPLICATION_DIR, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CE_APPLICATION_DIR );
  return;
}

std::string get_ce_application_dir( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CE_APPLICATION_DIR, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CE_APPLICATION_DIR );
  return value;
}

void remove_ce_application_dir( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CE_APPLICATION_DIR );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CE_APPLICATION_DIR );
  return;
}

std::string unparse_ce_application_dir( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CE_APPLICATION_DIR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CE_APPLICATION_DIR );
  unparser.Unparse( value, tree );
  return value;
}

void set_ce_application_dir( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CE_APPLICATION_DIR, value );
}

std::string get_ce_application_dir( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CE_APPLICATION_DIR, value );
  return value;
}

void remove_ce_application_dir( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CE_APPLICATION_DIR );
  return;
}

std::string unparse_ce_application_dir( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CE_APPLICATION_DIR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_grid_resource( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::GRID_RESOURCE, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::GRID_RESOURCE );
  return;
}

std::string get_grid_resource( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::GRID_RESOURCE, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::GRID_RESOURCE );
  return value;
}

void remove_grid_resource( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::GRID_RESOURCE );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::GRID_RESOURCE );
  return;
}

std::string unparse_grid_resource( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::GRID_RESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::GRID_RESOURCE );
  unparser.Unparse( value, tree );
  return value;
}

void set_grid_resource( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::GRID_RESOURCE, value );
}

std::string get_grid_resource( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::GRID_RESOURCE, value );
  return value;
}

void remove_grid_resource( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::GRID_RESOURCE );
  return;
}

std::string unparse_grid_resource( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::GRID_RESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_nordugrid_rsl( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::NORDUGRID_RSL, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::NORDUGRID_RSL );
  return;
}

std::string get_nordugrid_rsl( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::NORDUGRID_RSL, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::NORDUGRID_RSL );
  return value;
}

void remove_nordugrid_rsl( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::NORDUGRID_RSL );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::NORDUGRID_RSL );
  return;
}

std::string unparse_nordugrid_rsl( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::NORDUGRID_RSL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::NORDUGRID_RSL );
  unparser.Unparse( value, tree );
  return value;
}

void set_nordugrid_rsl( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::NORDUGRID_RSL, value );
}

std::string get_nordugrid_rsl( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::NORDUGRID_RSL, value );
  return value;
}

void remove_nordugrid_rsl( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::NORDUGRID_RSL );
  return;
}

std::string unparse_nordugrid_rsl( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::NORDUGRID_RSL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_ce_requirements( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CE_REQUIREMENTS, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CE_REQUIREMENTS );
  return;
}

std::string get_ce_requirements( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CE_REQUIREMENTS, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CE_REQUIREMENTS );
  return value;
}

void remove_ce_requirements( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CE_REQUIREMENTS );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CE_REQUIREMENTS );
  return;
}

std::string unparse_ce_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CE_REQUIREMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_ce_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CE_REQUIREMENTS, value );
}

std::string get_ce_requirements( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CE_REQUIREMENTS, value );
  return value;
}

void remove_ce_requirements( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CE_REQUIREMENTS );
  return;
}

std::string unparse_ce_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CE_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_ceinfo_host_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::CE_INFO_HOST, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::CE_INFO_HOST );
  return;
}

std::string get_ceinfo_host_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDLPrivate::CE_INFO_HOST, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::CE_INFO_HOST );
  return value;
}

void remove_ceinfo_host_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::CE_INFO_HOST );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::CE_INFO_HOST );
  return;
}

std::string unparse_ceinfo_host_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CE_INFO_HOST );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::CE_INFO_HOST );
  unparser.Unparse( value, tree );
  return value;
}

void set_ceinfo_host_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::CE_INFO_HOST, value );
}

std::string get_ceinfo_host_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDLPrivate::CE_INFO_HOST, value );
  return value;
}

void remove_ceinfo_host_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::CE_INFO_HOST );
  return;
}

std::string unparse_ceinfo_host_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::CE_INFO_HOST );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_replans_count( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDLPrivate::REPLANS_COUNT, value );
  if( !res ) throw CannotSetAttribute( JDLPrivate::REPLANS_COUNT );
  return;
}

int get_replans_count( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDLPrivate::REPLANS_COUNT, value );
  if( !res ) throw CannotGetAttribute( JDLPrivate::REPLANS_COUNT );
  return value;
}

void remove_replans_count( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDLPrivate::REPLANS_COUNT );
  if( !res ) throw CannotRemoveAttribute( JDLPrivate::REPLANS_COUNT );
  return;
}

std::string unparse_replans_count( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::REPLANS_COUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDLPrivate::REPLANS_COUNT );
  unparser.Unparse( value, tree );
  return value;
}

void set_replans_count( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDLPrivate::REPLANS_COUNT, value );
  return;
}

int get_replans_count( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDLPrivate::REPLANS_COUNT, value );
  return value;
}

void remove_replans_count( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDLPrivate::REPLANS_COUNT );
  return;
}

std::string unparse_replans_count( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDLPrivate::REPLANS_COUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}


void set_edg_previous_matches_ex(
  classad::ClassAd& ad,
  std::vector<std::pair<std::string,int> > const& previous_matches
)
{
  std::vector<classad::ExprTree*> expr_list;
  for (std::vector<std::pair<std::string,int> >::const_iterator it = previous_matches.begin();
       it != previous_matches.end(); ++it) {

    classad::ClassAd* ad = new classad::ClassAd;
    ad->InsertAttr("ce_id", it->first);
    ad->InsertAttr("timestamp", it->second);
    expr_list.push_back(ad);

  }

  classad::ExprTree* tmp_expr = classad::ExprList::MakeExprList(expr_list);
  ad.Insert("edg_previous_matches_ex", tmp_expr);
}

} // namespace jdl
} // namespace glite

// Local Variables:
// mode: c++
// End:
