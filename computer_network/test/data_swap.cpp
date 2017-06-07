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

    int cwnd = 1, rwnd = BUFFER_SIZE, threshold = THRESHOLD;
    int send_byte_index = 1, need_send_byte = 0, send_byte = 0;
    int send_packet = 0, receive_packet = 0;
    
    // check dup_ack
    int dup_ack = 0, loss_packet = 2560;
    map<int, int> dup_map;

    Tcp_pkt snd_pkt, rcv_pkt;

    snd_pkt = server_tcp_pkt_init();
    socklen_t len = sizeof(client_addr);

    printf("Start to send the file, the file size is %d bytes.\n", file_size);
    cout<<"*****Slow start*****"<<endl;

    // first send
    snd_pkt.header.ack_num = server_ack_num;
    snd_pkt.header.flag = 0;

    while(rwnd > 0)
    {
        printf("cwnd = %d, rwnd = %d, threshold = %d\n", cwnd, rwnd, threshold);
        need_send_byte = min(cwnd, file_size);
        send_packet = 0;

        while(need_send_byte > 0)
        {
            if(need_send_byte >= MSS)
                send_byte = MSS;
            else
                send_byte = need_send_byte;

            need_send_byte -= send_byte;

            memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));
            for(int i=0; i<send_byte; i++)
                snd_pkt.data[i] = 'A';
            
            snd_pkt.header.seq_num = send_byte_index;
            snd_pkt.header.ack_num += 1;

            if(loss_packet == send_byte_index)
            {
                loss_packet = 0;
                printf("\tSend a packet at : %d byte\n***loss at %d byte***\n", send_byte_index, send_byte_index);
            }
            else
            {
                sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);
                printf("\tSend a packet at : %d byte\n", send_byte_index);
            }

            if(dup_map.find(send_byte_index) != dup_map.end())
            {
                dup_map[send_byte_index] = 0;
            }
            else
            {
                dup_map.insert(pair<int, int>(send_byte_index, 0));
            }

            send_packet++;
            send_byte_index += send_byte;
            file_size -= send_byte;
            rwnd -= send_byte;
        }

        receive_packet = 0;
        while(recvfrom(server_sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_addr, (socklen_t *)&len) != -1)
        {
            if(get_ack_flag(rcv_pkt.header))
            {
                printf("\tReceive a packet (seq_num = %u, ack_num = %u)\n", rcv_pkt.header.seq_num, rcv_pkt.header.ack_num);
                rwnd = BUFFER_SIZE - rcv_pkt.header.window_size;
                receive_packet++;

                // check dup_ack
                if(dup_map.find(rcv_pkt.header.ack_num) != dup_map.end())
                {
                    dup_map[rcv_pkt.header.ack_num]++;
                }
                else
                {
                    dup_map.insert(pair<int, int>(rcv_pkt.header.ack_num, 1));
                }

                if(dup_map[rcv_pkt.header.ack_num] == 3)
                {
                    dup_ack = 1;
                    DEBUG("find dup_ack %d\n", rcv_pkt.header.ack_num);
                }

                send_byte_index = rcv_pkt.header.ack_num;
            }

            if(receive_packet == send_packet || dup_ack)
                break;
        }

        if(dup_ack)
        {
            cout<<"Receive three duplicate ACKs"<<endl;
            cout<<"*****Fast recovery*****"<<endl;
            cout<<"*****Congestion avoidance*****"<<endl;
            threshold = cwnd / 2;
            cwnd = threshold;
            file_size = rwnd;
            slow_start = false;
            congestion_avoidance = true;
            send_byte_index = rcv_pkt.header.ack_num;
            dup_ack = 0;
            DEBUG("find dup_ack\nfile_size %d\n", file_size);
            continue;
        }

        if(slow_start)
        {
            cwnd *= 2;
            if(cwnd >= threshold)
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
    int before_receive_byte = 0;
    int request_byte_index = 1;
    int dup_ack = 0;

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

        
        if(request_byte_index == rcv_pkt.header.seq_num)
        {
            receive_byte = receive_byte + strlen((char*)rcv_pkt.data);
            request_byte_index = receive_byte + 1;
            DEBUG("request_byte_index %d\n", request_byte_index);
        }

        DEBUG("receive_byte %d\n", receive_byte);
        snd_pkt.header.seq_num = ++client_seq_num;
        snd_pkt.header.ack_num = request_byte_index;
        snd_pkt.header.flag = 16; // ack = 16
        snd_pkt.header.window_size = receive_byte;

        sendto(client_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&send_addr, len);
        send_packet++;

        if(receive_byte == BUFFER_SIZE)
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