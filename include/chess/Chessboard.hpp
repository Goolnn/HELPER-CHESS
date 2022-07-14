#ifndef GOOLNN_HELPERCHESS_CHESS_CHESSBOARD
#define GOOLNN_HELPERCHESS_CHESS_CHESSBOARD

#include "chess/Piece.hpp"
#include "tool/Byte.hpp"

class Chessboard{
    private:
        Team round;
        Team team;

        Byte* piecesStatus;
        Byte* data;
    
    public:
        const Byte CHESSBOARD_WIDTH=6;
        const Byte CHESSBOARD_HEIGHT=8;

        Chessboard();
        ~Chessboard();

        void setRound(Team team);
        void setTeam(Team team);

        void setPiece(Byte x,Byte y,Piece piece);

        void setPieceStatus(Piece piece,PieceStatus pieceStatus);
        void setPiecesStatus(Byte* piecesStatus);
        void setData(Byte* data);

        Team getRound();
        Team getTeam();

        Piece getPiece(Byte x,Byte y);

        PieceStatus getPieceStatus(Piece piece);
        void getPiecesStatus(Byte* piecesData);
        void getData(Byte* data);

        void clear();

};

#endif
