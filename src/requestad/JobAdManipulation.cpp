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
#include "JobAdManipulation.h"
#include "JDLAttributes.h"

using namespace glite::wmsutils::classads;
namespace utilities = glite::wmsutils::classads;

namespace glite {
namespace jdl {


void set_requirements( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::REQUIREMENTS, value );
  if( !res ) throw CannotSetAttribute( JDL::REQUIREMENTS );
  return;
}

bool get_requirements( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::REQUIREMENTS, value );
  if( !res ) throw CannotGetAttribute( JDL::REQUIREMENTS );
  return value;
}

void remove_requirements( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::REQUIREMENTS );
  if( !res ) throw CannotRemoveAttribute( JDL::REQUIREMENTS );
  return;
}

std::string unparse_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::REQUIREMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_requirements( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::REQUIREMENTS, value );
  return;
}

bool get_requirements( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::REQUIREMENTS, value );
  return value;
}

void remove_requirements( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::REQUIREMENTS );
  return;
}

std::string unparse_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_fuzzy_rank( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::FUZZY_RANK, value );
  if( !res ) throw CannotSetAttribute( JDL::FUZZY_RANK );
  return;
}

bool get_fuzzy_rank( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::FUZZY_RANK, value );
  if( !res ) throw CannotGetAttribute( JDL::FUZZY_RANK );
  return value;
}

void remove_fuzzy_rank( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::FUZZY_RANK );
  if( !res ) throw CannotRemoveAttribute( JDL::FUZZY_RANK );
  return;
}

std::string unparse_fuzzy_rank( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::FUZZY_RANK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::FUZZY_RANK );
  unparser.Unparse( value, tree );
  return value;
}

void set_fuzzy_rank( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::FUZZY_RANK, value );
  return;
}

bool get_fuzzy_rank( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::FUZZY_RANK, value );
  return value;
}

void remove_fuzzy_rank( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::FUZZY_RANK );
  return;
}

std::string unparse_fuzzy_rank( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::FUZZY_RANK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_allow_zipped_isb( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::ALLOW_ZIPPED_ISB, value );
  if( !res ) throw CannotSetAttribute( JDL::ALLOW_ZIPPED_ISB );
  return;
}

bool get_allow_zipped_isb( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::ALLOW_ZIPPED_ISB, value );
  if( !res ) throw CannotGetAttribute( JDL::ALLOW_ZIPPED_ISB );
  return value;
}

void remove_allow_zipped_isb( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::ALLOW_ZIPPED_ISB );
  if( !res ) throw CannotRemoveAttribute( JDL::ALLOW_ZIPPED_ISB );
  return;
}

std::string unparse_allow_zipped_isb( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ALLOW_ZIPPED_ISB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::ALLOW_ZIPPED_ISB );
  unparser.Unparse( value, tree );
  return value;
}

void set_allow_zipped_isb( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::ALLOW_ZIPPED_ISB, value );
  return;
}

bool get_allow_zipped_isb( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::ALLOW_ZIPPED_ISB, value );
  return value;
}

void remove_allow_zipped_isb( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::ALLOW_ZIPPED_ISB );
  return;
}

std::string unparse_allow_zipped_isb( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ALLOW_ZIPPED_ISB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_perusal_file_enable( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::PU_FILE_ENABLE, value );
  if( !res ) throw CannotSetAttribute( JDL::PU_FILE_ENABLE );
  return;
}

bool get_perusal_file_enable( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::PU_FILE_ENABLE, value );
  if( !res ) throw CannotGetAttribute( JDL::PU_FILE_ENABLE );
  return value;
}

void remove_perusal_file_enable( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::PU_FILE_ENABLE );
  if( !res ) throw CannotRemoveAttribute( JDL::PU_FILE_ENABLE );
  return;
}

std::string unparse_perusal_file_enable( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PU_FILE_ENABLE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::PU_FILE_ENABLE );
  unparser.Unparse( value, tree );
  return value;
}

void set_perusal_file_enable( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::PU_FILE_ENABLE, value );
  return;
}

bool get_perusal_file_enable( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::PU_FILE_ENABLE, value );
  return value;
}

void remove_perusal_file_enable( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::PU_FILE_ENABLE );
  return;
}

std::string unparse_perusal_file_enable( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PU_FILE_ENABLE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_nodes_collocation( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::NODES_COLLOCATION, value );
  if( !res ) throw CannotSetAttribute( JDL::NODES_COLLOCATION );
  return;
}

bool get_nodes_collocation( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::NODES_COLLOCATION, value );
  if( !res ) throw CannotGetAttribute( JDL::NODES_COLLOCATION );
  return value;
}

void remove_nodes_collocation( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::NODES_COLLOCATION );
  if( !res ) throw CannotRemoveAttribute( JDL::NODES_COLLOCATION );
  return;
}

std::string unparse_nodes_collocation( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODES_COLLOCATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::NODES_COLLOCATION );
  unparser.Unparse( value, tree );
  return value;
}

void set_nodes_collocation( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::NODES_COLLOCATION, value );
  return;
}

bool get_nodes_collocation( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::NODES_COLLOCATION, value );
  return value;
}

void remove_nodes_collocation( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::NODES_COLLOCATION );
  return;
}

std::string unparse_nodes_collocation( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODES_COLLOCATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_move_to_ce( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::MOVE_TO_CE, value );
  if( !res ) throw CannotSetAttribute( JDL::MOVE_TO_CE );
  return;
}

bool get_move_to_ce( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::MOVE_TO_CE, value );
  if( !res ) throw CannotGetAttribute( JDL::MOVE_TO_CE );
  return value;
}

void remove_move_to_ce( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::MOVE_TO_CE );
  if( !res ) throw CannotRemoveAttribute( JDL::MOVE_TO_CE );
  return;
}

std::string unparse_move_to_ce( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MOVE_TO_CE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::MOVE_TO_CE );
  unparser.Unparse( value, tree );
  return value;
}

void set_move_to_ce( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::MOVE_TO_CE, value );
  return;
}

bool get_move_to_ce( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::MOVE_TO_CE, value );
  return value;
}

void remove_move_to_ce( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::MOVE_TO_CE );
  return;
}

std::string unparse_move_to_ce( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MOVE_TO_CE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_short_deadline_job( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::SHORT_DEADLINE_JOB, value );
  if( !res ) throw CannotSetAttribute( JDL::SHORT_DEADLINE_JOB );
  return;
}

bool get_short_deadline_job( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::SHORT_DEADLINE_JOB, value );
  if( !res ) throw CannotGetAttribute( JDL::SHORT_DEADLINE_JOB );
  return value;
}

void remove_short_deadline_job( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SHORT_DEADLINE_JOB );
  if( !res ) throw CannotRemoveAttribute( JDL::SHORT_DEADLINE_JOB );
  return;
}

std::string unparse_short_deadline_job( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHORT_DEADLINE_JOB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SHORT_DEADLINE_JOB );
  unparser.Unparse( value, tree );
  return value;
}

void set_short_deadline_job( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SHORT_DEADLINE_JOB, value );
  return;
}

bool get_short_deadline_job( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::SHORT_DEADLINE_JOB, value );
  return value;
}

void remove_short_deadline_job( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SHORT_DEADLINE_JOB );
  return;
}

std::string unparse_short_deadline_job( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHORT_DEADLINE_JOB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_whole_nodes( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::WHOLENODES, value );
  if( !res ) throw CannotSetAttribute( JDL::WHOLENODES );
  return;
}

bool get_whole_nodes( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::WHOLENODES, value );
  if( !res ) throw CannotGetAttribute( JDL::WHOLENODES );
  return value;
}

void remove_whole_nodes( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::WHOLENODES );
  if( !res ) throw CannotRemoveAttribute( JDL::WHOLENODES );
  return;
}

std::string unparse_whole_nodes( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::WHOLENODES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::WHOLENODES );
  unparser.Unparse( value, tree );
  return value;
}

void set_whole_nodes( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::WHOLENODES, value );
  return;
}

bool get_whole_nodes( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::WHOLENODES, value );
  return value;
}

void remove_whole_nodes( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::WHOLENODES );
  return;
}

std::string unparse_whole_nodes( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::WHOLENODES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_enable_wms_feedback( classad::ClassAd &job_ad, const bool &value )
{
  bool res = job_ad.InsertAttr( JDL::ENABLE_WMS_FEEDBACK, value );
  if( !res ) throw CannotSetAttribute( JDL::ENABLE_WMS_FEEDBACK );
  return;
}

bool get_enable_wms_feedback( const classad::ClassAd &job_ad )
{
  bool value, res;
  res = job_ad.EvaluateAttrBool( JDL::ENABLE_WMS_FEEDBACK, value );
  if( !res ) throw CannotGetAttribute( JDL::ENABLE_WMS_FEEDBACK );
  return value;
}

void remove_enable_wms_feedback( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::ENABLE_WMS_FEEDBACK );
  if( !res ) throw CannotRemoveAttribute( JDL::ENABLE_WMS_FEEDBACK );
  return;
}

std::string unparse_enable_wms_feedback( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ENABLE_WMS_FEEDBACK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::ENABLE_WMS_FEEDBACK );
  unparser.Unparse( value, tree );
  return value;
}

void set_enable_wms_feedback( classad::ClassAd &job_ad, bool value, bool &good )
{
  good = job_ad.InsertAttr( JDL::ENABLE_WMS_FEEDBACK, value );
  return;
}

bool get_enable_wms_feedback( const classad::ClassAd &job_ad, bool &good )
{
  bool value;
  good = job_ad.EvaluateAttrBool( JDL::ENABLE_WMS_FEEDBACK, value );
  return value;
}

void remove_enable_wms_feedback( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::ENABLE_WMS_FEEDBACK );
  return;
}

std::string unparse_enable_wms_feedback( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ENABLE_WMS_FEEDBACK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_exit_code( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::EXITCODE, value );
  if( !res ) throw CannotSetAttribute( JDL::EXITCODE );
  return;
}

int get_exit_code( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::EXITCODE, value );
  if( !res ) throw CannotGetAttribute( JDL::EXITCODE );
  return value;
}

void remove_exit_code( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::EXITCODE );
  if( !res ) throw CannotRemoveAttribute( JDL::EXITCODE );
  return;
}

std::string unparse_exit_code( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EXITCODE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::EXITCODE );
  unparser.Unparse( value, tree );
  return value;
}

void set_exit_code( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::EXITCODE, value );
  return;
}

int get_exit_code( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::EXITCODE, value );
  return value;
}

void remove_exit_code( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::EXITCODE );
  return;
}

std::string unparse_exit_code( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EXITCODE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_node_number( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::NODENUMB, value );
  if( !res ) throw CannotSetAttribute( JDL::NODENUMB );
  return;
}

int get_node_number( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::NODENUMB, value );
  if( !res ) throw CannotGetAttribute( JDL::NODENUMB );
  return value;
}

void remove_node_number( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::NODENUMB );
  if( !res ) throw CannotRemoveAttribute( JDL::NODENUMB );
  return;
}

std::string unparse_node_number( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODENUMB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::NODENUMB );
  unparser.Unparse( value, tree );
  return value;
}

void set_node_number( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::NODENUMB, value );
  return;
}

int get_node_number( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::NODENUMB, value );
  return value;
}

void remove_node_number( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::NODENUMB );
  return;
}

std::string unparse_node_number( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODENUMB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_cpu_number( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::CPUNUMBER, value );
  if( !res ) throw CannotSetAttribute( JDL::CPUNUMBER );
  return;
}

int get_cpu_number( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::CPUNUMBER, value );
  if( !res ) throw CannotGetAttribute( JDL::CPUNUMBER );
  return value;
}

void remove_cpu_number( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CPUNUMBER );
  if( !res ) throw CannotRemoveAttribute( JDL::CPUNUMBER );
  return;
}

std::string unparse_cpu_number( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CPUNUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CPUNUMBER );
  unparser.Unparse( value, tree );
  return value;
}

void set_cpu_number( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CPUNUMBER, value );
  return;
}

int get_cpu_number( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::CPUNUMBER, value );
  return value;
}

void remove_cpu_number( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CPUNUMBER );
  return;
}

std::string unparse_cpu_number( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CPUNUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_listener_port( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::SHPORT, value );
  if( !res ) throw CannotSetAttribute( JDL::SHPORT );
  return;
}

int get_listener_port( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::SHPORT, value );
  if( !res ) throw CannotGetAttribute( JDL::SHPORT );
  return value;
}

void remove_listener_port( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SHPORT );
  if( !res ) throw CannotRemoveAttribute( JDL::SHPORT );
  return;
}

std::string unparse_listener_port( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHPORT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SHPORT );
  unparser.Unparse( value, tree );
  return value;
}

void set_listener_port( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SHPORT, value );
  return;
}

int get_listener_port( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::SHPORT, value );
  return value;
}

void remove_listener_port( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SHPORT );
  return;
}

std::string unparse_listener_port( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHPORT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_retry_count( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::RETRYCOUNT, value );
  if( !res ) throw CannotSetAttribute( JDL::RETRYCOUNT );
  return;
}

int get_retry_count( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::RETRYCOUNT, value );
  if( !res ) throw CannotGetAttribute( JDL::RETRYCOUNT );
  return value;
}

void remove_retry_count( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::RETRYCOUNT );
  if( !res ) throw CannotRemoveAttribute( JDL::RETRYCOUNT );
  return;
}

std::string unparse_retry_count( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::RETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::RETRYCOUNT );
  unparser.Unparse( value, tree );
  return value;
}

void set_retry_count( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::RETRYCOUNT, value );
  return;
}

int get_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::RETRYCOUNT, value );
  return value;
}

void remove_retry_count( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::RETRYCOUNT );
  return;
}

std::string unparse_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::RETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_shallow_retry_count( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::SHALLOWRETRYCOUNT, value );
  if( !res ) throw CannotSetAttribute( JDL::SHALLOWRETRYCOUNT );
  return;
}

int get_shallow_retry_count( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::SHALLOWRETRYCOUNT, value );
  if( !res ) throw CannotGetAttribute( JDL::SHALLOWRETRYCOUNT );
  return value;
}

void remove_shallow_retry_count( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SHALLOWRETRYCOUNT );
  if( !res ) throw CannotRemoveAttribute( JDL::SHALLOWRETRYCOUNT );
  return;
}

std::string unparse_shallow_retry_count( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHALLOWRETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SHALLOWRETRYCOUNT );
  unparser.Unparse( value, tree );
  return value;
}

void set_shallow_retry_count( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SHALLOWRETRYCOUNT, value );
  return;
}

int get_shallow_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::SHALLOWRETRYCOUNT, value );
  return value;
}

void remove_shallow_retry_count( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SHALLOWRETRYCOUNT );
  return;
}

std::string unparse_shallow_retry_count( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHALLOWRETRYCOUNT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_perusal_time_interval( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::PU_TIME_INTERVAL, value );
  if( !res ) throw CannotSetAttribute( JDL::PU_TIME_INTERVAL );
  return;
}

int get_perusal_time_interval( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::PU_TIME_INTERVAL, value );
  if( !res ) throw CannotGetAttribute( JDL::PU_TIME_INTERVAL );
  return value;
}

void remove_perusal_time_interval( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::PU_TIME_INTERVAL );
  if( !res ) throw CannotRemoveAttribute( JDL::PU_TIME_INTERVAL );
  return;
}

std::string unparse_perusal_time_interval( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PU_TIME_INTERVAL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::PU_TIME_INTERVAL );
  unparser.Unparse( value, tree );
  return value;
}

void set_perusal_time_interval( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::PU_TIME_INTERVAL, value );
  return;
}

int get_perusal_time_interval( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::PU_TIME_INTERVAL, value );
  return value;
}

void remove_perusal_time_interval( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::PU_TIME_INTERVAL );
  return;
}

std::string unparse_perusal_time_interval( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PU_TIME_INTERVAL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_smpgranularity( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::SMPGRANULARITY, value );
  if( !res ) throw CannotSetAttribute( JDL::SMPGRANULARITY );
  return;
}

int get_smpgranularity( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::SMPGRANULARITY, value );
  if( !res ) throw CannotGetAttribute( JDL::SMPGRANULARITY );
  return value;
}

void remove_smpgranularity( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SMPGRANULARITY );
  if( !res ) throw CannotRemoveAttribute( JDL::SMPGRANULARITY );
  return;
}

std::string unparse_smpgranularity( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SMPGRANULARITY );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SMPGRANULARITY );
  unparser.Unparse( value, tree );
  return value;
}

void set_smpgranularity( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SMPGRANULARITY, value );
  return;
}

int get_smpgranularity( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::SMPGRANULARITY, value );
  return value;
}

void remove_smpgranularity( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SMPGRANULARITY );
  return;
}

std::string unparse_smpgranularity( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SMPGRANULARITY );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_host_number( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::HOSTNUMBER, value );
  if( !res ) throw CannotSetAttribute( JDL::HOSTNUMBER );
  return;
}

int get_host_number( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::HOSTNUMBER, value );
  if( !res ) throw CannotGetAttribute( JDL::HOSTNUMBER );
  return value;
}

void remove_host_number( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::HOSTNUMBER );
  if( !res ) throw CannotRemoveAttribute( JDL::HOSTNUMBER );
  return;
}

std::string unparse_host_number( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::HOSTNUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::HOSTNUMBER );
  unparser.Unparse( value, tree );
  return value;
}

void set_host_number( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::HOSTNUMBER, value );
  return;
}

int get_host_number( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::HOSTNUMBER, value );
  return value;
}

void remove_host_number( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::HOSTNUMBER );
  return;
}

std::string unparse_host_number( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::HOSTNUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_ce_match( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::CE_MATCH, value );
  if( !res ) throw CannotSetAttribute( JDL::CE_MATCH );
  return;
}

int get_ce_match( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::CE_MATCH, value );
  if( !res ) throw CannotGetAttribute( JDL::CE_MATCH );
  return value;
}

void remove_ce_match( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CE_MATCH );
  if( !res ) throw CannotRemoveAttribute( JDL::CE_MATCH );
  return;
}

std::string unparse_ce_match( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CE_MATCH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CE_MATCH );
  unparser.Unparse( value, tree );
  return value;
}

void set_ce_match( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CE_MATCH, value );
  return;
}

int get_ce_match( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::CE_MATCH, value );
  return value;
}

void remove_ce_match( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CE_MATCH );
  return;
}

std::string unparse_ce_match( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CE_MATCH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_job_steps( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::CHKPT_STEPS, value );
  if( !res ) throw CannotSetAttribute( JDL::CHKPT_STEPS );
  return;
}

int get_job_steps( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::CHKPT_STEPS, value );
  if( !res ) throw CannotGetAttribute( JDL::CHKPT_STEPS );
  return value;
}

void remove_job_steps( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CHKPT_STEPS );
  if( !res ) throw CannotRemoveAttribute( JDL::CHKPT_STEPS );
  return;
}

std::string unparse_job_steps( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_STEPS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CHKPT_STEPS );
  unparser.Unparse( value, tree );
  return value;
}

void set_job_steps( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CHKPT_STEPS, value );
  return;
}

int get_job_steps( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::CHKPT_STEPS, value );
  return value;
}

void remove_job_steps( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CHKPT_STEPS );
  return;
}

std::string unparse_job_steps( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_STEPS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_current_step( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::CHKPT_CURRENTSTEP, value );
  if( !res ) throw CannotSetAttribute( JDL::CHKPT_CURRENTSTEP );
  return;
}

int get_current_step( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::CHKPT_CURRENTSTEP, value );
  if( !res ) throw CannotGetAttribute( JDL::CHKPT_CURRENTSTEP );
  return value;
}

void remove_current_step( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CHKPT_CURRENTSTEP );
  if( !res ) throw CannotRemoveAttribute( JDL::CHKPT_CURRENTSTEP );
  return;
}

std::string unparse_current_step( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_CURRENTSTEP );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CHKPT_CURRENTSTEP );
  unparser.Unparse( value, tree );
  return value;
}

void set_current_step( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CHKPT_CURRENTSTEP, value );
  return;
}

int get_current_step( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::CHKPT_CURRENTSTEP, value );
  return value;
}

void remove_current_step( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CHKPT_CURRENTSTEP );
  return;
}

std::string unparse_current_step( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_CURRENTSTEP );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_expiry_time( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::EXPIRY_TIME, value );
  if( !res ) throw CannotSetAttribute( JDL::EXPIRY_TIME );
  return;
}

int get_expiry_time( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::EXPIRY_TIME, value );
  if( !res ) throw CannotGetAttribute( JDL::EXPIRY_TIME );
  return value;
}

void remove_expiry_time( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::EXPIRY_TIME );
  if( !res ) throw CannotRemoveAttribute( JDL::EXPIRY_TIME );
  return;
}

std::string unparse_expiry_time( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EXPIRY_TIME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::EXPIRY_TIME );
  unparser.Unparse( value, tree );
  return value;
}

void set_expiry_time( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::EXPIRY_TIME, value );
  return;
}

int get_expiry_time( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::EXPIRY_TIME, value );
  return value;
}

void remove_expiry_time( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::EXPIRY_TIME );
  return;
}

std::string unparse_expiry_time( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EXPIRY_TIME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_creation_time( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::CREATION_TIME, value );
  if( !res ) throw CannotSetAttribute( JDL::CREATION_TIME );
  return;
}

int get_creation_time( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::CREATION_TIME, value );
  if( !res ) throw CannotGetAttribute( JDL::CREATION_TIME );
  return value;
}

void remove_creation_time( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CREATION_TIME );
  if( !res ) throw CannotRemoveAttribute( JDL::CREATION_TIME );
  return;
}

std::string unparse_creation_time( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CREATION_TIME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CREATION_TIME );
  unparser.Unparse( value, tree );
  return value;
}

void set_creation_time( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CREATION_TIME, value );
  return;
}

int get_creation_time( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::CREATION_TIME, value );
  return value;
}

void remove_creation_time( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CREATION_TIME );
  return;
}

std::string unparse_creation_time( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CREATION_TIME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_validity_time( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::VALIDITY_TIME, value );
  if( !res ) throw CannotSetAttribute( JDL::VALIDITY_TIME );
  return;
}

int get_validity_time( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::VALIDITY_TIME, value );
  if( !res ) throw CannotGetAttribute( JDL::VALIDITY_TIME );
  return value;
}

void remove_validity_time( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::VALIDITY_TIME );
  if( !res ) throw CannotRemoveAttribute( JDL::VALIDITY_TIME );
  return;
}

std::string unparse_validity_time( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::VALIDITY_TIME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::VALIDITY_TIME );
  unparser.Unparse( value, tree );
  return value;
}

void set_validity_time( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::VALIDITY_TIME, value );
  return;
}

int get_validity_time( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::VALIDITY_TIME, value );
  return value;
}

void remove_validity_time( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::VALIDITY_TIME );
  return;
}

std::string unparse_validity_time( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::VALIDITY_TIME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_partition_number( classad::ClassAd &job_ad, const int &value )
{
  bool res = job_ad.InsertAttr( JDL::PARTITION_NUMBER, value );
  if( !res ) throw CannotSetAttribute( JDL::PARTITION_NUMBER );
  return;
}

int get_partition_number( const classad::ClassAd &job_ad )
{
  bool res;
  int value;
  res = job_ad.EvaluateAttrNumber( JDL::PARTITION_NUMBER, value );
  if( !res ) throw CannotGetAttribute( JDL::PARTITION_NUMBER );
  return value;
}

void remove_partition_number( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::PARTITION_NUMBER );
  if( !res ) throw CannotRemoveAttribute( JDL::PARTITION_NUMBER );
  return;
}

std::string unparse_partition_number( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PARTITION_NUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::PARTITION_NUMBER );
  unparser.Unparse( value, tree );
  return value;
}

void set_partition_number( classad::ClassAd &job_ad, int value, bool &good )
{
  good = job_ad.InsertAttr( JDL::PARTITION_NUMBER, value );
  return;
}

int get_partition_number( const classad::ClassAd &job_ad, bool &good )
{
  int value;
  good = job_ad.EvaluateAttrNumber( JDL::PARTITION_NUMBER, value );
  return value;
}

void remove_partition_number( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::PARTITION_NUMBER );
  return;
}

std::string unparse_partition_number( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PARTITION_NUMBER );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_rank( classad::ClassAd &job_ad, const double &value )
{
  bool res = job_ad.InsertAttr( JDL::RANK, value );
  if( !res ) throw CannotSetAttribute( JDL::RANK );
  return;
}

double get_rank( const classad::ClassAd &job_ad )
{
  bool res;
  double value;
  res = job_ad.EvaluateAttrNumber( JDL::RANK, value );
  if( !res ) throw CannotGetAttribute( JDL::RANK );
  return value;
}

void remove_rank( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::RANK );
  if( !res ) throw CannotRemoveAttribute( JDL::RANK );
  return;
}

std::string unparse_rank( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::RANK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::RANK );
  unparser.Unparse( value, tree );
  return value;
}

void set_rank( classad::ClassAd &job_ad, double value, bool &good )
{
  good = job_ad.InsertAttr( JDL::RANK, value );
  return;
}

double get_rank( const classad::ClassAd &job_ad, bool &good )
{
  double value;
  good = job_ad.EvaluateAttrNumber( JDL::RANK, value );
  return value;
}

void remove_rank( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::RANK );
  return;
}

std::string unparse_rank( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::RANK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_fuzzy_factor( classad::ClassAd &job_ad, const double &value )
{
  bool res = job_ad.InsertAttr( JDL::FUZZY_FACTOR, value );
  if( !res ) throw CannotSetAttribute( JDL::FUZZY_FACTOR );
  return;
}

double get_fuzzy_factor( const classad::ClassAd &job_ad )
{
  bool res;
  double value;
  res = job_ad.EvaluateAttrNumber( JDL::FUZZY_FACTOR, value );
  if( !res ) throw CannotGetAttribute( JDL::FUZZY_FACTOR );
  return value;
}

void remove_fuzzy_factor( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::FUZZY_FACTOR );
  if( !res ) throw CannotRemoveAttribute( JDL::FUZZY_FACTOR );
  return;
}

std::string unparse_fuzzy_factor( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::FUZZY_FACTOR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::FUZZY_FACTOR );
  unparser.Unparse( value, tree );
  return value;
}

void set_fuzzy_factor( classad::ClassAd &job_ad, double value, bool &good )
{
  good = job_ad.InsertAttr( JDL::FUZZY_FACTOR, value );
  return;
}

double get_fuzzy_factor( const classad::ClassAd &job_ad, bool &good )
{
  double value;
  good = job_ad.EvaluateAttrNumber( JDL::FUZZY_FACTOR, value );
  return value;
}

void remove_fuzzy_factor( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::FUZZY_FACTOR );
  return;
}

std::string unparse_fuzzy_factor( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::FUZZY_FACTOR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_notification_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::NOTIFYTYPE, value );
  if( !res ) throw CannotSetAttribute( JDL::NOTIFYTYPE );
  return;
}

std::string get_notification_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::NOTIFYTYPE, value );
  if( !res ) throw CannotGetAttribute( JDL::NOTIFYTYPE );
  return value;
}

void remove_notification_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::NOTIFYTYPE );
  if( !res ) throw CannotRemoveAttribute( JDL::NOTIFYTYPE );
  return;
}

std::string unparse_notification_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NOTIFYTYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::NOTIFYTYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_notification_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::NOTIFYTYPE, value );
}

std::string get_notification_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::NOTIFYTYPE, value );
  return value;
}

void remove_notification_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::NOTIFYTYPE );
  return;
}

std::string unparse_notification_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NOTIFYTYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_job_status( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::JOBSTATUS, value );
  if( !res ) throw CannotSetAttribute( JDL::JOBSTATUS );
  return;
}

std::string get_job_status( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::JOBSTATUS, value );
  if( !res ) throw CannotGetAttribute( JDL::JOBSTATUS );
  return value;
}

void remove_job_status( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::JOBSTATUS );
  if( !res ) throw CannotRemoveAttribute( JDL::JOBSTATUS );
  return;
}

std::string unparse_job_status( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOBSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::JOBSTATUS );
  unparser.Unparse( value, tree );
  return value;
}

void set_job_status( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::JOBSTATUS, value );
}

std::string get_job_status( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::JOBSTATUS, value );
  return value;
}

void remove_job_status( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::JOBSTATUS );
  return;
}

std::string unparse_job_status( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOBSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_aborted_reason( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::ABORTREASON, value );
  if( !res ) throw CannotSetAttribute( JDL::ABORTREASON );
  return;
}

std::string get_aborted_reason( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::ABORTREASON, value );
  if( !res ) throw CannotGetAttribute( JDL::ABORTREASON );
  return value;
}

void remove_aborted_reason( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::ABORTREASON );
  if( !res ) throw CannotRemoveAttribute( JDL::ABORTREASON );
  return;
}

std::string unparse_aborted_reason( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ABORTREASON );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::ABORTREASON );
  unparser.Unparse( value, tree );
  return value;
}

void set_aborted_reason( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::ABORTREASON, value );
}

std::string get_aborted_reason( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::ABORTREASON, value );
  return value;
}

void remove_aborted_reason( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::ABORTREASON );
  return;
}

std::string unparse_aborted_reason( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ABORTREASON );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_globus_resource_contact_string( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::GLOBUSRESOURCE, value );
  if( !res ) throw CannotSetAttribute( JDL::GLOBUSRESOURCE );
  return;
}

std::string get_globus_resource_contact_string( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::GLOBUSRESOURCE, value );
  if( !res ) throw CannotGetAttribute( JDL::GLOBUSRESOURCE );
  return value;
}

void remove_globus_resource_contact_string( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::GLOBUSRESOURCE );
  if( !res ) throw CannotRemoveAttribute( JDL::GLOBUSRESOURCE );
  return;
}

std::string unparse_globus_resource_contact_string( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::GLOBUSRESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::GLOBUSRESOURCE );
  unparser.Unparse( value, tree );
  return value;
}

void set_globus_resource_contact_string( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::GLOBUSRESOURCE, value );
}

std::string get_globus_resource_contact_string( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::GLOBUSRESOURCE, value );
  return value;
}

void remove_globus_resource_contact_string( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::GLOBUSRESOURCE );
  return;
}

std::string unparse_globus_resource_contact_string( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::GLOBUSRESOURCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_queue_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::QUEUENAME, value );
  if( !res ) throw CannotSetAttribute( JDL::QUEUENAME );
  return;
}

std::string get_queue_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::QUEUENAME, value );
  if( !res ) throw CannotGetAttribute( JDL::QUEUENAME );
  return value;
}

void remove_queue_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::QUEUENAME );
  if( !res ) throw CannotRemoveAttribute( JDL::QUEUENAME );
  return;
}

std::string unparse_queue_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::QUEUENAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::QUEUENAME );
  unparser.Unparse( value, tree );
  return value;
}

void set_queue_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::QUEUENAME, value );
}

std::string get_queue_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::QUEUENAME, value );
  return value;
}

void remove_queue_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::QUEUENAME );
  return;
}

std::string unparse_queue_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::QUEUENAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_match_status( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::MATCHSTATUS, value );
  if( !res ) throw CannotSetAttribute( JDL::MATCHSTATUS );
  return;
}

std::string get_match_status( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::MATCHSTATUS, value );
  if( !res ) throw CannotGetAttribute( JDL::MATCHSTATUS );
  return value;
}

void remove_match_status( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::MATCHSTATUS );
  if( !res ) throw CannotRemoveAttribute( JDL::MATCHSTATUS );
  return;
}

std::string unparse_match_status( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MATCHSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::MATCHSTATUS );
  unparser.Unparse( value, tree );
  return value;
}

void set_match_status( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::MATCHSTATUS, value );
}

std::string get_match_status( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::MATCHSTATUS, value );
  return value;
}

void remove_match_status( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::MATCHSTATUS );
  return;
}

std::string unparse_match_status( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MATCHSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_ce_rank( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::CE_RANK, value );
  if( !res ) throw CannotSetAttribute( JDL::CE_RANK );
  return;
}

std::string get_ce_rank( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::CE_RANK, value );
  if( !res ) throw CannotGetAttribute( JDL::CE_RANK );
  return value;
}

void remove_ce_rank( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CE_RANK );
  if( !res ) throw CannotRemoveAttribute( JDL::CE_RANK );
  return;
}

std::string unparse_ce_rank( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CE_RANK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CE_RANK );
  unparser.Unparse( value, tree );
  return value;
}

void set_ce_rank( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CE_RANK, value );
}

std::string get_ce_rank( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::CE_RANK, value );
  return value;
}

void remove_ce_rank( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CE_RANK );
  return;
}

std::string unparse_ce_rank( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CE_RANK );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_cancel_status( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::CANCELSTATUS, value );
  if( !res ) throw CannotSetAttribute( JDL::CANCELSTATUS );
  return;
}

std::string get_cancel_status( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::CANCELSTATUS, value );
  if( !res ) throw CannotGetAttribute( JDL::CANCELSTATUS );
  return value;
}

void remove_cancel_status( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CANCELSTATUS );
  if( !res ) throw CannotRemoveAttribute( JDL::CANCELSTATUS );
  return;
}

std::string unparse_cancel_status( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CANCELSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CANCELSTATUS );
  unparser.Unparse( value, tree );
  return value;
}

void set_cancel_status( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CANCELSTATUS, value );
}

std::string get_cancel_status( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::CANCELSTATUS, value );
  return value;
}

void remove_cancel_status( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CANCELSTATUS );
  return;
}

std::string unparse_cancel_status( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CANCELSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_failure_reason( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::FAILUREREASON, value );
  if( !res ) throw CannotSetAttribute( JDL::FAILUREREASON );
  return;
}

std::string get_failure_reason( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::FAILUREREASON, value );
  if( !res ) throw CannotGetAttribute( JDL::FAILUREREASON );
  return value;
}

void remove_failure_reason( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::FAILUREREASON );
  if( !res ) throw CannotRemoveAttribute( JDL::FAILUREREASON );
  return;
}

std::string unparse_failure_reason( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::FAILUREREASON );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::FAILUREREASON );
  unparser.Unparse( value, tree );
  return value;
}

void set_failure_reason( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::FAILUREREASON, value );
}

std::string get_failure_reason( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::FAILUREREASON, value );
  return value;
}

void remove_failure_reason( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::FAILUREREASON );
  return;
}

std::string unparse_failure_reason( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::FAILUREREASON );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_transfer_status( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::TRANSFERSTATUS, value );
  if( !res ) throw CannotSetAttribute( JDL::TRANSFERSTATUS );
  return;
}

std::string get_transfer_status( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::TRANSFERSTATUS, value );
  if( !res ) throw CannotGetAttribute( JDL::TRANSFERSTATUS );
  return value;
}

void remove_transfer_status( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::TRANSFERSTATUS );
  if( !res ) throw CannotRemoveAttribute( JDL::TRANSFERSTATUS );
  return;
}

std::string unparse_transfer_status( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::TRANSFERSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::TRANSFERSTATUS );
  unparser.Unparse( value, tree );
  return value;
}

void set_transfer_status( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::TRANSFERSTATUS, value );
}

std::string get_transfer_status( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::TRANSFERSTATUS, value );
  return value;
}

void remove_transfer_status( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::TRANSFERSTATUS );
  return;
}

std::string unparse_transfer_status( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::TRANSFERSTATUS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_sandbox_file( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::SANDBOXFILE, value );
  if( !res ) throw CannotSetAttribute( JDL::SANDBOXFILE );
  return;
}

std::string get_sandbox_file( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::SANDBOXFILE, value );
  if( !res ) throw CannotGetAttribute( JDL::SANDBOXFILE );
  return value;
}

void remove_sandbox_file( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SANDBOXFILE );
  if( !res ) throw CannotRemoveAttribute( JDL::SANDBOXFILE );
  return;
}

std::string unparse_sandbox_file( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SANDBOXFILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SANDBOXFILE );
  unparser.Unparse( value, tree );
  return value;
}

void set_sandbox_file( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SANDBOXFILE, value );
}

std::string get_sandbox_file( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::SANDBOXFILE, value );
  return value;
}

void remove_sandbox_file( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SANDBOXFILE );
  return;
}

std::string unparse_sandbox_file( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SANDBOXFILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_edg_jobid( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::JOBID, value );
  if( !res ) throw CannotSetAttribute( JDL::JOBID );
  return;
}

std::string get_edg_jobid( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::JOBID, value );
  if( !res ) throw CannotGetAttribute( JDL::JOBID );
  return value;
}

void remove_edg_jobid( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::JOBID );
  if( !res ) throw CannotRemoveAttribute( JDL::JOBID );
  return;
}

std::string unparse_edg_jobid( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOBID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::JOBID );
  unparser.Unparse( value, tree );
  return value;
}

void set_edg_jobid( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::JOBID, value );
}

std::string get_edg_jobid( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::JOBID, value );
  return value;
}

void remove_edg_jobid( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::JOBID );
  return;
}

std::string unparse_edg_jobid( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOBID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_ce_id( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::CEID, value );
  if( !res ) throw CannotSetAttribute( JDL::CEID );
  return;
}

std::string get_ce_id( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::CEID, value );
  if( !res ) throw CannotGetAttribute( JDL::CEID );
  return value;
}

void remove_ce_id( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CEID );
  if( !res ) throw CannotRemoveAttribute( JDL::CEID );
  return;
}

std::string unparse_ce_id( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CEID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CEID );
  unparser.Unparse( value, tree );
  return value;
}

void set_ce_id( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CEID, value );
}

std::string get_ce_id( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::CEID, value );
  return value;
}

void remove_ce_id( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CEID );
  return;
}

std::string unparse_ce_id( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CEID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_submit_to( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::SUBMIT_TO, value );
  if( !res ) throw CannotSetAttribute( JDL::SUBMIT_TO );
  return;
}

std::string get_submit_to( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::SUBMIT_TO, value );
  if( !res ) throw CannotGetAttribute( JDL::SUBMIT_TO );
  return value;
}

void remove_submit_to( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SUBMIT_TO );
  if( !res ) throw CannotRemoveAttribute( JDL::SUBMIT_TO );
  return;
}

std::string unparse_submit_to( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SUBMIT_TO );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SUBMIT_TO );
  unparser.Unparse( value, tree );
  return value;
}

void set_submit_to( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SUBMIT_TO, value );
}

std::string get_submit_to( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::SUBMIT_TO, value );
  return value;
}

void remove_submit_to( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SUBMIT_TO );
  return;
}

std::string unparse_submit_to( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SUBMIT_TO );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_executable( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::EXECUTABLE, value );
  if( !res ) throw CannotSetAttribute( JDL::EXECUTABLE );
  return;
}

std::string get_executable( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::EXECUTABLE, value );
  if( !res ) throw CannotGetAttribute( JDL::EXECUTABLE );
  return value;
}

void remove_executable( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::EXECUTABLE );
  if( !res ) throw CannotRemoveAttribute( JDL::EXECUTABLE );
  return;
}

std::string unparse_executable( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EXECUTABLE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::EXECUTABLE );
  unparser.Unparse( value, tree );
  return value;
}

void set_executable( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::EXECUTABLE, value );
}

std::string get_executable( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::EXECUTABLE, value );
  return value;
}

void remove_executable( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::EXECUTABLE );
  return;
}

std::string unparse_executable( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EXECUTABLE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_std_output( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::STDOUTPUT, value );
  if( !res ) throw CannotSetAttribute( JDL::STDOUTPUT );
  return;
}

std::string get_std_output( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::STDOUTPUT, value );
  if( !res ) throw CannotGetAttribute( JDL::STDOUTPUT );
  return value;
}

void remove_std_output( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::STDOUTPUT );
  if( !res ) throw CannotRemoveAttribute( JDL::STDOUTPUT );
  return;
}

std::string unparse_std_output( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STDOUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::STDOUTPUT );
  unparser.Unparse( value, tree );
  return value;
}

void set_std_output( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::STDOUTPUT, value );
}

std::string get_std_output( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::STDOUTPUT, value );
  return value;
}

void remove_std_output( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::STDOUTPUT );
  return;
}

std::string unparse_std_output( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STDOUTPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_std_input( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::STDINPUT, value );
  if( !res ) throw CannotSetAttribute( JDL::STDINPUT );
  return;
}

std::string get_std_input( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::STDINPUT, value );
  if( !res ) throw CannotGetAttribute( JDL::STDINPUT );
  return value;
}

void remove_std_input( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::STDINPUT );
  if( !res ) throw CannotRemoveAttribute( JDL::STDINPUT );
  return;
}

std::string unparse_std_input( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STDINPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::STDINPUT );
  unparser.Unparse( value, tree );
  return value;
}

void set_std_input( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::STDINPUT, value );
}

std::string get_std_input( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::STDINPUT, value );
  return value;
}

void remove_std_input( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::STDINPUT );
  return;
}

std::string unparse_std_input( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STDINPUT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_std_error( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::STDERROR, value );
  if( !res ) throw CannotSetAttribute( JDL::STDERROR );
  return;
}

std::string get_std_error( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::STDERROR, value );
  if( !res ) throw CannotGetAttribute( JDL::STDERROR );
  return value;
}

void remove_std_error( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::STDERROR );
  if( !res ) throw CannotRemoveAttribute( JDL::STDERROR );
  return;
}

std::string unparse_std_error( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STDERROR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::STDERROR );
  unparser.Unparse( value, tree );
  return value;
}

void set_std_error( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::STDERROR, value );
}

std::string get_std_error( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::STDERROR, value );
  return value;
}

void remove_std_error( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::STDERROR );
  return;
}

std::string unparse_std_error( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STDERROR );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_arguments( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::ARGUMENTS, value );
  if( !res ) throw CannotSetAttribute( JDL::ARGUMENTS );
  return;
}

std::string get_arguments( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::ARGUMENTS, value );
  if( !res ) throw CannotGetAttribute( JDL::ARGUMENTS );
  return value;
}

void remove_arguments( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::ARGUMENTS );
  if( !res ) throw CannotRemoveAttribute( JDL::ARGUMENTS );
  return;
}

std::string unparse_arguments( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ARGUMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::ARGUMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_arguments( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::ARGUMENTS, value );
}

std::string get_arguments( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::ARGUMENTS, value );
  return value;
}

void remove_arguments( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::ARGUMENTS );
  return;
}

std::string unparse_arguments( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ARGUMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_prologue( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::PROLOGUE, value );
  if( !res ) throw CannotSetAttribute( JDL::PROLOGUE );
  return;
}

std::string get_prologue( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::PROLOGUE, value );
  if( !res ) throw CannotGetAttribute( JDL::PROLOGUE );
  return value;
}

void remove_prologue( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::PROLOGUE );
  if( !res ) throw CannotRemoveAttribute( JDL::PROLOGUE );
  return;
}

std::string unparse_prologue( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PROLOGUE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::PROLOGUE );
  unparser.Unparse( value, tree );
  return value;
}

void set_prologue( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::PROLOGUE, value );
}

std::string get_prologue( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::PROLOGUE, value );
  return value;
}

void remove_prologue( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::PROLOGUE );
  return;
}

std::string unparse_prologue( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PROLOGUE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_prologue_arguments( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::PROLOGUE_ARGUMENTS, value );
  if( !res ) throw CannotSetAttribute( JDL::PROLOGUE_ARGUMENTS );
  return;
}

std::string get_prologue_arguments( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::PROLOGUE_ARGUMENTS, value );
  if( !res ) throw CannotGetAttribute( JDL::PROLOGUE_ARGUMENTS );
  return value;
}

void remove_prologue_arguments( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::PROLOGUE_ARGUMENTS );
  if( !res ) throw CannotRemoveAttribute( JDL::PROLOGUE_ARGUMENTS );
  return;
}

std::string unparse_prologue_arguments( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PROLOGUE_ARGUMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::PROLOGUE_ARGUMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_prologue_arguments( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::PROLOGUE_ARGUMENTS, value );
}

std::string get_prologue_arguments( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::PROLOGUE_ARGUMENTS, value );
  return value;
}

void remove_prologue_arguments( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::PROLOGUE_ARGUMENTS );
  return;
}

std::string unparse_prologue_arguments( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PROLOGUE_ARGUMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_epilogue( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::EPILOGUE, value );
  if( !res ) throw CannotSetAttribute( JDL::EPILOGUE );
  return;
}

std::string get_epilogue( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::EPILOGUE, value );
  if( !res ) throw CannotGetAttribute( JDL::EPILOGUE );
  return value;
}

void remove_epilogue( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::EPILOGUE );
  if( !res ) throw CannotRemoveAttribute( JDL::EPILOGUE );
  return;
}

std::string unparse_epilogue( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EPILOGUE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::EPILOGUE );
  unparser.Unparse( value, tree );
  return value;
}

void set_epilogue( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::EPILOGUE, value );
}

std::string get_epilogue( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::EPILOGUE, value );
  return value;
}

void remove_epilogue( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::EPILOGUE );
  return;
}

std::string unparse_epilogue( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EPILOGUE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_epilogue_arguments( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::EPILOGUE_ARGUMENTS, value );
  if( !res ) throw CannotSetAttribute( JDL::EPILOGUE_ARGUMENTS );
  return;
}

std::string get_epilogue_arguments( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::EPILOGUE_ARGUMENTS, value );
  if( !res ) throw CannotGetAttribute( JDL::EPILOGUE_ARGUMENTS );
  return value;
}

void remove_epilogue_arguments( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::EPILOGUE_ARGUMENTS );
  if( !res ) throw CannotRemoveAttribute( JDL::EPILOGUE_ARGUMENTS );
  return;
}

std::string unparse_epilogue_arguments( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EPILOGUE_ARGUMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::EPILOGUE_ARGUMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_epilogue_arguments( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::EPILOGUE_ARGUMENTS, value );
}

std::string get_epilogue_arguments( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::EPILOGUE_ARGUMENTS, value );
  return value;
}

void remove_epilogue_arguments( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::EPILOGUE_ARGUMENTS );
  return;
}

std::string unparse_epilogue_arguments( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::EPILOGUE_ARGUMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_my_proxy_server( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::MYPROXY, value );
  if( !res ) throw CannotSetAttribute( JDL::MYPROXY );
  return;
}

std::string get_my_proxy_server( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::MYPROXY, value );
  if( !res ) throw CannotGetAttribute( JDL::MYPROXY );
  return value;
}

void remove_my_proxy_server( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::MYPROXY );
  if( !res ) throw CannotRemoveAttribute( JDL::MYPROXY );
  return;
}

std::string unparse_my_proxy_server( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MYPROXY );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::MYPROXY );
  unparser.Unparse( value, tree );
  return value;
}

void set_my_proxy_server( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::MYPROXY, value );
}

std::string get_my_proxy_server( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::MYPROXY, value );
  return value;
}

void remove_my_proxy_server( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::MYPROXY );
  return;
}

std::string unparse_my_proxy_server( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MYPROXY );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_job_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::JOBTYPE, value );
  if( !res ) throw CannotSetAttribute( JDL::JOBTYPE );
  return;
}

std::string get_job_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::JOBTYPE, value );
  if( !res ) throw CannotGetAttribute( JDL::JOBTYPE );
  return value;
}

void remove_job_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::JOBTYPE );
  if( !res ) throw CannotRemoveAttribute( JDL::JOBTYPE );
  return;
}

std::string unparse_job_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOBTYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::JOBTYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_job_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::JOBTYPE, value );
}

std::string get_job_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::JOBTYPE, value );
  return value;
}

void remove_job_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::JOBTYPE );
  return;
}

std::string unparse_job_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOBTYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output_se( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::OUTPUT_SE, value );
  if( !res ) throw CannotSetAttribute( JDL::OUTPUT_SE );
  return;
}

std::string get_output_se( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::OUTPUT_SE, value );
  if( !res ) throw CannotGetAttribute( JDL::OUTPUT_SE );
  return value;
}

void remove_output_se( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OUTPUT_SE );
  if( !res ) throw CannotRemoveAttribute( JDL::OUTPUT_SE );
  return;
}

std::string unparse_output_se( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OUTPUT_SE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OUTPUT_SE );
  unparser.Unparse( value, tree );
  return value;
}

void set_output_se( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::OUTPUT_SE, value );
}

std::string get_output_se( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::OUTPUT_SE, value );
  return value;
}

void remove_output_se( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OUTPUT_SE );
  return;
}

std::string unparse_output_se( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OUTPUT_SE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_replica_catalog( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::REPLICA_CATALOG, value );
  if( !res ) throw CannotSetAttribute( JDL::REPLICA_CATALOG );
  return;
}

std::string get_replica_catalog( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::REPLICA_CATALOG, value );
  if( !res ) throw CannotGetAttribute( JDL::REPLICA_CATALOG );
  return value;
}

void remove_replica_catalog( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::REPLICA_CATALOG );
  if( !res ) throw CannotRemoveAttribute( JDL::REPLICA_CATALOG );
  return;
}

std::string unparse_replica_catalog( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::REPLICA_CATALOG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::REPLICA_CATALOG );
  unparser.Unparse( value, tree );
  return value;
}

void set_replica_catalog( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::REPLICA_CATALOG, value );
}

std::string get_replica_catalog( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::REPLICA_CATALOG, value );
  return value;
}

void remove_replica_catalog( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::REPLICA_CATALOG );
  return;
}

std::string unparse_replica_catalog( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::REPLICA_CATALOG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_user_contact( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::USER_CONTACT, value );
  if( !res ) throw CannotSetAttribute( JDL::USER_CONTACT );
  return;
}

std::string get_user_contact( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::USER_CONTACT, value );
  if( !res ) throw CannotGetAttribute( JDL::USER_CONTACT );
  return value;
}

void remove_user_contact( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::USER_CONTACT );
  if( !res ) throw CannotRemoveAttribute( JDL::USER_CONTACT );
  return;
}

std::string unparse_user_contact( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::USER_CONTACT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::USER_CONTACT );
  unparser.Unparse( value, tree );
  return value;
}

void set_user_contact( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::USER_CONTACT, value );
}

std::string get_user_contact( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::USER_CONTACT, value );
  return value;
}

void remove_user_contact( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::USER_CONTACT );
  return;
}

std::string unparse_user_contact( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::USER_CONTACT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_certificate_subject( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::CERT_SUBJ, value );
  if( !res ) throw CannotSetAttribute( JDL::CERT_SUBJ );
  return;
}

std::string get_certificate_subject( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::CERT_SUBJ, value );
  if( !res ) throw CannotGetAttribute( JDL::CERT_SUBJ );
  return value;
}

void remove_certificate_subject( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CERT_SUBJ );
  if( !res ) throw CannotRemoveAttribute( JDL::CERT_SUBJ );
  return;
}

std::string unparse_certificate_subject( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CERT_SUBJ );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CERT_SUBJ );
  unparser.Unparse( value, tree );
  return value;
}

void set_certificate_subject( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CERT_SUBJ, value );
}

std::string get_certificate_subject( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::CERT_SUBJ, value );
  return value;
}

void remove_certificate_subject( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CERT_SUBJ );
  return;
}

std::string unparse_certificate_subject( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CERT_SUBJ );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::TYPE, value );
  if( !res ) throw CannotSetAttribute( JDL::TYPE );
  return;
}

std::string get_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::TYPE, value );
  if( !res ) throw CannotGetAttribute( JDL::TYPE );
  return value;
}

void remove_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::TYPE );
  if( !res ) throw CannotRemoveAttribute( JDL::TYPE );
  return;
}

std::string unparse_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::TYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::TYPE, value );
}

std::string get_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::TYPE, value );
  return value;
}

void remove_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::TYPE );
  return;
}

std::string unparse_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_lb_sequence_code( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::LB_SEQUENCE_CODE, value );
  if( !res ) throw CannotSetAttribute( JDL::LB_SEQUENCE_CODE );
  return;
}

std::string get_lb_sequence_code( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::LB_SEQUENCE_CODE, value );
  if( !res ) throw CannotGetAttribute( JDL::LB_SEQUENCE_CODE );
  return value;
}

void remove_lb_sequence_code( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::LB_SEQUENCE_CODE );
  if( !res ) throw CannotRemoveAttribute( JDL::LB_SEQUENCE_CODE );
  return;
}

std::string unparse_lb_sequence_code( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::LB_SEQUENCE_CODE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::LB_SEQUENCE_CODE );
  unparser.Unparse( value, tree );
  return value;
}

void set_lb_sequence_code( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::LB_SEQUENCE_CODE, value );
}

std::string get_lb_sequence_code( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::LB_SEQUENCE_CODE, value );
  return value;
}

void remove_lb_sequence_code( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::LB_SEQUENCE_CODE );
  return;
}

std::string unparse_lb_sequence_code( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::LB_SEQUENCE_CODE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_lrms_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::LRMS_TYPE, value );
  if( !res ) throw CannotSetAttribute( JDL::LRMS_TYPE );
  return;
}

std::string get_lrms_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::LRMS_TYPE, value );
  if( !res ) throw CannotGetAttribute( JDL::LRMS_TYPE );
  return value;
}

void remove_lrms_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::LRMS_TYPE );
  if( !res ) throw CannotRemoveAttribute( JDL::LRMS_TYPE );
  return;
}

std::string unparse_lrms_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::LRMS_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::LRMS_TYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_lrms_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::LRMS_TYPE, value );
}

std::string get_lrms_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::LRMS_TYPE, value );
  return value;
}

void remove_lrms_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::LRMS_TYPE );
  return;
}

std::string unparse_lrms_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::LRMS_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::ISB_BASE_URI, value );
  if( !res ) throw CannotSetAttribute( JDL::ISB_BASE_URI );
  return;
}

std::string get_input_sandbox_base_uri( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::ISB_BASE_URI, value );
  if( !res ) throw CannotGetAttribute( JDL::ISB_BASE_URI );
  return value;
}

void remove_input_sandbox_base_uri( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::ISB_BASE_URI );
  if( !res ) throw CannotRemoveAttribute( JDL::ISB_BASE_URI );
  return;
}

std::string unparse_input_sandbox_base_uri( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ISB_BASE_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::ISB_BASE_URI );
  unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::ISB_BASE_URI, value );
}

std::string get_input_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::ISB_BASE_URI, value );
  return value;
}

void remove_input_sandbox_base_uri( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::ISB_BASE_URI );
  return;
}

std::string unparse_input_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ISB_BASE_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::WMPISB_BASE_URI, value );
  if( !res ) throw CannotSetAttribute( JDL::WMPISB_BASE_URI );
  return;
}

std::string get_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::WMPISB_BASE_URI, value );
  if( !res ) throw CannotGetAttribute( JDL::WMPISB_BASE_URI );
  return value;
}

void remove_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::WMPISB_BASE_URI );
  if( !res ) throw CannotRemoveAttribute( JDL::WMPISB_BASE_URI );
  return;
}

std::string unparse_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::WMPISB_BASE_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::WMPISB_BASE_URI );
  unparser.Unparse( value, tree );
  return value;
}

void set_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::WMPISB_BASE_URI, value );
}

std::string get_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::WMPISB_BASE_URI, value );
  return value;
}

void remove_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::WMPISB_BASE_URI );
  return;
}

std::string unparse_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::WMPISB_BASE_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox_base_dest_uri( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::OSB_BASE_DEST_URI, value );
  if( !res ) throw CannotSetAttribute( JDL::OSB_BASE_DEST_URI );
  return;
}

std::string get_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::OSB_BASE_DEST_URI, value );
  if( !res ) throw CannotGetAttribute( JDL::OSB_BASE_DEST_URI );
  return value;
}

void remove_output_sandbox_base_dest_uri( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OSB_BASE_DEST_URI );
  if( !res ) throw CannotRemoveAttribute( JDL::OSB_BASE_DEST_URI );
  return;
}

std::string unparse_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OSB_BASE_DEST_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OSB_BASE_DEST_URI );
  unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox_base_dest_uri( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::OSB_BASE_DEST_URI, value );
}

std::string get_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::OSB_BASE_DEST_URI, value );
  return value;
}

void remove_output_sandbox_base_dest_uri( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OSB_BASE_DEST_URI );
  return;
}

std::string unparse_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OSB_BASE_DEST_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_jdl_original( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::JDL_ORIGINAL, value );
  if( !res ) throw CannotSetAttribute( JDL::JDL_ORIGINAL );
  return;
}

std::string get_jdl_original( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::JDL_ORIGINAL, value );
  if( !res ) throw CannotGetAttribute( JDL::JDL_ORIGINAL );
  return value;
}

void remove_jdl_original( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::JDL_ORIGINAL );
  if( !res ) throw CannotRemoveAttribute( JDL::JDL_ORIGINAL );
  return;
}

std::string unparse_jdl_original( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JDL_ORIGINAL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::JDL_ORIGINAL );
  unparser.Unparse( value, tree );
  return value;
}

void set_jdl_original( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::JDL_ORIGINAL, value );
}

std::string get_jdl_original( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::JDL_ORIGINAL, value );
  return value;
}

void remove_jdl_original( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::JDL_ORIGINAL );
  return;
}

std::string unparse_jdl_original( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JDL_ORIGINAL );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_delegation_id( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::DELEGATION_ID, value );
  if( !res ) throw CannotSetAttribute( JDL::DELEGATION_ID );
  return;
}

std::string get_delegation_id( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::DELEGATION_ID, value );
  if( !res ) throw CannotGetAttribute( JDL::DELEGATION_ID );
  return value;
}

void remove_delegation_id( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::DELEGATION_ID );
  if( !res ) throw CannotRemoveAttribute( JDL::DELEGATION_ID );
  return;
}

std::string unparse_delegation_id( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DELEGATION_ID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::DELEGATION_ID );
  unparser.Unparse( value, tree );
  return value;
}

void set_delegation_id( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::DELEGATION_ID, value );
}

std::string get_delegation_id( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::DELEGATION_ID, value );
  return value;
}

void remove_delegation_id( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::DELEGATION_ID );
  return;
}

std::string unparse_delegation_id( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DELEGATION_ID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_state_id( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::CHKPT_STATEID, value );
  if( !res ) throw CannotSetAttribute( JDL::CHKPT_STATEID );
  return;
}

std::string get_state_id( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::CHKPT_STATEID, value );
  if( !res ) throw CannotGetAttribute( JDL::CHKPT_STATEID );
  return value;
}

void remove_state_id( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CHKPT_STATEID );
  if( !res ) throw CannotRemoveAttribute( JDL::CHKPT_STATEID );
  return;
}

std::string unparse_state_id( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_STATEID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CHKPT_STATEID );
  unparser.Unparse( value, tree );
  return value;
}

void set_state_id( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CHKPT_STATEID, value );
}

std::string get_state_id( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::CHKPT_STATEID, value );
  return value;
}

void remove_state_id( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CHKPT_STATEID );
  return;
}

std::string unparse_state_id( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_STATEID );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_user_data( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::CHKPT_DATA, value );
  if( !res ) throw CannotSetAttribute( JDL::CHKPT_DATA );
  return;
}

std::string get_user_data( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::CHKPT_DATA, value );
  if( !res ) throw CannotGetAttribute( JDL::CHKPT_DATA );
  return value;
}

void remove_user_data( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CHKPT_DATA );
  if( !res ) throw CannotRemoveAttribute( JDL::CHKPT_DATA );
  return;
}

std::string unparse_user_data( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_DATA );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CHKPT_DATA );
  unparser.Unparse( value, tree );
  return value;
}

void set_user_data( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::CHKPT_DATA, value );
}

std::string get_user_data( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::CHKPT_DATA, value );
  return value;
}

void remove_user_data( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CHKPT_DATA );
  return;
}

std::string unparse_user_data( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_DATA );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_lbaddress( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::LB_ADDRESS, value );
  if( !res ) throw CannotSetAttribute( JDL::LB_ADDRESS );
  return;
}

std::string get_lbaddress( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::LB_ADDRESS, value );
  if( !res ) throw CannotGetAttribute( JDL::LB_ADDRESS );
  return value;
}

void remove_lbaddress( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::LB_ADDRESS );
  if( !res ) throw CannotRemoveAttribute( JDL::LB_ADDRESS );
  return;
}

std::string unparse_lbaddress( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::LB_ADDRESS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::LB_ADDRESS );
  unparser.Unparse( value, tree );
  return value;
}

void set_lbaddress( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::LB_ADDRESS, value );
}

std::string get_lbaddress( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::LB_ADDRESS, value );
  return value;
}

void remove_lbaddress( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::LB_ADDRESS );
  return;
}

std::string unparse_lbaddress( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::LB_ADDRESS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_virtual_organisation( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::VIRTUAL_ORGANISATION, value );
  if( !res ) throw CannotSetAttribute( JDL::VIRTUAL_ORGANISATION );
  return;
}

std::string get_virtual_organisation( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::VIRTUAL_ORGANISATION, value );
  if( !res ) throw CannotGetAttribute( JDL::VIRTUAL_ORGANISATION );
  return value;
}

void remove_virtual_organisation( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::VIRTUAL_ORGANISATION );
  if( !res ) throw CannotRemoveAttribute( JDL::VIRTUAL_ORGANISATION );
  return;
}

std::string unparse_virtual_organisation( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::VIRTUAL_ORGANISATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::VIRTUAL_ORGANISATION );
  unparser.Unparse( value, tree );
  return value;
}

void set_virtual_organisation( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::VIRTUAL_ORGANISATION, value );
}

std::string get_virtual_organisation( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::VIRTUAL_ORGANISATION, value );
  return value;
}

void remove_virtual_organisation( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::VIRTUAL_ORGANISATION );
  return;
}

std::string unparse_virtual_organisation( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::VIRTUAL_ORGANISATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_dsupload( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::DSUPLOAD, value );
  if( !res ) throw CannotSetAttribute( JDL::DSUPLOAD );
  return;
}

std::string get_dsupload( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::DSUPLOAD, value );
  if( !res ) throw CannotGetAttribute( JDL::DSUPLOAD );
  return value;
}

void remove_dsupload( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::DSUPLOAD );
  if( !res ) throw CannotRemoveAttribute( JDL::DSUPLOAD );
  return;
}

std::string unparse_dsupload( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DSUPLOAD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::DSUPLOAD );
  unparser.Unparse( value, tree );
  return value;
}

void set_dsupload( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::DSUPLOAD, value );
}

std::string get_dsupload( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::DSUPLOAD, value );
  return value;
}

void remove_dsupload( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::DSUPLOAD );
  return;
}

std::string unparse_dsupload( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DSUPLOAD );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output_file( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::OD_OUTPUT_FILE, value );
  if( !res ) throw CannotSetAttribute( JDL::OD_OUTPUT_FILE );
  return;
}

std::string get_output_file( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::OD_OUTPUT_FILE, value );
  if( !res ) throw CannotGetAttribute( JDL::OD_OUTPUT_FILE );
  return value;
}

void remove_output_file( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OD_OUTPUT_FILE );
  if( !res ) throw CannotRemoveAttribute( JDL::OD_OUTPUT_FILE );
  return;
}

std::string unparse_output_file( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OD_OUTPUT_FILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OD_OUTPUT_FILE );
  unparser.Unparse( value, tree );
  return value;
}

void set_output_file( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::OD_OUTPUT_FILE, value );
}

std::string get_output_file( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::OD_OUTPUT_FILE, value );
  return value;
}

void remove_output_file( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OD_OUTPUT_FILE );
  return;
}

std::string unparse_output_file( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OD_OUTPUT_FILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_logical_file_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::OD_LOGICAL_FILENAME, value );
  if( !res ) throw CannotSetAttribute( JDL::OD_LOGICAL_FILENAME );
  return;
}

std::string get_logical_file_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::OD_LOGICAL_FILENAME, value );
  if( !res ) throw CannotGetAttribute( JDL::OD_LOGICAL_FILENAME );
  return value;
}

void remove_logical_file_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OD_LOGICAL_FILENAME );
  if( !res ) throw CannotRemoveAttribute( JDL::OD_LOGICAL_FILENAME );
  return;
}

std::string unparse_logical_file_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OD_LOGICAL_FILENAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OD_LOGICAL_FILENAME );
  unparser.Unparse( value, tree );
  return value;
}

void set_logical_file_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::OD_LOGICAL_FILENAME, value );
}

std::string get_logical_file_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::OD_LOGICAL_FILENAME, value );
  return value;
}

void remove_logical_file_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OD_LOGICAL_FILENAME );
  return;
}

std::string unparse_logical_file_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OD_LOGICAL_FILENAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_storage_element( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::OD_STORAGE_ELEMENT, value );
  if( !res ) throw CannotSetAttribute( JDL::OD_STORAGE_ELEMENT );
  return;
}

std::string get_storage_element( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::OD_STORAGE_ELEMENT, value );
  if( !res ) throw CannotGetAttribute( JDL::OD_STORAGE_ELEMENT );
  return value;
}

void remove_storage_element( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OD_STORAGE_ELEMENT );
  if( !res ) throw CannotRemoveAttribute( JDL::OD_STORAGE_ELEMENT );
  return;
}

std::string unparse_storage_element( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OD_STORAGE_ELEMENT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OD_STORAGE_ELEMENT );
  unparser.Unparse( value, tree );
  return value;
}

void set_storage_element( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::OD_STORAGE_ELEMENT, value );
}

std::string get_storage_element( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::OD_STORAGE_ELEMENT, value );
  return value;
}

void remove_storage_element( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OD_STORAGE_ELEMENT );
  return;
}

std::string unparse_storage_element( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OD_STORAGE_ELEMENT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_hlrlocation( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::HLR_LOCATION, value );
  if( !res ) throw CannotSetAttribute( JDL::HLR_LOCATION );
  return;
}

std::string get_hlrlocation( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::HLR_LOCATION, value );
  if( !res ) throw CannotGetAttribute( JDL::HLR_LOCATION );
  return value;
}

void remove_hlrlocation( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::HLR_LOCATION );
  if( !res ) throw CannotRemoveAttribute( JDL::HLR_LOCATION );
  return;
}

std::string unparse_hlrlocation( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::HLR_LOCATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::HLR_LOCATION );
  unparser.Unparse( value, tree );
  return value;
}

void set_hlrlocation( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::HLR_LOCATION, value );
}

std::string get_hlrlocation( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::HLR_LOCATION, value );
  return value;
}

void remove_hlrlocation( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::HLR_LOCATION );
  return;
}

std::string unparse_hlrlocation( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::HLR_LOCATION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::GLITE_WMS_UI_DAG_NODE_NAME, value );
  if( !res ) throw CannotSetAttribute( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  return;
}

std::string get_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::GLITE_WMS_UI_DAG_NODE_NAME, value );
  if( !res ) throw CannotGetAttribute( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  return value;
}

void remove_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  if( !res ) throw CannotRemoveAttribute( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  return;
}

std::string unparse_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  unparser.Unparse( value, tree );
  return value;
}

void set_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::GLITE_WMS_UI_DAG_NODE_NAME, value );
}

std::string get_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::GLITE_WMS_UI_DAG_NODE_NAME, value );
  return value;
}

void remove_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  return;
}

std::string unparse_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::GLITE_WMS_UI_DAG_NODE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_node_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::NODE_NAME, value );
  if( !res ) throw CannotSetAttribute( JDL::NODE_NAME );
  return;
}

std::string get_node_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::NODE_NAME, value );
  if( !res ) throw CannotGetAttribute( JDL::NODE_NAME );
  return value;
}

void remove_node_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::NODE_NAME );
  if( !res ) throw CannotRemoveAttribute( JDL::NODE_NAME );
  return;
}

std::string unparse_node_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::NODE_NAME );
  unparser.Unparse( value, tree );
  return value;
}

void set_node_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::NODE_NAME, value );
}

std::string get_node_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::NODE_NAME, value );
  return value;
}

void remove_node_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::NODE_NAME );
  return;
}

std::string unparse_node_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODE_NAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_file( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::NODE_FILE, value );
  if( !res ) throw CannotSetAttribute( JDL::NODE_FILE );
  return;
}

std::string get_file( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::NODE_FILE, value );
  if( !res ) throw CannotGetAttribute( JDL::NODE_FILE );
  return value;
}

void remove_file( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::NODE_FILE );
  if( !res ) throw CannotRemoveAttribute( JDL::NODE_FILE );
  return;
}

std::string unparse_file( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODE_FILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::NODE_FILE );
  unparser.Unparse( value, tree );
  return value;
}

void set_file( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::NODE_FILE, value );
}

std::string get_file( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::NODE_FILE, value );
  return value;
}

void remove_file( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::NODE_FILE );
  return;
}

std::string unparse_file( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::NODE_FILE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_listener_host( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::SHHOST, value );
  if( !res ) throw CannotSetAttribute( JDL::SHHOST );
  return;
}

std::string get_listener_host( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::SHHOST, value );
  if( !res ) throw CannotGetAttribute( JDL::SHHOST );
  return value;
}

void remove_listener_host( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SHHOST );
  if( !res ) throw CannotRemoveAttribute( JDL::SHHOST );
  return;
}

std::string unparse_listener_host( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHHOST );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SHHOST );
  unparser.Unparse( value, tree );
  return value;
}

void set_listener_host( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SHHOST, value );
}

std::string get_listener_host( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::SHHOST, value );
  return value;
}

void remove_listener_host( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SHHOST );
  return;
}

std::string unparse_listener_host( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHHOST );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_listener_pipe_name( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::SHPIPEPATH, value );
  if( !res ) throw CannotSetAttribute( JDL::SHPIPEPATH );
  return;
}

std::string get_listener_pipe_name( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::SHPIPEPATH, value );
  if( !res ) throw CannotGetAttribute( JDL::SHPIPEPATH );
  return value;
}

void remove_listener_pipe_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SHPIPEPATH );
  if( !res ) throw CannotRemoveAttribute( JDL::SHPIPEPATH );
  return;
}

std::string unparse_listener_pipe_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHPIPEPATH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SHPIPEPATH );
  unparser.Unparse( value, tree );
  return value;
}

void set_listener_pipe_name( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::SHPIPEPATH, value );
}

std::string get_listener_pipe_name( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::SHPIPEPATH, value );
  return value;
}

void remove_listener_pipe_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SHPIPEPATH );
  return;
}

std::string unparse_listener_pipe_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SHPIPEPATH );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_perusal_files_dest_uri( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::PU_FILES_DEST_URI, value );
  if( !res ) throw CannotSetAttribute( JDL::PU_FILES_DEST_URI );
  return;
}

std::string get_perusal_files_dest_uri( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::PU_FILES_DEST_URI, value );
  if( !res ) throw CannotGetAttribute( JDL::PU_FILES_DEST_URI );
  return value;
}

void remove_perusal_files_dest_uri( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::PU_FILES_DEST_URI );
  if( !res ) throw CannotRemoveAttribute( JDL::PU_FILES_DEST_URI );
  return;
}

std::string unparse_perusal_files_dest_uri( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PU_FILES_DEST_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::PU_FILES_DEST_URI );
  unparser.Unparse( value, tree );
  return value;
}

void set_perusal_files_dest_uri( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::PU_FILES_DEST_URI, value );
}

std::string get_perusal_files_dest_uri( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::PU_FILES_DEST_URI, value );
  return value;
}

void remove_perusal_files_dest_uri( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::PU_FILES_DEST_URI );
  return;
}

std::string unparse_perusal_files_dest_uri( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PU_FILES_DEST_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_job_provenance( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::JOB_PROVENANCE, value );
  if( !res ) throw CannotSetAttribute( JDL::JOB_PROVENANCE );
  return;
}

std::string get_job_provenance( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::JOB_PROVENANCE, value );
  if( !res ) throw CannotGetAttribute( JDL::JOB_PROVENANCE );
  return value;
}

void remove_job_provenance( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::JOB_PROVENANCE );
  if( !res ) throw CannotRemoveAttribute( JDL::JOB_PROVENANCE );
  return;
}

std::string unparse_job_provenance( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOB_PROVENANCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::JOB_PROVENANCE );
  unparser.Unparse( value, tree );
  return value;
}

void set_job_provenance( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::JOB_PROVENANCE, value );
}

std::string get_job_provenance( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::JOB_PROVENANCE, value );
  return value;
}

void remove_job_provenance( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::JOB_PROVENANCE );
  return;
}

std::string unparse_job_provenance( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::JOB_PROVENANCE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_mw_version( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::MW_VERSION, value );
  if( !res ) throw CannotSetAttribute( JDL::MW_VERSION );
  return;
}

std::string get_mw_version( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::MW_VERSION, value );
  if( !res ) throw CannotGetAttribute( JDL::MW_VERSION );
  return value;
}

void remove_mw_version( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::MW_VERSION );
  if( !res ) throw CannotRemoveAttribute( JDL::MW_VERSION );
  return;
}

std::string unparse_mw_version( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MW_VERSION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::MW_VERSION );
  unparser.Unparse( value, tree );
  return value;
}

void set_mw_version( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::MW_VERSION, value );
}

std::string get_mw_version( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::MW_VERSION, value );
  return value;
}

void remove_mw_version( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::MW_VERSION );
  return;
}

std::string unparse_mw_version( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::MW_VERSION );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output_data( classad::ClassAd &job_ad, const classad::ExprTree *value )
{
  bool res = job_ad.Insert( JDL::OUTPUTDATA, value->Copy() );
  if( !res ) throw CannotSetAttribute( JDL::OUTPUTDATA );
  return;
}

classad::ExprTree *get_output_data( const classad::ClassAd &job_ad )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::OUTPUTDATA );
  if( !et ) 
  {
    throw CannotGetAttribute( JDL::OUTPUTDATA );
  }
  return et->Copy();
}

void remove_output_data( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OUTPUTDATA );
  if( !res ) throw CannotRemoveAttribute( JDL::OUTPUTDATA );
  return;
}

std::string unparse_output_data( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OUTPUTDATA );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OUTPUTDATA );
  unparser.Unparse( value, tree );
  return value;
}

void set_output_data( classad::ClassAd &job_ad, const classad::ExprTree *value, bool &good )
{
  good = job_ad.Insert( JDL::OUTPUTDATA, value->Copy() );
  return;
}

classad::ExprTree *get_output_data( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::OUTPUTDATA );
  good = et;
  return good ? et->Copy() : 0;
}

void remove_output_data( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OUTPUTDATA );
  return;
}

std::string unparse_output_data( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OUTPUTDATA );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_user_tags( classad::ClassAd &job_ad, const classad::ExprTree *value )
{
  bool res = job_ad.Insert( JDL::USERTAGS, value->Copy() );
  if( !res ) throw CannotSetAttribute( JDL::USERTAGS );
  return;
}

classad::ExprTree *get_user_tags( const classad::ClassAd &job_ad )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::USERTAGS );
  if( !et ) 
  {
    throw CannotGetAttribute( JDL::USERTAGS );
  }
  return et->Copy();
}

void remove_user_tags( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::USERTAGS );
  if( !res ) throw CannotRemoveAttribute( JDL::USERTAGS );
  return;
}

std::string unparse_user_tags( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::USERTAGS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::USERTAGS );
  unparser.Unparse( value, tree );
  return value;
}

void set_user_tags( classad::ClassAd &job_ad, const classad::ExprTree *value, bool &good )
{
  good = job_ad.Insert( JDL::USERTAGS, value->Copy() );
  return;
}

classad::ExprTree *get_user_tags( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::USERTAGS );
  good = et;
  return good ? et->Copy() : 0;
}

void remove_user_tags( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::USERTAGS );
  return;
}

std::string unparse_user_tags( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::USERTAGS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_data_requirements( classad::ClassAd &job_ad, const classad::ExprTree *value )
{
  bool res = job_ad.Insert( JDL::DATA_REQUIREMENTS, value->Copy() );
  if( !res ) throw CannotSetAttribute( JDL::DATA_REQUIREMENTS );
  return;
}

classad::ExprTree *get_data_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::DATA_REQUIREMENTS );
  if( !et ) 
  {
    throw CannotGetAttribute( JDL::DATA_REQUIREMENTS );
  }
  return et->Copy();
}

void remove_data_requirements( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::DATA_REQUIREMENTS );
  if( !res ) throw CannotRemoveAttribute( JDL::DATA_REQUIREMENTS );
  return;
}

std::string unparse_data_requirements( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::DATA_REQUIREMENTS );
  unparser.Unparse( value, tree );
  return value;
}

void set_data_requirements( classad::ClassAd &job_ad, const classad::ExprTree *value, bool &good )
{
  good = job_ad.Insert( JDL::DATA_REQUIREMENTS, value->Copy() );
  return;
}

classad::ExprTree *get_data_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::DATA_REQUIREMENTS );
  good = et;
  return good ? et->Copy() : 0;
}

void remove_data_requirements( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::DATA_REQUIREMENTS );
  return;
}

std::string unparse_data_requirements( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_REQUIREMENTS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_data_catalog_type( classad::ClassAd &job_ad, const std::string &value )
{
  bool res = job_ad.InsertAttr( JDL::DATA_CATALOG_TYPE, value );
  if( !res ) throw CannotSetAttribute( JDL::DATA_CATALOG_TYPE );
  return;
}

std::string get_data_catalog_type( const classad::ClassAd &job_ad )
{
  bool res;
  std::string value;
  res = job_ad.EvaluateAttrString( JDL::DATA_CATALOG_TYPE, value );
  if( !res ) throw CannotGetAttribute( JDL::DATA_CATALOG_TYPE );
  return value;
}

void remove_data_catalog_type( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::DATA_CATALOG_TYPE );
  if( !res ) throw CannotRemoveAttribute( JDL::DATA_CATALOG_TYPE );
  return;
}

std::string unparse_data_catalog_type( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_CATALOG_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::DATA_CATALOG_TYPE );
  unparser.Unparse( value, tree );
  return value;
}

void set_data_catalog_type( classad::ClassAd &job_ad, const std::string &value, bool &good )
{
  good = job_ad.InsertAttr( JDL::DATA_CATALOG_TYPE, value );
}

std::string get_data_catalog_type( const classad::ClassAd &job_ad, bool &good )
{
  std::string value;
  good = job_ad.EvaluateAttrString( JDL::DATA_CATALOG_TYPE, value );
  return value;
}

void remove_data_catalog_type( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::DATA_CATALOG_TYPE );
  return;
}

std::string unparse_data_catalog_type( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_CATALOG_TYPE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::OUTPUTSB, l );
  if( !res ) throw CannotSetAttribute( JDL::OUTPUTSB );
  return;
}

void get_output_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::OUTPUTSB, l );
  if( !res ) throw CannotGetAttribute( JDL::OUTPUTSB );
  return;
}

void remove_output_sandbox( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OUTPUTSB );
  if( !res ) throw CannotRemoveAttribute( JDL::OUTPUTSB );
  return;
}

std::string unparse_output_sandbox( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OUTPUTSB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OUTPUTSB );
  unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::OUTPUTSB, l );
  return;
}

void get_output_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::OUTPUTSB, l );
  return;
}

void remove_output_sandbox( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OUTPUTSB );
  return;
}

std::string unparse_output_sandbox( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OUTPUTSB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox_dest_uri( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::OSB_DEST_URI, l );
  if( !res ) throw CannotSetAttribute( JDL::OSB_DEST_URI );
  return;
}

void get_output_sandbox_dest_uri( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::OSB_DEST_URI, l );
  if( !res ) throw CannotGetAttribute( JDL::OSB_DEST_URI );
  return;
}

void remove_output_sandbox_dest_uri( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::OSB_DEST_URI );
  if( !res ) throw CannotRemoveAttribute( JDL::OSB_DEST_URI );
  return;
}

std::string unparse_output_sandbox_dest_uri( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OSB_DEST_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::OSB_DEST_URI );
  unparser.Unparse( value, tree );
  return value;
}

void set_output_sandbox_dest_uri( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::OSB_DEST_URI, l );
  return;
}

void get_output_sandbox_dest_uri( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::OSB_DEST_URI, l );
  return;
}

void remove_output_sandbox_dest_uri( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::OSB_DEST_URI );
  return;
}

std::string unparse_output_sandbox_dest_uri( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::OSB_DEST_URI );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox_dest_file_name( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::ISB_DEST_FILENAME, l );
  if( !res ) throw CannotSetAttribute( JDL::ISB_DEST_FILENAME );
  return;
}

void get_input_sandbox_dest_file_name( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::ISB_DEST_FILENAME, l );
  if( !res ) throw CannotGetAttribute( JDL::ISB_DEST_FILENAME );
  return;
}

void remove_input_sandbox_dest_file_name( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::ISB_DEST_FILENAME );
  if( !res ) throw CannotRemoveAttribute( JDL::ISB_DEST_FILENAME );
  return;
}

std::string unparse_input_sandbox_dest_file_name( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ISB_DEST_FILENAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::ISB_DEST_FILENAME );
  unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox_dest_file_name( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::ISB_DEST_FILENAME, l );
  return;
}

void get_input_sandbox_dest_file_name( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::ISB_DEST_FILENAME, l );
  return;
}

void remove_input_sandbox_dest_file_name( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::ISB_DEST_FILENAME );
  return;
}

std::string unparse_input_sandbox_dest_file_name( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ISB_DEST_FILENAME );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::INPUTSB, l );
  if( !res ) throw CannotSetAttribute( JDL::INPUTSB );
  return;
}

void get_input_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::INPUTSB, l );
  if( !res ) throw CannotGetAttribute( JDL::INPUTSB );
  return;
}

void remove_input_sandbox( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::INPUTSB );
  if( !res ) throw CannotRemoveAttribute( JDL::INPUTSB );
  return;
}

std::string unparse_input_sandbox( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::INPUTSB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::INPUTSB );
  unparser.Unparse( value, tree );
  return value;
}

void set_input_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::INPUTSB, l );
  return;
}

void get_input_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::INPUTSB, l );
  return;
}

void remove_input_sandbox( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::INPUTSB );
  return;
}

std::string unparse_input_sandbox( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::INPUTSB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_environment( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::ENVIRONMENT, l );
  if( !res ) throw CannotSetAttribute( JDL::ENVIRONMENT );
  return;
}

void get_environment( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::ENVIRONMENT, l );
  if( !res ) throw CannotGetAttribute( JDL::ENVIRONMENT );
  return;
}

void remove_environment( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::ENVIRONMENT );
  if( !res ) throw CannotRemoveAttribute( JDL::ENVIRONMENT );
  return;
}

std::string unparse_environment( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ENVIRONMENT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::ENVIRONMENT );
  unparser.Unparse( value, tree );
  return value;
}

void set_environment( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::ENVIRONMENT, l );
  return;
}

void get_environment( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::ENVIRONMENT, l );
  return;
}

void remove_environment( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::ENVIRONMENT );
  return;
}

std::string unparse_environment( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::ENVIRONMENT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_input_data( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::INPUTDATA, l );
  if( !res ) throw CannotSetAttribute( JDL::INPUTDATA );
  return;
}

void get_input_data( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::INPUTDATA, l );
  if( !res ) throw CannotGetAttribute( JDL::INPUTDATA );
  return;
}

void remove_input_data( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::INPUTDATA );
  if( !res ) throw CannotRemoveAttribute( JDL::INPUTDATA );
  return;
}

std::string unparse_input_data( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::INPUTDATA );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::INPUTDATA );
  unparser.Unparse( value, tree );
  return value;
}

void set_input_data( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::INPUTDATA, l );
  return;
}

void get_input_data( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::INPUTDATA, l );
  return;
}

void remove_input_data( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::INPUTDATA );
  return;
}

std::string unparse_input_data( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::INPUTDATA );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_data_access_protocol( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::DATA_ACCESS, l );
  if( !res ) throw CannotSetAttribute( JDL::DATA_ACCESS );
  return;
}

void get_data_access_protocol( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::DATA_ACCESS, l );
  if( !res ) throw CannotGetAttribute( JDL::DATA_ACCESS );
  return;
}

void remove_data_access_protocol( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::DATA_ACCESS );
  if( !res ) throw CannotRemoveAttribute( JDL::DATA_ACCESS );
  return;
}

std::string unparse_data_access_protocol( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_ACCESS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::DATA_ACCESS );
  unparser.Unparse( value, tree );
  return value;
}

void set_data_access_protocol( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::DATA_ACCESS, l );
  return;
}

void get_data_access_protocol( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::DATA_ACCESS, l );
  return;
}

void remove_data_access_protocol( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::DATA_ACCESS );
  return;
}

std::string unparse_data_access_protocol( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_ACCESS );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_data_catalog( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::DATA_CATALOG, l );
  if( !res ) throw CannotSetAttribute( JDL::DATA_CATALOG );
  return;
}

void get_data_catalog( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::DATA_CATALOG, l );
  if( !res ) throw CannotGetAttribute( JDL::DATA_CATALOG );
  return;
}

void remove_data_catalog( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::DATA_CATALOG );
  if( !res ) throw CannotRemoveAttribute( JDL::DATA_CATALOG );
  return;
}

std::string unparse_data_catalog( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_CATALOG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::DATA_CATALOG );
  unparser.Unparse( value, tree );
  return value;
}

void set_data_catalog( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::DATA_CATALOG, l );
  return;
}

void get_data_catalog( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::DATA_CATALOG, l );
  return;
}

void remove_data_catalog( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::DATA_CATALOG );
  return;
}

std::string unparse_data_catalog( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::DATA_CATALOG );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_storage_index( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::STORAGE_INDEX, l );
  if( !res ) throw CannotSetAttribute( JDL::STORAGE_INDEX );
  return;
}

void get_storage_index( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::STORAGE_INDEX, l );
  if( !res ) throw CannotGetAttribute( JDL::STORAGE_INDEX );
  return;
}

void remove_storage_index( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::STORAGE_INDEX );
  if( !res ) throw CannotRemoveAttribute( JDL::STORAGE_INDEX );
  return;
}

std::string unparse_storage_index( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STORAGE_INDEX );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::STORAGE_INDEX );
  unparser.Unparse( value, tree );
  return value;
}

void set_storage_index( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::STORAGE_INDEX, l );
  return;
}

void get_storage_index( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::STORAGE_INDEX, l );
  return;
}

void remove_storage_index( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::STORAGE_INDEX );
  return;
}

std::string unparse_storage_index( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STORAGE_INDEX );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_significant_attributes( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::SIGNIFICANT_ATTRIBUTES, l );
  if( !res ) throw CannotSetAttribute( JDL::SIGNIFICANT_ATTRIBUTES );
  return;
}

void get_significant_attributes( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::SIGNIFICANT_ATTRIBUTES, l );
  if( !res ) throw CannotGetAttribute( JDL::SIGNIFICANT_ATTRIBUTES );
  return;
}

void remove_significant_attributes( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::SIGNIFICANT_ATTRIBUTES );
  if( !res ) throw CannotRemoveAttribute( JDL::SIGNIFICANT_ATTRIBUTES );
  return;
}

std::string unparse_significant_attributes( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SIGNIFICANT_ATTRIBUTES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::SIGNIFICANT_ATTRIBUTES );
  unparser.Unparse( value, tree );
  return value;
}

void set_significant_attributes( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::SIGNIFICANT_ATTRIBUTES, l );
  return;
}

void get_significant_attributes( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::SIGNIFICANT_ATTRIBUTES, l );
  return;
}

void remove_significant_attributes( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::SIGNIFICANT_ATTRIBUTES );
  return;
}

std::string unparse_significant_attributes( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::SIGNIFICANT_ATTRIBUTES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_step_weight( classad::ClassAd &job_ad, const std::vector<int> &l )
{
  bool res = InsertAttrList( job_ad, JDL::STEPWEIGHT, l );
  if( !res ) throw CannotSetAttribute( JDL::STEPWEIGHT );
  return;
}

void get_step_weight( const classad::ClassAd &job_ad, std::vector<int> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::STEPWEIGHT, l );
  if( !res ) throw CannotGetAttribute( JDL::STEPWEIGHT );
  return;
}

void remove_step_weight( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::STEPWEIGHT );
  if( !res ) throw CannotRemoveAttribute( JDL::STEPWEIGHT );
  return;
}

std::string unparse_step_weight( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STEPWEIGHT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::STEPWEIGHT );
  unparser.Unparse( value, tree );
  return value;
}

void set_step_weight( classad::ClassAd &job_ad, const std::vector<int> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::STEPWEIGHT, l );
  return;
}

void get_step_weight( const classad::ClassAd &job_ad, std::vector<int> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::STEPWEIGHT, l );
  return;
}

void remove_step_weight( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::STEPWEIGHT );
  return;
}

std::string unparse_step_weight( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::STEPWEIGHT );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_prejob( classad::ClassAd &job_ad, const classad::ClassAd *value )
{
  bool res = job_ad.Insert( JDL::PREJOB, value->Copy() );
  if( !res ) throw CannotSetAttribute( JDL::PREJOB );
  return;
}

classad::ClassAd *get_prejob( const classad::ClassAd &job_ad )
{
  using classad::ExprTree;
  using classad::ClassAd;
  ExprTree *et = job_ad.Lookup( JDL::PREJOB );
  if( !( et and utilities::is_classad( et ) ) ) 
  {
    throw CannotGetAttribute( JDL::PREJOB );
  }
  return static_cast<ClassAd *>( et->Copy() );
}

void remove_prejob( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::PREJOB );
  if( !res ) throw CannotRemoveAttribute( JDL::PREJOB );
  return;
}

std::string unparse_prejob( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PREJOB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::PREJOB );
  unparser.Unparse( value, tree );
  return value;
}

void set_prejob( classad::ClassAd &job_ad, const classad::ClassAd *value, bool &good )
{
  good = job_ad.Insert( JDL::PREJOB, value->Copy() );
  return;
}

classad::ClassAd *get_prejob( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::PREJOB );
  good = et and utilities::is_classad( et );
  return good ? static_cast<classad::ClassAd *>( et->Copy() ) : 0;
}

void remove_prejob( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::PREJOB );
  return;
}

std::string unparse_prejob( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::PREJOB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_postjob( classad::ClassAd &job_ad, const classad::ClassAd *value )
{
  bool res = job_ad.Insert( JDL::POSTJOB, value->Copy() );
  if( !res ) throw CannotSetAttribute( JDL::POSTJOB );
  return;
}

classad::ClassAd *get_postjob( const classad::ClassAd &job_ad )
{
  using classad::ExprTree;
  using classad::ClassAd;
  ExprTree *et = job_ad.Lookup( JDL::POSTJOB );
  if( !( et and utilities::is_classad( et ) ) ) 
  {
    throw CannotGetAttribute( JDL::POSTJOB );
  }
  return static_cast<ClassAd *>( et->Copy() );
}

void remove_postjob( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::POSTJOB );
  if( !res ) throw CannotRemoveAttribute( JDL::POSTJOB );
  return;
}

std::string unparse_postjob( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::POSTJOB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::POSTJOB );
  unparser.Unparse( value, tree );
  return value;
}

void set_postjob( classad::ClassAd &job_ad, const classad::ClassAd *value, bool &good )
{
  good = job_ad.Insert( JDL::POSTJOB, value->Copy() );
  return;
}

classad::ClassAd *get_postjob( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::POSTJOB );
  good = et and utilities::is_classad( et );
  return good ? static_cast<classad::ClassAd *>( et->Copy() ) : 0;
}

void remove_postjob( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::POSTJOB );
  return;
}

std::string unparse_postjob( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::POSTJOB );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_job_state( classad::ClassAd &job_ad, const classad::ClassAd *value )
{
  bool res = job_ad.Insert( JDL::CHKPT_JOBSTATE, value->Copy() );
  if( !res ) throw CannotSetAttribute( JDL::CHKPT_JOBSTATE );
  return;
}

classad::ClassAd *get_job_state( const classad::ClassAd &job_ad )
{
  using classad::ExprTree;
  using classad::ClassAd;
  ExprTree *et = job_ad.Lookup( JDL::CHKPT_JOBSTATE );
  if( !( et and utilities::is_classad( et ) ) ) 
  {
    throw CannotGetAttribute( JDL::CHKPT_JOBSTATE );
  }
  return static_cast<ClassAd *>( et->Copy() );
}

void remove_job_state( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CHKPT_JOBSTATE );
  if( !res ) throw CannotRemoveAttribute( JDL::CHKPT_JOBSTATE );
  return;
}

std::string unparse_job_state( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_JOBSTATE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CHKPT_JOBSTATE );
  unparser.Unparse( value, tree );
  return value;
}

void set_job_state( classad::ClassAd &job_ad, const classad::ClassAd *value, bool &good )
{
  good = job_ad.Insert( JDL::CHKPT_JOBSTATE, value->Copy() );
  return;
}

classad::ClassAd *get_job_state( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *et = job_ad.Lookup( JDL::CHKPT_JOBSTATE );
  good = et and utilities::is_classad( et );
  return good ? static_cast<classad::ClassAd *>( et->Copy() ) : 0;
}

void remove_job_state( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CHKPT_JOBSTATE );
  return;
}

std::string unparse_job_state( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CHKPT_JOBSTATE );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}

void set_ces( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::CES, l );
  if( !res ) throw CannotSetAttribute( JDL::CES );
  return;
}

void get_ces( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::CES, l );
  if( !res ) throw CannotGetAttribute( JDL::CES );
  return;
}

void remove_ces( classad::ClassAd &job_ad )
{
  bool res = job_ad.Delete( JDL::CES );
  if( !res ) throw CannotRemoveAttribute( JDL::CES );
  return;
}

std::string unparse_ces( const classad::ClassAd &job_ad )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) throw CannotGetAttribute( JDL::CES );
  unparser.Unparse( value, tree );
  return value;
}

void set_ces( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::CES, l );
  return;
}

void get_ces( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::CES, l );
  return;
}

void remove_ces( classad::ClassAd &job_ad, bool &good )
{
  good = job_ad.Delete( JDL::CES );
  return;
}

std::string unparse_ces( const classad::ClassAd &job_ad, bool &good )
{
  classad::ExprTree *tree = job_ad.Lookup( JDL::CES );
  classad::ClassAdUnParser unparser;
  std::string value;
  if( !tree ) good = false;
  else unparser.Unparse( value, tree );
  return value;
}



void set_job_steps( classad::ClassAd &job_ad, const std::vector<std::string> &l )
{
  bool res = InsertAttrList( job_ad, JDL::CHKPT_STEPS, l );
  if( !res ) throw CannotSetAttribute( JDL::CHKPT_STEPS );
  return;
}

void get_job_steps( const classad::ClassAd &job_ad, std::vector<std::string> &l )
{
  bool res = EvaluateAttrListOrSingle( job_ad, JDL::CHKPT_STEPS, l );
  if( !res ) throw CannotGetAttribute( JDL::CHKPT_STEPS );
  return;
}

void set_job_steps( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good )
{
  good = InsertAttrList( job_ad, JDL::CHKPT_STEPS, l );
  return;
}

void get_job_steps( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good )
{
  good = EvaluateAttrListOrSingle( job_ad, JDL::CHKPT_STEPS, l );
  return;
}


} // namespace jdl
} // namespace glite

// Local Variables:
// mode: c++
// End:
