#include "window/Window.hpp"
#include "thread/ClientThread.hpp"
#include "net/DataPack.hpp"
#include "net/Client.hpp"

extern Window* window;
extern QString player;

bool playing=false;

void ClientThread::run(){
    while(true){
        if(Client::isConnected()){
            //数据接收
            DataPack input=DataPack();
            int result=Client::read(&input);

            if(result==0){
                printf(" < ");
                PrintBytes(input.getData(),input.getSize());

                unsigned int head=input.readUnsignedInt();

                if(head==0){
                    unsigned int status=input.readUnsignedInt();

                    if(status==0){
                        window->setWindowTitle(QString("助屋棋 - %1").arg(player));

                        window->connect.setParent(nullptr);

                        window->splitter.setParent(window);
                        window->splitter.setGeometry(QRect(window->VIEWER_OFFSET_X,window->VIEWER_OFFSET_Y,window->VIEWER_WIDTH,window->VIEWER_HEIGHT));

                        QMetaObject::invokeMethod(&window->splitter,"show");

                    }

                }else if(head==1){
                    unsigned int size=input.readUnsignedInt();

                    window->controller.playersList->clear();

                    for(unsigned int i=0;i<size;i++){
                        QString name=input.readString();
                        Byte status=input.readByte();

                        if(status==0){
                            window->controller.playersList->addItem(QString("空闲 - %1").arg(name));

                        }else if(status==1){
                            window->controller.playersList->addItem(QString("助屋 - %1").arg(name));

                        }else if(status==2){
                            window->controller.playersList->addItem(QString("随机 - %1").arg(name));

                        }else if(status==3){
                            window->controller.playersList->addItem(QString("敌组 - %1").arg(name));

                        }

                    }

                    Byte helpers=input.readByte();
                    Byte randoms=input.readByte();
                    Byte enemies=input.readByte();

                    window->controller.helpers=helpers;
                    window->controller.randoms=randoms;
                    window->controller.enemies=enemies;

                    window->controller.updateButtons();

                }else if(head==4){
                    QString helpers=input.readString();
                    QString enemies=input.readString();

                    Bytes data=input.read(48);
                    Bytes piecesStatus=input.read(12);
                    Byte round=input.readByte();

                    window->viewer.chessboard.setData(data.getData());
                    window->viewer.chessboard.setPiecesStatus(piecesStatus.getData());
                    window->viewer.chessboard.setRound((Team)round);

                    window->setWindowTitle(QString("助屋棋 - %1 - %2（助屋） vs %3（敌组）").arg(player).arg(helpers).arg(enemies));

                    if(helpers.compare(player)==0||enemies.compare(player)==0){
                        window->controller.lockButtons();
                        playing=true;

                    }

                    if(helpers.compare(player)==0){
                        window->viewer.chessboard.setTeam(Team::HELPERS);
                        window->viewer.chessboard.setRound(Team::HELPERS);

                    }else if(enemies.compare(player)==0){
                        window->viewer.chessboard.setTeam(Team::ENEMIES);
                        window->viewer.chessboard.setRound(Team::HELPERS);

                    }

                    window->viewer.win=false;

                }else if(head==5){
                    Bytes data=input.read(48);
                    Bytes piecesStatus=input.read(12);
                    Byte round=input.readByte();

                    window->viewer.chessboard.setData(data.getData());
                    window->viewer.chessboard.setPiecesStatus(piecesStatus.getData());
                    window->viewer.chessboard.setRound((Team)round);

                }else if(head==7){
                    Byte winnerTeam=input.readByte();
                    QString name=input.readString();

                    if(playing){
                        window->controller.unlockButtons();

                    }

                    window->viewer.win=true;
                    window->viewer.winnerTeam=winnerTeam;
                    window->viewer.winner=name;

                }

            }

        }

        Sleep(1);

    }

}
