#include "../include/operation_deserialization.h"
#include <stdlib.h>
#include <string.h>
#include <serialization_interface.h>
#include <serializable_objects.h>
#include <garbage_collector.h>
#include <commons/string.h>

t_request* deserialize(void* serialized_request){
    uint32_t operation;
    void* serialized_structure;
    uint32_t serialized_structure_size;

    int offset = 0;

    memcpy(&operation, serialized_request + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&serialized_structure_size, serialized_request + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    serialized_structure = safe_malloc(serialized_structure_size);
    memcpy(serialized_structure, serialized_request + offset, serialized_structure_size);

    t_serializable_object* serializable_object = serializable_object_with_code(operation);
    t_request* request = (*(serializable_object -> deserialize_function)) (serialized_structure);

    free(serialized_structure);
    return request;
}

t_request* deserialize_new_pokemon(void* serialized_structure) {

    uint32_t pokemon_name_length;
    char* pokemon_name;
    uint32_t pos_x;
    uint32_t pos_y;
    uint32_t quantity;

    uint32_t offset = 0;

    memcpy(&pokemon_name_length, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    uint32_t pokemon_name_length_including_with_trailing_null = pokemon_name_length + 2;
    pokemon_name = calloc(pokemon_name_length_including_with_trailing_null, sizeof(char));
    memcpy(pokemon_name, serialized_structure + offset, pokemon_name_length);
    offset += pokemon_name_length;
    memcpy(&pos_x, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&pos_y, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&quantity, serialized_structure + offset, sizeof(uint32_t));

    string_append(&pokemon_name, "\0");
    t_new_pokemon* new_pokemon = safe_malloc(sizeof(t_new_pokemon));
    new_pokemon -> pokemon_name = pokemon_name;
    new_pokemon -> pos_x = pos_x;
    new_pokemon -> pos_y = pos_y;
    new_pokemon -> quantity = quantity;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = NEW_POKEMON;
    request -> structure = (void*) new_pokemon;
    request -> sanitizer_function = free;

    consider_as_garbage(pokemon_name, free);
    return request;
}

t_request* deserialize_appeared_pokemon(void* serialized_structure) {

    uint32_t pokemon_name_length;
    char* pokemon_name;
    uint32_t pos_x;
    uint32_t pos_y;

    uint32_t offset = 0;

    memcpy(&pokemon_name_length, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    uint32_t pokemon_name_length_including_with_trailing_null = pokemon_name_length + 2;
    pokemon_name = calloc(pokemon_name_length_including_with_trailing_null, sizeof(char));
    memcpy(pokemon_name, serialized_structure + offset, pokemon_name_length);
    offset += pokemon_name_length;
    memcpy(&pos_x, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&pos_y, serialized_structure + offset, sizeof(uint32_t));

    string_append(&pokemon_name, "\0");
    t_appeared_pokemon* appeared_pokemon = safe_malloc(sizeof(t_appeared_pokemon));
    appeared_pokemon -> pokemon_name = pokemon_name;
    appeared_pokemon -> pos_x = pos_x;
    appeared_pokemon -> pos_y = pos_y;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = APPEARED_POKEMON;
    request -> structure = (void*) appeared_pokemon;
    request -> sanitizer_function = free;

    consider_as_garbage(pokemon_name, free);
    return request;
}

t_request* deserialize_get_pokemon(void* serialized_structure){
    //Mensaje GET envia unicamente el pokemon
    uint32_t pokemon_name_length;
    char* pokemon_name;
    uint32_t offset = 0;

    memcpy(&pokemon_name_length, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    uint32_t pokemon_name_length_including_with_trailing_null = pokemon_name_length + 2;
    pokemon_name = calloc(pokemon_name_length_including_with_trailing_null, sizeof(char));
    memcpy(pokemon_name, serialized_structure + offset, pokemon_name_length);

    string_append(&pokemon_name, "\0");
    t_get_pokemon* get_pokemon = safe_malloc(sizeof(t_get_pokemon));
    get_pokemon -> pokemon_name = pokemon_name;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = GET_POKEMON;
    request -> structure = (void*) get_pokemon;
    request -> sanitizer_function = free;

    consider_as_garbage(pokemon_name, free);
    return request;
}

t_request* deserialize_localized_pokemon(void* serialized_structure){
    uint32_t pokemon_name_length;
    char* pokemon_name;
    uint32_t quantity;
    t_list* positions = list_create();
    uint32_t offset = 0;

    memcpy(&pokemon_name_length, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    uint32_t pokemon_name_length_including_with_trailing_null = pokemon_name_length + 2;
    pokemon_name = calloc(pokemon_name_length_including_with_trailing_null, sizeof(char));
    memcpy(pokemon_name, serialized_structure + offset, pokemon_name_length);
    offset += pokemon_name_length;
    memcpy(&quantity, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    for(int i = 0; i < quantity * 2; i++){
        uint32_t* position = safe_malloc(sizeof(uint32_t));
        memcpy(position, serialized_structure + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);

        list_add(positions, (void *) position);
    }

    string_append(&pokemon_name, "\0");
    t_localized_pokemon* localized_pokemon = safe_malloc(sizeof(t_localized_pokemon));
    localized_pokemon -> pokemon_name = pokemon_name;
    localized_pokemon -> quantity = quantity;
    localized_pokemon -> positions = positions;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = LOCALIZED_POKEMON;
    request -> structure = (void*) localized_pokemon;
    request -> sanitizer_function = (void (*)(void *)) free_localized_pokemon;

    consider_as_garbage(pokemon_name, free);
    return request;
}

t_request* deserialize_catch_pokemon(void* serialized_structure) {

    uint32_t pokemon_name_length;
    char* pokemon_name;
    uint32_t pos_x;
    uint32_t pos_y;

    uint32_t offset = 0;

    memcpy(&pokemon_name_length, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    uint32_t pokemon_name_length_including_with_trailing_null = pokemon_name_length + 2;
    pokemon_name = calloc(pokemon_name_length_including_with_trailing_null, sizeof(char));
    memcpy(pokemon_name, serialized_structure + offset, pokemon_name_length);
    offset += pokemon_name_length;
    memcpy(&pos_x, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&pos_y, serialized_structure + offset, sizeof(uint32_t));

    string_append(&pokemon_name, "\0");
    t_catch_pokemon* catch_pokemon = safe_malloc(sizeof(t_catch_pokemon));
    catch_pokemon -> pokemon_name = pokemon_name;
    catch_pokemon -> pos_x = pos_x;
    catch_pokemon -> pos_y = pos_y;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = CATCH_POKEMON;
    request -> structure = (void*) catch_pokemon;
    request -> sanitizer_function = free;

    consider_as_garbage(pokemon_name, free);
    return request;
}

t_request* deserialize_caught_pokemon(void* serialized_structure){

    uint32_t caught_status;    // 0/1 - FAIL/OK
    uint32_t offset = 0;

    memcpy(&caught_status, serialized_structure + offset, sizeof(uint32_t));

    t_caught_pokemon* caught_pokemon = safe_malloc(sizeof(t_caught_pokemon));
    caught_pokemon->caught_status = caught_status;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = CAUGHT_POKEMON;
    request -> structure = (void*) caught_pokemon;
    request -> sanitizer_function = free;

    return request;
}

t_request* deserialize_subscribe_me(void* serialized_structure){

    uint32_t operation_queue;
    uint32_t process_description_length;
    char* process_description;

    uint32_t offset = 0;

    memcpy(&operation_queue, serialized_structure, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&process_description_length, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    uint32_t process_description_length_with_trailing_null = process_description_length + 2;
    process_description = calloc(process_description_length_with_trailing_null, sizeof(char));
    memcpy(process_description, serialized_structure + offset, process_description_length);

    string_append(&process_description, "\0");
    t_subscribe_me* subscribe_me = safe_malloc(sizeof(t_subscribe_me));
    subscribe_me -> operation_queue = operation_queue;
    subscribe_me -> process_description = process_description;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = SUBSCRIBE_ME;
    request -> structure = subscribe_me;
    request -> sanitizer_function = (void (*)(void *)) free_subscribe_me;

    return request;
}

t_request* deserialize_identified_message(void* serialized_structure){

    uint32_t message_id;
    uint32_t request_serialization_information_amount_of_bytes;
    void *serialized_request;

    uint32_t offset = 0;

    memcpy(&message_id, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&request_serialization_information_amount_of_bytes, serialized_structure + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    serialized_request = safe_malloc(request_serialization_information_amount_of_bytes);

    memcpy(serialized_request, serialized_structure + offset, request_serialization_information_amount_of_bytes);

    t_request* internal_request = deserialize(serialized_request);

    t_identified_message* identified_message = safe_malloc(sizeof(t_identified_message));
    identified_message -> message_id = message_id;
    identified_message -> request = internal_request;

    t_request* request = safe_malloc(sizeof(t_request));
    request -> operation = IDENTIFIED_MESSAGE;
    request -> structure = (void*) identified_message;
    request -> sanitizer_function = (void (*)(void *)) free_identified_message;

    free(serialized_request);
    return request;
}