#ifndef SIMPLETCPCHATCLIENT_H
#define SIMPLETCPCHATCLIENT_H


#include <qobject.h>
#include <atomic>
#define MAX 80
#define SA struct sockaddr
#include "SimpleTCPChatClient_global.h"

class SIMPLETCPCHATCLIENT_EXPORT SimpleTCPChatClient : public QObject
{
    Q_OBJECT

public:

    explicit SimpleTCPChatClient(int port);
    void SendMessage(const QString& text);
    void Stop();

public slots:
    void ReadLoop();

private:
    int sockfd;
    QString last_output;
    std::atomic<bool> running{false};

signals:
    void OutputChanged(const QString &output);
};

#endif // SIMPLETCPCHATCLIENT_H
