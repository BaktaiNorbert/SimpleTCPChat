#include "sessionmanager.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define MAX 512
#define PORT 8080
#define SA struct sockaddr

SessionManager::SessionManager() {
    int connfd;
    u_int len;
    struct sockaddr_in server_address, cli;
    printf("juh");
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    //bzero(&server_address, sizeof(server_address));
    memset(&server_address, 0, sizeof(server_address));

    // assign IP, PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&server_address, sizeof(server_address))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    printf("buh");
    newConnectionSearchingLoop();
}

void SessionManager::newConnectionSearchingLoop(){
    struct sockaddr_in cli;
    u_int len = sizeof(cli);
    for(;;){
        //accept next client.
        int connfd = accept(sockfd, (SA*)&cli, &len);
        //wait for introduction. [NAME]
        char buff[MAX];
        memset(buff, 0, MAX);

        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));

        auto client = std::make_unique<Client>(connfd, buff);
        client->thread = std::thread(&SessionManager::readingLoop, this, client.get());
        printf("client %s added", client->name.c_str());
        clients.push_back(std::move(client));
    }
}
//SENDER_NAME\tRECIEVER_NAME\tCONTENT
void SessionManager::readingLoop(Client* client){
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        memset(buff, 0, MAX);
        // read the message from client and copy it in buffer
        read(client->fd, buff, sizeof(buff));

        char* parts[3];
        int i = 0;
        char* token = strtok(buff, "\t");
        while (token != nullptr && i < 3)
        {
            parts[i++] = token;
            token = strtok(nullptr, "\t");
        }

        sendMessageTo(client, parts[1], parts[2]);
    }
}

void SessionManager::sendMessageTo(Client* sender, char* reciever_name, char* message){
    //find reciever. abort if not found.
    Client* reciever = nullptr;
    for(auto& client : clients){
        if (client->name == reciever_name){
            reciever = client.get();
            break;
        }
    }
    if (reciever == nullptr){
        return;
    }
    write(reciever->fd, message, strlen(message));
}