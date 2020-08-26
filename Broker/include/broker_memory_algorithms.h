#ifndef DELIBIRD_BROKER_MEMORY_ALGORITHMS_H
#define DELIBIRD_BROKER_MEMORY_ALGORITHMS_H

void initialize_broker_memory_algorithms();
t_message_allocator* initialize_message_allocator();

void* get_available_partition_search_algorithm();
void* get_partition_free_algorithm();
void memory_compaction_algorithm();


#endif //DELIBIRD_BROKER_MEMORY_ALGORITHMS_H
