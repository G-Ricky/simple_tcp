#ifndef SIMPLE_TCP_TCP_PACKET_H
#define SIMPLE_TCP_TCP_PACKET_H

#include "tcp_header.h"
#include "tcp_option.h"
#include "tcp_payload.h"
#include "tcp_stream.h"

typedef struct tcp_packet_t tcp_packet;

/**
 * 创建 tcp 报文段
 * @param stream
 * @return
 */
tcp_packet *tcp_packet_new_syn(tcp_stream *stream, uint16_t mss);

/**
 * 释放 tcp 报文段
 */
void tcp_packet_delete(tcp_packet *tcp_packet);

#endif //SIMPLE_TCP_TCP_PACKET_H
