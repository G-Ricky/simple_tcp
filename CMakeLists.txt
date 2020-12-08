cmake_minimum_required(VERSION 2.8)
project(simple_tcp C)

set(CMAKE_C_STANDARD 99)

include_directories(src)

add_executable(simple_tcp
    main.c
    main_demo.c
    src/tcp/tcp_header.c
    src/tcp/tcp_header.h
    src/tcp/tcp_header_raw.c
    src/tcp/tcp_header_raw.h
    src/tcp/tcp_option.c
    src/tcp/tcp_option.h
    src/tcp/tcp_option_raw.c
    src/tcp/tcp_option_raw.h
    src/tcp/tcp_payload.c
    src/tcp/tcp_payload.h
    src/tcp/tcp_payload_raw.c
    src/tcp/tcp_payload_raw.h
    src/tcp/tcp_pseudo_header.c
    src/tcp/tcp_pseudo_header.h
    src/tcp/tcp_pseudo_header_raw.c
    src/tcp/tcp_pseudo_header_raw.h
    src/util/printer.c
    src/util/printer.h
    src/util/tcp_util.c
    src/util/tcp_util.h
)