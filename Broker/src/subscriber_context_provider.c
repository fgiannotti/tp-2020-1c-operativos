#include "subscriber_context_provider.h"

t_subscriber_context* create_subscriber_context(int socket_fd, t_subscribe_me* subscribe_me){

    t_subscriber_context* subscriber_context = safe_malloc(sizeof(t_subscriber_context));
    subscriber_context -> operation_queue = subscribe_me -> operation_queue;
    subscriber_context -> socket_fd = socket_fd;
    subscriber_context -> process_description = subscribe_me -> process_description;
    subscriber_context -> last_message_id_received = 0; //lo inicializo en 0 por las dudas de que hayan problemas si no lo inicializo ahora.
    subscriber_context -> is_connection_active = true;

    return  subscriber_context;
}

bool has_active_connection(t_subscriber_context* subscriber_context){
    return subscriber_context -> is_connection_active;
}

void set_inactive_connection_for(t_subscriber_context* subscriber_context){
    subscriber_context -> is_connection_active = false;
}