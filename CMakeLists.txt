cmake_minimum_required(VERSION 2.8)
project(simple_tcp C)

set(CMAKE_C_STANDARD 99)

include_directories(tcp)

add_executable(simple_tcp
    main.c
    main_demo.c
    tcp/tcp_header.c
    tcp/tcp_header.h
    tcp/tcp_header_raw.c
    tcp/tcp_header_raw.h
    tcp/tcp_option.c
    tcp/tcp_option.h
    tcp/tcp_option_raw.c
    tcp/tcp_option_raw.h
    tcp/tcp_payload.c
    tcp/tcp_payload.h
    tcp/tcp_payload_raw.c
    tcp/tcp_payload_raw.h
    tcp/tcp_pseudo_header.c
    tcp/tcp_pseudo_header.h
    tcp/tcp_pseudo_header_raw.c
    tcp/tcp_pseudo_header_raw.h
    util/printer.c
    util/printer.h
    util/tcp_util.c
    util/tcp_util.h
)