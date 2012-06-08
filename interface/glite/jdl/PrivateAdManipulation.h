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

#ifndef GLITE_WMS_COMMON_REQUESTAD_PRIVATEADMANIPULATION_H
#define GLITE_WMS_COMMON_REQUESTAD_PRIVATEADMANIPULATION_H

#ifndef GLITE_WMS_X_STRING
#define GLITE_WMS_X_STRING
#include <string>
#endif

#ifndef GLITE_WMS_X_VECTOR
#define GLITE_WMS_X_VECTOR
#include <vector>
#endif

namespace classad {
class ClassAd;
}

namespace glite {
namespace jdl {


void set_transfer_executable( classad::ClassAd &job_ad, const bool &value );

bool get_transfer_executable( const classad::ClassAd &job_ad );

void remove_transfer_executable( classad::ClassAd &job_ad );

std::string unparse_transfer_executable( const classad::ClassAd &job_ad );

void set_transfer_executable( classad::ClassAd &job_ad, bool value, bool &good );

bool get_transfer_executable( const classad::ClassAd &job_ad, bool &good );

void remove_transfer_executable( classad::ClassAd &job_ad, bool &good );

std::string unparse_transfer_executable( const classad::ClassAd &job_ad, bool &good );

void set_copy_to_spool( classad::ClassAd &job_ad, const bool &value );

bool get_copy_to_spool( const classad::ClassAd &job_ad );

void remove_copy_to_spool( classad::ClassAd &job_ad );

std::string unparse_copy_to_spool( const classad::ClassAd &job_ad );

void set_copy_to_spool( classad::ClassAd &job_ad, bool value, bool &good );

bool get_copy_to_spool( const classad::ClassAd &job_ad, bool &good );

void remove_copy_to_spool( classad::ClassAd &job_ad, bool &good );

std::string unparse_copy_to_spool( const classad::ClassAd &job_ad, bool &good );

void set_stream_output( classad::ClassAd &job_ad, const bool &value );

bool get_stream_output( const classad::ClassAd &job_ad );

void remove_stream_output( classad::ClassAd &job_ad );

std::string unparse_stream_output( const classad::ClassAd &job_ad );

void set_stream_output( classad::ClassAd &job_ad, bool value, bool &good );

bool get_stream_output( const classad::ClassAd &job_ad, bool &good );

void remove_stream_output( classad::ClassAd &job_ad, bool &good );

std::string unparse_stream_output( const classad::ClassAd &job_ad, bool &good );

void set_stream_error( classad::ClassAd &job_ad, const bool &value );

bool get_stream_error( const classad::ClassAd &job_ad );

void remove_stream_error( classad::ClassAd &job_ad );

std::string unparse_stream_error( const classad::ClassAd &job_ad );

void set_stream_error( classad::ClassAd &job_ad, bool value, bool &good );

bool get_stream_error( const classad::ClassAd &job_ad, bool &good );

void remove_stream_error( classad::ClassAd &job_ad, bool &good );

std::string unparse_stream_error( const classad::ClassAd &job_ad, bool &good );

void set_notification( classad::ClassAd &job_ad, const std::string &value );

std::string get_notification( const classad::ClassAd &job_ad );

void remove_notification( classad::ClassAd &job_ad );

std::string unparse_notification( const classad::ClassAd &job_ad );

void set_notification( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_notification( const classad::ClassAd &job_ad, bool &good );

void remove_notification( classad::ClassAd &job_ad, bool &good );

std::string unparse_notification( const classad::ClassAd &job_ad, bool &good );

void set_log( classad::ClassAd &job_ad, const std::string &value );

std::string get_log( const classad::ClassAd &job_ad );

void remove_log( classad::ClassAd &job_ad );

std::string unparse_log( const classad::ClassAd &job_ad );

void set_log( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_log( const classad::ClassAd &job_ad, bool &good );

void remove_log( classad::ClassAd &job_ad, bool &good );

std::string unparse_log( const classad::ClassAd &job_ad, bool &good );

void set_output( classad::ClassAd &job_ad, const std::string &value );

std::string get_output( const classad::ClassAd &job_ad );

void remove_output( classad::ClassAd &job_ad );

std::string unparse_output( const classad::ClassAd &job_ad );

void set_output( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_output( const classad::ClassAd &job_ad, bool &good );

void remove_output( classad::ClassAd &job_ad, bool &good );

std::string unparse_output( const classad::ClassAd &job_ad, bool &good );

void set_error( classad::ClassAd &job_ad, const std::string &value );

std::string get_error( const classad::ClassAd &job_ad );

void remove_error( classad::ClassAd &job_ad );

std::string unparse_error( const classad::ClassAd &job_ad );

void set_error( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_error( const classad::ClassAd &job_ad, bool &good );

void remove_error( classad::ClassAd &job_ad, bool &good );

std::string unparse_error( const classad::ClassAd &job_ad, bool &good );

void set_error_( classad::ClassAd &job_ad, const std::string &value );

std::string get_error_( const classad::ClassAd &job_ad );

void remove_error_( classad::ClassAd &job_ad );

std::string unparse_error_( const classad::ClassAd &job_ad );

void set_error_( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_error_( const classad::ClassAd &job_ad, bool &good );

void remove_error_( classad::ClassAd &job_ad, bool &good );

std::string unparse_error_( const classad::ClassAd &job_ad, bool &good );

void set_x509_user_proxy( classad::ClassAd &job_ad, const std::string &value );

std::string get_x509_user_proxy( const classad::ClassAd &job_ad );

void remove_x509_user_proxy( classad::ClassAd &job_ad );

std::string unparse_x509_user_proxy( const classad::ClassAd &job_ad );

void set_x509_user_proxy( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_x509_user_proxy( const classad::ClassAd &job_ad, bool &good );

void remove_x509_user_proxy( classad::ClassAd &job_ad, bool &good );

std::string unparse_x509_user_proxy( const classad::ClassAd &job_ad, bool &good );

void set_submit_event_notes( classad::ClassAd &job_ad, const std::string &value );

std::string get_submit_event_notes( const classad::ClassAd &job_ad );

void remove_submit_event_notes( classad::ClassAd &job_ad );

std::string unparse_submit_event_notes( const classad::ClassAd &job_ad );

void set_submit_event_notes( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_submit_event_notes( const classad::ClassAd &job_ad, bool &good );

void remove_submit_event_notes( classad::ClassAd &job_ad, bool &good );

std::string unparse_submit_event_notes( const classad::ClassAd &job_ad, bool &good );

void set_submit_event_user_notes( classad::ClassAd &job_ad, const std::string &value );

std::string get_submit_event_user_notes( const classad::ClassAd &job_ad );

void remove_submit_event_user_notes( classad::ClassAd &job_ad );

std::string unparse_submit_event_user_notes( const classad::ClassAd &job_ad );

void set_submit_event_user_notes( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_submit_event_user_notes( const classad::ClassAd &job_ad, bool &good );

void remove_submit_event_user_notes( classad::ClassAd &job_ad, bool &good );

std::string unparse_submit_event_user_notes( const classad::ClassAd &job_ad, bool &good );

void set_input_sandbox_path( classad::ClassAd &job_ad, const std::string &value );

std::string get_input_sandbox_path( const classad::ClassAd &job_ad );

void remove_input_sandbox_path( classad::ClassAd &job_ad );

std::string unparse_input_sandbox_path( const classad::ClassAd &job_ad );

void set_input_sandbox_path( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_input_sandbox_path( const classad::ClassAd &job_ad, bool &good );

void remove_input_sandbox_path( classad::ClassAd &job_ad, bool &good );

std::string unparse_input_sandbox_path( const classad::ClassAd &job_ad, bool &good );

void set_output_sandbox_path( classad::ClassAd &job_ad, const std::string &value );

std::string get_output_sandbox_path( const classad::ClassAd &job_ad );

void remove_output_sandbox_path( classad::ClassAd &job_ad );

std::string unparse_output_sandbox_path( const classad::ClassAd &job_ad );

void set_output_sandbox_path( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_output_sandbox_path( const classad::ClassAd &job_ad, bool &good );

void remove_output_sandbox_path( classad::ClassAd &job_ad, bool &good );

std::string unparse_output_sandbox_path( const classad::ClassAd &job_ad, bool &good );

void set_globus_scheduler( classad::ClassAd &job_ad, const std::string &value );

std::string get_globus_scheduler( const classad::ClassAd &job_ad );

void remove_globus_scheduler( classad::ClassAd &job_ad );

std::string unparse_globus_scheduler( const classad::ClassAd &job_ad );

void set_globus_scheduler( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_globus_scheduler( const classad::ClassAd &job_ad, bool &good );

void remove_globus_scheduler( classad::ClassAd &job_ad, bool &good );

std::string unparse_globus_scheduler( const classad::ClassAd &job_ad, bool &good );

void set_grid_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_grid_type( const classad::ClassAd &job_ad );

void remove_grid_type( classad::ClassAd &job_ad );

std::string unparse_grid_type( const classad::ClassAd &job_ad );

void set_grid_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_grid_type( const classad::ClassAd &job_ad, bool &good );

void remove_grid_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_grid_type( const classad::ClassAd &job_ad, bool &good );

void set_remote_job_universe( classad::ClassAd &job_ad, const int &value );

int get_remote_job_universe( const classad::ClassAd &job_ad );

void remove_remote_job_universe( classad::ClassAd &job_ad );

std::string unparse_remote_job_universe( const classad::ClassAd &job_ad );

void set_remote_job_universe( classad::ClassAd &job_ad, int value, bool &good );

int get_remote_job_universe( const classad::ClassAd &job_ad, bool &good );

void remove_remote_job_universe( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_job_universe( const classad::ClassAd &job_ad, bool &good );

void set_remote_sub_universe( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_sub_universe( const classad::ClassAd &job_ad );

void remove_remote_sub_universe( classad::ClassAd &job_ad );

std::string unparse_remote_sub_universe( const classad::ClassAd &job_ad );

void set_remote_sub_universe( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_sub_universe( const classad::ClassAd &job_ad, bool &good );

void remove_remote_sub_universe( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_sub_universe( const classad::ClassAd &job_ad, bool &good );

void set_remote_job_grid_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_job_grid_type( const classad::ClassAd &job_ad );

void remove_remote_job_grid_type( classad::ClassAd &job_ad );

std::string unparse_remote_job_grid_type( const classad::ClassAd &job_ad );

void set_remote_job_grid_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_job_grid_type( const classad::ClassAd &job_ad, bool &good );

void remove_remote_job_grid_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_job_grid_type( const classad::ClassAd &job_ad, bool &good );

void set_daemon_unique_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_daemon_unique_name( const classad::ClassAd &job_ad );

void remove_daemon_unique_name( classad::ClassAd &job_ad );

std::string unparse_daemon_unique_name( const classad::ClassAd &job_ad );

void set_daemon_unique_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_daemon_unique_name( const classad::ClassAd &job_ad, bool &good );

void remove_daemon_unique_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_daemon_unique_name( const classad::ClassAd &job_ad, bool &good );

void set_condor_requirements( classad::ClassAd &job_ad, const std::string &value );

std::string get_condor_requirements( const classad::ClassAd &job_ad );

void remove_condor_requirements( classad::ClassAd &job_ad );

std::string unparse_condor_requirements( const classad::ClassAd &job_ad );

void set_condor_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_condor_requirements( const classad::ClassAd &job_ad, bool &good );

void remove_condor_requirements( classad::ClassAd &job_ad, bool &good );

std::string unparse_condor_requirements( const classad::ClassAd &job_ad, bool &good );

void set_remote_requirements( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_requirements( const classad::ClassAd &job_ad );

void remove_remote_requirements( classad::ClassAd &job_ad );

std::string unparse_remote_requirements( const classad::ClassAd &job_ad );

void set_remote_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_requirements( const classad::ClassAd &job_ad, bool &good );

void remove_remote_requirements( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_requirements( const classad::ClassAd &job_ad, bool &good );

void set_remote_env( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_env( const classad::ClassAd &job_ad );

void remove_remote_env( classad::ClassAd &job_ad );

std::string unparse_remote_env( const classad::ClassAd &job_ad );

void set_remote_env( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_env( const classad::ClassAd &job_ad, bool &good );

void remove_remote_env( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_env( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_queue( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_queue( const classad::ClassAd &job_ad );

void remove_remote_remote_queue( classad::ClassAd &job_ad );

std::string unparse_remote_remote_queue( const classad::ClassAd &job_ad );

void set_remote_remote_queue( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_queue( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_queue( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_queue( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_grid_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_grid_type( const classad::ClassAd &job_ad );

void remove_remote_remote_grid_type( classad::ClassAd &job_ad );

std::string unparse_remote_remote_grid_type( const classad::ClassAd &job_ad );

void set_remote_remote_grid_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_grid_type( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_grid_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_grid_type( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_job_universe( classad::ClassAd &job_ad, const int &value );

int get_remote_remote_job_universe( const classad::ClassAd &job_ad );

void remove_remote_remote_job_universe( classad::ClassAd &job_ad );

std::string unparse_remote_remote_job_universe( const classad::ClassAd &job_ad );

void set_remote_remote_job_universe( classad::ClassAd &job_ad, int value, bool &good );

int get_remote_remote_job_universe( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_job_universe( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_job_universe( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_requirements( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_requirements( const classad::ClassAd &job_ad );

void remove_remote_remote_requirements( classad::ClassAd &job_ad );

std::string unparse_remote_remote_requirements( const classad::ClassAd &job_ad );

void set_remote_remote_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_requirements( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_requirements( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_requirements( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_file_system_domain( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_file_system_domain( const classad::ClassAd &job_ad );

void remove_remote_remote_file_system_domain( classad::ClassAd &job_ad );

std::string unparse_remote_remote_file_system_domain( const classad::ClassAd &job_ad );

void set_remote_remote_file_system_domain( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_file_system_domain( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_file_system_domain( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_file_system_domain( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_uid_system_domain( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_uid_system_domain( const classad::ClassAd &job_ad );

void remove_remote_remote_uid_system_domain( classad::ClassAd &job_ad );

std::string unparse_remote_remote_uid_system_domain( const classad::ClassAd &job_ad );

void set_remote_remote_uid_system_domain( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_uid_system_domain( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_uid_system_domain( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_uid_system_domain( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_should_transfer_files( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_should_transfer_files( const classad::ClassAd &job_ad );

void remove_remote_remote_should_transfer_files( classad::ClassAd &job_ad );

std::string unparse_remote_remote_should_transfer_files( const classad::ClassAd &job_ad );

void set_remote_remote_should_transfer_files( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_should_transfer_files( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_should_transfer_files( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_should_transfer_files( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad );

void remove_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad );

std::string unparse_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad );

void set_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_when_to_transfer_output( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_nodenumber( classad::ClassAd &job_ad, const int &value );

int get_remote_remote_nodenumber( const classad::ClassAd &job_ad );

void remove_remote_remote_nodenumber( classad::ClassAd &job_ad );

std::string unparse_remote_remote_nodenumber( const classad::ClassAd &job_ad );

void set_remote_remote_nodenumber( classad::ClassAd &job_ad, int value, bool &good );

int get_remote_remote_nodenumber( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_nodenumber( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_nodenumber( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_stagecmd( classad::ClassAd &job_ad, const bool &value );

bool get_remote_remote_stagecmd( const classad::ClassAd &job_ad );

void remove_remote_remote_stagecmd( classad::ClassAd &job_ad );

std::string unparse_remote_remote_stagecmd( const classad::ClassAd &job_ad );

void set_remote_remote_stagecmd( classad::ClassAd &job_ad, bool value, bool &good );

bool get_remote_remote_stagecmd( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_stagecmd( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_stagecmd( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_edg_jobid( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_edg_jobid( const classad::ClassAd &job_ad );

void remove_remote_remote_edg_jobid( classad::ClassAd &job_ad );

std::string unparse_remote_remote_edg_jobid( const classad::ClassAd &job_ad );

void set_remote_remote_edg_jobid( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_edg_jobid( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_edg_jobid( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_edg_jobid( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_user_subject_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_user_subject_name( const classad::ClassAd &job_ad );

void remove_remote_remote_user_subject_name( classad::ClassAd &job_ad );

std::string unparse_remote_remote_user_subject_name( const classad::ClassAd &job_ad );

void set_remote_remote_user_subject_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_user_subject_name( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_user_subject_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_user_subject_name( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_ceid( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_ceid( const classad::ClassAd &job_ad );

void remove_remote_remote_ceid( classad::ClassAd &job_ad );

std::string unparse_remote_remote_ceid( const classad::ClassAd &job_ad );

void set_remote_remote_ceid( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_ceid( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_ceid( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_ceid( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_voms_fqan( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_voms_fqan( const classad::ClassAd &job_ad );

void remove_remote_remote_voms_fqan( classad::ClassAd &job_ad );

std::string unparse_remote_remote_voms_fqan( const classad::ClassAd &job_ad );

void set_remote_remote_voms_fqan( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_voms_fqan( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_voms_fqan( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_voms_fqan( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_virtual_organisation( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_virtual_organisation( const classad::ClassAd &job_ad );

void remove_remote_remote_virtual_organisation( classad::ClassAd &job_ad );

std::string unparse_remote_remote_virtual_organisation( const classad::ClassAd &job_ad );

void set_remote_remote_virtual_organisation( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_virtual_organisation( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_virtual_organisation( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_virtual_organisation( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_ce_requirements( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_ce_requirements( const classad::ClassAd &job_ad );

void remove_remote_remote_ce_requirements( classad::ClassAd &job_ad );

std::string unparse_remote_remote_ce_requirements( const classad::ClassAd &job_ad );

void set_remote_remote_ce_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_ce_requirements( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_ce_requirements( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_ce_requirements( const classad::ClassAd &job_ad, bool &good );

void set_remote_schedd( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_schedd( const classad::ClassAd &job_ad );

void remove_remote_schedd( classad::ClassAd &job_ad );

std::string unparse_remote_schedd( const classad::ClassAd &job_ad );

void set_remote_schedd( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_schedd( const classad::ClassAd &job_ad, bool &good );

void remove_remote_schedd( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_schedd( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_schedd( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_schedd( const classad::ClassAd &job_ad );

void remove_remote_remote_schedd( classad::ClassAd &job_ad );

std::string unparse_remote_remote_schedd( const classad::ClassAd &job_ad );

void set_remote_remote_schedd( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_schedd( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_schedd( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_schedd( const classad::ClassAd &job_ad, bool &good );

void set_remote_remote_pool( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_remote_pool( const classad::ClassAd &job_ad );

void remove_remote_remote_pool( classad::ClassAd &job_ad );

std::string unparse_remote_remote_pool( const classad::ClassAd &job_ad );

void set_remote_remote_pool( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_remote_pool( const classad::ClassAd &job_ad, bool &good );

void remove_remote_remote_pool( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_remote_pool( const classad::ClassAd &job_ad, bool &good );

void set_globus_resource( classad::ClassAd &job_ad, const std::string &value );

std::string get_globus_resource( const classad::ClassAd &job_ad );

void remove_globus_resource( classad::ClassAd &job_ad );

std::string unparse_globus_resource( const classad::ClassAd &job_ad );

void set_globus_resource( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_globus_resource( const classad::ClassAd &job_ad, bool &good );

void remove_globus_resource( classad::ClassAd &job_ad, bool &good );

std::string unparse_globus_resource( const classad::ClassAd &job_ad, bool &good );

void set_remote_globus_resource( classad::ClassAd &job_ad, const std::string &value );

std::string get_remote_globus_resource( const classad::ClassAd &job_ad );

void remove_remote_globus_resource( classad::ClassAd &job_ad );

std::string unparse_remote_globus_resource( const classad::ClassAd &job_ad );

void set_remote_globus_resource( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remote_globus_resource( const classad::ClassAd &job_ad, bool &good );

void remove_remote_globus_resource( classad::ClassAd &job_ad, bool &good );

std::string unparse_remote_globus_resource( const classad::ClassAd &job_ad, bool &good );

void set_site_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_site_name( const classad::ClassAd &job_ad );

void remove_site_name( classad::ClassAd &job_ad );

std::string unparse_site_name( const classad::ClassAd &job_ad );

void set_site_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_site_name( const classad::ClassAd &job_ad, bool &good );

void remove_site_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_site_name( const classad::ClassAd &job_ad, bool &good );

void set_initial_dir( classad::ClassAd &job_ad, const std::string &value );

std::string get_initial_dir( const classad::ClassAd &job_ad );

void remove_initial_dir( classad::ClassAd &job_ad );

std::string unparse_initial_dir( const classad::ClassAd &job_ad );

void set_initial_dir( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_initial_dir( const classad::ClassAd &job_ad, bool &good );

void remove_initial_dir( classad::ClassAd &job_ad, bool &good );

std::string unparse_initial_dir( const classad::ClassAd &job_ad, bool &good );

void set_site_gatekeeper( classad::ClassAd &job_ad, const std::string &value );

std::string get_site_gatekeeper( const classad::ClassAd &job_ad );

void remove_site_gatekeeper( classad::ClassAd &job_ad );

std::string unparse_site_gatekeeper( const classad::ClassAd &job_ad );

void set_site_gatekeeper( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_site_gatekeeper( const classad::ClassAd &job_ad, bool &good );

void remove_site_gatekeeper( classad::ClassAd &job_ad, bool &good );

std::string unparse_site_gatekeeper( const classad::ClassAd &job_ad, bool &good );

void set_should_transfer_files( classad::ClassAd &job_ad, const std::string &value );

std::string get_should_transfer_files( const classad::ClassAd &job_ad );

void remove_should_transfer_files( classad::ClassAd &job_ad );

std::string unparse_should_transfer_files( const classad::ClassAd &job_ad );

void set_should_transfer_files( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_should_transfer_files( const classad::ClassAd &job_ad, bool &good );

void remove_should_transfer_files( classad::ClassAd &job_ad, bool &good );

std::string unparse_should_transfer_files( const classad::ClassAd &job_ad, bool &good );

void set_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value );

std::string get_when_to_transfer_output( const classad::ClassAd &job_ad );

void remove_when_to_transfer_output( classad::ClassAd &job_ad );

std::string unparse_when_to_transfer_output( const classad::ClassAd &job_ad );

void set_when_to_transfer_output( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good );

void remove_when_to_transfer_output( classad::ClassAd &job_ad, bool &good );

std::string unparse_when_to_transfer_output( const classad::ClassAd &job_ad, bool &good );

void set_periodic_hold( classad::ClassAd &job_ad, const std::string &value );

std::string get_periodic_hold( const classad::ClassAd &job_ad );

void remove_periodic_hold( classad::ClassAd &job_ad );

std::string unparse_periodic_hold( const classad::ClassAd &job_ad );

void set_periodic_hold( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_periodic_hold( const classad::ClassAd &job_ad, bool &good );

void remove_periodic_hold( classad::ClassAd &job_ad, bool &good );

std::string unparse_periodic_hold( const classad::ClassAd &job_ad, bool &good );

void set_periodic_remove( classad::ClassAd &job_ad, const std::string &value );

std::string get_periodic_remove( const classad::ClassAd &job_ad );

void remove_periodic_remove( classad::ClassAd &job_ad );

std::string unparse_periodic_remove( const classad::ClassAd &job_ad );

void set_periodic_remove( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_periodic_remove( const classad::ClassAd &job_ad, bool &good );

void remove_periodic_remove( classad::ClassAd &job_ad, bool &good );

std::string unparse_periodic_remove( const classad::ClassAd &job_ad, bool &good );

void set_transfer_input_files( classad::ClassAd &job_ad, const std::string &value );

std::string get_transfer_input_files( const classad::ClassAd &job_ad );

void remove_transfer_input_files( classad::ClassAd &job_ad );

std::string unparse_transfer_input_files( const classad::ClassAd &job_ad );

void set_transfer_input_files( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_transfer_input_files( const classad::ClassAd &job_ad, bool &good );

void remove_transfer_input_files( classad::ClassAd &job_ad, bool &good );

std::string unparse_transfer_input_files( const classad::ClassAd &job_ad, bool &good );

void set_transfer_output_files( classad::ClassAd &job_ad, const std::string &value );

std::string get_transfer_output_files( const classad::ClassAd &job_ad );

void remove_transfer_output_files( classad::ClassAd &job_ad );

std::string unparse_transfer_output_files( const classad::ClassAd &job_ad );

void set_transfer_output_files( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_transfer_output_files( const classad::ClassAd &job_ad, bool &good );

void remove_transfer_output_files( classad::ClassAd &job_ad, bool &good );

std::string unparse_transfer_output_files( const classad::ClassAd &job_ad, bool &good );

void set_transfer_output( classad::ClassAd &job_ad, const std::string &value );

std::string get_transfer_output( const classad::ClassAd &job_ad );

void remove_transfer_output( classad::ClassAd &job_ad );

std::string unparse_transfer_output( const classad::ClassAd &job_ad );

void set_transfer_output( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_transfer_output( const classad::ClassAd &job_ad, bool &good );

void remove_transfer_output( classad::ClassAd &job_ad, bool &good );

std::string unparse_transfer_output( const classad::ClassAd &job_ad, bool &good );

void set_globus_rsl( classad::ClassAd &job_ad, const std::string &value );

std::string get_globus_rsl( const classad::ClassAd &job_ad );

void remove_globus_rsl( classad::ClassAd &job_ad );

std::string unparse_globus_rsl( const classad::ClassAd &job_ad );

void set_globus_rsl( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_globus_rsl( const classad::ClassAd &job_ad, bool &good );

void remove_globus_rsl( classad::ClassAd &job_ad, bool &good );

std::string unparse_globus_rsl( const classad::ClassAd &job_ad, bool &good );

void set_user_subject_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_user_subject_name( const classad::ClassAd &job_ad );

void remove_user_subject_name( classad::ClassAd &job_ad );

std::string unparse_user_subject_name( const classad::ClassAd &job_ad );

void set_user_subject_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_user_subject_name( const classad::ClassAd &job_ad, bool &good );

void remove_user_subject_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_user_subject_name( const classad::ClassAd &job_ad, bool &good );

void set_universe( classad::ClassAd &job_ad, const std::string &value );

std::string get_universe( const classad::ClassAd &job_ad );

void remove_universe( classad::ClassAd &job_ad );

std::string unparse_universe( const classad::ClassAd &job_ad );

void set_universe( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_universe( const classad::ClassAd &job_ad, bool &good );

void remove_universe( classad::ClassAd &job_ad, bool &good );

std::string unparse_universe( const classad::ClassAd &job_ad, bool &good );

void set_condor_submit_file( classad::ClassAd &job_ad, const std::string &value );

std::string get_condor_submit_file( const classad::ClassAd &job_ad );

void remove_condor_submit_file( classad::ClassAd &job_ad );

std::string unparse_condor_submit_file( const classad::ClassAd &job_ad );

void set_condor_submit_file( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_condor_submit_file( const classad::ClassAd &job_ad, bool &good );

void remove_condor_submit_file( classad::ClassAd &job_ad, bool &good );

std::string unparse_condor_submit_file( const classad::ClassAd &job_ad, bool &good );

void set_edg_dagid( classad::ClassAd &job_ad, const std::string &value );

std::string get_edg_dagid( const classad::ClassAd &job_ad );

void remove_edg_dagid( classad::ClassAd &job_ad );

std::string unparse_edg_dagid( const classad::ClassAd &job_ad );

void set_edg_dagid( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_edg_dagid( const classad::ClassAd &job_ad, bool &good );

void remove_edg_dagid( classad::ClassAd &job_ad, bool &good );

std::string unparse_edg_dagid( const classad::ClassAd &job_ad, bool &good );

void set_perusal_list_file_uri( classad::ClassAd &job_ad, const std::string &value );

std::string get_perusal_list_file_uri( const classad::ClassAd &job_ad );

void remove_perusal_list_file_uri( classad::ClassAd &job_ad );

std::string unparse_perusal_list_file_uri( const classad::ClassAd &job_ad );

void set_perusal_list_file_uri( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_perusal_list_file_uri( const classad::ClassAd &job_ad, bool &good );

void remove_perusal_list_file_uri( classad::ClassAd &job_ad, bool &good );

std::string unparse_perusal_list_file_uri( const classad::ClassAd &job_ad, bool &good );

void set_zipped_isb( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_zipped_isb( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_zipped_isb( classad::ClassAd &job_ad );

std::string unparse_zipped_isb( const classad::ClassAd &job_ad );

void set_zipped_isb( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_zipped_isb( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_zipped_isb( classad::ClassAd &job_ad, bool &good );

std::string unparse_zipped_isb( const classad::ClassAd &job_ad, bool &good );

void set_edg_previous_matches( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_edg_previous_matches( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_edg_previous_matches( classad::ClassAd &job_ad );

std::string unparse_edg_previous_matches( const classad::ClassAd &job_ad );

void set_edg_previous_matches( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_edg_previous_matches( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_edg_previous_matches( classad::ClassAd &job_ad, bool &good );

std::string unparse_edg_previous_matches( const classad::ClassAd &job_ad, bool &good );

void set_really_running_token( classad::ClassAd &job_ad, const std::string &value );

std::string get_really_running_token( const classad::ClassAd &job_ad );

void remove_really_running_token( classad::ClassAd &job_ad );

std::string unparse_really_running_token( const classad::ClassAd &job_ad );

void set_really_running_token( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_really_running_token( const classad::ClassAd &job_ad, bool &good );

void remove_really_running_token( classad::ClassAd &job_ad, bool &good );

std::string unparse_really_running_token( const classad::ClassAd &job_ad, bool &good );

void set_getenv( classad::ClassAd &job_ad, const bool &value );

bool get_getenv( const classad::ClassAd &job_ad );

void remove_getenv( classad::ClassAd &job_ad );

std::string unparse_getenv( const classad::ClassAd &job_ad );

void set_getenv( classad::ClassAd &job_ad, bool value, bool &good );

bool get_getenv( const classad::ClassAd &job_ad, bool &good );

void remove_getenv( classad::ClassAd &job_ad, bool &good );

std::string unparse_getenv( const classad::ClassAd &job_ad, bool &good );

void set_remove_kill_sig( classad::ClassAd &job_ad, const std::string &value );

std::string get_remove_kill_sig( const classad::ClassAd &job_ad );

void remove_remove_kill_sig( classad::ClassAd &job_ad );

std::string unparse_remove_kill_sig( const classad::ClassAd &job_ad );

void set_remove_kill_sig( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_remove_kill_sig( const classad::ClassAd &job_ad, bool &good );

void remove_remove_kill_sig( classad::ClassAd &job_ad, bool &good );

std::string unparse_remove_kill_sig( const classad::ClassAd &job_ad, bool &good );

void set_voms_fqan( classad::ClassAd &job_ad, const std::string &value );

std::string get_voms_fqan( const classad::ClassAd &job_ad );

void remove_voms_fqan( classad::ClassAd &job_ad );

std::string unparse_voms_fqan( const classad::ClassAd &job_ad );

void set_voms_fqan( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_voms_fqan( const classad::ClassAd &job_ad, bool &good );

void remove_voms_fqan( classad::ClassAd &job_ad, bool &good );

std::string unparse_voms_fqan( const classad::ClassAd &job_ad, bool &good );

void set_default_node_retry_count( classad::ClassAd &job_ad, const int &value );

int get_default_node_retry_count( const classad::ClassAd &job_ad );

void remove_default_node_retry_count( classad::ClassAd &job_ad );

std::string unparse_default_node_retry_count( const classad::ClassAd &job_ad );

void set_default_node_retry_count( classad::ClassAd &job_ad, int value, bool &good );

int get_default_node_retry_count( const classad::ClassAd &job_ad, bool &good );

void remove_default_node_retry_count( classad::ClassAd &job_ad, bool &good );

std::string unparse_default_node_retry_count( const classad::ClassAd &job_ad, bool &good );

void set_default_node_shallow_retry_count( classad::ClassAd &job_ad, const int &value );

int get_default_node_shallow_retry_count( const classad::ClassAd &job_ad );

void remove_default_node_shallow_retry_count( classad::ClassAd &job_ad );

std::string unparse_default_node_shallow_retry_count( const classad::ClassAd &job_ad );

void set_default_node_shallow_retry_count( classad::ClassAd &job_ad, int value, bool &good );

int get_default_node_shallow_retry_count( const classad::ClassAd &job_ad, bool &good );

void remove_default_node_shallow_retry_count( classad::ClassAd &job_ad, bool &good );

std::string unparse_default_node_shallow_retry_count( const classad::ClassAd &job_ad, bool &good );

void set_ce_application_dir( classad::ClassAd &job_ad, const std::string &value );

std::string get_ce_application_dir( const classad::ClassAd &job_ad );

void remove_ce_application_dir( classad::ClassAd &job_ad );

std::string unparse_ce_application_dir( const classad::ClassAd &job_ad );

void set_ce_application_dir( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_ce_application_dir( const classad::ClassAd &job_ad, bool &good );

void remove_ce_application_dir( classad::ClassAd &job_ad, bool &good );

std::string unparse_ce_application_dir( const classad::ClassAd &job_ad, bool &good );

void set_grid_resource( classad::ClassAd &job_ad, const std::string &value );

std::string get_grid_resource( const classad::ClassAd &job_ad );

void remove_grid_resource( classad::ClassAd &job_ad );

std::string unparse_grid_resource( const classad::ClassAd &job_ad );

void set_grid_resource( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_grid_resource( const classad::ClassAd &job_ad, bool &good );

void remove_grid_resource( classad::ClassAd &job_ad, bool &good );

std::string unparse_grid_resource( const classad::ClassAd &job_ad, bool &good );

void set_nordugrid_rsl( classad::ClassAd &job_ad, const std::string &value );

std::string get_nordugrid_rsl( const classad::ClassAd &job_ad );

void remove_nordugrid_rsl( classad::ClassAd &job_ad );

std::string unparse_nordugrid_rsl( const classad::ClassAd &job_ad );

void set_nordugrid_rsl( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_nordugrid_rsl( const classad::ClassAd &job_ad, bool &good );

void remove_nordugrid_rsl( classad::ClassAd &job_ad, bool &good );

std::string unparse_nordugrid_rsl( const classad::ClassAd &job_ad, bool &good );

void set_ce_requirements( classad::ClassAd &job_ad, const std::string &value );

std::string get_ce_requirements( const classad::ClassAd &job_ad );

void remove_ce_requirements( classad::ClassAd &job_ad );

std::string unparse_ce_requirements( const classad::ClassAd &job_ad );

void set_ce_requirements( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_ce_requirements( const classad::ClassAd &job_ad, bool &good );

void remove_ce_requirements( classad::ClassAd &job_ad, bool &good );

std::string unparse_ce_requirements( const classad::ClassAd &job_ad, bool &good );

void set_ceinfo_host_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_ceinfo_host_name( const classad::ClassAd &job_ad );

void remove_ceinfo_host_name( classad::ClassAd &job_ad );

std::string unparse_ceinfo_host_name( const classad::ClassAd &job_ad );

void set_ceinfo_host_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_ceinfo_host_name( const classad::ClassAd &job_ad, bool &good );

void remove_ceinfo_host_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_ceinfo_host_name( const classad::ClassAd &job_ad, bool &good );

void set_replans_count( classad::ClassAd &job_ad, const int &value );

int get_replans_count( const classad::ClassAd &job_ad );

void remove_replans_count( classad::ClassAd &job_ad );

std::string unparse_replans_count( const classad::ClassAd &job_ad );

void set_replans_count( classad::ClassAd &job_ad, int value, bool &good );

int get_replans_count( const classad::ClassAd &job_ad, bool &good );

void remove_replans_count( classad::ClassAd &job_ad, bool &good );

std::string unparse_replans_count( const classad::ClassAd &job_ad, bool &good );


void set_edg_previous_matches_ex(
  classad::ClassAd& ad,
  std::vector<std::pair<std::string,int> > const& previous_matches
);

} // namespace jdl
} // namespace glite

#endif /* GLITE_WMS_COMMON_REQUESTAD_PRIVATEADMANIPULATION_H */

// Local Variables:
// mode: c++
// End:
