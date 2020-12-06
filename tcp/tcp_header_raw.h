#ifndef SIMPLE_TCP_TCP_HEADER_RAW_H
#define SIMPLE_TCP_TCP_HEADER_RAW_H

#include <stdint.h>

/**
 * tcp 协议报文
 */
typedef struct tcp_header_raw_t {
    // 源端口号
    uint16_t src_port;
    // 目标端口号
    uint16_t dst_port;
    // 序列号
    uint32_t seq_num;
    // 确认号
    uint32_t ack_num;
    // 数据偏移和保留位
    uint8_t offset_and_rsv;
    // 标志位
    uint8_t flags;
    // 滑动窗口大小
    uint16_t wnd_size;
    // 校验和
    uint16_t checksum;
    // 紧急指针
    uint16_t urg_ptr;
} tcp_header_raw;

/**
 * 创建 tcp 首部
 * @return
 */
tcp_header_raw *tcp_header_raw_new();

/**
 * 释放 tcp 包资源
 * @param ptcp
 */
void tcp_header_raw_delete(tcp_header_raw *ptcp);

/**
 * 获取源端口
 * @param raw
 * @return
 */
inline uint16_t tcp_header_raw_get_src_port(tcp_header_raw *raw);
/**
 * 设置源端口
 * @param raw raw 报文对象
 * @param src_port 源端口
 */
inline void tcp_header_raw_set_src_port(tcp_header_raw *raw, uint16_t src_port);

/**
 * 获取目标端口
 * @param raw
 * @return
 */
inline uint16_t tcp_header_raw_get_dst_port(tcp_header_raw *raw);

/**
 * 设置目标端口
 * @param raw 报文对象
 * @param port 目标端口
 */
void tcp_header_raw_set_dst_port(tcp_header_raw *raw, uint16_t dst_port);

/**
 * 获取序列号
 * @param raw
 * @return
 */
inline uint32_t tcp_header_raw_get_seq_num(tcp_header_raw *raw);

/**
 * 设置序列号
 * @param raw raw 报文对象
 * @param seq_num 序列号
 */
inline void tcp_header_raw_set_seq_num(tcp_header_raw *raw, uint32_t seq_num);

/**
 * 获取确认号
 * @param raw
 * @return
 */
inline uint32_t tcp_header_raw_get_ack_num(tcp_header_raw *raw);
/**
 * 设置确认号
 * @param raw 报文对象
 * @param ack_num 确认号
 * @return
 */
inline void tcp_header_raw_set_ack_num(tcp_header_raw *raw, uint32_t ack_num);

/**
 * 获取数据偏移量
 * @param raw
 * @return
 */
inline uint8_t tcp_header_raw_get_data_offset(tcp_header_raw *raw);

/**
 * 设置数据偏移量（4 字节为一单位）
 * @param raw 报文对象
 * @param data_offset 数据偏移量
 */
inline void tcp_header_raw_set_data_offset(tcp_header_raw *raw, uint8_t data_offset);

/**
 * 设置保留位
 * @param raw 报文对象
 * @param rsv
 */
inline void tcp_header_raw_set_rsv(tcp_header_raw *raw, uint8_t rsv);

inline void tcp_header_raw_clear_flags(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_cwr(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_ece(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_urg(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_ack(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_psh(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_rst(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_syn(tcp_header_raw *raw);

inline void tcp_header_raw_set_syn(tcp_header_raw *raw);

inline uint8_t tcp_header_raw_get_fin(tcp_header_raw *raw);

/**
 * 获取滑动窗口大小
 * @param raw
 * @return
 */
inline uint16_t tcp_header_raw_get_wnd_size(tcp_header_raw *raw);

/**
 * 设置滑动窗口大小
 * @param raw 报文对象
 */
inline void tcp_header_raw_set_wnd_size(tcp_header_raw *raw, uint16_t wnd_size);

/**
 * 获取校验和
 * @param raw
 * @return
 */
inline uint16_t tcp_header_raw_get_checksum(tcp_header_raw *raw);

/**
 * 设置校验和
 * @param raw 报文对象
 * @param checkSum 校验和
 */
inline void tcp_header_raw_set_checksum(tcp_header_raw *raw, uint16_t checkSum);

/**
 * 获取紧急指针
 * @param raw
 * @return
 */
inline uint16_t tcp_header_raw_get_urg_ptr(tcp_header_raw *raw);

/**
 * 设置紧急指针
 * @param raw 报文对象
 * @param urg_ptr 紧急指针
 */
void tcp_header_raw_set_urg_ptr(tcp_header_raw *raw, uint16_t urg_ptr);
#endif //SIMPLE_TCP_TCP_HEADER_RAW_H
