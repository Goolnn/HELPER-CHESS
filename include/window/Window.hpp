#include <QMainWindow>
#include <QCloseEvent>
#include <QSplitter>
#include <QEvent>

#include "window/Controller.hpp"
#include "window/Connect.hpp"
#include "window/Viewer.hpp"

class Window:public QMainWindow{
    private:
        //启动动画
        bool launchAnimation=true;
        
        long startTime;

    public:
        const int WINDOW_WIDTH=800;
        const int WINDOW_HEIGHT=600;

        const int WINDOW_SHADOW_SIZE=18;
        const int WINDOW_CORNER_SIZE=10;

        const int WINDOW_TITLEBAR_SIZE=32;

        const int WINDOW_OFFSET_X=WINDOW_SHADOW_SIZE;
        const int WINDOW_OFFSET_Y=WINDOW_SHADOW_SIZE;

        const int VIEWER_OFFSET_X=WINDOW_OFFSET_X;
        const int VIEWER_OFFSET_Y=WINDOW_OFFSET_Y+WINDOW_TITLEBAR_SIZE;

        const int VIEWER_WIDTH=WINDOW_WIDTH;
        const int VIEWER_HEIGHT=WINDOW_HEIGHT-WINDOW_TITLEBAR_SIZE*2;

        const int WINDOW_ALL_WIDTH=this->WINDOW_WIDTH+this->WINDOW_SHADOW_SIZE*2;
        const int WINDOW_ALL_HEIGHT=this->WINDOW_HEIGHT+this->WINDOW_SHADOW_SIZE*2;

        Connect connect;

        QSplitter splitter;
        Viewer viewer;
        Controller controller;

        QString name;

        Window(QWidget* parent=nullptr);

        void setWindowTitle(QString title);
    
    protected:
        void paintEvent(QPaintEvent*);

        void closeEvent(QCloseEvent*);

};