#include "fourway.h"

bool server_four_way(Tcp_pkt p)
{
    Tcp_pkt snd_pkt, rcv_pkt = p;

    snd_pkt = server_tcp_pkt_init();
    socklen_t len = sizeof(client_addr);

    cout<<"=====Start the four-way handshake====="<<endl;
    printf("Receive a packet(FIN) from %s : %u\n", inet_ntoa(client_addr.sin_addr), rcv_pkt.header.src_port);
    printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

    // send ack for fin
    snd_pkt.header.seq_num = ++server_seq_num;
    snd_pkt.header.ack_num = rcv_pkt.header.seq_num + 1;
    snd_pkt.header.flag = 16; // ack = 16

    sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);

    printf("Send a packet(ACK) to %s : %u\n", inet_ntoa(client_addr.sin_addr), rcv_pkt.header.src_port);

    sleep(2);
    // send fin
    snd_pkt.header.seq_num = ++server_seq_num;
    snd_pkt.header.ack_num = rcv_pkt.header.seq_num + 1;
    snd_pkt.header.flag = 1; // fin = 1

    sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);

    printf("Send a packet(FIN) to %s : %u\n", inet_ntoa(client_addr.sin_addr), rcv_pkt.header.src_port);

    while(recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
    {
        if(get_ack_flag(rcv_pkt.header))
        {
            printf("Receive a packet(ACK) from %s : %u\n", inet_ntoa(client_addr.sin_addr), rcv_pkt.header.src_port);
            printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);
            server_ack_num = rcv_pkt.header.seq_num + 1;

            close(server_sockfd);
            cout<<"=====Complete the four-way handshake====="<<endl;

            return true;
        }
    }
    return false;
}

bool client_four_way()
{
    Tcp_pkt snd_pkt, rcv_pkt;

    snd_pkt = client_tcp_pkt_init();
    
    socklen_t len = sizeof(server_addr);

    snd_pkt.header.seq_num = ++client_seq_num;
    snd_pkt.header.ack_num = client_ack_num;
    snd_pkt.header.flag = 1; // fin = 1

    cout<<"=====Start the four-way handshake====="<<endl;

    sendto(client_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&send_addr, len);

    printf("Send a packet(FIN) to %s : %u\n", inet_ntoa(send_addr.sin_addr), htons(send_addr.sin_port));

    while(recvfrom(client_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&send_addr, (socklen_t *)&len) != -1)
    {
        if(get_ack_flag(rcv_pkt.header))
        {
            printf("Receive a packet(ACK) from %s : %u\n", inet_ntoa(send_addr.sin_addr), rcv_pkt.header.src_port);
            printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

            break;
        }
    }

    while(recvfrom(client_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&send_addr, (socklen_t *)&len) != -1)
    {
        if(get_fin_flag(rcv_pkt.header))
        {
            printf("Receive a packet(FIN) from %s : %u\n", inet_ntoa(send_addr.sin_addr), rcv_pkt.header.src_port);
            printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

            break;
        }
    }

    snd_pkt.header.seq_num = ++client_seq_num;
    snd_pkt.header.ack_num += 1;
    snd_pkt.header.flag = 16; // ack = 16

    sendto(client_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&send_addr, len);

    printf("Send a packet(ACK) to %s : %u\n", inet_ntoa(send_addr.sin_addr), htons(send_addr.sin_port));

    close(client_sockfd);
    cout<<"=====Complete the four-way handshake====="<<endl;

    return true;
}