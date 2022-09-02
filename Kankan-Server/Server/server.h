#ifndef SERVER_H
#define SERVER_H

#include "Controller/videosocialcontrol.h"
#include <unordered_map>
#include "epoller.h"
#include "../ThreadPool/threadpool.h"

extern "C" {
    #include <arpa/inet.h>
};


class Server
{
public:
    Server(int port, int threadNums);

    void start();

    void initSocket();

    void dealListen(int listenfd);
    void addClient(int connfd);
    int setNonBlocking(int fd);

    void dealRead(int fd);
    void dealWrite(int fd);

    void onRead(int fd);
    void onWrite(int fd);

private:
    char readBuffer[1024];
    char writeBuffer[1024];

    struct sockaddr_in m_serveraddr;
    int m_port;
    int listenfd;

    std::unique_ptr<epoller> m_epoller;
    std::unique_ptr<ThreadPool> m_threadpool;

    std::unordered_map<int, VideoSocialControl> _users;
};

#endif
