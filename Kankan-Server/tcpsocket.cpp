#include "tcpsocket.h"
#include "json.hpp"
#include <iostream>
#include <arpa/inet.h>
#include "videosocialcontrol.h"
#define MAXSIZE 2048

TcpSocket::TcpSocket()
{

}

void TcpSocket::connect()
{
    nlohmann::json m_json;
    m_json["id"] = 10;
    m_json["name"] = "cheng";
    m_json["video"]["id"] = "10_video";
    m_json["video"]["address"] = "wwwv.com";
    if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9877);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("bind error");
    }


    if (listen(listenfd, 5) < 0) {
        perror("listen error");
    }
    VideoSocialControl control;

    for ( ; ; ) {
        len = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len)) < 0) {
            perror("accept error");
        } else {
            std::cout << "连接成功" << std::endl;
        }
        std::cout << inet_ntoa(cliaddr.sin_addr) << std::endl;
        for (;;) {
            nlohmann::json h = receive();
            nlohmann::json js = control.handle(h);
            send(js);
        }
    }
}

int TcpSocket::send(nlohmann::json js)
{
    char send[MAXSIZE+1];
    //清空缓冲区
    bzero(&send, sizeof(send));

    std::string str = js.dump();
    if (str.size() == 0) return 0;
    std::cout << std::endl;
    char* c =  str.data();
    std::cout << "send:" << strlen(c) << "\n" << str << std::endl;
    int n = write(connfd, c, strlen(c));
    if (n < 0) {
        return -1;
    }

    return n;
}

nlohmann::json TcpSocket::receive()
{
    char recvline[MAXSIZE+1];
    //清空缓冲区
    bzero(&recvline, sizeof(recvline));

    int n = read(connfd, recvline, MAXSIZE);
    std::cout << std::endl;

    std::cout << "receive" << recvline << std::endl;
    nlohmann::json json = nlohmann::json::parse(std::string(recvline));
    return json;
}
