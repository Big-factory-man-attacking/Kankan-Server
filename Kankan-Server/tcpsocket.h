#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "json.hpp"
extern "C" {
    #include <sys/socket.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <string.h>
    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>
}

#define MAXLINE 1024

class TcpSocket
{
public:
    TcpSocket();
    void connect();
    int send(nlohmann::json js);
    nlohmann::json receive();
private:
    int listenfd, connfd;
    struct sockaddr_in serveraddr, cliaddr;
    char buffer[MAXLINE + 1];
    socklen_t len;
};

#endif // TCPSOCKET_H
