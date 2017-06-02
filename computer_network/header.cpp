#include "header.h"

string server_ip, client_ip;
int server_port, client_port;
int server_sockfd, client_sockfd;
struct sockaddr_in server_addr, client_addr;

int seq_num, ack_num;

Tcp_pkt server_tcp_pkt_init()
{
    Tcp_pkt p;
    memset(p.data, 0, sizeof(p.data));
    p.header.src_port = server_port;

    return p;
}

Tcp_pkt client_tcp_pkt_init()
{
    Tcp_pkt p;
    memset(p.data, 0, sizeof(p.data));
    p.header.src_port = client_port;

    return p;
}

bool get_fin_flag(Header h)
{
    return (h.flag) & 1 ? true : false;
}

bool get_syn_flag(Header h)
{
    return (h.flag) & 2 ? true : false;
}

bool get_rts_flag(Header h)
{
    return (h.flag) & 4 ? true : false;
}

bool get_ack_flag(Header h)
{
    return (h.flag) & 16 ? true : false;
}