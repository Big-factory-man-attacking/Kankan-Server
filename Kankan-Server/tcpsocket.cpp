#include "tcpsocket.h"

TcpSocket::TcpSocket()
{

}

void TcpSocket::connect()
{
    if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(13);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("bind error");
    }


    if (listen(listenfd, 5) < 0) {
        perror("listen error");
    }

    for ( ; ; ) {
        len = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len)) < 0) {
            perror("accept error");
        }
        ticks = time(NULL);

        snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
        if (write(connfd, buffer, strlen(buffer)) < 0) {
            perror("write error");
        }
    }

}
