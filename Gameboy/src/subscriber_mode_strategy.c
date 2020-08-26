#include "../include/subscriber_mode_strategy.h"
#include "../include/entry_point_validator.h"

t_role_mode* subscriber_role_mode_strategy;

bool subscriber_can_handle(uint32_t process_code){
    return process_code == SUSCRIPTOR;
}

char* subscriber_process_name_for_connection(){
    return broker_process_name();
}

void initialize_subscriber_mode_strategy(){
    subscriber_role_mode_strategy = safe_malloc(sizeof(t_role_mode));
    subscriber_role_mode_strategy -> can_handle_function = subscriber_can_handle;
    subscriber_role_mode_strategy -> is_valid_operation_function = is_valid_subscriber_operation;
    subscriber_role_mode_strategy -> pokemon_operation_structure_function = subscriber_pokemon_operation_structure;
    subscriber_role_mode_strategy -> process_name_for_connection = subscriber_process_name_for_connection();
    subscriber_role_mode_strategy -> is_subscriber_mode = true;
}

t_role_mode* subscriber_mode_strategy(){
    return subscriber_role_mode_strategy;
}