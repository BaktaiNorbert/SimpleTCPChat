#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Client.h"
#include "vector"

class SessionManager
{
public:
    SessionManager();
    void newConnectionSearchingLoop();
    std::vector<std::unique_ptr<Client>> clients;
private:
    int sockfd;
    void readingLoop(Client* client);
    void sendMessageTo(Client* sender, char* reciever_name, char* message);
};

#endif // SESSIONMANAGER_H
