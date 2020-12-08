
#include <stdlib.h>
#include <stdio.h>
#include "tcp_option.h"

tcp_option_item *tcp_option_item_create(uint8_t kind, uint8_t length) {
    tcp_option_item *option = malloc(sizeof(tcp_option));
    option->kind = 0xffu & kind;
    int byte_len;
    switch (kind) {
        // 1 字节选项
        case TCP_OPT_KIND_EOL:
        case TCP_OPT_KIND_NOP:
            option->length = NULL;
            option->meaning = NULL;
            return option;
        // 2 字节选项
        case TCP_OPT_KIND_SACK_PERMITTED:
            byte_len = 2;
        // 3 字节选项
        case TCP_OPT_KIND_WSOPT:
            byte_len = 3;
            break;
        // 4 字节选项
        case TCP_OPT_KIND_MSS:
            byte_len = 4;
            break;
        // 可变长选项
        default:
            byte_len = length;
            break;
    }
    option->length = malloc(sizeof(uint8_t));
    *(option->length) = byte_len;
    if (byte_len == 2) {
        option->meaning = NULL;
    } else {
        option->meaning = calloc(1, byte_len - 2);
    }
    return option;
}

void tcp_option_item_destroy(tcp_option_item *option) {
    if (option->length != NULL) {
        free(option->length);
    }
    if (option->meaning != NULL) {
        free(option->meaning);
    }
    free(option);
}

tcp_option *tcp_option_new() {
    tcp_option *option = malloc(sizeof(tcp_option));
    if (option == NULL) {
        fprintf(stderr, "Create tcp_option fail.");
        return NULL;
    }
    option->offset = 0;
    option->size = 0;
    option->count = 0;
    return option;
}

int tcp_option_add(tcp_option *option, uint8_t kind, uint8_t length, const uint8_t *data) {
    uint8_t i;
    switch (kind) {
        // 1 字节选项
        case TCP_OPT_KIND_EOL:
        case TCP_OPT_KIND_NOP:
            option->option[option->offset++] = kind;
            option->size++;
            break;
        // 可变长选项
        default:
            option->option[option->offset++] = kind;
            option->option[option->offset++] = length;
            for (i = 0; i < length - 2; ++i) {
                option->option[option->offset++] = data[i];
            }
            option->size += length;
            // 字节对齐
            uint8_t padding = length & 0x03u;
            for (i = 0; i < 4 - padding; ++i) {
                option->option[option->offset++] = TCP_OPT_KIND_NOP;
                option->size++;
            }
            break;
    }
    option->count = ((option->offset - 1u) >> 2u) + 1;
    return option->offset;
}

void tcp_option_delete(tcp_option *option) {
    free(option);
}