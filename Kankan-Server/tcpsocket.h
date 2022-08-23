#ifndef TCPSOCKET_H
#define TCPSOCKET_H

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
private:
    int listenfd, connfd;
    struct sockaddr_in serveraddr, cliaddr;
    char buffer[MAXLINE + 1];
    time_t ticks;
    socklen_t len;
};

#endif // TCPSOCKET_H
