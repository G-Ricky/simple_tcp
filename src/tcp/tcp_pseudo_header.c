#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include "tcp_pseudo_header.h"

tcp_pseudo_header *tcp_pseudo_header_new() {
    tcp_pseudo_header *header = malloc(sizeof(tcp_pseudo_header));
    if (header == NULL) {
        goto allocate_pseudo_header_fail;
    }
    tcp_pseudo_header_raw *raw = tcp_pseudo_header_raw_new();
    if (raw == NULL) {
        goto allocate_pseudo_header_raw_fail;
    }
    header->raw = raw;
    header->bytes = (uint8_t *) raw;
    header->length = sizeof(tcp_pseudo_header_raw);
    return header;

allocate_pseudo_header_raw_fail:
    free(header);
allocate_pseudo_header_fail:
    fprintf(stderr, "Create tcp_pseudo_header fail.");
    return NULL;
}

void tcp_pseudo_header_delete(tcp_pseudo_header *header) {
    tcp_pseudo_header_raw_delete(header->raw);
    free(header);
}

inline void tcp_pseudo_header_set_src_addr(tcp_pseudo_header *header, uint32_t src_addr) {
    tcp_pseudo_header_raw_set_src_addr(header->raw, src_addr);
}

void tcp_pseudo_header_set_dst_addr(tcp_pseudo_header *header, uint32_t dst_addr) {
    tcp_pseudo_header_raw_set_dst_addr(header->raw, dst_addr);
}

void tcp_pseudo_header_set_tcp_len(tcp_pseudo_header *header, uint16_t tcp_len) {
    tcp_pseudo_header_raw_set_tcp_len(header->raw, tcp_len);
}
