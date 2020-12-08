#ifndef SIMPLE_TCP_TCP_PAYLOAD_H
#define SIMPLE_TCP_TCP_PAYLOAD_H

#include <stdint.h>
#include <sys/types.h>
#include "tcp_payload_raw.h"

typedef struct tcp_payload_t {
    /**
     * tcp 数据
     */
    tcp_payload_raw *raw;

    /**
     * tcp 数据长度
     */
    ssize_t length;
} tcp_payload;

/**
 * 创建 tcp 数据
 * @return
 */
tcp_payload *tcp_payload_new();

/**
 * 释放 tcp 数据
 */
void tcp_payload_delete(tcp_payload *payload);

#endif //SIMPLE_TCP_TCP_PAYLOAD_H
