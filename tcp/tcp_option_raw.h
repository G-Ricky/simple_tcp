#ifndef SIMPLE_TCP_TCP_OPTION_RAW_H
#define SIMPLE_TCP_TCP_OPTION_RAW_H

#include <stdint.h>

#define TCP_OPT_MAX_LEN 40

/**
 * tcp 首部选项（全部）
 */
typedef struct tcp_option_raw_t {
    /**
     * 首部可选项
     * 最大长度 40
     */
    uint8_t option[TCP_OPT_MAX_LEN];

} tcp_option_raw;

/**
 * 创建首部选项
 * @return
 */
tcp_option_raw *tcp_option_raw_new();

/**
 * 释放首部选项
 * @param raw
 */
void tcp_option_raw_delete(tcp_option_raw *raw);

#endif //SIMPLE_TCP_TCP_OPTION_RAW_H
