#include <arpa/inet.h>
#include <common/string.h>
#include <memory.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "tcp_stream.h"
#include "tcp_packet.h"

tcp_stream *tcp_stream_new(const char *dst_ad, uint16_t dst_port) {
    tcp_stream *stream = malloc(sizeof(tcp_stream));
    if (stream == NULL) {
        goto allocate_stream_fail;
    }
    stream->dst_addr = string_new(dst_ad);
    if (stream->dst_addr == NULL) {
        goto allocate_dst_addr_fail;
    }
    stream->daddr = ntohl(inet_addr(dst_ad));
    stream->dst_port = dst_port;
    stream->src_addr = NULL;
    stream->src_port = 0u;
    stream->saddr = 0x00000000u;
    stream->conn_state = CLOSED;
    stream->sockfd = 0;
    // src_addr, src_port 发送时自动获取
    return stream;
allocate_dst_addr_fail:
    free(stream);
allocate_stream_fail:
    fprintf(stderr, "Create tcp_stream fail.");
    return NULL;
}

void tcp_stream_delete(tcp_stream *stream) {
    if (stream->src_addr != NULL) {
        string_delete(stream->src_addr);
    }
    if (stream->dst_addr != NULL) {
        string_delete(stream->dst_addr);
    }
    free(stream);
}

int tcp_stream_connect(tcp_stream *stream) {
    if (stream->conn_state != CLOSED) {
        fprintf(stderr, "Can not create a connection.");
        return -1;
    }
    if (stream->sockfd != 0) {
        fprintf(stderr, "Socket is already open.");
        return -2;
    }
    stream->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (stream->sockfd == -1) {
        perror("Open socket fail");
        return -3;
    }
    /*
     * 设置目标主机地址信息
     */
    struct sockaddr_in dst;
    socklen_t socklen = sizeof(dst);
    memset(&dst, 0, socklen);
    dst.sin_family = AF_INET;
    dst.sin_addr.s_addr = htonl(stream->daddr);
    dst.sin_port = htons(stream->dst_port);

    // TODO 获取未占用端口，获取源地址
    tcp_packet *packet = tcp_packet_new_syn(stream, 1460);
    // TODO 新线程接收 packet，发送 syn ...
    tcp_packet_delete(packet);
    return 0;
}
