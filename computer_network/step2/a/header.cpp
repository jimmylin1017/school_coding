#include "header.h"

string server_ip, send_ip, from_ip;
int server_port, send_port, from_port;
int server_sockfd, client_sockfd;
struct sockaddr_in server_addr, client_addr;
struct sockaddr_in send_addr, from_addr;

int server_seq_num, server_ack_num;
int client_seq_num, client_ack_num;

map<string, string> nat_map;

Tcp_pkt server_tcp_pkt_init()
{
    Tcp_pkt p;
    memset(p.data, '\0', sizeof(p.data));
    p.header.src_port = server_port;

    return p;
}

Tcp_pkt client_tcp_pkt_init()
{
    Tcp_pkt p;
    memset(p.data, '\0', sizeof(p.data));
    p.header.src_port = from_port;

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

void nat_map_init()
{
    nat_map["192.168.0.1"] = "10.0.0.1";
    nat_map["192.168.0.2"] = "10.0.0.2";
    nat_map["10.0.0.1"] = "192.168.0.1";
    nat_map["10.0.0.2"] = "192.168.0.2";
}