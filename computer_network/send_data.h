#ifndef HEADER_H
#define HEADER_H
#include "header.h"
#endif

bool slow_start;
bool congestion_avoidance;

void send_init();
bool server_send_data();
bool server_reveive_data();