#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <tcp/tcp_header.h>
#include <tcp/tcp_option.h>
#include <tcp/tcp_payload.h>
#include <tcp/tcp_pseudo_header.h>

static void compute_checksum(uint16_t *psum, const uint16_t *word, ssize_t length);

uint16_t tcp_compute_checksum(const tcp_pseudo_header *pseudo_header, const tcp_header *header, const tcp_payload *payload) {
    tcp_header_raw *header_copy;
    if (header->header->checksum != 0) {
        header_copy = malloc(sizeof(tcp_header_raw));
        memcpy(header_copy, header->header, 1);
        header_copy->checksum = 0;
    } else {
        header_copy = header->header;
    }

    uint16_t sum = 0;
    compute_checksum(&sum, (uint16_t *) pseudo_header->raw, pseudo_header->length);
    compute_checksum(&sum, (uint16_t *) header_copy, header->header_length);
    compute_checksum(&sum, (uint16_t *) header->option, header->option_length);
    compute_checksum(&sum, (uint16_t *) payload->raw, payload->length);

    if (header_copy != header->header) {
        free(header_copy);
    }
    return sum;
}

static void compute_checksum(uint16_t *psum, const uint16_t *word, ssize_t length) {
    if (length == 0 || word == NULL) {
        return;
    }
    uint32_t sum = *psum;
    uint32_t count = (uint32_t) (length - 1) >> 2u << 1u;
    uint32_t i;
    for (i = 0; i < count; ++i) {
        sum += (uint16_t) ~ntohs(word[i]);
        // 进位叠加到低位
        sum = (sum & 0xffffu) + ((sum >> 16u) & 0xffffu);
    }
    uint8_t *pbyte = (uint8_t *) word;
    uint8_t to_fixed = ((uint32_t) (length - 1) & 0x03u);
    uint8_t temp[4] = {0, 0, 0, 0};
    for (i = 0; i <= to_fixed; ++i) {
        temp[i] = pbyte[(count << 1u) + i];
    }
    uint16_t *temp_word = (uint16_t *) temp;
    for (i = 0; i < 2; ++i) {
        sum += (uint16_t) ~ntohs(temp_word[i]);
        // 进位叠加到低位
        sum = (sum & 0xffffu) + ((sum >> 16u) & 0xffffu);
    }
    *psum = sum;
}