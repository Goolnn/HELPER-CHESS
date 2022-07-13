#ifndef GOOLNN_HELPERCHESS_NET_SERVER
#define GOOLNN_HELPERCHESS_NET_SERVER

#include <QString>
#include <QList>

#include <winsock2.h>

#include "tool/Byte.hpp"
#include "net/DataPack.hpp"

class Client{
    private:
        SOCKET socket;
        QString name;

        //0 - 未准备
        //1 - 准备（助屋）
        //2 - 准备（随机）
        //3 - 准备（敌组）
        Byte status;           //玩家准备状态
    
    public:
        Client(SOCKET socket);

        void setName(QString name);
        void setStatus(Byte status);
        
        SOCKET getSocket();
        QString getName();
        Byte getStatus();

};

namespace Server{
    void write(QList<Client*>* clients,DataPack* dataPack);
    void write(Client* client,DataPack* dataPack);
    
    int read(Client* client,DataPack* dataPack);

};

#endif
