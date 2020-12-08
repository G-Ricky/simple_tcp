#ifndef SIMPLE_TCP_COMMON_STRING_H
#define SIMPLE_TCP_COMMON_STRING_H

#include <stdint.h>

typedef struct string_t {
    // 字符串长度
    uint32_t length;
    // 字符串值
    const char* value;
} string;

/**
 * 创建字符串
 * @param str
 * @return
 */
string *string_new(const char *str);

/**
 * 释放字符串空间
 * @param str
 */
void string_delete(string *str);

#endif //SIMPLE_TCP_COMMON_STRING_H
