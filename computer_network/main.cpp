#ifndef HEADER_H
#define HEADER_H
    #include "header.h"
#endif

#ifndef TCP_H
#define TCP_H
    #include "tcp.h"
#endif

void init()
{
    server_ip = "192.168.2.4";
    server_port = 12345;
    client_ip = "192.168.2.4";
    client_port = 12345;

    cout<<"====Parameter===="<<endl;
    cout<<"The RTT delay = "<<RTT<<" ms"<<endl;
    cout<<"The threshold = "<<THRESHOLD<<" bytes"<<endl;
    cout<<"The MSS = "<<MSS<<" bytes"<<endl;
    cout<<"The buffer size = "<<BUFFER_SIZE<<" bytes"<<endl;
    cout<<"Server's IP is "<<server_ip<<endl;
    cout<<"Server is listening on port "<<server_port<<endl;
    cout<<"==============="<<endl;
}

int main(int argc, char* argv[])
{
    int seq_num, port;
    string ip;
    int sockfd;

    Header h = {
        0,0,
        0,
        0,
        18,0,
        0,0,
        0
    };

    init();
    
    create_client();

/*
    if(argc > 1)
    {
        ip = argv[1];
        port = atoi(argv[2]);
        init(ip, port);
    }
    else
    {
        cout<<"please input ip and port number"<<endl;
        exit(1);
    }

    if(create_server())
    {
        DEBUG("create_server success\n");
        if(server_listen())
        {
            DEBUG("create_server success\n");
        }
    }
*/
    
    /*
    if(get_ack_flag(h))
        printf("ACK\n");
    else
        printf("no ACK\n");
    return 0;*/
}