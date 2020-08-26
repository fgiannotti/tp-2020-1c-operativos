#include "../include/broker_memory_manager.h"
#include "../../Utils/include/configuration_manager.h"
#include <commons/string.h>
#include <broker_memory_algorithms.h>
#include <broker_logs_manager.h>
#include <cache_information_builder.h>
#include <stdlib.h>

t_message_allocator* message_allocator;
t_list* blocks_information;

t_block_information* initialize_first_block_information(){
    uint32_t memory_size = config_get_int_at("TAMANO_MEMORIA");

    t_block_information* initial_block_information = safe_malloc(sizeof(t_block_information));
    initial_block_information->is_free = true;
    initial_block_information->block_size = memory_size;
    initial_block_information->initial_position = safe_malloc(memory_size);
    initial_block_information->memory_block = NULL;

    return initial_block_information;
}

void initialize_broker_memory_manager(){

    initialize_broker_memory_algorithms();
    message_allocator = initialize_message_allocator();

    t_block_information* initial_block_information = initialize_first_block_information();

    blocks_information = list_create();
    list_add(blocks_information,(void*) initial_block_information);

    log_successful_initialize_broker_memory_manager();
}

void allocate_message(t_identified_message* message){
    message_allocator->allocate_message_function (message,blocks_information);
}

char* dump_cache(){
    return cache_information_builder(blocks_information);
}
void free_broker_memory_manager(){
    list_destroy_and_destroy_elements(blocks_information,(void (*)(void *)) free);
    free(message_allocator);
}