#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include "tcp_pseudo_header_raw.h"

tcp_pseudo_header_raw *tcp_pseudo_header_raw_new() {
    tcp_pseudo_header_raw *raw = calloc(1, sizeof(tcp_pseudo_header_raw));
    if (raw == NULL) {
        fprintf(stderr, "Create tcp_pseudo_header_raw fail.");
    }
    tcp_pseudo_header_raw_set_reserve(raw, 0);
    tcp_pseudo_header_raw_set_protocol(raw, PROTOCOL_TCP);
    return raw;
}

uint32_t tcp_pseudo_header_raw_get_src_addr(tcp_pseudo_header_raw *pseudo_header) {
    return ntohl(pseudo_header->src_addr);
}

void tcp_pseudo_header_raw_set_src_addr(tcp_pseudo_header_raw *pseudo_header, uint32_t src_addr) {
    pseudo_header->src_addr = htonl(src_addr);
}

uint32_t tcp_pseudo_header_raw_get_dst_addr(tcp_pseudo_header_raw *pseudo_header) {
    return ntohl(pseudo_header->dst_addr);
}

void tcp_pseudo_header_raw_set_dst_addr(tcp_pseudo_header_raw *pseudo_header, uint32_t dst_addr) {
    pseudo_header->dst_addr = htonl(dst_addr);
}

uint32_t tcp_pseudo_header_raw_get_reserve(tcp_pseudo_header_raw *pseudo_header) {
    return ntohs(pseudo_header->reserve);
}

void tcp_pseudo_header_raw_set_reserve(tcp_pseudo_header_raw *pseudo_header, uint8_t reserve) {
    pseudo_header->reserve = reserve;
}

uint32_t tcp_pseudo_header_raw_get_protocol(tcp_pseudo_header_raw *pseudo_header) {
    return ntohs(pseudo_header->protocol);
}

void tcp_pseudo_header_raw_set_protocol(tcp_pseudo_header_raw *pseudo_header, uint8_t protocol) {
    pseudo_header->protocol = protocol;
}

uint32_t tcp_pseudo_header_raw_get_tcp_len(tcp_pseudo_header_raw *pseudo_header) {
    return ntohs(pseudo_header->tcp_len);
}

void tcp_pseudo_header_raw_set_tcp_len(tcp_pseudo_header_raw *pseudo_header, uint16_t tcp_len) {
    pseudo_header->tcp_len = htons(tcp_len);
}

void tcp_pseudo_header_raw_delete(tcp_pseudo_header_raw *pseudo_header) {
    free(pseudo_header);
}
