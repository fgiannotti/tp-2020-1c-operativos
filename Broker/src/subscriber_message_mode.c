#include <messages_roles.h>
#include <subscriber.h>
#include <subscriber_context_provider.h>
#include <stdlib.h>
#include "../include/subscriber_message_mode.h"
#include "../../Utils/include/queue_code_name_associations.h"
#include "../../Utils/include/socket.h"
#include "../../Utils/include/garbage_collector.h"

t_message_role* subscriber_message_mode;

t_message_role* subscriber_mode(){
    return subscriber_message_mode;
}

bool subscriber_mode_can_handle(uint32_t operation){
    return operation == SUBSCRIBE_ME;
}

void subscriber_mode_attending_message_function(t_connection_request* connection_request){
    t_subscribe_me* subscribe_me = (t_subscribe_me*) (connection_request -> request) -> structure;
    t_subscriber_context* subscriber_context =
            create_subscriber_context(connection_request -> socket_fd, subscribe_me);

    subscribe_client_to_queue(subscriber_context);
    send_ack_message(true, connection_request -> socket_fd);
    send_all_messages(subscriber_context);

    consider_as_garbage(connection_request -> request, (void (*)(void *)) free_request);
    free(connection_request);
}

void initialize_subscriber_message_mode(){
    subscriber_message_mode = safe_malloc(sizeof(t_message_role));
    subscriber_message_mode -> can_handle_function  = subscriber_mode_can_handle;
    subscriber_message_mode -> attending_message_function = subscriber_mode_attending_message_function;
}