#include "stdlib.h"
#include "tcp_option_raw.h"

tcp_option_raw *tcp_option_raw_new() {
    tcp_option_raw *raw = calloc(1, sizeof(tcp_option_raw));
    return raw;
}

void tcp_option_raw_delete(tcp_option_raw *raw) {
    free(raw);
}
