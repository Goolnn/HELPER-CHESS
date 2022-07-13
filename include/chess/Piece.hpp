#ifndef GOOLNN_HELPERCHESS_CHESS_PIECE
#define GOOLNN_HELPERCHESS_CHESS_PIECE

#include <QList>

class Chessboard;

enum class Team{
    EMPTY,
    HELPERS,
    ENEMIES

};

class Location{
    private:
        short x;
        short y;
    
    public:
        Location(short x,short y);
        Location();

        void setX(short x);
        void setY(short y);

        short getX();
        short getY();
        
};

enum Piece{
    PIECE_EMPTY             =0x00,      //空白

    //助屋
    PIECE_SHIBETA           =0x01,      //西伯太
    PIECE_A_CHAN            =0x02,      //阿灿
    PIECE_FUUGA             =0x03,      //风牙
    PIECE_KYAPPY            =0x04,      //卡亚普
    PIECE_MASHIRO           =0x05,      //真白
    PIECE_ANNA              =0x06,      //安娜

    //敌组
    PIECE_THE_MYSTERIOUS_MAN=0x07,      //谜之男子
    PIECE_KAISER            =0x08,      //凯撒
    PIECE_CECILIO           =0x09,      //赛西利欧
    PIECE_AGGREY            =0x0A,      //阿戈里
    PIECE_GILBERT           =0x0B,      //基尔巴特
    PIECE_GOOLNN            =0x0C       //谷林

};

namespace PieceAttribute{
    const short SHIBETA[]           ={ 0, 0,-1, 0, 0,
                                       0, 5, 1, 5, 0,
                                      -2, 2, 0, 3,-3,
                                       0, 5, 4, 5, 0,
                                       0, 0,-4, 0, 0};

    const short A_CHAN[]            ={ 0, 0, 0, 0, 0,
                                       0, 1, 1, 1, 0,
                                       0, 1, 0, 1, 0,
                                       0, 1, 1, 1, 0,
                                       0, 0, 0, 0, 0};

    const short FUUGA[]             ={-1, 0, 0, 0,-2,
                                       0, 1, 0, 2, 0,
                                       0, 0, 0, 0, 0,
                                       0, 3, 0, 4, 0,
                                      -3, 0, 0, 0,-4};

    const short KYAPPY[]            ={ 0, 0,-1, 0, 0,
                                       0, 0, 1, 0, 0,
                                       0, 3, 0, 3, 0,
                                       0, 0, 2, 0, 0,
                                       0, 0,-2, 0, 0};

    const short MASHIRO[]           ={ 0, 0, 0, 0, 0,
                                       0, 0, 3, 0, 0,
                                      -1, 1, 0, 2,-2,
                                       0, 0, 3, 0, 0,
                                       0, 0, 0, 0, 0};

    const short ANNA[]              ={ 0,-1, 0,-2, 0,
                                      -1, 1, 0, 2,-2,
                                       0, 0, 0, 0, 0,
                                      -3, 3, 0, 4,-4,
                                       0,-3, 0,-4, 0};

    const short THE_MYSTERIOUS_MAN[]={ 0, 1, 1, 1, 0,
                                       1, 0, 0, 0, 1,
                                       1, 0, 0, 0, 1,
                                       1, 0, 0, 0, 1,
                                       0, 1, 1, 1, 0};

    const short KAISER[]            ={ 0, 0, 0, 0, 0,
                                       0, 1, 1, 1, 0,
                                       0, 1, 0, 1, 0,
                                       0, 1, 1, 1, 0,
                                       0, 0, 0, 0, 0};

    const short CECILIO[]           ={ 0, 0,-1, 0, 0,
                                       0, 0, 1, 0, 0,
                                      -2, 2, 0, 3,-3,
                                       0, 0, 4, 0, 0,
                                       0, 0,-4, 0, 0};

    const short AGGREY[]            ={ 0, 0, 0, 0, 0,
                                       0, 3, 0, 3, 0,
                                      -1, 1, 0, 2,-2,
                                       0, 3, 0, 3, 0,
                                       0, 0, 0, 0, 0};

    const short GILBERT[]           ={-1, 0, 5, 0,-2,
                                       0, 1, 0, 2, 0,
                                       5, 0, 0, 0, 5,
                                       0, 3, 0, 4, 0,
                                      -3, 0, 5, 0,-4};

    const short GOOLNN[]            ={ 0, 0, 0, 0, 0,
                                       1, 1, 0, 1, 1,
                                       0, 0, 0, 0, 0,
                                       1, 1, 0, 1, 1,
                                       0, 0, 0, 0, 0};
    
}

namespace PieceTool{
    QList<Location> mapping(const short attribute[],Chessboard* chessboard,short x,short y);
    QList<Location> mapping(Chessboard* chessboard,Team team);

    const short* getAttribute(Piece piece);
    Team getTeam(Piece piece);

};

#endif
