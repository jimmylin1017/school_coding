#include "data_swap.h"

void send_init()
{
    slow_start = true;
    congestion_avoidance = false;
}

bool server_send_data()
{
    send_init();
    
    int file_size = FILE_SIZE; // bytes

    int cwnd = 1, rwnd = BUFFER_SIZE;
    int send_byte_index = 1, need_send_byte = 0, send_byte = 0, send_packet = 0, receive_packet = 0;

    Tcp_pkt snd_pkt, rcv_pkt;

    snd_pkt = server_tcp_pkt_init();
    socklen_t len = sizeof(client_addr);

    printf("Start to send the file, the file size is %d bytes.\n", file_size);
    cout<<"*****Slow start*****"<<endl;

    // first send
    server_seq_num = 1;
    snd_pkt.header.seq_num = server_seq_num;
    snd_pkt.header.ack_num = server_ack_num;
    snd_pkt.header.flag = 0;

    while(rwnd > 0 && file_size > 0)
    {
        printf("cwnd = %d, rwnd = %d, threshold = %d\n", cwnd, rwnd, THRESHOLD);
        need_send_byte = min(cwnd, file_size);
        send_packet = 0;
        while(rwnd > 0 && need_send_byte > 0 && file_size > 0)
        {
            //DEBUG("need_send_byte : %d\n", need_send_byte);

            if(need_send_byte >= MSS)
                send_byte = MSS;
            else
                send_byte = need_send_byte;

            need_send_byte -= send_byte;

            memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));
            for(int i=0; i<send_byte; i++)
                snd_pkt.data[i] = 'A';

            sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);
            printf("\tSend a packet at : %d byte\n", send_byte_index);
            
            snd_pkt.header.seq_num += send_byte;
            snd_pkt.header.ack_num += 1;
            send_byte_index += send_byte;

            file_size -= send_byte;
            rwnd -= send_byte;
            send_packet++;
        }
        
        receive_packet = 0;
        while(recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
        {
            if(get_ack_flag(rcv_pkt.header))
            {
                printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);
                rwnd = BUFFER_SIZE - rcv_pkt.header.window_size;
                receive_packet++;
            }

            if(receive_packet == send_packet)
            {
                break;
            }
        }

        if(slow_start)
        {
            cwnd *= 2;
            if(cwnd >= THRESHOLD)
            {
                slow_start = false;
                congestion_avoidance = true;
                cout<<"*****Congestion avoidance*****"<<endl;
            }
        }
        else if(congestion_avoidance)
        {
            cwnd += MSS;
        }
    }

    DEBUG("server_send_data finish\n");

    server_ack_num = snd_pkt.header.ack_num + 1;
    server_seq_num = snd_pkt.header.seq_num;

    return true;
}

bool client_receive_data()
{
    int file_size = FILE_SIZE; // bytes

    int cwnd = 1, rwnd = BUFFER_SIZE;
    int before_seq_num = 0, receive_byte = 0, send_packet = 0, receive_packet = 0;

    Tcp_pkt snd_pkt, rcv_pkt;

    snd_pkt = client_tcp_pkt_init();
    snd_pkt.header.ack_num = 0;
    
    socklen_t len = sizeof(server_addr);
   
    while(recvfrom(client_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&send_addr, (socklen_t *)&len) != -1)
    {
        receive_packet++;
        if(receive_packet == 1)
            printf("Receive a file from %s : %u\n", inet_ntoa(send_addr.sin_addr), rcv_pkt.header.src_port);

        printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);

        receive_byte = receive_byte + strlen((char*)rcv_pkt.data);
        before_seq_num = rcv_pkt.header.seq_num;

        if(receive_byte + 1 <= BUFFER_SIZE)
        {
            snd_pkt.header.seq_num = ++client_seq_num;
            snd_pkt.header.ack_num = receive_byte + 1;
            snd_pkt.header.flag = 16; // ack = 16
            snd_pkt.header.window_size = receive_byte;

            sendto(client_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&send_addr, len);
            send_packet++;
        }
        else if(receive_byte + 1 > BUFFER_SIZE)
        {
            DEBUG("client_receive_data finish\n");

            snd_pkt.header.seq_num = ++client_seq_num;
            snd_pkt.header.ack_num = receive_byte + 1;
            snd_pkt.header.flag = 16; // ack = 16

            sendto(client_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&send_addr, len);
            send_packet++;
            break;
        }
    }

    client_ack_num = snd_pkt.header.ack_num + 1;

    return true;
}