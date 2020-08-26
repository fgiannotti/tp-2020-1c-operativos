#ifndef DELIBIRD_TRAINER_THREAD_CONTEXT_STATE_CHAINED_EVALUATION_H
#define DELIBIRD_TRAINER_THREAD_CONTEXT_STATE_CHAINED_EVALUATION_H

#include "trainer_threads.h"
#include "../../Utils/include/chained_evaluation.h"

void initialize_trainer_thread_context_state_chained_evaluation();

void trainer_thread_context_state_chained_evaluation_value_when_caught_success_for(t_trainer_thread_context* trainer_thread_context);
void trainer_thread_context_state_chained_evaluation_value_when_caught_failed_for(t_trainer_thread_context* trainer_thread_context);

void free_trainer_thread_context_state_chained_evaluation();

#endif //DELIBIRD_TRAINER_THREAD_CONTEXT_STATE_CHAINED_EVALUATION_H
