#ifndef GOOLNN_HELPERCHESS_THREAD_CLIENTTHREAD
#define GOOLNN_HELPERCHESS_THREAD_CLIENTTHREAD

#include <QThread>

class ClientThread:public QThread{
    public:
        void run();
        
};

#endif
