#include "threeway.h"

bool server_three_way(Tcp_pkt p)
{
    Tcp_pkt snd_pkt, rcv_pkt = p;

    snd_pkt = server_tcp_pkt_init();
    socklen_t len = sizeof(client_addr);

    cout<<"=====Start the three-way handshake====="<<endl;
    printf("Receive a packet(SYN) from %s : %u\n", inet_ntoa(client_addr.sin_addr), htons(rcv_pkt.header.src_port));
    printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

    seq_num = (rand() % 10000) + 1;

    snd_pkt.header.seq_num = seq_num;
    snd_pkt.header.ack_num = rcv_pkt.header.ack_num + 1;
    snd_pkt.header.flag = 18; // ack = 16 + syn = 2

    sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);

    printf("Send a packet(SYN/ACK) to %s : %u\n", inet_ntoa(client_addr.sin_addr), htons(rcv_pkt.header.src_port));

    while(recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
    {
        if(get_ack_flag(rcv_pkt.header))
        {
            printf("Receive a packet(SYN) from %s : %u\n", inet_ntoa(client_addr.sin_addr), htons(rcv_pkt.header.src_port));
            printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

            return true;
        }
    }
    return false;
}

bool client_three_way()
{
    Tcp_pkt snd_pkt, rcv_pkt = p;

    snd_pkt = server_tcp_pkt_init();
    socklen_t len = sizeof(client_addr);

    cout<<"=====Start the three-way handshake====="<<endl;
    printf("Receive a packet(SYN) from %s : %u\n", inet_ntoa(client_addr.sin_addr), htons(rcv_pkt.header.src_port));
    printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

    seq_num = (rand() % 10000) + 1;

    snd_pkt.header.seq_num = seq_num;
    snd_pkt.header.ack_num = rcv_pkt.header.ack_num + 1;
    snd_pkt.header.flag = 18; // ack = 16 + syn = 2

    sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);

    printf("Send a packet(SYN/ACK) to %s : %u\n", inet_ntoa(client_addr.sin_addr), htons(rcv_pkt.header.src_port));

    while(recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
    {
        if(get_ack_flag(rcv_pkt.header))
        {
            printf("Receive a packet(SYN) from %s : %u\n", inet_ntoa(client_addr.sin_addr), htons(rcv_pkt.header.src_port));
            printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

            return true;
        }
    }
    return false;
}