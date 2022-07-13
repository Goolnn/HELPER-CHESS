#ifndef GOOLNN_HELPERCHESS_NET_CLIENT
#define GOOLNN_HELPERCHESS_NET_CLIENT

#include <QString>

#include <winsock2.h>

#include "net/DataPack.hpp"

namespace Client{
    void connect(QString address,int port);

    void write(DataPack* dataPack);
    int read(DataPack* dataPack);

    void close();

    bool isConnected();

};

#endif
