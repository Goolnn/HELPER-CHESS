#include "window/Window.hpp"
#include "net/Client.hpp"

Window::Window(QWidget* parent):QStackedWidget(parent){
    this->splitter.addWidget(&this->controller);
    this->splitter.addWidget(&this->viewer);

    this->setWindowTitle("助屋棋");
    this->resize(800,600);

    this->addWidget(&this->connect);
    this->addWidget(&this->splitter);

    this->setCurrentIndex(0);

}

void Window::closeEvent(QCloseEvent*){
    Client::close();

    this->close();

}
