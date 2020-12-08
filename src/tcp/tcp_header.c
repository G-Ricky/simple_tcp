
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "tcp_header.h"
#include "tcp_header_raw.h"
#include "tcp_option_raw.h"

tcp_header *tcp_header_new() {
    tcp_header *header = malloc(sizeof(tcp_header));
    header->header = tcp_header_raw_new();
    if (header->header == NULL) {
        goto allocate_header_fail;
    }
    header->option = tcp_option_raw_new();
    if (header->option == NULL) {
        goto allocate_option_fail;
    }
    tcp_header_set_seq_num(header, random());
    tcp_header_set_ack_num(header, 0);
    tcp_header_set_data_offset(header, 5);
    tcp_header_set_rsv(header, 0);
    tcp_header_clear_flags(header);
    tcp_header_set_wnd_size(header, 64240);
    tcp_header_set_checksum(header, 0);
    tcp_header_set_urg_ptr(header, 0);
    header->header_length = 20;
    header->option_length = 0;
    header->option_field_count = 0;
    return header;
allocate_option_fail:
    tcp_header_raw_delete(header->header);
allocate_header_fail:
    free(header);
    fprintf(stderr, "Fail to allocate memory.");
    return NULL;
}

void tcp_header_delete(tcp_header *header) {
    tcp_header_raw_delete(header->header);
    tcp_option_raw_delete(header->option);
    free(header);
}

inline void tcp_header_set_src_port(tcp_header *header, uint16_t src_port) {
    tcp_header_raw_set_src_port(header->header, src_port);
}

inline void tcp_header_set_dst_port(tcp_header *header, uint16_t dst_port) {
    tcp_header_raw_set_dst_port(header->header, dst_port);
}

inline void tcp_header_set_seq_num(tcp_header *header, uint32_t seq_num) {
    tcp_header_raw_set_seq_num(header->header, seq_num);
}

inline void tcp_header_set_ack_num(tcp_header *header, uint32_t ack_num) {
    tcp_header_raw_set_ack_num(header->header, ack_num);
}

void tcp_header_set_data_offset(tcp_header *header, uint8_t data_offset) {
    tcp_header_raw_set_data_offset(header->header, data_offset);
}

void tcp_header_set_rsv(tcp_header *header, uint8_t rsv) {
    tcp_header_raw_set_rsv(header->header, rsv);
}

inline void tcp_header_clear_flags(tcp_header *header) {
    tcp_header_raw_clear_flags(header->header);
}

inline void tcp_header_set_syn(tcp_header *header) {
    tcp_header_raw_set_syn(header->header);
}

inline void tcp_header_set_wnd_size(tcp_header *header, uint16_t wnd_size) {
    tcp_header_raw_set_wnd_size(header->header, wnd_size);
}

inline void tcp_header_set_checksum(tcp_header *header, uint16_t checksum) {
    tcp_header_raw_set_checksum(header->header, checksum);
}

inline void tcp_header_set_urg_ptr(tcp_header *header, uint16_t urg_ptr) {
    tcp_header_raw_set_urg_ptr(header->header, urg_ptr);
}
