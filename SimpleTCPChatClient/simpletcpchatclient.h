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

    explicit SimpleTCPChatClient(char* ip, int port, char* username, char* target_user);
    void SendMessage(const QString& text);
    void Stop();

public slots:
    void ReadLoop();

private:
    int sockfd;
    QString last_output;
    char* target_user;
    std::atomic<bool> running{false};

signals:
    void OutputChanged(const QString &output);
};

#endif // SIMPLETCPCHATCLIENT_H
