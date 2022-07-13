#include "chess/Chessboard.hpp"
#include "chess/Piece.hpp"

bool team(Piece piece1,Piece piece2);
bool find(const short attribute[],short num,short x,short y,Chessboard* chessboard);

Location::Location(short x,short y){
    this->x=x;
    this->y=y;

}

Location::Location(){
    this->x=0;
    this->y=0;

}

void Location::setX(short x){
    this->x=x;

}

void Location::setY(short y){
    this->y=y;

}

short Location::getX(){
    return this->x;

}

short Location::getY(){
    return this->y;

}

QList<Location> PieceTool::mapping(const short attribute[],Chessboard* chessboard,short x,short y){
    short map[]={0,0,0,0,0,
                 0,0,0,0,0,
                 0,0,0,0,0,
                 0,0,0,0,0,
                 0,0,0,0,0};
    
    for(int yy=0;yy<5;yy++){
        for(int xx=0;xx<5;xx++){
            if(x-2+xx>=0&&y-2+yy>=0&&x-2+xx<=5&&y-2+yy<=7){
                if(attribute[yy*5+xx]>0){
                    if(chessboard->getPiece(x-2+xx,y-2+yy)==PIECE_EMPTY){
                        switch(PieceTool::getTeam(chessboard->getPiece(x,y))){
                            case Team::HELPERS:
                                if(!(((x-2+xx)==2||(x-2+xx)==3)&&(y-2+yy)==7)){
                                    map[yy*5+xx]=1;

                                }

                                break;
                            
                            case Team::ENEMIES:
                                if(!(((x-2+xx)==2||(x-2+xx)==3)&&(y-2+yy)==0)){
                                    map[yy*5+xx]=1;

                                }

                                break;
                            
                            default:
                                break;

                        }


                    }else{
                        if(!team(chessboard->getPiece(x,y),chessboard->getPiece(x-2+xx,y-2+yy))){
                            map[yy*5+xx]=1;

                        }

                    }

                }else if(attribute[yy*5+xx]<0){
                    if(find(attribute,attribute[yy*5+xx],x,y,chessboard)&&!team(chessboard->getPiece(x,y),chessboard->getPiece(x-2+xx,y-2+yy))){
                        switch(PieceTool::getTeam(chessboard->getPiece(x,y))){
                            case Team::HELPERS:
                                if(!(((x-2+xx)==2||(x-2+xx)==3)&&(y-2+yy)==7)){
                                    map[yy*5+xx]=1;

                                }

                                break;
                            
                            case Team::ENEMIES:
                                if(!(((x-2+xx)==2||(x-2+xx)==3)&&(y-2+yy)==0)){
                                    map[yy*5+xx]=1;

                                }

                                break;
                            
                            default:
                                break;

                        }

                    }

                }

            }

        }

    }

    QList<Location> result;

    for(int yy=0;yy<5;yy++){
        for(int xx=0;xx<5;xx++){
            if(map[yy*5+xx]!=0){
                result.append(Location(x-2+xx,y-2+yy));

            }

        }

    }

    return result;

}

QList<Location> PieceTool::mapping(Chessboard* chessboard,Team team){
    QList<Location> result;

    switch(team){
        case Team::HELPERS:
            result.push_back(Location(1,7));
            result.push_back(Location(4,7));
            result.push_back(Location(1,6));
            result.push_back(Location(2,6));
            result.push_back(Location(3,6));
            result.push_back(Location(4,6));

            break;
            
        case Team::ENEMIES:
            result.push_back(Location(1,0));
            result.push_back(Location(4,0));
            result.push_back(Location(1,1));
            result.push_back(Location(2,1));
            result.push_back(Location(3,1));
            result.push_back(Location(4,1));

            break;
        
        default:
            break;

    }

    for(int i=0,size=result.size();i<size;i++){
        for(int j=0;j<result.size();j++){
            Location location=result.at(j);
            if(chessboard->getPiece(location.getX(),location.getY())!=PIECE_EMPTY){
                result.removeAt(j);
                break;

            }

        }

    }

    return result;

}

const short* PieceTool::getAttribute(Piece piece){
    switch(piece){
        case PIECE_SHIBETA:
            return PieceAttribute::SHIBETA;
            break;

        case PIECE_A_CHAN:
            return PieceAttribute::A_CHAN;
            break;

        case PIECE_FUUGA:
            return PieceAttribute::FUUGA;
            break;

        case PIECE_KYAPPY:
            return PieceAttribute::KYAPPY;
            break;

        case PIECE_MASHIRO:
            return PieceAttribute::MASHIRO;
            break;

        case PIECE_ANNA:
            return PieceAttribute::ANNA;
            break;
        
        case PIECE_THE_MYSTERIOUS_MAN:
            return PieceAttribute::THE_MYSTERIOUS_MAN;
            break;

        case PIECE_KAISER:
            return PieceAttribute::KAISER;
            break;

        case PIECE_CECILIO:
            return PieceAttribute::CECILIO;
            break;

        case PIECE_AGGREY:
            return PieceAttribute::AGGREY;
            break;

        case PIECE_GILBERT:
            return PieceAttribute::GILBERT;
            break;

        case PIECE_GOOLNN:
            return PieceAttribute::GOOLNN;
            break;
        
        default:
            return nullptr;
            break;
        
    }

}

Team PieceTool::getTeam(Piece piece){
    switch(piece){
        case PIECE_SHIBETA:
        case PIECE_A_CHAN:
        case PIECE_FUUGA:
        case PIECE_KYAPPY:
        case PIECE_MASHIRO:
        case PIECE_ANNA:
            return Team::HELPERS;
        
        case PIECE_EMPTY:
            return Team::EMPTY;
        
        default:
            return Team::ENEMIES;
        

    }

}

bool team(Piece piece1,Piece piece2){
    switch(piece1){
        case PIECE_SHIBETA:
        case PIECE_A_CHAN:
        case PIECE_FUUGA:
        case PIECE_KYAPPY:
        case PIECE_MASHIRO:
        case PIECE_ANNA:
            switch(piece2){
                case PIECE_SHIBETA:
                case PIECE_A_CHAN:
                case PIECE_FUUGA:
                case PIECE_KYAPPY:
                case PIECE_MASHIRO:
                case PIECE_ANNA:
                    return true;
                
                default:
                    return false;

            }

        default:
            switch(piece2){
                case PIECE_SHIBETA:
                case PIECE_A_CHAN:
                case PIECE_FUUGA:
                case PIECE_KYAPPY:
                case PIECE_MASHIRO:
                case PIECE_ANNA:
                case PIECE_EMPTY:
                    return false;
                
                default:
                    return true;
                    
            }

    }

}

bool find(const short attribute[],short num,short x,short y,Chessboard* chessboard){
    for(int yy=0;yy<5;yy++){
        for(int xx=0;xx<5;xx++){
            if(attribute[yy*5+xx]==-num){
                if(chessboard->getPiece(x-2+xx,y-2+yy)!=PIECE_EMPTY){
                    return false;

                }

            }

        }

    }

    return true;

}
