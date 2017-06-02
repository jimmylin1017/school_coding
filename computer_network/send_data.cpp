#include "send_data.h"

void send_init()
{
    slow_start = true;
    congestion_avoidance = false;
}

bool server_send_data()
{
    int file_size = 10240; // bytes

    int cwnd = 1, rwnd = file_size;

    cout<<"*****Slow start*****"<<endl;

    while (true)
    {
        if(slow_start)
        {
            sendto(server_sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_addr, len);
        }
    }
}