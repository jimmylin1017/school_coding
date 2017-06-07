#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <thread>

#include <sys/types.h>

using namespace std;

#ifdef _DEBUG
    #define DEBUG(format, args...) printf("[%s:%d] " format, __FILE__, __LINE__, ##args)
#else
    #define DEBUG(format, args...)
#endif

#define RTT 200
#define THRESHOLD 4096
#define MSS 512
#define BUFFER_SIZE 10241
#define LOCALIP "127.0.0.1"
#define FILE_SIZE 10241

typedef struct header
{
    unsigned short src_port; // Source port (16 bits)
    unsigned short des_port; // Destination port (16 bits)
    unsigned int seq_num; // Sequence number (32 bits)
    unsigned int ack_num; // Acknowledgment number (32 bits)
    unsigned short flag; // Data offset (4 bits) + not use 6 bit + UAPRSF 6 bit
    unsigned short window_size; // Window Size (Receive Window) 16 bit
    unsigned short checksum; // Checksum 16 bit
    unsigned short urg; // Urgent pointer (if URG set) 16 bit
    unsigned int options; // Options

} Header;

typedef struct tcp_pkt
{
    Header header;
    unsigned char data[MSS];
} Tcp_pkt;

/**********

server: server_ip, server_port, server_sockfd, server_addr, client_addr

client: send_ip, from_ip, send_port, from_port, client_sockfd, send_addr, from_addr

**********/
extern string server_ip, send_ip, from_ip;
extern int server_port, send_port, from_port;
extern int server_sockfd, client_sockfd;
extern struct sockaddr_in server_addr, client_addr;
extern struct sockaddr_in send_addr, from_addr;

extern int server_seq_num, server_ack_num;
extern int client_seq_num, client_ack_num;

Tcp_pkt server_tcp_pkt_init();
Tcp_pkt client_tcp_pkt_init();
bool get_fin_flag(Header h);
bool get_syn_flag(Header h);
bool get_rts_flag(Header h);
bool get_ack_flag(Header h);