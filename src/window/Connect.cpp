#include <QStackedWidget>

#include <pthread.h>

#include "window/Controller.hpp"
#include "window/Connect.hpp"
#include "window/Window.hpp"
#include "thread/ClientThread.hpp"
#include "net/Client.hpp"

extern QString player;

Connect::Connect(QWidget* parent):QWidget(parent){
    this->hLayout1.addStretch();
    this->hLayout1.addWidget(&addressLabel);
    this->hLayout1.addWidget(&addressInputer);
    this->hLayout1.addStretch();

    this->hLayout2.addStretch();
    this->hLayout2.addWidget(&nameLabel);
    this->hLayout2.addWidget(&nameInputer);
    this->hLayout2.addStretch();

    this->hLayout3.addStretch();
    this->hLayout3.addWidget(&connectButton);
    this->hLayout3.addStretch();

    this->layout.addStretch();
    this->layout.addLayout(&hLayout1);
    this->layout.addLayout(&hLayout2);
    this->layout.addLayout(&hLayout3);
    this->layout.addStretch();

    this->setLayout(&layout);

    QObject::connect(&this->connectButton,SIGNAL(clicked()),this,SLOT(connect()));

}

void Connect::connect(){
    QStringList list=this->addressInputer.text().split(":");

    QString address=list.at(0);
    int port=list.at(1).toInt();
    QString name=this->nameInputer.text();

    if(!Client::isConnected()){
        Client::connect(address,port);

        ClientThread* clientThread=new ClientThread();
        clientThread->start();

    }

    DataPack dataPack=DataPack();
    dataPack.writeUnsignedInt(0);
    dataPack.writeString(name);

    Client::write(&dataPack);

    player=name;

    // DataPack reply=DataPack();
    // while(Client::read(&reply)!=0);

    // unsigned int head=reply.readUnsignedInt();
    
    // if(head==0){
    //     if(reply.readUnsignedInt()==0){
    //         QStackedWidget* window=(QStackedWidget*)this->window();
    //         window->setCurrentIndex(1);

    //         //请求玩家列表
    //         DataPack a=DataPack();
    //         a.writeUnsignedInt(1);

    //         Client::write(&a);

    //         //获取回复数据
    //         DataPack b=DataPack();
    //         while(Client::read(&b)!=0);

    //         head=b.readUnsignedInt();
    //         unsigned int size=b.readUnsignedInt();

    //         printf("头部数据：%d 玩家数量：%d\n",head,size);

    //         for(unsigned int i=0;i<size;i++){
    //             QString name=b.readString();
    //             Byte status=b.readByte();

    //             printf("%d - %s\n",status,name.toStdString().data());

    //         }

    //     }

    // }
    
}
