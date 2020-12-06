#ifndef SIMPLE_TCP_TCP_UTIL_H
#define SIMPLE_TCP_TCP_UTIL_H

#include <stdlib.h>
#include "tcp_header.h"
#include "tcp_payload.h"
#include "tcp_pseudo_header.h"

/**
 * 计算首部校验和
 * @param pseudo_header
 * @param header
 * @param payload
 * @return
 */
uint16_t tcp_compute_checksum(const tcp_pseudo_header *pseudo_header, const tcp_header *header, const tcp_payload *payload);

#endif //SIMPLE_TCP_TCP_UTIL_H
