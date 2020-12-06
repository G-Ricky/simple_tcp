#ifndef SIMPLE_TCP_UTIL_PRINTER_H
#define SIMPLE_TCP_UTIL_PRINTER_H

#include "tcp_header.h"
#include "tcp_pseudo_header.h"

void printer_print_tcp_header(tcp_header *header);

void printer_print_tcp_pseudo_header(tcp_pseudo_header *pseudo_header);

#endif //SIMPLE_TCP_UTIL_PRINTER_H
