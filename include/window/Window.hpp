#include <QStackedWidget>
#include <QCloseEvent>
#include <QSplitter>

#include "window/Controller.hpp"
#include "window/Connect.hpp"
#include "window/Viewer.hpp"

class Window:public QStackedWidget{
    public:
        Connect connect;

        QSplitter splitter;
        Viewer viewer;
        Controller controller;

        QString name;

        Window(QWidget* parent=nullptr);
    
    protected:
        void closeEvent(QCloseEvent*);

};