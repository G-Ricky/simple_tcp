#ifndef SIMPLE_TCP_TCP_PAYLOAD_RAW_H
#define SIMPLE_TCP_TCP_PAYLOAD_RAW_H

#include <stdint.h>

typedef struct tcp_payload_raw_t {
    // tcp 数据
    uint8_t *data;
} tcp_payload_raw;

tcp_payload_raw *tcp_payload_raw_new();

void tcp_payload_raw_delete(tcp_payload_raw *raw);

#endif //SIMPLE_TCP_TCP_PAYLOAD_RAW_H
