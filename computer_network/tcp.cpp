#include "tcp.h"

/*******

struct sockaddr_in {
    sa_family_t sin_family; // address family: AF_INET
    in_port_t sin_port; // port in network byte order
    struct in_addr sin_addr; // internet address
};

// Internet address.
struct in_addr {
    uint32_t s_addr;     // address in network byte order
};

*******/

bool create_server()
{
    // create UDP socket
    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(server_sockfd < 0)
    {
        perror("server_sockfd failed: ");
        return false;
    }

    // initialize address
    memset((char *)&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str()); // convert c string to uint32_t
    server_addr.sin_port = htons(server_port); // convert values between host and network byte order

    if(bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("server_sockfd bind failed: ");
        return false;
    }

    return true;
}

bool server_listen()
{
    Tcp_pkt snd_pkt, rcv_pkt;
    
    snd_pkt = server_tcp_pkt_init();
    socklen_t len = sizeof(client_addr);
    while (recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
    {
        if(get_syn_flag(rcv_pkt.header))
        {
            if(server_three_way(rcv_pkt)) return true;
        }
    }
}

bool create_client()
{
    // create UDP socket
    client_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(server_sockfd < 0)
    {
        perror("client_sockfd failed: ");
        return false;
    }

    // initialize address
    memset((char *)&client_addr, '\0', sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(client_ip.c_str()); // convert c string to uint32_t
    client_addr.sin_port = htons(client_port); // convert values between host and network byte order
}