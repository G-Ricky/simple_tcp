#include <arpa/inet.h>
#include <common/string.h>
#include <memory.h>
#include <netinet/in.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include "tcp_stream.h"
#include "tcp_packet.h"

typedef struct route_t {
    // 目标地址 主机序
    uint32_t destination;
    // 网关 主机序
    uint32_t gateway;
    // 子网掩码 主机序
    uint32_t netmask;
    // 路径长度
    uint8_t metric;
    // 接口名称
    string *iface;
} route;

typedef struct route_table_t {
    // 路由表项
    route *routes;
    // 路由表项数
    int count;
    // 路由表总容量
    int capacity;
} route_table;

static route_table *route_table_new(int capacity);

static void route_table_delete(route_table *table);

/**
 * 添加路由规则到路由表
 * @param table
 * @param r
 * @return -1 if errors
 */
static int route_table_add(route_table *table, route *r);

/**
 * metric 比较
 * @param t1
 * @param t2
 * @return
 */
static int route_metric_comparator(route *r1, route *r2);

/**
 * 计算获取 2 的 n 次方的容量
 * @param capacity
 * @return
 */
static int table_size_for(int capacity);

static uint32_t get_source_address_from_route(uint32_t daddr);

/**
 * 获取网络位位数
 * @param netmask
 * @return
 */
uint8_t get_net_bits(uint32_t netmask);

tcp_stream *tcp_stream_new(const char *dst_ad, uint16_t dst_port) {
    tcp_stream *stream = malloc(sizeof(tcp_stream));
    if (stream == NULL) {
        goto allocate_stream_fail;
    }
    stream->dst_addr = string_new(dst_ad);
    if (stream->dst_addr == NULL) {
        goto allocate_dst_addr_fail;
    }
    stream->daddr = ntohl(inet_addr(dst_ad));
    stream->dst_port = dst_port;
    stream->src_addr = NULL;
    stream->src_port = 0u;
    stream->saddr = 0x00000000u;
    stream->conn_state = CLOSED;
    stream->sockfd = 0;
    // src_addr, src_port 发送时自动获取
    return stream;
allocate_dst_addr_fail:
    free(stream);
allocate_stream_fail:
    fprintf(stderr, "Create tcp_stream fail.");
    return NULL;
}

void tcp_stream_delete(tcp_stream *stream) {
    if (stream->src_addr != NULL) {
        string_delete(stream->src_addr);
    }
    if (stream->dst_addr != NULL) {
        string_delete(stream->dst_addr);
    }
    free(stream);
}

int tcp_stream_connect(tcp_stream *stream) {
    if (stream->conn_state != CLOSED) {
        fprintf(stderr, "Can not create a connection.");
        return -1;
    }
    if (stream->sockfd != 0) {
        fprintf(stderr, "Socket is already open.");
        return -2;
    }
    stream->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (stream->sockfd == -1) {
        perror("Open socket fail");
        return -3;
    }
    /*
     * 设置目标主机地址信息
     */
    struct sockaddr_in dst;
    socklen_t socklen = sizeof(dst);
    memset(&dst, 0, socklen);
    dst.sin_family = AF_INET;
    dst.sin_addr.s_addr = htonl(stream->daddr);
    dst.sin_port = htons(stream->dst_port);
    stream->src_port = get_source_address_from_route(stream->daddr);

    // TODO 获取未占用端口，获取源地址
    tcp_packet *packet = tcp_packet_new_syn(stream, 1460);
    // TODO 新线程接收 packet，发送 syn ...
    tcp_packet_delete(packet);
    return 0;
}

/**
 * 从路由表获取
 * @return 32位主机序 ip
 */
uint32_t get_source_address_from_route(uint32_t daddr) {
    FILE *fp;
    char buff[1024];

    /* Open the command for reading. */
    fp = popen("route -n", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        goto error_after_starting;
    }

    // 格式
    // Destination Gateway Genmask Flags Metric Ref Use Iface
    // 0.0.0.0 10.0.3.2 0.0.0.0 UG 101 0 0 enp0s8
    regex_t regex;
    // 编译正则表达式
    int res = regcomp(&regex, "(0|1\\d?\\d?|2\\d?|2[0-4]\\d|25[0-5]|[3-9]\\d?)(\\.(0|1\\d?\\d?|2\\d?|2[0-4]\\d|25[0-5]|[3-9]\\d?)){3}", REG_EXTENDED);
    if (res != 0) {
        fprintf(stderr, "Failed to compile ip regex.");
        goto error_after_reg;
    }
    // 储存匹配结果
    regmatch_t match;
    /**
     * @var part_ptr 字符串分割后每一部分的首地址
     * @var ptr 初始字符串地址 或 NULL
     */
    char *part_ptr, *ptr;
    route_table *table = route_table_new(8);
    // 解析路由表的每一行
    /* Read the output a line at a time - output it. */
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        // 匹配正则
        res = regexec(&regex, buff, 1, &match, 0);
        if (res != 0) {
            continue;
        }
        // 包含 ip 地址的情况，为路由表项
        ptr = buff;
        int part_num = 0;
        route r;
        while ((part_ptr = strtok(ptr, " ")) != NULL) {
            char *endptr;
            long metric;
            // destination, gateway, netmask 字段，并按顺序填充内存地址
            switch (part_num) {
                case 0:
                case 1:
                case 2:
                    *((uint32_t *) &r + part_num) = ntohl(inet_addr(part_ptr));
                    break;
                case 3:
                case 5:
                case 6:
                    // do nothing
                    break;
                case 4:
                    // metric 字段
                    // 路径长度，经过各个链接的代价总和
                    metric = strtol(part_ptr, &endptr, 10);
                    if (*endptr != '\0') {
                        fprintf(stderr, "parse metric error");
                        goto error_after_table;
                    }
                    if (metric > 255) {
                        metric = 255;
                    } else if (metric < 1) {
                        metric = 1;
                    }
                    r.metric = metric;
                    break;
                case 7:
                    r.iface = string_new(part_ptr);
                    break;
                default:
                    goto outer_loop;
            }
            printf("substr:%s, %p\n", part_ptr, part_ptr);
            ptr = NULL;
            part_num++;
        }
outer_loop:
        // 成功匹配到路由规则
        if (part_num != 0) {
            printf("destination=%08x, gateway=%08x, netmask=%08x\n", r.destination, r.gateway, r.netmask);
            route_table_add(table, &r);
        }
    }

    route *optimal_route = NULL;
    uint8_t max_net_bits = 0;
    int i;
    for (i = 0; i < table->count; ++i) {
        route *r = &table->routes[i];
        // 路由不匹配
        if (r->destination != (r->netmask & daddr)) {
            continue;
        }
        uint8_t net_bits = get_net_bits(r->netmask);
        // 首个匹配的路由
        if (optimal_route == NULL
            // 当前匹配的网络位比之前匹配的网络位长
            || net_bits > max_net_bits
            // 匹配的网络位位数相同时，比较 metric
            || (net_bits == max_net_bits && r->metric > optimal_route->metric)) {
            optimal_route = r;
            max_net_bits = net_bits;
        }
    }

    printf("Destination Gateway Genmask Metric Iface\n");
    printf("%08x %08x %u %u %s\n",
        optimal_route->destination, optimal_route->gateway, get_net_bits(optimal_route->netmask), optimal_route->metric,
        optimal_route->iface->value);

    // TODO 根据接口名称匹配网络地址

    route_table_delete(table);
    regfree(&regex);
    /* close */
    pclose(fp);
    return 0;
error_after_table:
    route_table_delete(table);
error_after_reg:
    regfree(&regex);
error_after_popen:
    pclose(fp);
error_after_starting:
    return 0;
}

route_table *route_table_new(int capacity) {
    if (capacity <= 0) {
        fprintf(stderr, "capacity must be positive.");
        return NULL;
    }
    route_table *table = malloc(sizeof(route_table));
    if (table == NULL) {
        goto allocate_route_table_fail;
    }
    table->capacity = table_size_for(capacity);
    table->routes = malloc(table->capacity * sizeof(route));
    if (table->routes == NULL) {
        goto allocate_routes_fail;
    }
    table->count = 0;
    return table;
allocate_routes_fail:
    perror("Create routes fail");
    free(table);
allocate_route_table_fail:
    perror("Create route_table fail");
    return NULL;
}

void route_table_delete(route_table *table) {
    int i = 0;
    for (; i < table->count; ++i) {
        string *iface = table->routes[i].iface;
        if (iface != NULL) {
            string_delete(iface);
        }
    }
    free(table->routes);
    free(table);
}

int route_table_add(route_table *table, route *r) {
    if (table->count >= table->capacity) {
        int new_capacity = (uint32_t) table->capacity << 1u;
        route *new_routes = malloc(new_capacity * sizeof(route));
        if (new_routes == NULL) {
            perror("Create new table fail");
            return -1;
        }
        table->capacity = new_capacity;
        table->routes = new_routes;
    }
    // 复制路由表规则到数组
    table->routes[table->count++] = *r;
    return 0;
}

int table_size_for(int capacity) {
    uint32_t n = capacity - 1;
    n |= n >> 16u;
    n |= n >> 8u;
    n |= n >> 4u;
    n |= n >> 2u;
    n |= n >> 1u;
    return n <= 0 ? 1 : (int) (n + 1);
}

int route_metric_comparator(route *r1, route *r2) {
    return r1->metric > r2->metric
        ? 1
        : r1->metric < r2->metric ? -1 : 0;
}

uint8_t get_net_bits(uint32_t netmask) {
    uint8_t bits = 0;
    while (netmask != 0) {
        bits++;
        netmask <<= 1u;
    }
    return bits;
}