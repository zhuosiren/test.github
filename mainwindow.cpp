#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_chatServer=new ChatServer(this);
    connect(m_chatServer,&ChatServer::logMessage,this,&MainWindow::logMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startStopBt_clicked()
{
    if(m_chatServer->isListening()){
        m_chatServer->stopServer();
        ui->startStopBt->setText("启动服务器");
        logMessage("服务器已经停止");
    }
    else{
        if(!m_chatServer->listen(QHostAddress::Any,1967)){
            QMessageBox::critical(this,"错误","无法启动服务器");
            return;
        }
        logMessage("服务器已经启动");
        ui->startStopBt->setText("停止服务器");

    }
}

void MainWindow::logMessage(const QString &msg)
{
    ui->logEdit->appendPlainText(msg);
}

