#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "clib_openiap.h"

// Default workitem queue
const char* DEFAULT_WIQ = "test2queue";

// Queue event callback: reply with JSON {"message":"hello", "dt": timestamp}
const char* queue_event_callback(struct QueueEventWrapper *event) {
    static char reply[128];
    time_t now = time(NULL);
    snprintf(reply, sizeof(reply), "{\"message\":\"hello\",\"dt\":%ld}", now);
    if (event && event->data) {
        char log_msg[256];
        snprintf(log_msg, sizeof(log_msg), "Queue event received. Data: %s", event->data);
        info(log_msg);
    } else {
        info("Queue event received. Data: (null)");
    }
    return reply;
}

int main(void) {
    printf("hello function in c");
    struct ClientWrapper *client = create_client();
    if (!client) {
        printf("Failed to create client.");
        return 1;
    }

    struct ConnectResponseWrapper *resp = client_connect(client, "");
    if (!resp || !resp->success) {
        printf("Failed to connect.");
        if (resp) free_connect_response(resp);
        free_client(client);
        return 1;
    }
    info("Connected successfully.");
    free_connect_response(resp);

    struct RegisterQueueRequestWrapper req = {
        .queuename = "test2queue",
        .request_id = 1
    };
    struct RegisterQueueResponseWrapper *qresp = register_queue_async(client, &req, queue_event_callback);
    if (!qresp || !qresp->success) {
        error("Failed to register queue."); // Logging with single string argument
        if (qresp) free_register_queue_response(qresp);
        client_disconnect(client);
        free_client(client);
        return 1;
    }
    info("Queue 'test2queue' registered.");
    free_register_queue_response(qresp);

    printf("chellofn: listening on queue 'test2queue'. Press Ctrl+C to exit.\n");
    while (1) {
        sleep(1);
    }

    client_disconnect(client);
    free_client(client);
    return 0;
}
