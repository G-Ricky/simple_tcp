#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tcp_header.h"
#include "tcp_payload.h"
#include "tcp_pseudo_header.h"
#include "util/printer.h"
#include "util/tcp_util.h"

int main() {
    puts("starting");
    srand(time(NULL));
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (fd == -1) {
        perror("open socket fail: ");
        return -1;
    }
    puts("开始整活");
    uint16_t src_port = 15049u;
    uint16_t dst_port = 8080u;
    uint32_t src_addr = ntohl(inet_addr("10.10.0.103"));
    uint32_t dst_addr = ntohl(inet_addr("10.10.0.1"));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(dst_addr);
    addr.sin_port = htons(src_port);

    // 设置 tcp 首部
    tcp_header *header = tcp_header_new();
    tcp_header_set_src_port(header, src_port);
    tcp_header_set_dst_port(header, dst_port);
    tcp_header_set_syn(header);

    // 设置 payload
    tcp_payload *payload = tcp_payload_new();

    // 计算伪首部
    tcp_pseudo_header *pseudo_header = tcp_pseudo_header_new();
    tcp_pseudo_header_set_src_addr(pseudo_header, src_addr);
    tcp_pseudo_header_set_dst_addr(pseudo_header, dst_addr);
    tcp_pseudo_header_set_tcp_len(pseudo_header, header->header_length + payload->length);


    uint16_t checksum = tcp_compute_checksum(pseudo_header, header, payload);
    tcp_header_set_checksum(header, checksum);

    printf("tcp 首部：\n");
    printer_print_tcp_header(header);
    printf("tcp 伪首部：\n");
    printer_print_tcp_pseudo_header(pseudo_header);


//    int bind_result = bind(fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
//    if (bind_result == -1) {
//        perror("bind fail");
//        goto destroy;
//    }
    ssize_t n = sendto(fd, header->header, sizeof(tcp_header_raw), 0, (struct sockaddr *) &addr, sizeof(addr));
    printf("n=%d\n", n);
    if (n == -1) {
        perror("send error");
        goto destroy;
    }

    // TODO 三次握手 ack 确认
//    uint8_t buff[2048];
//    int addr_len = sizeof(addr);
//    int recv_result;
//    int i;
//    while (1) {
//        recv_result = recvfrom(fd, buff, 2048, 0, (struct sockaddr *) &addr, (socklen_t *) &addr_len);
//        if (recv_result == -1) {
//            perror("read error");
//            goto destroy;
//        }
//        for (i = 0; i < recv_result; ++i) {
//            printf("%02x ", buff[i]);
//        }
//    }
destroy:
    tcp_pseudo_header_delete(pseudo_header);
    tcp_payload_delete(payload);
    tcp_header_delete(header);
    return 0;
}
