#include <iostream>

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include "sessionmanager.h"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

using namespace std;


int main()
{
    SessionManager* sessionManager = new SessionManager();
    while(true){

    }
}

