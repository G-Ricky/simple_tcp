
#include <stdio.h>
#include <stdlib.h>
#include "tcp_payload.h"

tcp_payload *tcp_payload_new() {
    tcp_payload *payload = malloc(sizeof(tcp_payload));
    if (payload == NULL) {
        goto allocate_payload_fail;
    }
    payload->raw = tcp_payload_raw_new();
    if (payload->raw == NULL) {
        goto allocate_payload_raw_fail;
    }
    payload->raw->data = NULL;
    payload->length = 0;
    return payload;

allocate_payload_raw_fail:
    free(payload);
allocate_payload_fail:
    fprintf(stderr, "Create tcp_payload fail");
    return NULL;
}

void tcp_payload_delete(tcp_payload *payload) {
    if (payload->raw->data != NULL) {
        payload->length = 0;
        free(payload->raw->data);
    }
    tcp_payload_raw_delete(payload->raw);
    free(payload);
}
