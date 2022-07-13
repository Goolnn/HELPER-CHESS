#include <string.h>
#include <stdlib.h>

#include "chess/Chessboard.hpp"

Chessboard::Chessboard(){
    //初始化棋盘状态
    this->round=Team::EMPTY;
    this->team=Team::EMPTY;

    //为棋盘申请内存空间
    this->data=(Byte*)calloc(1,this->CHESSBOARD_WIDTH*this->CHESSBOARD_HEIGHT);

}

Chessboard::~Chessboard(){
    //释放内存
    free(this->data);

}

void Chessboard::setRound(Team team){
    this->round=team;

}

void Chessboard::setTeam(Team team){
    this->team=team;

}

void Chessboard::setPiece(Byte x,Byte y,Piece piece){
    this->data[y*this->CHESSBOARD_WIDTH+x]=piece;

}

void Chessboard::setData(Byte* data){
    //保存内存数据
    memcpy(this->data,data,this->CHESSBOARD_WIDTH*this->CHESSBOARD_HEIGHT);

}

Team Chessboard::getRound(){
    return this->round;

}

Team Chessboard::getTeam(){
    return this->team;
    
}

Piece Chessboard::getPiece(Byte x,Byte y){
    return (Piece)this->data[y*this->CHESSBOARD_WIDTH+x];

}

void Chessboard::getData(Byte* data){
    //复制内存数据
    memcpy(data,this->data,this->CHESSBOARD_WIDTH*this->CHESSBOARD_HEIGHT);

}

void Chessboard::clear(){
    for(int i=0;i<48;i++){
        this->data[i]=0;

    }

}
