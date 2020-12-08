#include <stdio.h>
#include <stdint.h>
#include "printer.h"

void printer_print_tcp_header(tcp_header *header) {
    uint8_t *bytes = (uint8_t *) header->header;
    uint64_t i;
    for (i = 0; i < header->header_length; ++i) {
        if ((i & 3u) == 3u) {
            printf("%02x\n", bytes[i]);
        } else {
            printf("%02x ", bytes[i]);
        }
    }
}

void printer_print_tcp_pseudo_header(tcp_pseudo_header *pseudo_header) {
    uint8_t *bytes = pseudo_header->bytes;
    uint64_t i;
    for (i = 0; i < pseudo_header->length; ++i) {
        if ((i & 3u) == 3u) {
            printf("%02x\n", bytes[i]);
        } else {
            printf("%02x ", bytes[i]);
        }
    }
}

