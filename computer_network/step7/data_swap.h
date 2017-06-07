#ifndef HEADER_H
#define HEADER_H
    #include "header.h"
#endif

static bool slow_start;
static bool congestion_avoidance;

void send_init();
bool server_send_data();
bool client_receive_data(); 