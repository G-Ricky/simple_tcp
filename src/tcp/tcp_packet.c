#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "tcp_packet.h"
#include "tcp_stream.h"

struct tcp_packet_t {

    /**
     * tcp 固定头部
     */
    tcp_header *header;

    /**
     * tcp 首部选项
     */
    tcp_option *option;

    /**
     * tcp 数据
     */
    tcp_payload *payload;
};

tcp_packet *tcp_packet_new_syn(tcp_stream *stream, uint16_t mss) {
    tcp_packet *packet = malloc(sizeof(tcp_packet));
    if (packet == NULL) {
        goto allocate_packet_fail;
    }
    packet->header = tcp_header_new();
    if (packet->header == NULL) {
        goto allocate_header_fail;
    }
    packet->option = tcp_option_new();
    if (packet->option == NULL) {
        goto allocate_option_fail;
    }
    packet->payload = tcp_payload_new();
    if (packet->payload == NULL) {
        goto allocate_payload_fail;
    }
    // 设置固定首部
    tcp_header_set_src_port(packet->header, stream->src_port);
    tcp_header_set_dst_port(packet->header, stream->dst_port);
    tcp_header_set_seq_num(packet->header, random()); // TODO 使用 linux 的生成方法
    tcp_header_set_syn(packet->header);
    // 设置首部选项
    uint16_t mss_net = htons(mss);
    tcp_option_add(packet->option, TCP_OPT_KIND_MSS, 4, (uint8_t *) &mss_net);
    return packet;
allocate_payload_fail:
    tcp_option_delete(packet->option);
allocate_option_fail:
    tcp_header_delete(packet->header);
allocate_header_fail:
    free(packet);
allocate_packet_fail:
    fprintf(stderr, "Create tcp_packet fail.");
    return NULL;
}

void tcp_packet_delete(tcp_packet *packet) {
    tcp_payload_delete(packet->payload);
    tcp_option_delete(packet->option);
    tcp_header_delete(packet->header);
    free(packet);
}
