#ifndef SIMPLE_TCP_TCP_PSEUDO_HEADER_RAW_H
#define SIMPLE_TCP_TCP_PSEUDO_HEADER_RAW_H

#include <stdint.h>

#define PROTOCOL_TCP 0x06

/**
 * tcp 伪首部
 */
typedef struct tcp_pseudo_header_raw_t {
    // 源地址
    uint32_t src_addr;
    // 目标地址
    uint32_t dst_addr;
    // 保留位
    uint8_t reserve;
    // 传输层协议号
    uint8_t protocol;
    // TCP报文长度
    uint16_t tcp_len;
} tcp_pseudo_header_raw;

/**
 * 创建伪首部
 * @return
 */
tcp_pseudo_header_raw *tcp_pseudo_header_raw_new();

/**
 * 获取源地址
 * @param pseudo_header
 * @return
 */
uint32_t tcp_pseudo_header_raw_get_src_addr(tcp_pseudo_header_raw *pseudo_header);

/**
 * 设置源地址
 * @param pseudo_header
 * @param src_addr
 */
void tcp_pseudo_header_raw_set_src_addr(tcp_pseudo_header_raw *pseudo_header, uint32_t src_addr);

/**
 * 获取目标地址
 * @param pseudo_header
 * @return
 */
uint32_t tcp_pseudo_header_raw_get_dst_addr(tcp_pseudo_header_raw *pseudo_header);

/**
 * 设置目标地址
 * @param pseudo_header
 * @param dst_addr
 */
void tcp_pseudo_header_raw_set_dst_addr(tcp_pseudo_header_raw *pseudo_header, uint32_t dst_addr);

/**
 * 获取保留位
 * @param pseudo_header
 * @return
 */
uint32_t tcp_pseudo_header_raw_get_reserve(tcp_pseudo_header_raw *pseudo_header);

/**
 * 设置保留位
 * @param pseudo_header
 * @param reserve
 */
void tcp_pseudo_header_raw_set_reserve(tcp_pseudo_header_raw *pseudo_header, uint8_t reserve);

/**
 * 获取协议号
 * @param pseudo_header
 * @return
 */
uint32_t tcp_pseudo_header_raw_get_protocol(tcp_pseudo_header_raw *pseudo_header);

/**
 * 设置协议号
 * @param pseudo_header
 * @param protocol
 */
void tcp_pseudo_header_raw_set_protocol(tcp_pseudo_header_raw *pseudo_header, uint8_t protocol);

/**
 * 获取 tcp 报文长度
 * @param pseudo_header
 * @return
 */
uint32_t tcp_pseudo_header_raw_get_tcp_len(tcp_pseudo_header_raw *pseudo_header);

/**
 * 设置 tcp 报文长度
 * @param pseudo_header
 * @param tcp_len
 */
void tcp_pseudo_header_raw_set_tcp_len(tcp_pseudo_header_raw *pseudo_header, uint16_t tcp_len);

/**
 * 释放伪首部资源
 * @param pseudo_header
 */
void tcp_pseudo_header_raw_delete(tcp_pseudo_header_raw *pseudo_header);

#endif //SIMPLE_TCP_TCP_PSEUDO_HEADER_RAW_H
