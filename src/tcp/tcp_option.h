#ifndef SIMPLE_TCP_TCP_OPTION_H
#define SIMPLE_TCP_TCP_OPTION_H

#include <stdint.h>

#define TCP_OPT_MAX_LEN 40

/**
 * EOL 指示首部可选项是否到结尾
 * This option code indicates the end of the option list.  This
 * might not coincide with the end of the TCP header according to
 * the Data Offset field.  This is used at the end of all options,
 * not the end of each option, and need only be used if the end of
 * the options would not otherwise coincide with the end of the TCP
 * header.
 * 仅当首部长度与数据偏移（Data Offset）
 * 字段不相同时使用，如果相同则不需要 EOL 标记
 * @see https://www.ietf.org/rfc/rfc793.html#section-3.1 Header Format > Options > Specific Option Definitions > End of Option List
 */
#define TCP_OPT_KIND_EOL 0x00u
#define TCP_OPT_KIND_NOP 0x01u
#define TCP_OPT_KIND_MSS 0x02u
#define TCP_OPT_KIND_WSOPT 0x03u
#define TCP_OPT_KIND_SACK_PERMITTED 0x04u

/**
 * tcp 首部选项（单个）
 *
 * 任意一个 TCP 报文段都必须能够处理首部选项
 * 任意一个 TCP 报文段都必须忽略还没有实现的选项，
 * 并且假设该选项包含一个“长度”字段（所有将来定义的
 * 首部选项都会有“长度”字段）
 * TCP 必须处理好非法的长度字段而不会使程序崩溃（例如：0），
 * 建议的处理方式是重置（reset）和记录原因
 * @see https://www.ietf.org/rfc/rfc1122.html#page-85 TCP Options
 *
 * tcp 首部选项可能会有以下两种情况
 *   1. 只包含一个字段 option-kind 的八位组
 *   2. 包含三个字段：一个 option-kind 的八位组，一个 option-length 的八位组，和一个 option-data 的实际数据字段，长度由 option-length 决定
 * option-length 包含了 option-kind, option-length
 * 和 option-data 的总长度（其中 option-kind 的长度
 * 加 option-length 的长度固定为 2）
 * 注意：option
 * @see https://www.ietf.org/rfc/rfc793.html#section-3.1 Header Format > Options
 */
typedef struct tcp_option_item_t {
    uint8_t kind;
    uint8_t *length;
    uint8_t *meaning;
} tcp_option_item;

/**
 * tcp 首部选项（全部）
 */
typedef struct tcp_option_t {
    /**
     * 首部可选项
     * 最大长度 40
     */
    uint8_t option[TCP_OPT_MAX_LEN];

    /**
     * 当前偏移
     */
    uint8_t offset;

    /**
     * 实际长度（单位：字节）
     */
    uint8_t size;

    /**
     * 分组个数（单位：4字节）
     */
    uint8_t count;
} tcp_option;

/**
 * 创建 tcp 首部选项
 * @return
 */
tcp_option *tcp_option_create();

/**
 * 添加首部选项
 * 如果 kind 为 EOL 或 NOP，length 和 data 将会被忽略
 * 如果 length 小于或等于 2，data 字段将会被忽略
 * 需要调用者做数组溢出检查
 * 需要调用者检查固定长度的 kind 和 length 是否对应
 * @param kind 首部选项类型字段
 * @param length 首部选项长度字段
 * @param data 首部选项数据字段
 * @return 下一个offset
 */
int tcp_option_add(tcp_option *option, uint8_t kind, uint8_t length, const uint8_t *data);

/**
 * 释放 tcp 首部选项
 * @param option
 */
void tcp_option_destroy(tcp_option *option);

#endif //SIMPLE_TCP_TCP_OPTION_H
