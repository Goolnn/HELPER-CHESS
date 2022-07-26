#include <QGraphicsOpacityEffect>
#include <QSvgRenderer>
#include <QPainterPath>
#include <QPainter>

#include "window/Window.hpp"
#include "tool/BezierCurve.hpp"
#include "net/Client.hpp"

Window::Window(QWidget* parent):QMainWindow(parent){
    //设置窗口参数
    this->setWindowTitle("助屋棋");
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //初始化启动动画
    this->startTime=GetTickCount();

    //设置窗口大小
    this->resize(this->WINDOW_ALL_WIDTH,this->WINDOW_ALL_HEIGHT);

    //初始化分割界面
    this->splitter.addWidget(&this->controller);
    this->splitter.addWidget(&this->viewer);

    //设置界面
    this->connect.setParent(this);
    this->connect.setGeometry(this->VIEWER_OFFSET_X,this->VIEWER_OFFSET_Y,this->VIEWER_WIDTH,this->VIEWER_HEIGHT);

    //设置界面透明
    QGraphicsOpacityEffect* opacityEffect=new QGraphicsOpacityEffect();
    this->connect.setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0);

}

void Window::setWindowTitle(QString title){
    QMainWindow::setWindowTitle(title);
    this->update();

}

void Window::paintEvent(QPaintEvent*){
    QPainter p=QPainter(this);

    //启动抗锯齿
    p.setRenderHint(QPainter::Antialiasing,true);

    //启动动画
    if(this->launchAnimation){
        //播放时间
        long playedTime=GetTickCount()-this->startTime;

        //缓动函数
        BezierCurve b=BezierCurve();

        b.addPoint(0,0);
        b.addPoint(0,1);
        b.addPoint(1,1);

        if(playedTime<=750){
            //动画参数
            float t=b.calc(playedTime/750.0).getY();

            float windowWidth=this->WINDOW_WIDTH*t;
            float windowHeight=this->WINDOW_HEIGHT*t;

            //绘制背景
            p.setBrush(QBrush(QColor(255,255,255,255*t)));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRoundedRect(this->WINDOW_OFFSET_X+(this->WINDOW_WIDTH-windowWidth)/2,this->WINDOW_OFFSET_Y+(this->WINDOW_HEIGHT-windowHeight)/2,windowWidth,windowHeight,this->WINDOW_CORNER_SIZE,this->WINDOW_CORNER_SIZE);

            this->update();

        }else if(playedTime>750&&playedTime<=1250){
            //动画参数
            float t=b.calc((playedTime-750)/500.0).getY();

            //绘制窗口阴影
            QLinearGradient lg;
            QRadialGradient rg;

            //上边缘阴影
            lg=QLinearGradient(this->WINDOW_ALL_WIDTH/2,this->WINDOW_OFFSET_Y+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_WIDTH/2,0);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,0,this->WINDOW_WIDTH-this->WINDOW_CORNER_SIZE*2*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3);

            //下边缘阴影
            lg=QLinearGradient(this->WINDOW_ALL_WIDTH/2,this->WINDOW_ALL_HEIGHT-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_WIDTH/2,this->WINDOW_ALL_HEIGHT);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_WIDTH-this->WINDOW_CORNER_SIZE*2*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3);

            //左边缘阴影
            lg=QLinearGradient(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT/2,0,this->WINDOW_ALL_HEIGHT/2);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(0,this->WINDOW_OFFSET_Y+this->WINDOW_CORNER_SIZE*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3,this->WINDOW_HEIGHT-this->WINDOW_CORNER_SIZE*2*3);

            //右边缘阴影
            lg=QLinearGradient(this->WINDOW_ALL_WIDTH-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT/2,this->WINDOW_ALL_WIDTH,this->WINDOW_ALL_HEIGHT/2);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_OFFSET_Y+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_HEIGHT-WINDOW_CORNER_SIZE*2*3);

            //左上角阴影
            rg=QRadialGradient(WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(0,0,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            //右上角阴影
            rg=QRadialGradient(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,0,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            //左下角阴影
            rg=QRadialGradient(WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(0,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            //右下角阴影
            rg=QRadialGradient(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125*t));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);
            
            //绘制背景
            p.setBrush(QBrush(QColor(255,255,255,255)));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRoundedRect(this->WINDOW_OFFSET_X,this->WINDOW_OFFSET_Y,this->WINDOW_WIDTH,this->WINDOW_HEIGHT,this->WINDOW_CORNER_SIZE,this->WINDOW_CORNER_SIZE);

            //绘制窗口标题
            p.setPen(QPen(QColor(0,0,0,255*t)));

            QFont font;
            font.setPointSize(10);
            p.setFont(font);

            p.drawText(WINDOW_OFFSET_X,WINDOW_OFFSET_Y,WINDOW_WIDTH,WINDOW_TITLEBAR_SIZE,Qt::AlignCenter,this->windowTitle());

            //绘制窗口图标
            QSvgRenderer sr;

            sr.load(QString("./resource/icon/close.svg"));
            sr.render(&p,QRectF(WINDOW_OFFSET_X+WINDOW_WIDTH-WINDOW_TITLEBAR_SIZE,WINDOW_OFFSET_Y,WINDOW_TITLEBAR_SIZE,WINDOW_TITLEBAR_SIZE));

            sr.load(QString("./resource/icon/minimize.svg"));
            sr.render(&p,QRectF(WINDOW_OFFSET_X+WINDOW_WIDTH-WINDOW_TITLEBAR_SIZE*2,WINDOW_OFFSET_Y,WINDOW_TITLEBAR_SIZE,WINDOW_TITLEBAR_SIZE));

            //绘制窗口控件
            ((QGraphicsOpacityEffect*)this->connect.graphicsEffect())->setOpacity(t);

            this->update();

        }else{
            //绘制窗口阴影
            QLinearGradient lg;
            QRadialGradient rg;

            //上边缘阴影
            lg=QLinearGradient(this->WINDOW_ALL_WIDTH/2,this->WINDOW_OFFSET_Y+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_WIDTH/2,0);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,0,this->WINDOW_WIDTH-this->WINDOW_CORNER_SIZE*2*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3);

            //下边缘阴影
            lg=QLinearGradient(this->WINDOW_ALL_WIDTH/2,this->WINDOW_ALL_HEIGHT-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_WIDTH/2,this->WINDOW_ALL_HEIGHT);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_WIDTH-this->WINDOW_CORNER_SIZE*2*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3);

            //左边缘阴影
            lg=QLinearGradient(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT/2,0,this->WINDOW_ALL_HEIGHT/2);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(0,this->WINDOW_OFFSET_Y+this->WINDOW_CORNER_SIZE*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3,this->WINDOW_HEIGHT-this->WINDOW_CORNER_SIZE*2*3);

            //右边缘阴影
            lg=QLinearGradient(this->WINDOW_ALL_WIDTH-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT/2,this->WINDOW_ALL_WIDTH,this->WINDOW_ALL_HEIGHT/2);

            lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(lg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_OFFSET_Y+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_HEIGHT-WINDOW_CORNER_SIZE*2*3);

            //左上角阴影
            rg=QRadialGradient(WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(0,0,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            //右上角阴影
            rg=QRadialGradient(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,0,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            //左下角阴影
            rg=QRadialGradient(WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(0,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            //右下角阴影
            rg=QRadialGradient(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

            rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
            rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

            p.setBrush(QBrush(rg));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);
            
            //绘制背景
            p.setBrush(QBrush(QColor(255,255,255,255)));
            p.setPen(QPen(QColor(0,0,0,0)));

            p.drawRoundedRect(this->WINDOW_OFFSET_X,this->WINDOW_OFFSET_Y,this->WINDOW_WIDTH,this->WINDOW_HEIGHT,this->WINDOW_CORNER_SIZE,this->WINDOW_CORNER_SIZE);

            //绘制窗口标题
            p.setPen(QPen(QColor(0,0,0,255)));

            QFont font;
            font.setPointSize(10);
            p.setFont(font);

            p.drawText(WINDOW_OFFSET_X,WINDOW_OFFSET_Y,WINDOW_WIDTH,WINDOW_TITLEBAR_SIZE,Qt::AlignCenter,this->windowTitle());

            //绘制窗口图标
            QSvgRenderer sr;

            sr.load(QString("./resource/icon/close.svg"));
            sr.render(&p,QRectF(WINDOW_OFFSET_X+WINDOW_WIDTH-WINDOW_TITLEBAR_SIZE,WINDOW_OFFSET_Y,WINDOW_TITLEBAR_SIZE,WINDOW_TITLEBAR_SIZE));

            sr.load(QString("./resource/icon/minimize.svg"));
            sr.render(&p,QRectF(WINDOW_OFFSET_X+WINDOW_WIDTH-WINDOW_TITLEBAR_SIZE*2,WINDOW_OFFSET_Y,WINDOW_TITLEBAR_SIZE,WINDOW_TITLEBAR_SIZE));

            //绘制窗口控件
            ((QGraphicsOpacityEffect*)this->connect.graphicsEffect())->setOpacity(1);

            this->launchAnimation=false;

            this->update();
            
        }

    }else{
        //绘制窗口阴影
        QLinearGradient lg;
        QRadialGradient rg;

        //上边缘阴影
        lg=QLinearGradient(this->WINDOW_ALL_WIDTH/2,this->WINDOW_OFFSET_Y+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_WIDTH/2,0);

        lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(lg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,0,this->WINDOW_WIDTH-this->WINDOW_CORNER_SIZE*2*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3);

        //下边缘阴影
        lg=QLinearGradient(this->WINDOW_ALL_WIDTH/2,this->WINDOW_ALL_HEIGHT-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_WIDTH/2,this->WINDOW_ALL_HEIGHT);

        lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(lg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_WIDTH-this->WINDOW_CORNER_SIZE*2*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3);

        //左边缘阴影
        lg=QLinearGradient(this->WINDOW_OFFSET_X+this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT/2,0,this->WINDOW_ALL_HEIGHT/2);

        lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(lg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(0,this->WINDOW_OFFSET_Y+this->WINDOW_CORNER_SIZE*3,this->WINDOW_SHADOW_SIZE+this->WINDOW_CORNER_SIZE*3,this->WINDOW_HEIGHT-this->WINDOW_CORNER_SIZE*2*3);

        //右边缘阴影
        lg=QLinearGradient(this->WINDOW_ALL_WIDTH-this->WINDOW_SHADOW_SIZE-this->WINDOW_CORNER_SIZE*3,this->WINDOW_ALL_HEIGHT/2,this->WINDOW_ALL_WIDTH,this->WINDOW_ALL_HEIGHT/2);

        lg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        lg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(lg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_OFFSET_Y+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_HEIGHT-WINDOW_CORNER_SIZE*2*3);

        //左上角阴影
        rg=QRadialGradient(WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(rg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(0,0,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        //右上角阴影
        rg=QRadialGradient(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(rg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,0,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        //左下角阴影
        rg=QRadialGradient(WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(rg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(0,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        //右下角阴影
        rg=QRadialGradient(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        rg.setColorAt(0.0,QColor(0,0,0,255*0.125));
        rg.setColorAt(1.0,QColor(0,0,0,255*0.0));

        p.setBrush(QBrush(rg));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(WINDOW_ALL_WIDTH-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_ALL_HEIGHT-WINDOW_SHADOW_SIZE-WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3,WINDOW_SHADOW_SIZE+WINDOW_CORNER_SIZE*3);

        //设置蒙版
        QPainterPath background;

        background.setFillRule(Qt::WindingFill);
        background.addRoundedRect(this->WINDOW_OFFSET_X,this->WINDOW_OFFSET_Y,this->WINDOW_WIDTH,this->WINDOW_HEIGHT,this->WINDOW_CORNER_SIZE,this->WINDOW_CORNER_SIZE);

        p.setClipPath(background);

        //绘制窗口背景
        p.setBrush(QBrush(QColor(255,255,255,255)));
        p.setPen(QPen(QColor(0,0,0,0)));

        p.drawRect(this->WINDOW_OFFSET_X,this->WINDOW_OFFSET_Y,this->WINDOW_WIDTH,this->WINDOW_HEIGHT);

        p.setClipping(false);

        //绘制窗口标题
        p.setPen(QPen(QColor(0,0,0,255)));

        QFont font;
        font.setPointSize(10);
        p.setFont(font);

        p.drawText(WINDOW_OFFSET_X,WINDOW_OFFSET_Y,WINDOW_WIDTH,WINDOW_TITLEBAR_SIZE,Qt::AlignCenter,this->windowTitle());

        //绘制窗口图标
        QSvgRenderer sr;

        sr.load(QString("./resource/icon/close.svg"));
        sr.render(&p,QRectF(WINDOW_OFFSET_X+WINDOW_WIDTH-WINDOW_TITLEBAR_SIZE,WINDOW_OFFSET_Y,WINDOW_TITLEBAR_SIZE,WINDOW_TITLEBAR_SIZE));

        sr.load(QString("./resource/icon/minimize.svg"));
        sr.render(&p,QRectF(WINDOW_OFFSET_X+WINDOW_WIDTH-WINDOW_TITLEBAR_SIZE*2,WINDOW_OFFSET_Y,WINDOW_TITLEBAR_SIZE,WINDOW_TITLEBAR_SIZE));

    }


}

void Window::closeEvent(QCloseEvent*){
    Client::close();

    this->close();

}
