#ifndef SIMPLE_TCP_TCP_STREAM_H
#define SIMPLE_TCP_TCP_STREAM_H

#include <common/string.h>
#include "tcp_header.h"
#include "tcp_option.h"

typedef enum tcp_connect_state_t {
    CLOSED = 0,
} tcp_connect_state;

typedef struct tcp_stream_t {
    /**
     * 源地址
     */
    string *src_addr;

    /**
     * 目标地址
     */
    string *dst_addr;

    /**
     * 源地址数字 ip，主机字节序
     */
    uint32_t saddr;

    /**
     * 目标地址数字 ip，主机字节序
     */
    uint32_t daddr;

    /**
     * 源端口，主机字节序
     */
    uint16_t src_port;

    /**
     * 目标端口，主机字节序
     */
    uint16_t dst_port;

    /**
     * 连接状态
     */
    tcp_connect_state conn_state;

    /**
     * socket 文件描述符
     */
    int sockfd;

} tcp_stream;

/**
 * 创建一个 socket
 * @param dst_ad
 * @param dst_port
 * @return
 */
tcp_stream *tcp_stream_new(const char *dst_ad, uint16_t dst_port);

/**
 * 释放一个 socket
 * @param stream
 */
void tcp_stream_delete(tcp_stream *stream);

/**
 * 建立连接
 * @param stream
 * @return 错误码
 */
int tcp_stream_connect(tcp_stream *stream);

#endif //SIMPLE_TCP_TCP_STREAM_H
