#include <stdio.h>
#include <stdlib.h>
#include "tcp_payload_raw.h"

tcp_payload_raw *tcp_payload_raw_new() {
    tcp_payload_raw *raw = malloc(sizeof(tcp_payload_raw));
    if (raw == NULL) {
        fprintf(stderr, "Create tcp_payload_raw fail");
        return NULL;
    }
    raw->data = NULL;
    return raw;
}

void tcp_payload_raw_delete(tcp_payload_raw *raw) {
    if (raw->data != NULL) {
        free(raw->data);
    }
    free(raw);
}
