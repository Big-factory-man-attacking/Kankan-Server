#ifndef SERVER_H
#define SERVER_H

#include "videosocialcontrol.h"
#include <unordered_map>
#include "epoller.h"

class Server
{
public:
    Server(int port);

    void start();

    void initSocket();

    void dealListen(int listenfd);
    void addClient(int connfd);
    int setNonBlocking(int fd);

    void dealRead();
    void dealWrite();

private:
    struct sockaddr_in m_serveraddr;
    int m_port;

    int listenfd;

    std::unique_ptr<epoller> m_epoller;

    std::unordered_map<int, VideoSocialControl> _users;
};

#endif
