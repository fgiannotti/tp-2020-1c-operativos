#ifndef DELIBIRD_OPERATION_SERIALIZATION_H
#define DELIBIRD_OPERATION_SERIALIZATION_H

#include "serialization_interface.h"

t_serialization_information* serialize_appeared_pokemon(void* structure);
t_serialization_information* serialize_new_pokemon(void* structure);
t_serialization_information* serialize_catch_pokemon(void* structure);
t_serialization_information* serialize_caught_pokemon(void* structure);
t_serialization_information* serialize_get_pokemon(void* structure);
t_serialization_information* serialize_localized_pokemon(void* structure);
t_serialization_information* serialize_subscribe_me(void* structure);
t_serialization_information* serialize_identified_message(void* structure);


#endif //DELIBIRD_OPERATION_SERIALIZATION_H