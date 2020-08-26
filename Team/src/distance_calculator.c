#include "distance_calculator.h"
#include <stdlib.h>

uint32_t distance_between(t_localizable_object* localizable_object, t_localizable_object* another_localizable_object){
    uint32_t x_distance = abs(localizable_object -> pos_x - another_localizable_object -> pos_x);
    uint32_t y_distance = abs(localizable_object -> pos_y - another_localizable_object -> pos_y);

    return x_distance + y_distance;
}

void* closest_trainer_thread_context_to(t_trainer_thread_context* trainer_thread_context,
                                        t_trainer_thread_context* another_trainer_thread_context,
                                        t_localizable_object* pokemon){

    uint32_t trainer_distance = distance_between(trainer_thread_context -> localizable_trainer, pokemon);
    uint32_t another_trainer_distance = distance_between(another_trainer_thread_context -> localizable_trainer, pokemon);

    return trainer_distance < another_trainer_distance ? trainer_thread_context : another_trainer_thread_context;
}

t_trainer_thread_context* trainer_thread_context_closest_to(t_list* trainer_thread_contexts, t_localizable_object* localizable_pokemon){

    t_trainer_thread_context* seed_trainer_thread_context = list_get(trainer_thread_contexts, 0);

    void* _closest_trainer_thread_context(void* trainer_thread_context, void* another_trainer_thread_context){
        return closest_trainer_thread_context_to(trainer_thread_context, another_trainer_thread_context, localizable_pokemon);
    }

    return list_fold(trainer_thread_contexts, seed_trainer_thread_context, _closest_trainer_thread_context);
}

void* closest_targetable_pokemon_to_trainer(t_targetable_object* targetable_pokemon,
                                    t_targetable_object* another_targetable_pokemon,
                                    t_localizable_object* localizable_trainer){

    t_localizable_object* localizable_pokemon = targetable_pokemon -> localizable_pokemon;
    t_localizable_object* another_localizable_pokemon = another_targetable_pokemon -> localizable_pokemon;

    uint32_t localizable_pokemon_distance = distance_between(localizable_pokemon, localizable_trainer);
    uint32_t another_localizable_pokemon_distance = distance_between(another_localizable_pokemon, localizable_trainer);

    return localizable_pokemon_distance < another_localizable_pokemon_distance ? targetable_pokemon : another_targetable_pokemon;
}

t_targetable_object* closest_targetable_pokemon(t_list* targetable_pokemons, t_localizable_object* localizable_trainer){

    t_targetable_object* seed_targetable_pokemon = list_get(targetable_pokemons, 0);

    void* _closest_targetable_pokemon_to(void* targetable_pokemon, void* another_targetable_pokemon){
        return closest_targetable_pokemon_to_trainer(targetable_pokemon, another_targetable_pokemon, localizable_trainer);
    }

    return list_fold(targetable_pokemons, seed_targetable_pokemon, _closest_targetable_pokemon_to);
}