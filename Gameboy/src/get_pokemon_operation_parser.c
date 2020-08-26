#include <get_pokemon_operation_parser.h>
#include <stdlib.h>
#include "../../Utils/include/serializable_objects.h"

t_pokemon_operation_parser* get_pokemon_parser;

bool get_pokemon_can_handle(uint32_t operation_code){
    return operation_code == GET_POKEMON;
}

void* get_pokemon_parse_function(char** arguments){
    t_get_pokemon* get_pokemon = safe_malloc(sizeof(t_get_pokemon));
    get_pokemon -> pokemon_name = arguments[0];

    if(get_pokemon_parser -> should_build_identified_message){
        t_request* request = safe_malloc(sizeof(t_request));
        request -> operation = GET_POKEMON;
        request -> structure = (void*) get_pokemon;
        request -> sanitizer_function = free;

        t_identified_message* identified_message = safe_malloc(sizeof(t_identified_message));
        identified_message -> message_id = atoi(arguments[1]);
        identified_message -> request = request;

        return identified_message;
    }

    return get_pokemon;
}

void initialize_get_pokemon_operation_parser_with(bool should_build_identified_message){
    get_pokemon_parser = safe_malloc(sizeof(t_pokemon_operation_parser));
    get_pokemon_parser -> can_handle_function = get_pokemon_can_handle;
    get_pokemon_parser -> parse_function = get_pokemon_parse_function;
    get_pokemon_parser -> should_build_identified_message = should_build_identified_message;
}

t_pokemon_operation_parser* get_pokemon_operation_parser(){
    return get_pokemon_parser;
}