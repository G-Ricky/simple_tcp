#ifndef SIMPLE_TCP_TCP_HEADER_H
#define SIMPLE_TCP_TCP_HEADER_H

#include "tcp_header_raw.h"
#include "tcp_option_raw.h"

typedef struct tcp_header_t {
    // 固定首部
    tcp_header_raw *header;
    // 可选首部
    tcp_option_raw *option;
    // 固定首部长度，20 字节
    ssize_t header_length;
    // 可选首部长度，0 - 40 字节
    ssize_t option_length;
    // 可选首部字段数
    int option_field_count;
} tcp_header;

/**
 * 创建 tcp 首部
 * @return
 */
tcp_header *tcp_header_new();

/**
 * 释放 tcp 首部
 * @param header
 */
void tcp_header_delete(tcp_header *header);

/**
 * 设置源端口
 * @param header
 * @param src_port
 */
inline void tcp_header_set_src_port(tcp_header *header, uint16_t src_port);

/**
 * 设置目标端口
 * @param header
 * @param dst_port
 */
inline void tcp_header_set_dst_port(tcp_header *header, uint16_t dst_port);

/**
 * 设置序列号
 * @param header
 * @param seq_num
 */
inline void tcp_header_set_seq_num(tcp_header *header, uint32_t seq_num);

/**
 * 设置确认号
 * @param header
 * @param ack_num
 */
inline void tcp_header_set_ack_num(tcp_header *header, uint32_t ack_num);

/**
 * 设置数据偏移量
 * @param header
 * @param data_offset
 */
void tcp_header_set_data_offset(tcp_header *header, uint8_t data_offset);

/**
 * 设置保留位
 * @param header
 * @param rsv
 */
void tcp_header_set_rsv(tcp_header *header, uint8_t rsv);

/**
 * 清除所有标志
 * @param header
 */
inline void tcp_header_clear_flags(tcp_header *header);

/**
 * 设置 syn 标志
 * @param header
 */
inline void tcp_header_set_syn(tcp_header *header);

/**
 * 设置滑动窗口大小
 * @param header
 * @param wnd_size
 */
inline void tcp_header_set_wnd_size(tcp_header *header, uint16_t wnd_size);

/**
 * 设置首部校验和
 * @param header
 * @param checksum
 */
inline void tcp_header_set_checksum(tcp_header *header, uint16_t checksum);

/**
 * 设置紧急指针
 * @param header
 * @param urg_ptr
 */
inline void tcp_header_set_urg_ptr(tcp_header *header, uint16_t urg_ptr);

#endif //SIMPLE_TCP_TCP_HEADER_H
