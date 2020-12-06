#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include "tcp_header_raw.h"

tcp_header_raw *tcp_header_raw_new() {
    tcp_header_raw *raw = calloc(1, sizeof(tcp_header_raw));
    if (raw == NULL) {
        fprintf(stderr, "Create tcp_header_raw fail.");
        return NULL;
    }
    return raw;
}

void tcp_header_raw_delete(tcp_header_raw *ptcp) {
    free(ptcp);
}

inline uint16_t tcp_header_raw_get_src_port(tcp_header_raw *raw) {
    return ntohs(raw->src_port);
}

inline void tcp_header_raw_set_src_port(tcp_header_raw *raw, uint16_t src_port) {
    raw->src_port = htons(src_port);
}

inline uint16_t tcp_header_raw_get_dst_port(tcp_header_raw *raw) {
    return ntohs(raw->dst_port);
}

void tcp_header_raw_set_dst_port(tcp_header_raw *raw, uint16_t dst_port) {
    raw->dst_port = htons(dst_port);
}

inline uint32_t tcp_header_raw_get_seq_num(tcp_header_raw *raw) {
    return ntohl(raw->seq_num);
}

inline void tcp_header_raw_set_seq_num(tcp_header_raw *raw, uint32_t seq_num) {
    raw->seq_num = htonl(seq_num);
}

inline uint32_t tcp_header_raw_get_ack_num(tcp_header_raw *raw) {
    return ntohl(raw->ack_num);
}

inline void tcp_header_raw_set_ack_num(tcp_header_raw *raw, uint32_t ack_num) {
    raw->ack_num = htonl(ack_num);
}

inline uint8_t tcp_header_raw_get_data_offset(tcp_header_raw *raw) {
    return (uint32_t) raw->offset_and_rsv >> 4u & 0x0fu;
}

inline void tcp_header_raw_set_data_offset(tcp_header_raw *raw, uint8_t data_offset) {
    raw->offset_and_rsv &= 0x0fu; // 清除 data_offset
    raw->offset_and_rsv |= (data_offset & 0x0fu) << 4u;
}

inline void tcp_header_raw_set_rsv(tcp_header_raw *raw, uint8_t rsv) {
    raw->offset_and_rsv &= 0xf0u; // 清除保留位
    raw->offset_and_rsv |= rsv & 0x0fu;
}

inline void tcp_header_raw_clear_flags(tcp_header_raw *raw) {
    raw->flags = 0;
}

inline uint8_t tcp_header_raw_get_cwr(tcp_header_raw *raw) {
    return (uint32_t) raw->flags >> 7u & 0x1u;
}

inline uint8_t tcp_header_raw_get_ece(tcp_header_raw *raw) {
    return (uint32_t) raw->flags >> 6u & 0x1u;
}

inline uint8_t tcp_header_raw_get_urg(tcp_header_raw *raw) {
    return (uint32_t) raw->flags >> 5u & 0x1u;
}

inline uint8_t tcp_header_raw_get_ack(tcp_header_raw *raw) {
    return (uint32_t) raw->flags >> 4u & 0x1u;
}

inline uint8_t tcp_header_raw_get_psh(tcp_header_raw *raw) {
    return (uint32_t) raw->flags >> 3u & 0x1u;
}

inline uint8_t tcp_header_raw_get_rst(tcp_header_raw *raw) {
    return (uint32_t) raw->flags >> 2u & 0x1u;
}

inline uint8_t tcp_header_raw_get_syn(tcp_header_raw *raw) {
    return (uint32_t) raw->flags >> 1u & 0x1u;
}

inline void tcp_header_raw_set_syn(tcp_header_raw *raw) {
    raw->flags |= (0x01u << 1u);
}

inline uint8_t tcp_header_raw_get_fin(tcp_header_raw *raw) {
    return (uint32_t) raw->flags & 0x1u;
}

inline uint16_t tcp_header_raw_get_wnd_size(tcp_header_raw *raw) {
    return ntohs(raw->wnd_size);
}

void tcp_header_raw_set_wnd_size(tcp_header_raw *raw, uint16_t wnd_size) {
    raw->wnd_size = htons(wnd_size);
}

inline uint16_t tcp_header_raw_get_checksum(tcp_header_raw *raw) {
    return ntohs(raw->checksum);
}

void tcp_header_raw_set_checksum(tcp_header_raw *raw, uint16_t checkSum) {
    raw->checksum = htons(checkSum);
}

inline uint16_t tcp_header_raw_get_urg_ptr(tcp_header_raw *raw) {
    return ntohs(raw->urg_ptr);
}

void tcp_header_raw_set_urg_ptr(tcp_header_raw *raw, uint16_t urg_ptr) {
    raw->urg_ptr = htons(urg_ptr);
}
