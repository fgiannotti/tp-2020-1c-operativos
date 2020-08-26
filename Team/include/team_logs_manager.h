#ifndef DELIBIRD_TEAM_LOGS_MANAGER_H
#define DELIBIRD_TEAM_LOGS_MANAGER_H

#include <stdint.h>
#include "team_manager.h"
#include "trainer_threads.h"

void initialize_team_logs_manager();
void log_failed_attempt_to_communicate_with_broker(char* default_action);
void log_initiating_communication_retry_process_with_broker();
void log_failed_retry_of_communication_with_broker();
void log_succesful_retry_of_communication_with_broker();
void log_thread_sleep_time_configuration_error();
void log_queue_thread_create_error();
void log_no_locations_found_for(char* pokemon_name);
void log_query_performer_not_found_error_for(uint32_t operation);
void log_trainer_thread_create_error();
void log_succesful_creation_of_thread_of_trainer(uint32_t sequential_number);
void log_no_schedulable_threads_available_for(char* pokemon_name);
void log_trainer_thread_context_not_found_error_for(uint32_t sequential_number);
void log_scheduling_algorithm_not_found_error_for(char* scheduling_algorithm_name);
void log_pokemon_not_belonging_to_global_goal_error_for(char* pokemon_name);
void log_targetable_pokemon_not_found_error_for(t_localizable_object* localizable_pokemon);
void log_trainer_added_to_new(t_localizable_object* localizable_trainer);
void log_trainer_schedule(t_localizable_object* localizable_trainer, char* reason);
void log_trainer_movement(t_localizable_object* localizable_trainer);
void log_trainer_execution(t_localizable_object* localizable_trainer, char* reason);
void log_trainer_blocked(t_trainer_thread_context* trainer_thread_context);
void log_trainer_has_accomplished_own_goal(t_localizable_object* localizable_trainer);
void log_unknown_thread_action_type_error();
void log_thread_action_to_perform_by(t_trainer_thread_context* trainer_thread_context);
void log_failed_caught_of(t_localizable_object* localizable_pokemon);
void log_succesfully_caught(t_localizable_object* localizable_pokemon);
void log_succesfully_caught_due_to_failed_communication_with_broker(t_localizable_object* localizable_pokemon);
void log_expected_to_be_empty_error_for(uint32_t state);
void log_expected_to_be_not_empty_error_for(uint32_t state);
void log_message_id_not_required(uint32_t queue_code, uint32_t message_id);
void log_not_matching_trainers_amount_with_finished_thread_contexts_amount_on_global_goal_accomplished_error();
void log_appeared_pokemon_not_necessary_for_global_goal(char* pokemon_name);
void log_global_goal_not_consistent_with_trainers_requirements_error();
void log_invalid_transition_error();
void log_invalid_state_error();
void log_more_than_one_trainer_thread_context_executing_error_for(t_list* trainer_thread_contexts);
void log_not_matching_pokemon_name_between_get_and_localized_error(char* get_response_pokemon_name, char* localized_pokemon_name);
void log_message_ignored_due_to_previous_existing_occurrences_for(t_localized_pokemon* localized_pokemon);
void log_global_goal_accomplished();

void free_team_logs_manager();

#endif //DELIBIRD_TEAM_LOGS_MANAGER_H
