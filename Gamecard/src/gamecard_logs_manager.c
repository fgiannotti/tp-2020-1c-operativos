#include "../include/gamecard_logs_manager.h"
#include "../../Utils/include/logger.h"
#include <commons/string.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void initialize_gamecard_logs_manager(){
    initialize_logger_for("Gamecard");
    create_main_logger();
    create_process_execution_logger();
}

void log_initiating_communication_retry_process_with_broker_from_gamecard(){
    char* message = "Inicio del proceso de reintento de comunicación con el Broker.";
    log_succesful_message(main_logger(), message);
    log_succesful_message(process_execution_logger(), message);
}

void log_succesful_retry_of_communication_with_broker_from_gamecard(){
    char* message = "El proceso de reintento de comunicación con el Broker ha sido exitoso.";
    log_succesful_message(main_logger(), message);
    log_succesful_message(process_execution_logger(), message);
}

void log_failed_attempt_to_communicate_with_broker_from_gamecard(char* default_action){
    char* message = string_from_format("Falló la comunicación con Broker. Por defecto, %s.", default_action);
    log_errorful_message(main_logger(), message);
    log_errorful_message(process_execution_logger(), message);
    free(message);
}

void log_failed_retry_of_communication_with_broker_from_gamecard(){
    char* message = "Falló el reintento de comunicación con el Broker.";
    log_errorful_message(main_logger(), message);
    log_errorful_message(process_execution_logger(), message);
};

void log_thread_sleep_time_configuration_error_from_gamecard(){
    char* message = string_new();
    string_append(&message, "Se produjo un error al intentar dormir el hilo: ");
    string_append(&message, strerror(errno));

    log_errorful_message(main_logger(), message);
    log_errorful_message(process_execution_logger(), message);

    free(message);
    free_gamecard_logs_manager();
    exit(EXIT_FAILURE);
} //es identico al de team, se podria pasar a Utils

void log_queue_thread_create_error_from_gamecard(){
    char* message = string_new();
    string_append(&message, "Falló la creación del hilo para escuchar una cola del Broker: ");
    string_append(&message, strerror(errno));

    log_errorful_message(process_execution_logger(), message);

    free(message);
    free_gamecard_logs_manager();
    exit(EXIT_FAILURE);
}

void log_invalid_operation_to_query_performer_from_gamecard(uint32_t operation){
    char* message = string_from_format("No se ha encontrado un query performer que maneje operaciones de código %u", operation);
    log_errorful_message(process_execution_logger(), message);
    free(message);
}

void log_query_performer_not_found_error_from_gamecard_for(uint32_t operation){
    char* message = string_from_format("No se ha encontrado un query performer que maneje operaciones de código %u", operation);
    log_errorful_message(process_execution_logger(), message);
    free(message);
}

void free_gamecard_logs_manager(){
    free_loggers();
}