#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Client.h"
#include "vector"

class SessionManager
{
public:
    SessionManager();
    std::vector<Client> clients;
};

#endif // SESSIONMANAGER_H
