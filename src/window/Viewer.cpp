#include <QPainterPath>
#include <QPainter>
#include <QPointF>
#include <QColor>
#include <QBrush>
#include <QRectF>
#include <QRect>
#include <QFont>
#include <QPen>

#include <stdio.h>

#include "window/Viewer.hpp"
#include "tool/BezierCurve.hpp"
#include "net/DataPack.hpp"
#include "net/Client.hpp"

Viewer::Viewer(){
    //设置检测鼠标移动事件
    this->setMouseTracking(true);

    //初始化棋子图标
    this->icons[0]=new QImage("./resource/西伯太.png");
    this->icons[1]=new QImage("./resource/阿灿.png");
    this->icons[2]=new QImage("./resource/风牙.png");
    this->icons[3]=new QImage("./resource/卡亚普.png");
    this->icons[4]=new QImage("./resource/真白.png");
    this->icons[5]=new QImage("./resource/安娜.png");

    this->icons[6]=new QImage("./resource/谜之男子.png");
    this->icons[7]=new QImage("./resource/凯撒.png");
    this->icons[8]=new QImage("./resource/赛西里欧.png");
    this->icons[9]=new QImage("./resource/阿戈里.png");
    this->icons[10]=new QImage("./resource/基尔巴特.png");
    this->icons[11]=new QImage("./resource/谷林.png");

    //初始化棋盘
    this->backgrounds=new short[this->chessboard.CHESSBOARD_WIDTH*this->chessboard.CHESSBOARD_HEIGHT];

    for(int i=0;i<this->chessboard.CHESSBOARD_WIDTH*this->chessboard.CHESSBOARD_HEIGHT;i++){
        this->backgrounds[i]=0;

    }

}

Viewer::~Viewer(){
    //清理棋子图标数据
    for(int i=0;i<12;i++){
        delete this->icons[i];

    }

    // //清理棋盘数据
    // delete this->chessboard;

}

void Viewer::paintEvent(QPaintEvent* event){
    QPainter p=QPainter(this);

    //启动抗锯齿
    p.setRenderHint(QPainter::Antialiasing,true);
    
    //计算绘制数据
    const int WIDGET_WIDTH=event->rect().width();
    const int WIDGET_HEIGHT=event->rect().height();

    if((double)WIDGET_WIDTH/WIDGET_HEIGHT>6.0/8){
        this->visualWidth=(double)WIDGET_HEIGHT/8*6;
        this->visualHeight=WIDGET_HEIGHT;

    }else{
        this->visualWidth=WIDGET_WIDTH;
        this->visualHeight=(double)WIDGET_WIDTH/6*8;

    }

    this->visualX=(WIDGET_WIDTH-this->visualWidth)/2;
    this->visualY=(WIDGET_HEIGHT-this->visualHeight)/2;

    this->pieceSize=this->visualWidth/this->chessboard.CHESSBOARD_WIDTH;

    this->chooserX=this->visualX+(this->visualWidth-this->chooserWidth)/2;
    this->chooserY=this->visualY+(this->visualHeight-this->chooserHeight)/2;

    this->chooserWidth=this->pieceSize*3;
    this->chooserHeight=this->pieceSize*2;

    for(int i=0;i<this->chessboard.CHESSBOARD_WIDTH*this->chessboard.CHESSBOARD_HEIGHT;i++){
        this->backgrounds[i]=0;

    }

    //计算阴影
    if(!(this->focusX==-1&&this->focusY==-1)&&(this->chessboard.getPiece(this->focusX,this->focusY)!=PIECE_EMPTY||((this->focusX==2||this->focusX==3)&&(this->focusY==0||this->focusY==7)))){
        if((this->focusX==2||this->focusX==3)&&this->focusY==0){
            this->backgrounds[0*this->chessboard.CHESSBOARD_WIDTH+2]=3;
            this->backgrounds[0*this->chessboard.CHESSBOARD_WIDTH+3]=3;

            QList<Location> locations=PieceTool::mapping(&this->chessboard,Team::ENEMIES);

            for(Location location:locations){
                if(this->mouseX==location.getX()&&this->mouseY==location.getY()){
                    this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;

                }else{
                    this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=4;

                }

            }

        }else if((this->focusX==2||this->focusX==3)&&this->focusY==7){
            this->backgrounds[7*this->chessboard.CHESSBOARD_WIDTH+2]=3;
            this->backgrounds[7*this->chessboard.CHESSBOARD_WIDTH+3]=3;

            QList<Location> locations=PieceTool::mapping(&this->chessboard,Team::HELPERS);

            for(Location location:locations){
                if(this->mouseX==location.getX()&&this->mouseY==location.getY()){
                    this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;

                }else{
                    this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=4;

                }

            }

        }else{
            if(this->chessboard.getPiece(this->focusX,this->focusY)!=PIECE_EMPTY){
                this->backgrounds[this->focusY*this->chessboard.CHESSBOARD_WIDTH+this->focusX]=3;

                QList<Location> locations=PieceTool::mapping(PieceTool::getAttribute(this->chessboard.getPiece(this->focusX,this->focusY)),&this->chessboard,this->focusX,this->focusY);

                for(Location location:locations){
                    if(this->mouseX==location.getX()&&this->mouseY==location.getY()){
                        this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;

                    }else{
                        this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=4;

                    }

                }

            }

        }

    }else{
        if(!(this->mouseX==-1&&this->mouseY==-1)){
            if((this->mouseX==2||this->mouseX==3)&&this->mouseY==0){
                this->backgrounds[0*this->chessboard.CHESSBOARD_WIDTH+2]=1;
                this->backgrounds[0*this->chessboard.CHESSBOARD_WIDTH+3]=1;

                QList<Location> locations=PieceTool::mapping(&this->chessboard,Team::ENEMIES);

                for(Location location:locations){
                    if(this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]==4){
                        this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;

                    }else{
                        if(this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]!=PIECE_EMPTY){
                            this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;
                            
                        }else{
                            this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=2;

                        }

                    }

                }

            }else if((this->mouseX==2||this->mouseX==3)&&this->mouseY==7){
                this->backgrounds[7*this->chessboard.CHESSBOARD_WIDTH+2]=1;
                this->backgrounds[7*this->chessboard.CHESSBOARD_WIDTH+3]=1;

                QList<Location> locations=PieceTool::mapping(&this->chessboard,Team::HELPERS);

                for(Location location:locations){
                    if(this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]==4){
                        this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;

                    }else{
                        if(this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]!=PIECE_EMPTY){
                            this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;
                            
                        }else{
                            this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=2;

                        }

                    }

                }

            }else{
                if(this->chessboard.getPiece(this->mouseX,this->mouseY)!=PIECE_EMPTY){
                    this->backgrounds[this->mouseY*this->chessboard.CHESSBOARD_WIDTH+this->mouseX]=1;

                    QList<Location> locations=PieceTool::mapping(PieceTool::getAttribute(this->chessboard.getPiece(this->mouseX,this->mouseY)),&this->chessboard,this->mouseX,this->mouseY);

                    for(Location location:locations){
                        if(this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]==4){
                            this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;

                        }else{
                            if(this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]!=PIECE_EMPTY){
                                this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=5;
                                
                            }else{
                                this->backgrounds[location.getY()*this->chessboard.CHESSBOARD_WIDTH+location.getX()]=2;

                            }

                        }

                    }

                }

            }

        }

    }


    //绘制阴影
    for(int y=0;y<this->chessboard.CHESSBOARD_HEIGHT;y++){
        for(int x=0;x<this->chessboard.CHESSBOARD_WIDTH;x++){
            if((x==2||x==3)&&(y==0||y==7)&&(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==1||this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==3)){
                if(x==2){
                    if(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==1){
                        this->drawChessboardShadow(&p,x,y,2,0.25);

                    }else if(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==3){
                        this->drawChessboardShadow(&p,x,y,2,0.35);

                    }

                }

            }else{
                if(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==1){
                    this->drawChessboardShadow(&p,x,y,1,0.25);

                }else if(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==2){
                    this->drawChessboardShadow(&p,x,y,1,0.1);

                }else if(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==3){
                    this->drawChessboardShadow(&p,x,y,1,0.35);

                }else if(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==4){
                    this->drawChessboardShadow(&p,x,y,1,0.25);

                }else if(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]==5){
                    this->drawChessboardShadow(&p,x,y,1,0.45);

                }

            }

        }

    }

    //绘制棋子
    for(int y=0;y<this->chessboard.CHESSBOARD_HEIGHT;y++){
        for(int x=0;x<this->chessboard.CHESSBOARD_WIDTH;x++){
            if(this->chessboard.getPiece(x,y)!=Piece::PIECE_EMPTY){
                p.drawImage(QPointF(this->visualX+this->pieceSize*x,this->visualY+this->pieceSize*y),this->icons[this->chessboard.getPiece(x,y)-1]->scaled(pieceSize,pieceSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

            }

        }

    }

    //绘制棋盘
    p.setBrush(QBrush(QColor(0,0,0,0)));
    p.setPen(QPen(QColor(0,0,0,255)));
    
    p.drawRoundedRect(QRectF(this->visualX,this->visualY,this->visualWidth,this->visualHeight),16,16);

    for(int i=1;i<this->chessboard.CHESSBOARD_WIDTH;i++){
        if(i==3){
            p.drawLine(QPointF(this->visualX+this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*i,this->visualY+this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT),QPointF(this->visualX+this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*i,this->visualY+this->visualHeight-this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT));

        }else{
            p.drawLine(QPointF(this->visualX+this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*i,this->visualY),QPointF(this->visualX+this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*i,this->visualY+this->visualHeight));

        }

    }

    for(int i=1;i<this->chessboard.CHESSBOARD_HEIGHT;i++){
        p.drawLine(QPointF(this->visualX,this->visualY+this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT*i),QPointF(this->visualX+this->visualWidth,this->visualY+this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT*i));

    }

    //绘制文字
    QFont font=QFont();
    font.setPointSizeF(24.0*(this->visualWidth/450));
    p.setFont(font);

    p.setPen(QPen(QColor(0,0,0)));

    if(this->chessboard.getRound()==Team::ENEMIES){
        p.setPen(QPen(QColor(255,0,0)));
        
    }

    p.drawText(QRectF(this->visualX+this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*2,this->visualY,this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*2,this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT),Qt::AlignCenter,"敌组");
    
    p.setPen(QPen(QColor(0,0,0)));

    if(this->chessboard.getRound()==Team::HELPERS){
        p.setPen(QPen(QColor(255,0,0)));
        
    }

    p.drawText(QRectF(this->visualX+this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*2,this->visualY+this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT*7,this->visualWidth/this->chessboard.CHESSBOARD_WIDTH*2,this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT),Qt::AlignCenter,"助屋");

    //绘制人物选择
    if(this->characterChooser){
        p.setBrush(QBrush(QColor(0,0,0,255*0.35)));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRoundedRect(QRectF(this->chooserX,this->chooserY,this->chooserWidth,this->chooserHeight),10,10);

        if(!(this->chooserMouseX==-1&&this->chooserMouseY==-1)){
            p.drawRoundedRect(QRectF(this->chooserX+this->pieceSize*this->chooserMouseX,this->chooserY+this->pieceSize*this->chooserMouseY,this->pieceSize,this->pieceSize),10,10);

        }

        //绘制人物
        for(int y=0;y<2;y++){
            for(int x=0;x<3;x++){
                if(this->chessboard.getTeam()==Team::HELPERS){
                    p.drawImage(QPointF(this->chooserX+pieceSize*x,this->chooserY+pieceSize*y),this->icons[y*3+x]->scaled(pieceSize,pieceSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

                }else if(this->chessboard.getTeam()==Team::ENEMIES){
                    p.drawImage(QPointF(this->chooserX+pieceSize*x,this->chooserY+pieceSize*y),this->icons[6+y*3+x]->scaled(pieceSize,pieceSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                    
                }
                

            }

        }

    }

    //绘制胜利画面
    if(this->win){
        p.setBrush(QBrush(QColor(0,0,0,0.5*255)));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(0,0,WIDGET_WIDTH,WIDGET_HEIGHT);

        font=QFont();
        font.setPointSize(48);

        p.setPen(QPen(QColor(255,0,0)));
        p.setFont(font);
        
        if(this->winnerTeam==0){
            p.drawText(0,0,WIDGET_WIDTH,WIDGET_HEIGHT,Qt::AlignCenter,"助屋得胜！");

        }else if(this->winnerTeam==1){
            p.drawText(0,0,WIDGET_WIDTH,WIDGET_HEIGHT,Qt::AlignCenter,"敌组得胜！");

        }

    }

    //绘制DEBUG数据
    font=QFont();
    font.setPointSize(10);

    p.setPen(QPen(QColor(0,0,0)));
    p.setFont(font);

    p.drawText(10,10,500,500,Qt::AlignLeft|Qt::AlignTop,QString("鼠标坐标：(%1,%2)\n焦点坐标：(%3,%4)").arg(this->mouseX).arg(this->mouseY).arg(this->focusX).arg(this->focusY));

    // font=QFont();
    // font.setPointSize(16);
    // p.setFont(font);

    // p.setPen(QPen(QColor(255,0,0)));

    // for(int y=0;y<this->chessboard.CHESSBOARD_HEIGHT;y++){
    //     for(int x=0;x<this->chessboard.CHESSBOARD_WIDTH;x++){
    //         p.drawText(QRectF(this->visualX+this->pieceSize*x,this->visualY+this->pieceSize*y,this->pieceSize,this->pieceSize),Qt::AlignCenter,QString::number(this->backgrounds[y*this->chessboard.CHESSBOARD_WIDTH+x]));

    //     }

    // }

    //更新画面
    this->update();

}

void Viewer::mouseMoveEvent(QMouseEvent* event){
    if(!win){
        if(!this->characterChooser){
            if(event->position().x()>this->visualX&&event->position().x()<this->visualX+this->visualWidth&&event->position().y()>this->visualY&&event->position().y()<this->visualY+this->visualHeight){
                this->mouseX=event->position().x()-this->visualX;
                this->mouseY=event->position().y()-this->visualY;

                this->mouseX=this->mouseX/this->pieceSize;
                this->mouseY=this->mouseY/this->pieceSize;

            }else{
                this->mouseX=-1;
                this->mouseY=-1;

            }

        }else{
            this->mouseX=-1;
            this->mouseY=-1;
            
            if(event->position().x()>this->chooserX&&event->position().x()<this->chooserX+this->chooserWidth&&event->position().y()>this->chooserY&&event->position().y()<this->chooserY+this->chooserHeight){
                this->chooserMouseX=event->position().x()-(this->visualX+(this->visualWidth-this->chooserWidth)/2);
                this->chooserMouseY=event->position().y()-(this->visualY+(this->visualHeight-this->chooserHeight)/2);

                this->chooserMouseX=this->chooserMouseX/this->pieceSize;
                this->chooserMouseY=this->chooserMouseY/this->pieceSize;

            }else{
                this->chooserMouseX=-1;
                this->chooserMouseY=-1;

            }

        }

    }

}

void Viewer::mousePressEvent(QMouseEvent* event){
    if(!win){
        if(event->button()==Qt::LeftButton){
            int oldFocusX;
            int oldFocusY;

            if(this->characterChooser){
                if(event->position().x()>this->visualX+(this->visualWidth-this->chooserWidth)/2&&event->position().y()>this->visualY+(this->visualHeight-this->chooserHeight)/2&&event->position().x()<this->visualX+(this->visualWidth-this->chooserWidth)/2+this->chooserWidth&&event->position().y()<this->visualY+(this->visualHeight-this->chooserHeight)/2+this->chooserHeight){
                    this->chessboard.setPiece(this->focusX,this->focusY,(Piece)(this->chooserMouseY*3+this->chooserMouseX+(this->chessboard.getTeam()==Team::HELPERS?1:7)));

                    this->characterChooser=false;

                    this->focusX=-1;
                    this->focusY=-1;

                    // this->changeRound();

                    //更新棋盘
                    DataPack chessboard=DataPack();
                    Byte data[48];
                    this->chessboard.getData(data);
                    chessboard.writeUnsignedInt(6);
                    chessboard.write((void*)data,48);
                    Client::write(&chessboard);

                }else{
                    this->characterChooser=false;

                    this->focusX=-1;
                    this->focusY=-1;

                }

            }else{
                if(event->position().x()>this->visualX&&event->position().x()<this->visualX+this->visualWidth&&event->position().y()>this->visualY&&event->position().y()<this->visualY+this->visualHeight){
                    oldFocusX=this->focusX;
                    oldFocusY=this->focusY;

                    this->focusX=event->position().x()-this->visualX;
                    this->focusY=event->position().y()-this->visualY;

                    this->focusX=this->focusX/this->pieceSize;
                    this->focusY=this->focusY/this->pieceSize;

                    if((oldFocusX>=0&&oldFocusY>=0)&&this->chessboard.getPiece(oldFocusX,oldFocusY)!=PIECE_EMPTY&&PieceTool::getTeam(this->chessboard.getPiece(oldFocusX,oldFocusY))==this->chessboard.getRound()){
                        QList<Location> locations=PieceTool::mapping(PieceTool::getAttribute(this->chessboard.getPiece(oldFocusX,oldFocusY)),&this->chessboard,oldFocusX,oldFocusY);

                        for(Location location:locations){
                            if(location.getX()==this->focusX&&location.getY()==this->focusY){
                                Piece piece=this->chessboard.getPiece(oldFocusX,oldFocusY);

                                this->chessboard.setPiece(oldFocusX,oldFocusY,PIECE_EMPTY);
                                this->chessboard.setPiece(this->focusX,this->focusY,piece);

                                this->focusX=-1;
                                this->focusY=-1;

                                this->mouseX=-1;
                                this->mouseY=-1;

                                // this->changeRound();

                                //更新棋盘
                                DataPack chessboard=DataPack();
                                Byte data[48];
                                this->chessboard.getData(data);
                                chessboard.writeUnsignedInt(6);
                                chessboard.write((void*)data,48);
                                Client::write(&chessboard);

                            }

                        }

                    }

                    if((oldFocusX==2||oldFocusX==3)&&oldFocusY==0){
                        if(this->chessboard.getTeam()==Team::ENEMIES){
                            QList<Location> list=PieceTool::mapping(&this->chessboard,Team::ENEMIES);

                            this->characterChooser=false;

                            for(int i=0;i<list.size();i++){
                                Location location=list.at(i);

                                if(this->focusX==location.getX()&&this->focusY==location.getY()){
                                    this->characterChooser=true;

                                    break;

                                }

                            }

                        }

                    }else if((oldFocusX==2||oldFocusX==3)&&oldFocusY==7){
                        if(this->chessboard.getTeam()==Team::HELPERS){
                            QList<Location> list=PieceTool::mapping(&this->chessboard,Team::HELPERS);

                            this->characterChooser=false;

                            for(int i=0;i<list.size();i++){
                                Location location=list.at(i);

                                if(this->focusX==location.getX()&&this->focusY==location.getY()){
                                    this->characterChooser=true;

                                    break;

                                }

                            }

                        }

                    }else{
                        this->characterChooser=false;

                    }

                }else{
                    this->characterChooser=false;

                    this->focusX=-1;
                    this->focusY=-1;

                }

            }

        }else{
            this->characterChooser=false;

            this->focusX=-1;
            this->focusY=-1;

        }

    }

}

void Viewer::drawChessboardShadow(QPainter* p,double x,double y,Byte size,double opacity){
    QPainterPath background=QPainterPath();
    background.addRoundedRect(this->visualX,this->visualY,this->visualWidth,this->visualHeight,16,16);

    QPainterPath rect=QPainterPath();

    rect.addRect(this->visualX+x*this->pieceSize,this->visualY+y*(this->visualHeight/this->chessboard.CHESSBOARD_HEIGHT),this->pieceSize*size,this->pieceSize);

    background-=background-rect;

    p->setBrush(QBrush(QColor(0,0,0,255*opacity)));
    p->setPen(QPen(QColor(0,0,0,0)));

    p->drawPath(background);

}

void Viewer::changeRound(){
    if(this->chessboard.getRound()==Team::ENEMIES){
        this->chessboard.setRound(Team::HELPERS);

    }else if(this->chessboard.getRound()==Team::HELPERS){
        this->chessboard.setRound(Team::ENEMIES);

    }

}

// long long getMicroSeconds(){
//     return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

// }
