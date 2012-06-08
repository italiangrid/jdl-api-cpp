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

#ifndef GLITE_WMS_COMMON_REQUESTAD_JOBADMANIPULATION_H
#define GLITE_WMS_COMMON_REQUESTAD_JOBADMANIPULATION_H

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
class ExprTree;
}

namespace glite {
namespace jdl {


void set_requirements( classad::ClassAd &job_ad, const bool &value );

bool get_requirements( const classad::ClassAd &job_ad );

void remove_requirements( classad::ClassAd &job_ad );

std::string unparse_requirements( const classad::ClassAd &job_ad );

void set_requirements( classad::ClassAd &job_ad, bool value, bool &good );

bool get_requirements( const classad::ClassAd &job_ad, bool &good );

void remove_requirements( classad::ClassAd &job_ad, bool &good );

std::string unparse_requirements( const classad::ClassAd &job_ad, bool &good );

void set_fuzzy_rank( classad::ClassAd &job_ad, const bool &value );

bool get_fuzzy_rank( const classad::ClassAd &job_ad );

void remove_fuzzy_rank( classad::ClassAd &job_ad );

std::string unparse_fuzzy_rank( const classad::ClassAd &job_ad );

void set_fuzzy_rank( classad::ClassAd &job_ad, bool value, bool &good );

bool get_fuzzy_rank( const classad::ClassAd &job_ad, bool &good );

void remove_fuzzy_rank( classad::ClassAd &job_ad, bool &good );

std::string unparse_fuzzy_rank( const classad::ClassAd &job_ad, bool &good );

void set_allow_zipped_isb( classad::ClassAd &job_ad, const bool &value );

bool get_allow_zipped_isb( const classad::ClassAd &job_ad );

void remove_allow_zipped_isb( classad::ClassAd &job_ad );

std::string unparse_allow_zipped_isb( const classad::ClassAd &job_ad );

void set_allow_zipped_isb( classad::ClassAd &job_ad, bool value, bool &good );

bool get_allow_zipped_isb( const classad::ClassAd &job_ad, bool &good );

void remove_allow_zipped_isb( classad::ClassAd &job_ad, bool &good );

std::string unparse_allow_zipped_isb( const classad::ClassAd &job_ad, bool &good );

void set_perusal_file_enable( classad::ClassAd &job_ad, const bool &value );

bool get_perusal_file_enable( const classad::ClassAd &job_ad );

void remove_perusal_file_enable( classad::ClassAd &job_ad );

std::string unparse_perusal_file_enable( const classad::ClassAd &job_ad );

void set_perusal_file_enable( classad::ClassAd &job_ad, bool value, bool &good );

bool get_perusal_file_enable( const classad::ClassAd &job_ad, bool &good );

void remove_perusal_file_enable( classad::ClassAd &job_ad, bool &good );

std::string unparse_perusal_file_enable( const classad::ClassAd &job_ad, bool &good );

void set_nodes_collocation( classad::ClassAd &job_ad, const bool &value );

bool get_nodes_collocation( const classad::ClassAd &job_ad );

void remove_nodes_collocation( classad::ClassAd &job_ad );

std::string unparse_nodes_collocation( const classad::ClassAd &job_ad );

void set_nodes_collocation( classad::ClassAd &job_ad, bool value, bool &good );

bool get_nodes_collocation( const classad::ClassAd &job_ad, bool &good );

void remove_nodes_collocation( classad::ClassAd &job_ad, bool &good );

std::string unparse_nodes_collocation( const classad::ClassAd &job_ad, bool &good );

void set_move_to_ce( classad::ClassAd &job_ad, const bool &value );

bool get_move_to_ce( const classad::ClassAd &job_ad );

void remove_move_to_ce( classad::ClassAd &job_ad );

std::string unparse_move_to_ce( const classad::ClassAd &job_ad );

void set_move_to_ce( classad::ClassAd &job_ad, bool value, bool &good );

bool get_move_to_ce( const classad::ClassAd &job_ad, bool &good );

void remove_move_to_ce( classad::ClassAd &job_ad, bool &good );

std::string unparse_move_to_ce( const classad::ClassAd &job_ad, bool &good );

void set_short_deadline_job( classad::ClassAd &job_ad, const bool &value );

bool get_short_deadline_job( const classad::ClassAd &job_ad );

void remove_short_deadline_job( classad::ClassAd &job_ad );

std::string unparse_short_deadline_job( const classad::ClassAd &job_ad );

void set_short_deadline_job( classad::ClassAd &job_ad, bool value, bool &good );

bool get_short_deadline_job( const classad::ClassAd &job_ad, bool &good );

void remove_short_deadline_job( classad::ClassAd &job_ad, bool &good );

std::string unparse_short_deadline_job( const classad::ClassAd &job_ad, bool &good );

void set_whole_nodes( classad::ClassAd &job_ad, const bool &value );

bool get_whole_nodes( const classad::ClassAd &job_ad );

void remove_whole_nodes( classad::ClassAd &job_ad );

std::string unparse_whole_nodes( const classad::ClassAd &job_ad );

void set_whole_nodes( classad::ClassAd &job_ad, bool value, bool &good );

bool get_whole_nodes( const classad::ClassAd &job_ad, bool &good );

void remove_whole_nodes( classad::ClassAd &job_ad, bool &good );

std::string unparse_whole_nodes( const classad::ClassAd &job_ad, bool &good );

void set_enable_wms_feedback( classad::ClassAd &job_ad, const bool &value );

bool get_enable_wms_feedback( const classad::ClassAd &job_ad );

void remove_enable_wms_feedback( classad::ClassAd &job_ad );

std::string unparse_enable_wms_feedback( const classad::ClassAd &job_ad );

void set_enable_wms_feedback( classad::ClassAd &job_ad, bool value, bool &good );

bool get_enable_wms_feedback( const classad::ClassAd &job_ad, bool &good );

void remove_enable_wms_feedback( classad::ClassAd &job_ad, bool &good );

std::string unparse_enable_wms_feedback( const classad::ClassAd &job_ad, bool &good );

void set_exit_code( classad::ClassAd &job_ad, const int &value );

int get_exit_code( const classad::ClassAd &job_ad );

void remove_exit_code( classad::ClassAd &job_ad );

std::string unparse_exit_code( const classad::ClassAd &job_ad );

void set_exit_code( classad::ClassAd &job_ad, int value, bool &good );

int get_exit_code( const classad::ClassAd &job_ad, bool &good );

void remove_exit_code( classad::ClassAd &job_ad, bool &good );

std::string unparse_exit_code( const classad::ClassAd &job_ad, bool &good );

void set_node_number( classad::ClassAd &job_ad, const int &value );

int get_node_number( const classad::ClassAd &job_ad );

void remove_node_number( classad::ClassAd &job_ad );

std::string unparse_node_number( const classad::ClassAd &job_ad );

void set_node_number( classad::ClassAd &job_ad, int value, bool &good );

int get_node_number( const classad::ClassAd &job_ad, bool &good );

void remove_node_number( classad::ClassAd &job_ad, bool &good );

std::string unparse_node_number( const classad::ClassAd &job_ad, bool &good );

void set_cpu_number( classad::ClassAd &job_ad, const int &value );

int get_cpu_number( const classad::ClassAd &job_ad );

void remove_cpu_number( classad::ClassAd &job_ad );

std::string unparse_cpu_number( const classad::ClassAd &job_ad );

void set_cpu_number( classad::ClassAd &job_ad, int value, bool &good );

int get_cpu_number( const classad::ClassAd &job_ad, bool &good );

void remove_cpu_number( classad::ClassAd &job_ad, bool &good );

std::string unparse_cpu_number( const classad::ClassAd &job_ad, bool &good );

void set_listener_port( classad::ClassAd &job_ad, const int &value );

int get_listener_port( const classad::ClassAd &job_ad );

void remove_listener_port( classad::ClassAd &job_ad );

std::string unparse_listener_port( const classad::ClassAd &job_ad );

void set_listener_port( classad::ClassAd &job_ad, int value, bool &good );

int get_listener_port( const classad::ClassAd &job_ad, bool &good );

void remove_listener_port( classad::ClassAd &job_ad, bool &good );

std::string unparse_listener_port( const classad::ClassAd &job_ad, bool &good );

void set_retry_count( classad::ClassAd &job_ad, const int &value );

int get_retry_count( const classad::ClassAd &job_ad );

void remove_retry_count( classad::ClassAd &job_ad );

std::string unparse_retry_count( const classad::ClassAd &job_ad );

void set_retry_count( classad::ClassAd &job_ad, int value, bool &good );

int get_retry_count( const classad::ClassAd &job_ad, bool &good );

void remove_retry_count( classad::ClassAd &job_ad, bool &good );

std::string unparse_retry_count( const classad::ClassAd &job_ad, bool &good );

void set_shallow_retry_count( classad::ClassAd &job_ad, const int &value );

int get_shallow_retry_count( const classad::ClassAd &job_ad );

void remove_shallow_retry_count( classad::ClassAd &job_ad );

std::string unparse_shallow_retry_count( const classad::ClassAd &job_ad );

void set_shallow_retry_count( classad::ClassAd &job_ad, int value, bool &good );

int get_shallow_retry_count( const classad::ClassAd &job_ad, bool &good );

void remove_shallow_retry_count( classad::ClassAd &job_ad, bool &good );

std::string unparse_shallow_retry_count( const classad::ClassAd &job_ad, bool &good );

void set_perusal_time_interval( classad::ClassAd &job_ad, const int &value );

int get_perusal_time_interval( const classad::ClassAd &job_ad );

void remove_perusal_time_interval( classad::ClassAd &job_ad );

std::string unparse_perusal_time_interval( const classad::ClassAd &job_ad );

void set_perusal_time_interval( classad::ClassAd &job_ad, int value, bool &good );

int get_perusal_time_interval( const classad::ClassAd &job_ad, bool &good );

void remove_perusal_time_interval( classad::ClassAd &job_ad, bool &good );

std::string unparse_perusal_time_interval( const classad::ClassAd &job_ad, bool &good );

void set_smpgranularity( classad::ClassAd &job_ad, const int &value );

int get_smpgranularity( const classad::ClassAd &job_ad );

void remove_smpgranularity( classad::ClassAd &job_ad );

std::string unparse_smpgranularity( const classad::ClassAd &job_ad );

void set_smpgranularity( classad::ClassAd &job_ad, int value, bool &good );

int get_smpgranularity( const classad::ClassAd &job_ad, bool &good );

void remove_smpgranularity( classad::ClassAd &job_ad, bool &good );

std::string unparse_smpgranularity( const classad::ClassAd &job_ad, bool &good );

void set_host_number( classad::ClassAd &job_ad, const int &value );

int get_host_number( const classad::ClassAd &job_ad );

void remove_host_number( classad::ClassAd &job_ad );

std::string unparse_host_number( const classad::ClassAd &job_ad );

void set_host_number( classad::ClassAd &job_ad, int value, bool &good );

int get_host_number( const classad::ClassAd &job_ad, bool &good );

void remove_host_number( classad::ClassAd &job_ad, bool &good );

std::string unparse_host_number( const classad::ClassAd &job_ad, bool &good );

void set_ce_match( classad::ClassAd &job_ad, const int &value );

int get_ce_match( const classad::ClassAd &job_ad );

void remove_ce_match( classad::ClassAd &job_ad );

std::string unparse_ce_match( const classad::ClassAd &job_ad );

void set_ce_match( classad::ClassAd &job_ad, int value, bool &good );

int get_ce_match( const classad::ClassAd &job_ad, bool &good );

void remove_ce_match( classad::ClassAd &job_ad, bool &good );

std::string unparse_ce_match( const classad::ClassAd &job_ad, bool &good );

void set_job_steps( classad::ClassAd &job_ad, const int &value );

int get_job_steps( const classad::ClassAd &job_ad );

void remove_job_steps( classad::ClassAd &job_ad );

std::string unparse_job_steps( const classad::ClassAd &job_ad );

void set_job_steps( classad::ClassAd &job_ad, int value, bool &good );

int get_job_steps( const classad::ClassAd &job_ad, bool &good );

void remove_job_steps( classad::ClassAd &job_ad, bool &good );

std::string unparse_job_steps( const classad::ClassAd &job_ad, bool &good );

void set_current_step( classad::ClassAd &job_ad, const int &value );

int get_current_step( const classad::ClassAd &job_ad );

void remove_current_step( classad::ClassAd &job_ad );

std::string unparse_current_step( const classad::ClassAd &job_ad );

void set_current_step( classad::ClassAd &job_ad, int value, bool &good );

int get_current_step( const classad::ClassAd &job_ad, bool &good );

void remove_current_step( classad::ClassAd &job_ad, bool &good );

std::string unparse_current_step( const classad::ClassAd &job_ad, bool &good );

void set_expiry_time( classad::ClassAd &job_ad, const int &value );

int get_expiry_time( const classad::ClassAd &job_ad );

void remove_expiry_time( classad::ClassAd &job_ad );

std::string unparse_expiry_time( const classad::ClassAd &job_ad );

void set_expiry_time( classad::ClassAd &job_ad, int value, bool &good );

int get_expiry_time( const classad::ClassAd &job_ad, bool &good );

void remove_expiry_time( classad::ClassAd &job_ad, bool &good );

std::string unparse_expiry_time( const classad::ClassAd &job_ad, bool &good );

void set_creation_time( classad::ClassAd &job_ad, const int &value );

int get_creation_time( const classad::ClassAd &job_ad );

void remove_creation_time( classad::ClassAd &job_ad );

std::string unparse_creation_time( const classad::ClassAd &job_ad );

void set_creation_time( classad::ClassAd &job_ad, int value, bool &good );

int get_creation_time( const classad::ClassAd &job_ad, bool &good );

void remove_creation_time( classad::ClassAd &job_ad, bool &good );

std::string unparse_creation_time( const classad::ClassAd &job_ad, bool &good );

void set_validity_time( classad::ClassAd &job_ad, const int &value );

int get_validity_time( const classad::ClassAd &job_ad );

void remove_validity_time( classad::ClassAd &job_ad );

std::string unparse_validity_time( const classad::ClassAd &job_ad );

void set_validity_time( classad::ClassAd &job_ad, int value, bool &good );

int get_validity_time( const classad::ClassAd &job_ad, bool &good );

void remove_validity_time( classad::ClassAd &job_ad, bool &good );

std::string unparse_validity_time( const classad::ClassAd &job_ad, bool &good );

void set_partition_number( classad::ClassAd &job_ad, const int &value );

int get_partition_number( const classad::ClassAd &job_ad );

void remove_partition_number( classad::ClassAd &job_ad );

std::string unparse_partition_number( const classad::ClassAd &job_ad );

void set_partition_number( classad::ClassAd &job_ad, int value, bool &good );

int get_partition_number( const classad::ClassAd &job_ad, bool &good );

void remove_partition_number( classad::ClassAd &job_ad, bool &good );

std::string unparse_partition_number( const classad::ClassAd &job_ad, bool &good );

void set_rank( classad::ClassAd &job_ad, const double &value );

double get_rank( const classad::ClassAd &job_ad );

void remove_rank( classad::ClassAd &job_ad );

std::string unparse_rank( const classad::ClassAd &job_ad );

void set_rank( classad::ClassAd &job_ad, double value, bool &good );

double get_rank( const classad::ClassAd &job_ad, bool &good );

void remove_rank( classad::ClassAd &job_ad, bool &good );

std::string unparse_rank( const classad::ClassAd &job_ad, bool &good );

void set_fuzzy_factor( classad::ClassAd &job_ad, const double &value );

double get_fuzzy_factor( const classad::ClassAd &job_ad );

void remove_fuzzy_factor( classad::ClassAd &job_ad );

std::string unparse_fuzzy_factor( const classad::ClassAd &job_ad );

void set_fuzzy_factor( classad::ClassAd &job_ad, double value, bool &good );

double get_fuzzy_factor( const classad::ClassAd &job_ad, bool &good );

void remove_fuzzy_factor( classad::ClassAd &job_ad, bool &good );

std::string unparse_fuzzy_factor( const classad::ClassAd &job_ad, bool &good );

void set_notification_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_notification_type( const classad::ClassAd &job_ad );

void remove_notification_type( classad::ClassAd &job_ad );

std::string unparse_notification_type( const classad::ClassAd &job_ad );

void set_notification_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_notification_type( const classad::ClassAd &job_ad, bool &good );

void remove_notification_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_notification_type( const classad::ClassAd &job_ad, bool &good );

void set_job_status( classad::ClassAd &job_ad, const std::string &value );

std::string get_job_status( const classad::ClassAd &job_ad );

void remove_job_status( classad::ClassAd &job_ad );

std::string unparse_job_status( const classad::ClassAd &job_ad );

void set_job_status( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_job_status( const classad::ClassAd &job_ad, bool &good );

void remove_job_status( classad::ClassAd &job_ad, bool &good );

std::string unparse_job_status( const classad::ClassAd &job_ad, bool &good );

void set_aborted_reason( classad::ClassAd &job_ad, const std::string &value );

std::string get_aborted_reason( const classad::ClassAd &job_ad );

void remove_aborted_reason( classad::ClassAd &job_ad );

std::string unparse_aborted_reason( const classad::ClassAd &job_ad );

void set_aborted_reason( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_aborted_reason( const classad::ClassAd &job_ad, bool &good );

void remove_aborted_reason( classad::ClassAd &job_ad, bool &good );

std::string unparse_aborted_reason( const classad::ClassAd &job_ad, bool &good );

void set_globus_resource_contact_string( classad::ClassAd &job_ad, const std::string &value );

std::string get_globus_resource_contact_string( const classad::ClassAd &job_ad );

void remove_globus_resource_contact_string( classad::ClassAd &job_ad );

std::string unparse_globus_resource_contact_string( const classad::ClassAd &job_ad );

void set_globus_resource_contact_string( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_globus_resource_contact_string( const classad::ClassAd &job_ad, bool &good );

void remove_globus_resource_contact_string( classad::ClassAd &job_ad, bool &good );

std::string unparse_globus_resource_contact_string( const classad::ClassAd &job_ad, bool &good );

void set_queue_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_queue_name( const classad::ClassAd &job_ad );

void remove_queue_name( classad::ClassAd &job_ad );

std::string unparse_queue_name( const classad::ClassAd &job_ad );

void set_queue_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_queue_name( const classad::ClassAd &job_ad, bool &good );

void remove_queue_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_queue_name( const classad::ClassAd &job_ad, bool &good );

void set_match_status( classad::ClassAd &job_ad, const std::string &value );

std::string get_match_status( const classad::ClassAd &job_ad );

void remove_match_status( classad::ClassAd &job_ad );

std::string unparse_match_status( const classad::ClassAd &job_ad );

void set_match_status( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_match_status( const classad::ClassAd &job_ad, bool &good );

void remove_match_status( classad::ClassAd &job_ad, bool &good );

std::string unparse_match_status( const classad::ClassAd &job_ad, bool &good );

void set_ce_rank( classad::ClassAd &job_ad, const std::string &value );

std::string get_ce_rank( const classad::ClassAd &job_ad );

void remove_ce_rank( classad::ClassAd &job_ad );

std::string unparse_ce_rank( const classad::ClassAd &job_ad );

void set_ce_rank( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_ce_rank( const classad::ClassAd &job_ad, bool &good );

void remove_ce_rank( classad::ClassAd &job_ad, bool &good );

std::string unparse_ce_rank( const classad::ClassAd &job_ad, bool &good );

void set_cancel_status( classad::ClassAd &job_ad, const std::string &value );

std::string get_cancel_status( const classad::ClassAd &job_ad );

void remove_cancel_status( classad::ClassAd &job_ad );

std::string unparse_cancel_status( const classad::ClassAd &job_ad );

void set_cancel_status( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_cancel_status( const classad::ClassAd &job_ad, bool &good );

void remove_cancel_status( classad::ClassAd &job_ad, bool &good );

std::string unparse_cancel_status( const classad::ClassAd &job_ad, bool &good );

void set_failure_reason( classad::ClassAd &job_ad, const std::string &value );

std::string get_failure_reason( const classad::ClassAd &job_ad );

void remove_failure_reason( classad::ClassAd &job_ad );

std::string unparse_failure_reason( const classad::ClassAd &job_ad );

void set_failure_reason( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_failure_reason( const classad::ClassAd &job_ad, bool &good );

void remove_failure_reason( classad::ClassAd &job_ad, bool &good );

std::string unparse_failure_reason( const classad::ClassAd &job_ad, bool &good );

void set_transfer_status( classad::ClassAd &job_ad, const std::string &value );

std::string get_transfer_status( const classad::ClassAd &job_ad );

void remove_transfer_status( classad::ClassAd &job_ad );

std::string unparse_transfer_status( const classad::ClassAd &job_ad );

void set_transfer_status( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_transfer_status( const classad::ClassAd &job_ad, bool &good );

void remove_transfer_status( classad::ClassAd &job_ad, bool &good );

std::string unparse_transfer_status( const classad::ClassAd &job_ad, bool &good );

void set_sandbox_file( classad::ClassAd &job_ad, const std::string &value );

std::string get_sandbox_file( const classad::ClassAd &job_ad );

void remove_sandbox_file( classad::ClassAd &job_ad );

std::string unparse_sandbox_file( const classad::ClassAd &job_ad );

void set_sandbox_file( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_sandbox_file( const classad::ClassAd &job_ad, bool &good );

void remove_sandbox_file( classad::ClassAd &job_ad, bool &good );

std::string unparse_sandbox_file( const classad::ClassAd &job_ad, bool &good );

void set_edg_jobid( classad::ClassAd &job_ad, const std::string &value );

std::string get_edg_jobid( const classad::ClassAd &job_ad );

void remove_edg_jobid( classad::ClassAd &job_ad );

std::string unparse_edg_jobid( const classad::ClassAd &job_ad );

void set_edg_jobid( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_edg_jobid( const classad::ClassAd &job_ad, bool &good );

void remove_edg_jobid( classad::ClassAd &job_ad, bool &good );

std::string unparse_edg_jobid( const classad::ClassAd &job_ad, bool &good );

void set_ce_id( classad::ClassAd &job_ad, const std::string &value );

std::string get_ce_id( const classad::ClassAd &job_ad );

void remove_ce_id( classad::ClassAd &job_ad );

std::string unparse_ce_id( const classad::ClassAd &job_ad );

void set_ce_id( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_ce_id( const classad::ClassAd &job_ad, bool &good );

void remove_ce_id( classad::ClassAd &job_ad, bool &good );

std::string unparse_ce_id( const classad::ClassAd &job_ad, bool &good );

void set_submit_to( classad::ClassAd &job_ad, const std::string &value );

std::string get_submit_to( const classad::ClassAd &job_ad );

void remove_submit_to( classad::ClassAd &job_ad );

std::string unparse_submit_to( const classad::ClassAd &job_ad );

void set_submit_to( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_submit_to( const classad::ClassAd &job_ad, bool &good );

void remove_submit_to( classad::ClassAd &job_ad, bool &good );

std::string unparse_submit_to( const classad::ClassAd &job_ad, bool &good );

void set_executable( classad::ClassAd &job_ad, const std::string &value );

std::string get_executable( const classad::ClassAd &job_ad );

void remove_executable( classad::ClassAd &job_ad );

std::string unparse_executable( const classad::ClassAd &job_ad );

void set_executable( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_executable( const classad::ClassAd &job_ad, bool &good );

void remove_executable( classad::ClassAd &job_ad, bool &good );

std::string unparse_executable( const classad::ClassAd &job_ad, bool &good );

void set_std_output( classad::ClassAd &job_ad, const std::string &value );

std::string get_std_output( const classad::ClassAd &job_ad );

void remove_std_output( classad::ClassAd &job_ad );

std::string unparse_std_output( const classad::ClassAd &job_ad );

void set_std_output( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_std_output( const classad::ClassAd &job_ad, bool &good );

void remove_std_output( classad::ClassAd &job_ad, bool &good );

std::string unparse_std_output( const classad::ClassAd &job_ad, bool &good );

void set_std_input( classad::ClassAd &job_ad, const std::string &value );

std::string get_std_input( const classad::ClassAd &job_ad );

void remove_std_input( classad::ClassAd &job_ad );

std::string unparse_std_input( const classad::ClassAd &job_ad );

void set_std_input( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_std_input( const classad::ClassAd &job_ad, bool &good );

void remove_std_input( classad::ClassAd &job_ad, bool &good );

std::string unparse_std_input( const classad::ClassAd &job_ad, bool &good );

void set_std_error( classad::ClassAd &job_ad, const std::string &value );

std::string get_std_error( const classad::ClassAd &job_ad );

void remove_std_error( classad::ClassAd &job_ad );

std::string unparse_std_error( const classad::ClassAd &job_ad );

void set_std_error( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_std_error( const classad::ClassAd &job_ad, bool &good );

void remove_std_error( classad::ClassAd &job_ad, bool &good );

std::string unparse_std_error( const classad::ClassAd &job_ad, bool &good );

void set_arguments( classad::ClassAd &job_ad, const std::string &value );

std::string get_arguments( const classad::ClassAd &job_ad );

void remove_arguments( classad::ClassAd &job_ad );

std::string unparse_arguments( const classad::ClassAd &job_ad );

void set_arguments( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_arguments( const classad::ClassAd &job_ad, bool &good );

void remove_arguments( classad::ClassAd &job_ad, bool &good );

std::string unparse_arguments( const classad::ClassAd &job_ad, bool &good );

void set_prologue( classad::ClassAd &job_ad, const std::string &value );

std::string get_prologue( const classad::ClassAd &job_ad );

void remove_prologue( classad::ClassAd &job_ad );

std::string unparse_prologue( const classad::ClassAd &job_ad );

void set_prologue( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_prologue( const classad::ClassAd &job_ad, bool &good );

void remove_prologue( classad::ClassAd &job_ad, bool &good );

std::string unparse_prologue( const classad::ClassAd &job_ad, bool &good );

void set_prologue_arguments( classad::ClassAd &job_ad, const std::string &value );

std::string get_prologue_arguments( const classad::ClassAd &job_ad );

void remove_prologue_arguments( classad::ClassAd &job_ad );

std::string unparse_prologue_arguments( const classad::ClassAd &job_ad );

void set_prologue_arguments( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_prologue_arguments( const classad::ClassAd &job_ad, bool &good );

void remove_prologue_arguments( classad::ClassAd &job_ad, bool &good );

std::string unparse_prologue_arguments( const classad::ClassAd &job_ad, bool &good );

void set_epilogue( classad::ClassAd &job_ad, const std::string &value );

std::string get_epilogue( const classad::ClassAd &job_ad );

void remove_epilogue( classad::ClassAd &job_ad );

std::string unparse_epilogue( const classad::ClassAd &job_ad );

void set_epilogue( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_epilogue( const classad::ClassAd &job_ad, bool &good );

void remove_epilogue( classad::ClassAd &job_ad, bool &good );

std::string unparse_epilogue( const classad::ClassAd &job_ad, bool &good );

void set_epilogue_arguments( classad::ClassAd &job_ad, const std::string &value );

std::string get_epilogue_arguments( const classad::ClassAd &job_ad );

void remove_epilogue_arguments( classad::ClassAd &job_ad );

std::string unparse_epilogue_arguments( const classad::ClassAd &job_ad );

void set_epilogue_arguments( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_epilogue_arguments( const classad::ClassAd &job_ad, bool &good );

void remove_epilogue_arguments( classad::ClassAd &job_ad, bool &good );

std::string unparse_epilogue_arguments( const classad::ClassAd &job_ad, bool &good );

void set_my_proxy_server( classad::ClassAd &job_ad, const std::string &value );

std::string get_my_proxy_server( const classad::ClassAd &job_ad );

void remove_my_proxy_server( classad::ClassAd &job_ad );

std::string unparse_my_proxy_server( const classad::ClassAd &job_ad );

void set_my_proxy_server( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_my_proxy_server( const classad::ClassAd &job_ad, bool &good );

void remove_my_proxy_server( classad::ClassAd &job_ad, bool &good );

std::string unparse_my_proxy_server( const classad::ClassAd &job_ad, bool &good );

void set_job_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_job_type( const classad::ClassAd &job_ad );

void remove_job_type( classad::ClassAd &job_ad );

std::string unparse_job_type( const classad::ClassAd &job_ad );

void set_job_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_job_type( const classad::ClassAd &job_ad, bool &good );

void remove_job_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_job_type( const classad::ClassAd &job_ad, bool &good );

void set_output_se( classad::ClassAd &job_ad, const std::string &value );

std::string get_output_se( const classad::ClassAd &job_ad );

void remove_output_se( classad::ClassAd &job_ad );

std::string unparse_output_se( const classad::ClassAd &job_ad );

void set_output_se( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_output_se( const classad::ClassAd &job_ad, bool &good );

void remove_output_se( classad::ClassAd &job_ad, bool &good );

std::string unparse_output_se( const classad::ClassAd &job_ad, bool &good );

void set_replica_catalog( classad::ClassAd &job_ad, const std::string &value );

std::string get_replica_catalog( const classad::ClassAd &job_ad );

void remove_replica_catalog( classad::ClassAd &job_ad );

std::string unparse_replica_catalog( const classad::ClassAd &job_ad );

void set_replica_catalog( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_replica_catalog( const classad::ClassAd &job_ad, bool &good );

void remove_replica_catalog( classad::ClassAd &job_ad, bool &good );

std::string unparse_replica_catalog( const classad::ClassAd &job_ad, bool &good );

void set_user_contact( classad::ClassAd &job_ad, const std::string &value );

std::string get_user_contact( const classad::ClassAd &job_ad );

void remove_user_contact( classad::ClassAd &job_ad );

std::string unparse_user_contact( const classad::ClassAd &job_ad );

void set_user_contact( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_user_contact( const classad::ClassAd &job_ad, bool &good );

void remove_user_contact( classad::ClassAd &job_ad, bool &good );

std::string unparse_user_contact( const classad::ClassAd &job_ad, bool &good );

void set_certificate_subject( classad::ClassAd &job_ad, const std::string &value );

std::string get_certificate_subject( const classad::ClassAd &job_ad );

void remove_certificate_subject( classad::ClassAd &job_ad );

std::string unparse_certificate_subject( const classad::ClassAd &job_ad );

void set_certificate_subject( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_certificate_subject( const classad::ClassAd &job_ad, bool &good );

void remove_certificate_subject( classad::ClassAd &job_ad, bool &good );

std::string unparse_certificate_subject( const classad::ClassAd &job_ad, bool &good );

void set_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_type( const classad::ClassAd &job_ad );

void remove_type( classad::ClassAd &job_ad );

std::string unparse_type( const classad::ClassAd &job_ad );

void set_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_type( const classad::ClassAd &job_ad, bool &good );

void remove_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_type( const classad::ClassAd &job_ad, bool &good );

void set_lb_sequence_code( classad::ClassAd &job_ad, const std::string &value );

std::string get_lb_sequence_code( const classad::ClassAd &job_ad );

void remove_lb_sequence_code( classad::ClassAd &job_ad );

std::string unparse_lb_sequence_code( const classad::ClassAd &job_ad );

void set_lb_sequence_code( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_lb_sequence_code( const classad::ClassAd &job_ad, bool &good );

void remove_lb_sequence_code( classad::ClassAd &job_ad, bool &good );

std::string unparse_lb_sequence_code( const classad::ClassAd &job_ad, bool &good );

void set_lrms_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_lrms_type( const classad::ClassAd &job_ad );

void remove_lrms_type( classad::ClassAd &job_ad );

std::string unparse_lrms_type( const classad::ClassAd &job_ad );

void set_lrms_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_lrms_type( const classad::ClassAd &job_ad, bool &good );

void remove_lrms_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_lrms_type( const classad::ClassAd &job_ad, bool &good );

void set_input_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value );

std::string get_input_sandbox_base_uri( const classad::ClassAd &job_ad );

void remove_input_sandbox_base_uri( classad::ClassAd &job_ad );

std::string unparse_input_sandbox_base_uri( const classad::ClassAd &job_ad );

void set_input_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_input_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good );

void remove_input_sandbox_base_uri( classad::ClassAd &job_ad, bool &good );

std::string unparse_input_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good );

void set_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value );

std::string get_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad );

void remove_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad );

std::string unparse_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad );

void set_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good );

void remove_wmpinput_sandbox_base_uri( classad::ClassAd &job_ad, bool &good );

std::string unparse_wmpinput_sandbox_base_uri( const classad::ClassAd &job_ad, bool &good );

void set_output_sandbox_base_dest_uri( classad::ClassAd &job_ad, const std::string &value );

std::string get_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad );

void remove_output_sandbox_base_dest_uri( classad::ClassAd &job_ad );

std::string unparse_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad );

void set_output_sandbox_base_dest_uri( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad, bool &good );

void remove_output_sandbox_base_dest_uri( classad::ClassAd &job_ad, bool &good );

std::string unparse_output_sandbox_base_dest_uri( const classad::ClassAd &job_ad, bool &good );

void set_jdl_original( classad::ClassAd &job_ad, const std::string &value );

std::string get_jdl_original( const classad::ClassAd &job_ad );

void remove_jdl_original( classad::ClassAd &job_ad );

std::string unparse_jdl_original( const classad::ClassAd &job_ad );

void set_jdl_original( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_jdl_original( const classad::ClassAd &job_ad, bool &good );

void remove_jdl_original( classad::ClassAd &job_ad, bool &good );

std::string unparse_jdl_original( const classad::ClassAd &job_ad, bool &good );

void set_delegation_id( classad::ClassAd &job_ad, const std::string &value );

std::string get_delegation_id( const classad::ClassAd &job_ad );

void remove_delegation_id( classad::ClassAd &job_ad );

std::string unparse_delegation_id( const classad::ClassAd &job_ad );

void set_delegation_id( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_delegation_id( const classad::ClassAd &job_ad, bool &good );

void remove_delegation_id( classad::ClassAd &job_ad, bool &good );

std::string unparse_delegation_id( const classad::ClassAd &job_ad, bool &good );

void set_state_id( classad::ClassAd &job_ad, const std::string &value );

std::string get_state_id( const classad::ClassAd &job_ad );

void remove_state_id( classad::ClassAd &job_ad );

std::string unparse_state_id( const classad::ClassAd &job_ad );

void set_state_id( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_state_id( const classad::ClassAd &job_ad, bool &good );

void remove_state_id( classad::ClassAd &job_ad, bool &good );

std::string unparse_state_id( const classad::ClassAd &job_ad, bool &good );

void set_user_data( classad::ClassAd &job_ad, const std::string &value );

std::string get_user_data( const classad::ClassAd &job_ad );

void remove_user_data( classad::ClassAd &job_ad );

std::string unparse_user_data( const classad::ClassAd &job_ad );

void set_user_data( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_user_data( const classad::ClassAd &job_ad, bool &good );

void remove_user_data( classad::ClassAd &job_ad, bool &good );

std::string unparse_user_data( const classad::ClassAd &job_ad, bool &good );

void set_lbaddress( classad::ClassAd &job_ad, const std::string &value );

std::string get_lbaddress( const classad::ClassAd &job_ad );

void remove_lbaddress( classad::ClassAd &job_ad );

std::string unparse_lbaddress( const classad::ClassAd &job_ad );

void set_lbaddress( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_lbaddress( const classad::ClassAd &job_ad, bool &good );

void remove_lbaddress( classad::ClassAd &job_ad, bool &good );

std::string unparse_lbaddress( const classad::ClassAd &job_ad, bool &good );

void set_virtual_organisation( classad::ClassAd &job_ad, const std::string &value );

std::string get_virtual_organisation( const classad::ClassAd &job_ad );

void remove_virtual_organisation( classad::ClassAd &job_ad );

std::string unparse_virtual_organisation( const classad::ClassAd &job_ad );

void set_virtual_organisation( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_virtual_organisation( const classad::ClassAd &job_ad, bool &good );

void remove_virtual_organisation( classad::ClassAd &job_ad, bool &good );

std::string unparse_virtual_organisation( const classad::ClassAd &job_ad, bool &good );

void set_dsupload( classad::ClassAd &job_ad, const std::string &value );

std::string get_dsupload( const classad::ClassAd &job_ad );

void remove_dsupload( classad::ClassAd &job_ad );

std::string unparse_dsupload( const classad::ClassAd &job_ad );

void set_dsupload( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_dsupload( const classad::ClassAd &job_ad, bool &good );

void remove_dsupload( classad::ClassAd &job_ad, bool &good );

std::string unparse_dsupload( const classad::ClassAd &job_ad, bool &good );

void set_output_file( classad::ClassAd &job_ad, const std::string &value );

std::string get_output_file( const classad::ClassAd &job_ad );

void remove_output_file( classad::ClassAd &job_ad );

std::string unparse_output_file( const classad::ClassAd &job_ad );

void set_output_file( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_output_file( const classad::ClassAd &job_ad, bool &good );

void remove_output_file( classad::ClassAd &job_ad, bool &good );

std::string unparse_output_file( const classad::ClassAd &job_ad, bool &good );

void set_logical_file_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_logical_file_name( const classad::ClassAd &job_ad );

void remove_logical_file_name( classad::ClassAd &job_ad );

std::string unparse_logical_file_name( const classad::ClassAd &job_ad );

void set_logical_file_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_logical_file_name( const classad::ClassAd &job_ad, bool &good );

void remove_logical_file_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_logical_file_name( const classad::ClassAd &job_ad, bool &good );

void set_storage_element( classad::ClassAd &job_ad, const std::string &value );

std::string get_storage_element( const classad::ClassAd &job_ad );

void remove_storage_element( classad::ClassAd &job_ad );

std::string unparse_storage_element( const classad::ClassAd &job_ad );

void set_storage_element( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_storage_element( const classad::ClassAd &job_ad, bool &good );

void remove_storage_element( classad::ClassAd &job_ad, bool &good );

std::string unparse_storage_element( const classad::ClassAd &job_ad, bool &good );

void set_hlrlocation( classad::ClassAd &job_ad, const std::string &value );

std::string get_hlrlocation( const classad::ClassAd &job_ad );

void remove_hlrlocation( classad::ClassAd &job_ad );

std::string unparse_hlrlocation( const classad::ClassAd &job_ad );

void set_hlrlocation( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_hlrlocation( const classad::ClassAd &job_ad, bool &good );

void remove_hlrlocation( classad::ClassAd &job_ad, bool &good );

std::string unparse_hlrlocation( const classad::ClassAd &job_ad, bool &good );

void set_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad );

void remove_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad );

std::string unparse_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad );

void set_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad, bool &good );

void remove_glite_wl_ui_dag_node_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_glite_wl_ui_dag_node_name( const classad::ClassAd &job_ad, bool &good );

void set_node_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_node_name( const classad::ClassAd &job_ad );

void remove_node_name( classad::ClassAd &job_ad );

std::string unparse_node_name( const classad::ClassAd &job_ad );

void set_node_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_node_name( const classad::ClassAd &job_ad, bool &good );

void remove_node_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_node_name( const classad::ClassAd &job_ad, bool &good );

void set_file( classad::ClassAd &job_ad, const std::string &value );

std::string get_file( const classad::ClassAd &job_ad );

void remove_file( classad::ClassAd &job_ad );

std::string unparse_file( const classad::ClassAd &job_ad );

void set_file( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_file( const classad::ClassAd &job_ad, bool &good );

void remove_file( classad::ClassAd &job_ad, bool &good );

std::string unparse_file( const classad::ClassAd &job_ad, bool &good );

void set_listener_host( classad::ClassAd &job_ad, const std::string &value );

std::string get_listener_host( const classad::ClassAd &job_ad );

void remove_listener_host( classad::ClassAd &job_ad );

std::string unparse_listener_host( const classad::ClassAd &job_ad );

void set_listener_host( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_listener_host( const classad::ClassAd &job_ad, bool &good );

void remove_listener_host( classad::ClassAd &job_ad, bool &good );

std::string unparse_listener_host( const classad::ClassAd &job_ad, bool &good );

void set_listener_pipe_name( classad::ClassAd &job_ad, const std::string &value );

std::string get_listener_pipe_name( const classad::ClassAd &job_ad );

void remove_listener_pipe_name( classad::ClassAd &job_ad );

std::string unparse_listener_pipe_name( const classad::ClassAd &job_ad );

void set_listener_pipe_name( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_listener_pipe_name( const classad::ClassAd &job_ad, bool &good );

void remove_listener_pipe_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_listener_pipe_name( const classad::ClassAd &job_ad, bool &good );

void set_perusal_files_dest_uri( classad::ClassAd &job_ad, const std::string &value );

std::string get_perusal_files_dest_uri( const classad::ClassAd &job_ad );

void remove_perusal_files_dest_uri( classad::ClassAd &job_ad );

std::string unparse_perusal_files_dest_uri( const classad::ClassAd &job_ad );

void set_perusal_files_dest_uri( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_perusal_files_dest_uri( const classad::ClassAd &job_ad, bool &good );

void remove_perusal_files_dest_uri( classad::ClassAd &job_ad, bool &good );

std::string unparse_perusal_files_dest_uri( const classad::ClassAd &job_ad, bool &good );

void set_job_provenance( classad::ClassAd &job_ad, const std::string &value );

std::string get_job_provenance( const classad::ClassAd &job_ad );

void remove_job_provenance( classad::ClassAd &job_ad );

std::string unparse_job_provenance( const classad::ClassAd &job_ad );

void set_job_provenance( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_job_provenance( const classad::ClassAd &job_ad, bool &good );

void remove_job_provenance( classad::ClassAd &job_ad, bool &good );

std::string unparse_job_provenance( const classad::ClassAd &job_ad, bool &good );

void set_mw_version( classad::ClassAd &job_ad, const std::string &value );

std::string get_mw_version( const classad::ClassAd &job_ad );

void remove_mw_version( classad::ClassAd &job_ad );

std::string unparse_mw_version( const classad::ClassAd &job_ad );

void set_mw_version( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_mw_version( const classad::ClassAd &job_ad, bool &good );

void remove_mw_version( classad::ClassAd &job_ad, bool &good );

std::string unparse_mw_version( const classad::ClassAd &job_ad, bool &good );

void set_output_data( classad::ClassAd &job_ad, const classad::ExprTree *value );

classad::ExprTree *get_output_data( const classad::ClassAd &job_ad );

void remove_output_data( classad::ClassAd &job_ad );

std::string unparse_output_data( const classad::ClassAd &job_ad );

void set_output_data( classad::ClassAd &job_ad, const classad::ExprTree *value, bool &good );

classad::ExprTree *get_output_data( const classad::ClassAd &job_ad, bool &good );

void remove_output_data( classad::ClassAd &job_ad, bool &good );

std::string unparse_output_data( const classad::ClassAd &job_ad, bool &good );

void set_user_tags( classad::ClassAd &job_ad, const classad::ExprTree *value );

classad::ExprTree *get_user_tags( const classad::ClassAd &job_ad );

void remove_user_tags( classad::ClassAd &job_ad );

std::string unparse_user_tags( const classad::ClassAd &job_ad );

void set_user_tags( classad::ClassAd &job_ad, const classad::ExprTree *value, bool &good );

classad::ExprTree *get_user_tags( const classad::ClassAd &job_ad, bool &good );

void remove_user_tags( classad::ClassAd &job_ad, bool &good );

std::string unparse_user_tags( const classad::ClassAd &job_ad, bool &good );

void set_data_requirements( classad::ClassAd &job_ad, const classad::ExprTree *value );

classad::ExprTree *get_data_requirements( const classad::ClassAd &job_ad );

void remove_data_requirements( classad::ClassAd &job_ad );

std::string unparse_data_requirements( const classad::ClassAd &job_ad );

void set_data_requirements( classad::ClassAd &job_ad, const classad::ExprTree *value, bool &good );

classad::ExprTree *get_data_requirements( const classad::ClassAd &job_ad, bool &good );

void remove_data_requirements( classad::ClassAd &job_ad, bool &good );

std::string unparse_data_requirements( const classad::ClassAd &job_ad, bool &good );

void set_data_catalog_type( classad::ClassAd &job_ad, const std::string &value );

std::string get_data_catalog_type( const classad::ClassAd &job_ad );

void remove_data_catalog_type( classad::ClassAd &job_ad );

std::string unparse_data_catalog_type( const classad::ClassAd &job_ad );

void set_data_catalog_type( classad::ClassAd &job_ad, const std::string &value, bool &good );

std::string get_data_catalog_type( const classad::ClassAd &job_ad, bool &good );

void remove_data_catalog_type( classad::ClassAd &job_ad, bool &good );

std::string unparse_data_catalog_type( const classad::ClassAd &job_ad, bool &good );

void set_output_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_output_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_output_sandbox( classad::ClassAd &job_ad );

std::string unparse_output_sandbox( const classad::ClassAd &job_ad );

void set_output_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_output_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_output_sandbox( classad::ClassAd &job_ad, bool &good );

std::string unparse_output_sandbox( const classad::ClassAd &job_ad, bool &good );

void set_output_sandbox_dest_uri( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_output_sandbox_dest_uri( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_output_sandbox_dest_uri( classad::ClassAd &job_ad );

std::string unparse_output_sandbox_dest_uri( const classad::ClassAd &job_ad );

void set_output_sandbox_dest_uri( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_output_sandbox_dest_uri( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_output_sandbox_dest_uri( classad::ClassAd &job_ad, bool &good );

std::string unparse_output_sandbox_dest_uri( const classad::ClassAd &job_ad, bool &good );

void set_input_sandbox_dest_file_name( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_input_sandbox_dest_file_name( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_input_sandbox_dest_file_name( classad::ClassAd &job_ad );

std::string unparse_input_sandbox_dest_file_name( const classad::ClassAd &job_ad );

void set_input_sandbox_dest_file_name( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_input_sandbox_dest_file_name( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_input_sandbox_dest_file_name( classad::ClassAd &job_ad, bool &good );

std::string unparse_input_sandbox_dest_file_name( const classad::ClassAd &job_ad, bool &good );

void set_input_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_input_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_input_sandbox( classad::ClassAd &job_ad );

std::string unparse_input_sandbox( const classad::ClassAd &job_ad );

void set_input_sandbox( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_input_sandbox( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_input_sandbox( classad::ClassAd &job_ad, bool &good );

std::string unparse_input_sandbox( const classad::ClassAd &job_ad, bool &good );

void set_environment( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_environment( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_environment( classad::ClassAd &job_ad );

std::string unparse_environment( const classad::ClassAd &job_ad );

void set_environment( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_environment( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_environment( classad::ClassAd &job_ad, bool &good );

std::string unparse_environment( const classad::ClassAd &job_ad, bool &good );

void set_input_data( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_input_data( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_input_data( classad::ClassAd &job_ad );

std::string unparse_input_data( const classad::ClassAd &job_ad );

void set_input_data( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_input_data( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_input_data( classad::ClassAd &job_ad, bool &good );

std::string unparse_input_data( const classad::ClassAd &job_ad, bool &good );

void set_data_access_protocol( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_data_access_protocol( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_data_access_protocol( classad::ClassAd &job_ad );

std::string unparse_data_access_protocol( const classad::ClassAd &job_ad );

void set_data_access_protocol( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_data_access_protocol( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_data_access_protocol( classad::ClassAd &job_ad, bool &good );

std::string unparse_data_access_protocol( const classad::ClassAd &job_ad, bool &good );

void set_data_catalog( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_data_catalog( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_data_catalog( classad::ClassAd &job_ad );

std::string unparse_data_catalog( const classad::ClassAd &job_ad );

void set_data_catalog( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_data_catalog( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_data_catalog( classad::ClassAd &job_ad, bool &good );

std::string unparse_data_catalog( const classad::ClassAd &job_ad, bool &good );

void set_storage_index( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_storage_index( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_storage_index( classad::ClassAd &job_ad );

std::string unparse_storage_index( const classad::ClassAd &job_ad );

void set_storage_index( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_storage_index( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_storage_index( classad::ClassAd &job_ad, bool &good );

std::string unparse_storage_index( const classad::ClassAd &job_ad, bool &good );

void set_significant_attributes( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_significant_attributes( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_significant_attributes( classad::ClassAd &job_ad );

std::string unparse_significant_attributes( const classad::ClassAd &job_ad );

void set_significant_attributes( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_significant_attributes( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_significant_attributes( classad::ClassAd &job_ad, bool &good );

std::string unparse_significant_attributes( const classad::ClassAd &job_ad, bool &good );

void set_step_weight( classad::ClassAd &job_ad, const std::vector<int> &l );

void get_step_weight( const classad::ClassAd &job_ad, std::vector<int> &l );

void remove_step_weight( classad::ClassAd &job_ad );

std::string unparse_step_weight( const classad::ClassAd &job_ad );

void set_step_weight( classad::ClassAd &job_ad, const std::vector<int> &l, bool &good );

void get_step_weight( const classad::ClassAd &job_ad, std::vector<int> &l, bool &good );

void remove_step_weight( classad::ClassAd &job_ad, bool &good );

std::string unparse_step_weight( const classad::ClassAd &job_ad, bool &good );

void set_prejob( classad::ClassAd &job_ad, const classad::ClassAd *value );

classad::ClassAd *get_prejob( const classad::ClassAd &job_ad );

void remove_prejob( classad::ClassAd &job_ad );

std::string unparse_prejob( const classad::ClassAd &job_ad );

void set_prejob( classad::ClassAd &job_ad, const classad::ClassAd *value, bool &good );

classad::ClassAd *get_prejob( const classad::ClassAd &job_ad, bool &good );

void remove_prejob( classad::ClassAd &job_ad, bool &good );

std::string unparse_prejob( const classad::ClassAd &job_ad, bool &good );

void set_postjob( classad::ClassAd &job_ad, const classad::ClassAd *value );

classad::ClassAd *get_postjob( const classad::ClassAd &job_ad );

void remove_postjob( classad::ClassAd &job_ad );

std::string unparse_postjob( const classad::ClassAd &job_ad );

void set_postjob( classad::ClassAd &job_ad, const classad::ClassAd *value, bool &good );

classad::ClassAd *get_postjob( const classad::ClassAd &job_ad, bool &good );

void remove_postjob( classad::ClassAd &job_ad, bool &good );

std::string unparse_postjob( const classad::ClassAd &job_ad, bool &good );

void set_job_state( classad::ClassAd &job_ad, const classad::ClassAd *value );

classad::ClassAd *get_job_state( const classad::ClassAd &job_ad );

void remove_job_state( classad::ClassAd &job_ad );

std::string unparse_job_state( const classad::ClassAd &job_ad );

void set_job_state( classad::ClassAd &job_ad, const classad::ClassAd *value, bool &good );

classad::ClassAd *get_job_state( const classad::ClassAd &job_ad, bool &good );

void remove_job_state( classad::ClassAd &job_ad, bool &good );

std::string unparse_job_state( const classad::ClassAd &job_ad, bool &good );

void set_ces( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_ces( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void remove_ces( classad::ClassAd &job_ad );

std::string unparse_ces( const classad::ClassAd &job_ad );

void set_ces( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_ces( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );

void remove_ces( classad::ClassAd &job_ad, bool &good );

std::string unparse_ces( const classad::ClassAd &job_ad, bool &good );



void set_job_steps( classad::ClassAd &job_ad, const std::vector<std::string> &l );

void get_job_steps( const classad::ClassAd &job_ad, std::vector<std::string> &l );

void set_job_steps( classad::ClassAd &job_ad, const std::vector<std::string> &l, bool &good );

void get_job_steps( const classad::ClassAd &job_ad, std::vector<std::string> &l, bool &good );


} // namespace jdl
} // namespace glite

#endif

// Local Variables:
// mode: c++
// End:
