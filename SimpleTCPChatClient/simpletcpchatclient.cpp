#include "simpletcpchatclient.h"

#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <qobject.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero() nyeh, memset()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

SimpleTCPChatClient::SimpleTCPChatClient(int port) {
    int connfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    memset(&servaddr, 0, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);

    // connect the client socket to server socket
    if (::connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    //introduce
    write(sockfd, "client 1", 8);
    last_output = "";
}

void SimpleTCPChatClient::ReadLoop(){
    char buff[MAX];
    int n;
    running = true;
    for (;;) {
        memset(buff, 0, sizeof(buff));
        n = read(sockfd, buff, sizeof(buff)-1);
        if ((strncmp(buff, "exit", 4)) == 0) {
            return;
        }
        if (n <= 0)
            return; // connection closed or error

        buff[n] = '\0';
        if (last_output != QString::fromUtf8(buff)){
            last_output = buff;
            emit OutputChanged(last_output);
        }
    }
}

void SimpleTCPChatClient::SendMessage(const QString& text){
    QString out = "client 1\tclient 1\t" + text;
    QByteArray data = out.toUtf8();
    write(sockfd, data.constData(), data.size());
}

void SimpleTCPChatClient::Stop(){
    running = false;
    ::shutdown(sockfd, SHUT_RDWR);
    ::close(sockfd);
}