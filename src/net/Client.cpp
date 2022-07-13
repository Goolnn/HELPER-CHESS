#include "net/Client.hpp"

SOCKET server;

bool connected=false;

void Client::connect(QString address,int port){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);

    struct sockaddr_in serveraddr;

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.S_un.S_addr=inet_addr(address.toStdString().data());

    server=socket(AF_INET,SOCK_STREAM,0);

    unsigned long argp=1;
    ioctlsocket(server,FIONBIO,&argp);

    connect(server,(sockaddr*)&serveraddr,sizeof(serveraddr));

    connected=true;

}

void Client::write(DataPack* dataPack){
    unsigned int size=dataPack->getSize();

    while(send(server,(const char*)&size,4,0)==-1);
    send(server,(const char*)dataPack->getData(),size,0);

}

int Client::read(DataPack* dataPack){
    unsigned int size;
    int len=recv(server,(char*)&size,sizeof(int),0);

    if(len==-1||len==0){
        return -1;

    }else{
        Byte data[size];

        while(true){
            len=recv(server,(char*)data,size,0);

            if(len!=-1&&len!=0){
                break;

            }

        }

        dataPack->write(data,size);
        dataPack->seek(0);

        return 0;
        
    }

}

void Client::close(){
    closesocket(server);

}

bool Client::isConnected(){
    return connected;

}
