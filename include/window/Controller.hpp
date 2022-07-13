#ifndef GOOLNN_HELPERCHESS_WINDOW_CONTROLER
#define GOOLNN_HELPERCHESS_WINDOW_CONTROLER

#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QWidget>

#include "tool/Byte.hpp"

class Controller:public QWidget{
    Q_OBJECT

    public:
        QVBoxLayout* vBox;

        QHBoxLayout* hBox;
        
        QPushButton* helpersButton;
        QPushButton* randomButton;
        QPushButton* enemiesButton;

        QListWidget* playersList;

        Byte helpers;
        Byte randoms;
        Byte enemies;

        Byte choice;

        Controller();
        ~Controller();

        void updateButtons();
        
        void lockButtons();
        void unlockButtons();
    
    private slots:
        void helperReady();
        void randomReady();
        void enemiesReady();

};

#endif
