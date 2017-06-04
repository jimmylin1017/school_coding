#include "tcp.h"

void init(int port)
{
    server_ip = LOCALIP;
    server_port = port;
    from_ip = LOCALIP;
    from_port = port;

    cout<<"====Parameter===="<<endl;
    cout<<"The RTT delay = "<<RTT<<" ms"<<endl;
    cout<<"The threshold = "<<THRESHOLD<<" bytes"<<endl;
    cout<<"The MSS = "<<MSS<<" bytes"<<endl;
    cout<<"The buffer size = "<<BUFFER_SIZE<<" bytes"<<endl;
    cout<<"Server's IP is "<<server_ip<<endl;
    cout<<"Server is listening on port "<<server_port<<endl;
    cout<<"==============="<<endl;
}

void run_server()
{
    if(create_server())
    {
        DEBUG("create_server success\n");
        if(server_listen())
        {
            DEBUG("server_listen success\n");
        }   
    }
}

void run_client()
{
    cout<<"(ClientFunction)Please Input Node [IP] [Port] you want to connect"<<endl;
    cin>>send_ip>>send_port;
    if(create_client())
    {
        DEBUG("create_client success\n");
        if(client_connect())
        {
            DEBUG("client_connect success\n");
        }
    }
}

int main(int argc, char* argv[])
{
    int seq_num, port;
    string ip;
    int sockfd;

    srand(time(NULL)); // use for random sequence num

    // test for header structure
    Header h = {
        0,0,
        0,
        0,
        18,0,
        0,0,
        0
    };

    cout<<htons(INADDR_ANY)<<endl;

    if(argc > 1)
    {
        init(atoi(argv[argc-1]));
    }
    else
    {
        cout<<"Please input port"<<endl;
        exit(1);
    }

    thread server_thread(run_server);
    thread client_thread(run_client);

    while(1);
    
    /*
    if(get_ack_flag(h))
        printf("ACK\n");
    else
        printf("no ACK\n");
    return 0;*/
}