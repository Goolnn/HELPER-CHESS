#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QApplication>
#include <QHBoxLayout>
#include <QSplitter>
#include <QWidget>

#include <winsock2.h>

#include <iostream>

#include "window/Controller.hpp"
#include "window/Connect.hpp"
#include "window/Window.hpp"
#include "window/Viewer.hpp"
#include "tool/Byte.hpp"
#include "net/DataPack.hpp"
#include "net/Server.hpp"

using namespace std;

Window* window;
QString player;

/*
 * 助屋棋 | Helper Chess
 */
int main(int argc,char* argv[]){
    //客户端启动
    if(argc==1||(argc==2&&strcmp(argv[1],"-client")==0)){
        QApplication application=QApplication(argc,argv);
        window=new Window();

        window->show();

        return application.exec();
        
    //服务端启动
    }else if(argc==2&&strcmp(argv[1],"-server")==0){
        //初始化服务端参数
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2,2),&wsaData);

        struct sockaddr_in serveraddr;

        serveraddr.sin_family=AF_INET;
        serveraddr.sin_port=htons(20227);
        serveraddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");

        //创建服务端套接字
        SOCKET server=socket(AF_INET,SOCK_STREAM,0);

        //启动无阻塞通信
        unsigned long argp=1;
        ioctlsocket(server,FIONBIO,&argp);

        //绑定并启动监听
        bind(server,(sockaddr*)&serveraddr,sizeof(serveraddr));
        listen(server,0);

        //客户端列表
        QList<Client*> clients;

        //对局棋盘
        Chessboard chessboard=Chessboard();

        //对局者
        QString helpersPlayer;
        QString enemiesPlayer;

        Client* player1=nullptr;
        Client* player2=nullptr;

        //对局开始
        bool start=false;

        while(true){
            //连接客户端
            struct sockaddr_in clientaddr;
            int len=sizeof(clientaddr);
            SOCKET socket=accept(server,(sockaddr*)&clientaddr,&len);

            if(socket!=INVALID_SOCKET){
                clients.push_back(new Client(socket));

                cout<<" · 未命名客户端 - 连接成功"<<endl;

            }

            //处理客户端信息
            for(int i=0;i<clients.size();i++){
                Client* client=clients.at(i);

                DataPack dataPack=DataPack();
                int result=Server::read(client,&dataPack);

                if(result==0){
                    unsigned int head=dataPack.readUnsignedInt();

                    //判断用户是否传入用户名
                    if(client->getName().compare("")==0){
                        if(head==0){
                            QString name=dataPack.readString();

                            bool sameName=false;
                            
                            //检测重名
                            for(int j=0;j<clients.size();j++){
                                if(i!=j&&name.compare(clients.at(j)->getName())==0){
                                    sameName=true;
                                    break;

                                }

                            }

                            if(!sameName){
                                client->setName(name);

                                DataPack reply=DataPack();
                                reply.writeUnsignedInt(0);
                                reply.writeUnsignedInt(0);
                                Server::write(client,&reply);

                                //广播玩家列表
                                DataPack playerList=DataPack();

                                Byte helpers=0;
                                Byte randoms=0;
                                Byte enemies=0;

                                playerList.writeUnsignedInt(1);                  //写入头部信息
                                playerList.writeUnsignedInt(clients.size());     //写入玩家数量
                                
                                for(int i=0;i<clients.size();i++){
                                    Client* temp=clients.at(i);

                                    playerList.writeString(temp->getName());     //写入玩家名称
                                    playerList.writeByte(temp->getStatus());     //写入玩家状态

                                    if(temp->getStatus()==1)helpers++;
                                    if(temp->getStatus()==2)randoms++;
                                    if(temp->getStatus()==3)enemies++;

                                }

                                playerList.writeByte(helpers);
                                playerList.writeByte(randoms);
                                playerList.writeByte(enemies);

                                Server::write(&clients,&playerList);

                                if(start){
                                    //发送对局开始
                                    DataPack gameStart=DataPack();
                                    gameStart.writeUnsignedInt(4);
                                    gameStart.writeString(helpersPlayer);
                                    gameStart.writeString(enemiesPlayer);

                                    Byte data[48];
                                    chessboard.getData(data);
                                    gameStart.write((void*)data,48);

                                    Server::write(client,&gameStart);

                                }

                            }else{
                                DataPack reply=DataPack();
                                reply.writeUnsignedInt(0);
                                reply.writeUnsignedInt(1);
                                Server::write(client,&reply);

                            }

                        }

                    }else{
                        //请求玩家列表
                        if(head==1){
                            //广播玩家列表
                            DataPack playerList=DataPack();

                            Byte helpers=0;
                            Byte randoms=0;
                            Byte enemies=0;

                            playerList.writeUnsignedInt(1);                  //写入头部信息
                            playerList.writeUnsignedInt(clients.size());     //写入玩家数量
                            
                            for(int i=0;i<clients.size();i++){
                                Client* temp=clients.at(i);

                                playerList.writeString(temp->getName());     //写入玩家名称
                                playerList.writeByte(temp->getStatus());     //写入玩家状态

                                if(temp->getStatus()==1)helpers++;
                                if(temp->getStatus()==2)randoms++;
                                if(temp->getStatus()==3)enemies++;

                            }

                            playerList.writeByte(helpers);
                            playerList.writeByte(randoms);
                            playerList.writeByte(enemies);

                            Server::write(&clients,&playerList);

                        //请求棋盘状态
                        }else if(head==2){
                            DataPack reply=DataPack();

                            reply.writeUnsignedInt(2);                  //写入头部数据
                            //施工中 未完待续

                        }else if(head==3){
                            Byte status=dataPack.readByte();
                            client->setStatus(status);

                            //广播玩家列表
                            DataPack playerList=DataPack();

                            Byte helpers=0;
                            Byte randoms=0;
                            Byte enemies=0;

                            playerList.writeUnsignedInt(1);                  //写入头部信息
                            playerList.writeUnsignedInt(clients.size());     //写入玩家数量
                            
                            for(int i=0;i<clients.size();i++){
                                Client* temp=clients.at(i);

                                playerList.writeString(temp->getName());     //写入玩家名称
                                playerList.writeByte(temp->getStatus());     //写入玩家状态

                                if(temp->getStatus()==1)helpers++;
                                if(temp->getStatus()==2)randoms++;
                                if(temp->getStatus()==3)enemies++;

                            }

                            playerList.writeByte(helpers);
                            playerList.writeByte(randoms);
                            playerList.writeByte(enemies);

                            Server::write(&clients,&playerList);

                            //开始游戏判断
                            if(!start){
                                QList<Client*> ready;

                                for(int i=0;i<clients.size();i++){
                                    Client* temp=clients.at(i);

                                    if(temp->getStatus()!=0){
                                        ready.push_back(temp);

                                    }

                                }

                                if(ready.size()>=2){
                                    srand(time(0));

                                    int index1=0;
                                    int index2=0;

                                    do{
                                        index1=rand()%ready.size();
                                        index2=rand()%ready.size();

                                    }while(index1==index2);

                                    player1=ready.at(index1);
                                    player2=ready.at(index2);

                                    printf("\n");
                                    printf("%s %s\n",player1->getName().toStdString().data(),player2->getName().toStdString().data());
                                    printf("\n");

                                    Byte team1=player1->getStatus();
                                    Byte team2=player2->getStatus();

                                    //两厢情愿
                                    if(team1==1&&team2==3){
                                        helpersPlayer=player1->getName();
                                        enemiesPlayer=player2->getName();

                                    }else if(team1==3&&team2==1){
                                        helpersPlayer=player2->getName();
                                        enemiesPlayer=player1->getName();

                                    }

                                    //一方随机
                                    if(team1==2&&team2!=2){
                                        if(team2==1){
                                            helpersPlayer=player2->getName();
                                            enemiesPlayer=player1->getName();

                                        }else{
                                            helpersPlayer=player1->getName();
                                            enemiesPlayer=player2->getName();

                                        }

                                    }else if(team1!=2&&team2==2){
                                        if(team1==1){
                                            helpersPlayer=player1->getName();
                                            enemiesPlayer=player2->getName();

                                        }else{
                                            helpersPlayer=player2->getName();
                                            enemiesPlayer=player1->getName();

                                        }

                                    }

                                    //相互对峙
                                    if(team1==team2){
                                        helpersPlayer=player1->getName();
                                        enemiesPlayer=player2->getName();

                                    }

                                    //广播对局开始
                                    DataPack gameStart=DataPack();
                                    gameStart.writeUnsignedInt(4);
                                    gameStart.writeString(helpersPlayer);
                                    gameStart.writeString(enemiesPlayer);

                                    Byte data[48];
                                    chessboard.getData(data);
                                    gameStart.write((void*)data,48);

                                    Server::write(&clients,&gameStart);

                                    start=true;

                                }

                            }

                        }else if(head==6){
                            Bytes data=dataPack.read(48);

                            chessboard.setData(data.getData());

                            //广播棋盘
                            DataPack chessdata=DataPack();
                            chessdata.writeUnsignedInt(5);
                            chessdata.write((void*)data.getData(),48);
                            Server::write(&clients,&chessdata);

                            //胜负判断
                            if(chessboard.getPiece(2,0)!=PIECE_EMPTY||chessboard.getPiece(3,0)!=PIECE_EMPTY){
                                DataPack winner=DataPack();
                                winner.writeUnsignedInt(7);
                                winner.writeByte(0);
                                winner.writeString(helpersPlayer);
                                Server::write(&clients,&winner);

                                helpersPlayer="";
                                enemiesPlayer="";
                                start=false;
                                chessboard.clear();

                                player1->setStatus(0);
                                player2->setStatus(0);

                            }else if(chessboard.getPiece(2,7)!=PIECE_EMPTY||chessboard.getPiece(3,7)!=PIECE_EMPTY){
                                DataPack winner=DataPack();
                                winner.writeUnsignedInt(7);
                                winner.writeByte(1);
                                winner.writeString(enemiesPlayer);
                                Server::write(&clients,&winner);

                                helpersPlayer="";
                                enemiesPlayer="";
                                start=false;
                                chessboard.clear();

                                player1->setStatus(0);
                                player2->setStatus(0);

                            }

                        }

                    }

                //判断客户端是否关闭
                }else if(WSAGetLastError()==WSAECONNRESET||WSAGetLastError()==0){
                    if(client->getName().compare("")==0){
                        cout<<" · 未命名客户端 - 断开连接"<<endl;

                        clients.removeAt(i);

                    }else{
                        cout<<" · "<<client->getName().toStdString()<<" - 断开连接"<<endl;

                        clients.removeAt(i);

                        //广播玩家列表
                        DataPack playerList=DataPack();

                        Byte helpers=0;
                        Byte randoms=0;
                        Byte enemies=0;

                        playerList.writeUnsignedInt(1);                  //写入头部信息
                        playerList.writeUnsignedInt(clients.size());     //写入玩家数量
                        
                        for(int i=0;i<clients.size();i++){
                            Client* temp=clients.at(i);

                            playerList.writeString(temp->getName());     //写入玩家名称
                            playerList.writeByte(temp->getStatus());     //写入玩家状态

                            if(temp->getStatus()==1)helpers++;
                            if(temp->getStatus()==2)randoms++;
                            if(temp->getStatus()==3)enemies++;

                        }

                        playerList.writeByte(helpers);
                        playerList.writeByte(randoms);
                        playerList.writeByte(enemies);

                        Server::write(&clients,&playerList);

                    }

                    break;

                }

            }

            Sleep(1);

        }

    }

}
