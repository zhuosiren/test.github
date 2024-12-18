#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include"serverworker.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent=nullptr);

protected:
    QVector<ServerWorker *>m_clients;
    void incomingConnection(qintptr socketDescriptor) override;
    void broadcast(const QJsonObject &message,ServerWorker *exclude);

signals:
    void logMessage(const QString &msg);

public slots:
    void stopServer();
    void jsonReceived(ServerWorker *sender,const QJsonObject &docObj);

    void userDisconnected(ServerWorker *sender);
};

#endif // CHATSERVER_H
