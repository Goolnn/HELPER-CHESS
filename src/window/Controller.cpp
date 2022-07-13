#include <QListWidgetItem>

#include "window/Controller.hpp"
#include "net/DataPack.hpp"
#include "net/Client.hpp"

Controller::Controller(){
    this->helpers=0;
    this->randoms=0;
    this->enemies=0;

    this->choice=0;

    this->helpersButton=new QPushButton(QString("助屋（%1）").arg(helpers));
    this->randomButton=new QPushButton(QString("随机（%1）").arg(randoms));
    this->enemiesButton=new QPushButton(QString("敌组（%1）").arg(enemies));

    this->hBox=new QHBoxLayout();

    this->hBox->addWidget(this->helpersButton);
    this->hBox->addWidget(this->randomButton);
    this->hBox->addWidget(this->enemiesButton);

    this->playersList=new QListWidget();

    this->vBox=new QVBoxLayout();

    playersList->addItem("a");

    this->vBox->addWidget(this->playersList);
    this->vBox->addLayout(this->hBox);

    this->setLayout(this->vBox);

    QObject::connect(this->helpersButton,SIGNAL(clicked()),this,SLOT(helperReady()));
    QObject::connect(this->randomButton,SIGNAL(clicked()),this,SLOT(randomReady()));
    QObject::connect(this->enemiesButton,SIGNAL(clicked()),this,SLOT(enemiesReady()));

}

Controller::~Controller(){
    delete this->vBox;

    delete this->hBox;
    
    delete this->helpersButton;
    delete this->randomButton;
    delete this->enemiesButton;

    delete this->playersList;

}

void Controller::updateButtons(){
    this->helpersButton->setText(QString("助屋（%1）").arg(helpers));
    this->randomButton->setText(QString("随机（%1）").arg(randoms));
    this->enemiesButton->setText(QString("敌组（%1）").arg(enemies));

}

void Controller::lockButtons(){
    this->helpersButton->setEnabled(false);
    this->randomButton->setEnabled(false);
    this->enemiesButton->setEnabled(false);

}

void Controller::unlockButtons(){
    this->helpersButton->setEnabled(true);
    this->randomButton->setEnabled(true);
    this->enemiesButton->setEnabled(true);

    this->helpersButton->setStyleSheet("QPushButton{font-weight:normal;}");
    this->randomButton->setStyleSheet("QPushButton{font-weight:normal;}");
    this->enemiesButton->setStyleSheet("QPushButton{font-weight:normal;}");

    this->choice=0;

    DataPack dataPack=DataPack();
    dataPack.writeUnsignedInt(3);
    dataPack.writeByte(this->choice);
    Client::write(&dataPack);

}

void Controller::helperReady(){
    this->randomButton->setStyleSheet("QPushButton{font-weight:normal;}");
    this->enemiesButton->setStyleSheet("QPushButton{font-weight:normal;}");

    if(this->choice!=1){
        this->helpersButton->setStyleSheet("QPushButton{font-weight:bold;}");
        this->choice=1;

    }else{
        this->helpersButton->setStyleSheet("QPushButton{font-weight:normal;}");
        this->choice=0;

    }

    DataPack dataPack=DataPack();
    dataPack.writeUnsignedInt(3);
    dataPack.writeByte(this->choice);
    Client::write(&dataPack);

}

void Controller::randomReady(){
    this->helpersButton->setStyleSheet("QPushButton{font-weight:normal;}");
    this->enemiesButton->setStyleSheet("QPushButton{font-weight:normal;}");

    if(this->choice!=2){
        this->randomButton->setStyleSheet("QPushButton{font-weight:bold;}");
        this->choice=2;

    }else{
        this->randomButton->setStyleSheet("QPushButton{font-weight:normal;}");
        this->choice=0;

    }

    DataPack dataPack=DataPack();
    dataPack.writeUnsignedInt(3);
    dataPack.writeByte(this->choice);
    Client::write(&dataPack);

}

void Controller::enemiesReady(){
    this->helpersButton->setStyleSheet("QPushButton{font-weight:normal;}");
    this->randomButton->setStyleSheet("QPushButton{font-weight:normal;}");

    if(this->choice!=3){
        this->enemiesButton->setStyleSheet("QPushButton{font-weight:bold;}");
        this->choice=3;

    }else{
        this->enemiesButton->setStyleSheet("QPushButton{font-weight:normal;}");
        this->choice=0;

    }

    DataPack dataPack=DataPack();
    dataPack.writeUnsignedInt(3);
    dataPack.writeByte(this->choice);
    Client::write(&dataPack);

}
