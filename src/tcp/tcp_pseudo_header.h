#ifndef SIMPLE_TCP_TCP_PSEUDO_HEADER_H
#define SIMPLE_TCP_TCP_PSEUDO_HEADER_H

#include <stdint.h>
#include "tcp_pseudo_header_raw.h"

typedef struct tcp_pseudo_header {
    tcp_pseudo_header_raw *raw;
    uint8_t *bytes;
    ssize_t length;
} tcp_pseudo_header;

/**
 * 创建伪首部
 * @return
 */
tcp_pseudo_header *tcp_pseudo_header_new();

/**
 * 释放伪首部
 * @param header
 */
void tcp_pseudo_header_delete(tcp_pseudo_header *header);

/**
 * 设置源地址
 * @param header
 * @param src_addr
 */
inline void tcp_pseudo_header_set_src_addr(tcp_pseudo_header *header, uint32_t src_addr);

/**
 * 设置目标地址
 * @param header
 * @param dst_addr
 */
inline void tcp_pseudo_header_set_dst_addr(tcp_pseudo_header *header, uint32_t dst_addr);

/**
 * 设置 tcp 报文长度
 * @param header
 * @param tcp_len
 */
inline void tcp_pseudo_header_set_tcp_len(tcp_pseudo_header *header, uint16_t tcp_len);

#endif //SIMPLE_TCP_TCP_PSEUDO_HEADER_H
