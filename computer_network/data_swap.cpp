#include "data_swap.h"

void send_init()
{
    slow_start = true;
    congestion_avoidance = false;
}

bool server_send_data()
{
    int file_size = FILE_SIZE; // bytes

    int cwnd = 1, rwnd = BUFFER_SIZE, send_byte = 1;

    Tcp_pkt snd_pkt, rcv_pkt;

    snd_pkt = server_tcp_pkt_init();
    socklen_t len = sizeof(client_addr);

    cout<<"*****Slow start*****"<<endl;
    server_seq_num = 1;

    // first send
    snd_pkt.header.seq_num = server_seq_num;
    snd_pkt.header.ack_num = server_ack_num;
    snd_pkt.header.flag = 0;

    printf("cwnd = %d, rwnd = %d, threshold = %d\n", cwnd, rwnd, THRESHOLD);
    sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);

    while(recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
    {
        // other send
        if(get_ack_flag(rcv_pkt.header))
        {
            


            
            printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);
        }
    }

    // other send
    while (send_byte <= file_size)
    {
        rwnd -= send_byte;
        server_seq_num += send_byte;
        cwnd += send_byte;
        send_byte *= 2;
        
        snd_pkt.header.seq_num = server_seq_num;
        snd_pkt.header.ack_num = rcv_pkt.header.seq_num + 1;
        snd_pkt.header.flag = 0;

        printf("cwnd = %d, rwnd = %d, threshold = %d\n", cwnd, rwnd, THRESHOLD);
        sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);

        while(recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
        {
            if(get_ack_flag(rcv_pkt.header))
            {
                printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);
                break;
            }
        }


        /*if(slow_start)
        {
            sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);
        }*/
    }
}