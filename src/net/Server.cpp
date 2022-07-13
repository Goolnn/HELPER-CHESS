#include <iostream>

#include "net/Server.hpp"

using namespace std;

void Server::write(Client* client,DataPack* dataPack){
    unsigned int size=dataPack->getSize();

    send(client->getSocket(),(const char*)&size,4,0);
    send(client->getSocket(),(const char*)dataPack->getData(),size,0);

    if(client->getName().compare("")==0){
        cout<<" > 未命名客户端 - "<<dataPack->getSize()<<"字节 - ";
        PrintBytes(dataPack->getData(),dataPack->getSize());

    }else{
        cout<<" > "<<client->getName().toStdString()<<" - "<<dataPack->getSize()<<"字节 - ";
        PrintBytes(dataPack->getData(),dataPack->getSize());

    }

}

void Server::write(QList<Client*>* clients,DataPack* dataPack){
    unsigned int size=dataPack->getSize();

    for(int i=0;i<clients->size();i++){
        Client* client=clients->at(i);

        send(client->getSocket(),(const char*)&size,4,0);
        send(client->getSocket(),(const char*)dataPack->getData(),size,0);

        if(client->getName().compare("")==0){
            cout<<" > 未命名客户端 - "<<dataPack->getSize()<<"字节 - ";
            PrintBytes(dataPack->getData(),dataPack->getSize());

        }else{
            cout<<" > "<<client->getName().toStdString()<<" - "<<dataPack->getSize()<<"字节 - ";
            PrintBytes(dataPack->getData(),dataPack->getSize());

        }

    }
    
}

int Server::read(Client* client,DataPack* dataPack){
    unsigned int size;
    int len=recv(client->getSocket(),(char*)&size,sizeof(int),0);

    if(len==-1||len==0){
        return -1;

    }else{
        Byte data[size];

        while(true){
            len=recv(client->getSocket(),(char*)data,size,0);

            if(len!=-1&&len!=0){
                break;

            }

        }

        dataPack->write(data,size);
        dataPack->seek(0);

        if(client->getName().compare("")==0){
            cout<<" < 未命名客户端 - "<<dataPack->getSize()<<"字节 - ";
            PrintBytes(dataPack->getData(),dataPack->getSize());

        }else{
            cout<<" < "<<client->getName().toStdString()<<" - "<<dataPack->getSize()<<"字节 - ";
            PrintBytes(dataPack->getData(),dataPack->getSize());

        }

        return 0;
        
    }

}

Client::Client(SOCKET socket){
    this->socket=socket;

    this->status=0;

}

void Client::setName(QString name){
    this->name=name;

}

void Client::setStatus(Byte status){
    this->status=status;
    
}

SOCKET Client::getSocket(){
    return this->socket;

}

QString Client::getName(){
    return this->name;

}

Byte Client::getStatus(){
    return this->status;

}
