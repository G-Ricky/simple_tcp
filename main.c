#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <tcp/tcp_header.h>
#include <tcp/tcp_payload.h>
#include <tcp/tcp_pseudo_header.h>
#include <util/printer.h>
#include <util/tcp_util.h>
#include <tcp/tcp_stream.h>

#define BUFF_SIZE 2048

int main(int argc, const char **argv) {
    if (argc < 3) {
        puts("usage: ./simple_tcp [ip] [port]");
        return -1;
    }
    char *endptr = NULL;
    const char *dst_ad = argv[1];
    uint32_t dst_addr = ntohl(inet_addr(dst_ad));
    uint16_t dst_port = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0') {
        puts("parse port fail.");
        return -1;
    }
    printf("trying to connect: %s:%s\n", argv[1], argv[2]);
    // 创建 socket
    tcp_stream *stream = tcp_stream_new(dst_ad, dst_port);
    // 连接
    tcp_stream_connect(stream);
    tcp_stream_delete(stream);

    return 0;
}
