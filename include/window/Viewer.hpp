#ifndef GOOLNN_HELPERCHESS_WINDOW_CHESSBOARD
#define GOOLNN_HELPERCHESS_WINDOW_CHESSBOARD

#include <QPaintEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QImage>

#include "chess/Chessboard.hpp"
#include "chess/Piece.hpp"

//显示器
//用于绘制棋盘内容
class Viewer:public QWidget{
    private:
        double visualX;
        double visualY;

        double visualWidth;
        double visualHeight;

        double pieceSize;

        double chooserX;
        double chooserY;

        double chooserWidth;
        double chooserHeight;

        int mouseX=-1;
        int mouseY=-1;

        int focusX=-1;
        int focusY=-1;

        int chooserMouseX=-1;
        int chooserMouseY=-1;

        QImage* icons[12];

        bool characterChooser=false;

        short* backgrounds;

        void drawChessboardShadow(QPainter* p,double x,double y,Byte size,double opacity);
    
    public:
        Chessboard chessboard;

        bool win=false;
        Byte winnerTeam;
        QString winner;
        
        Viewer();
        ~Viewer();

        void changeRound();
    
    protected:
        void paintEvent(QPaintEvent* event);

        void mouseMoveEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);

};

#endif
