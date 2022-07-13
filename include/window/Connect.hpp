#ifndef GOOLNN_HELPERCHESS_WINDOW_CONNECT
#define GOOLNN_HELPERCHESS_WINDOW_CONNECT

#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>

class Connect:public QWidget{
    Q_OBJECT

    private:
        QVBoxLayout layout=QVBoxLayout();

        QHBoxLayout hLayout1=QHBoxLayout();
        QHBoxLayout hLayout2=QHBoxLayout();
        QHBoxLayout hLayout3=QHBoxLayout();

        QLabel addressLabel=QLabel("地址");
        QLineEdit addressInputer=QLineEdit("103.205.254.211:20227");

        QLabel nameLabel=QLabel("名称");
        QLineEdit nameInputer=QLineEdit("Goolnn");

        QPushButton connectButton=QPushButton("连接");
    
    public:
        Connect(QWidget* parent=nullptr);
    
    private slots:
        void connect();

};

#endif
