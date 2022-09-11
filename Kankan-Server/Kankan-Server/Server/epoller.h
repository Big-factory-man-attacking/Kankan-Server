#ifndef EPOLLER_H
#define EPOLLER_H

#include <vector>

extern "C" {
    #include <sys/epoll.h>
};

class epoller
{
public:
    epoller(int MAXNUM = 5);

    int Wait();
    void Addfd(int fd);
    void Delfd(int fd);

    epoll_event* getEvents();

private:
    int m_epollfd;
//    std::vector<struct epoll_event> _events;
    epoll_event _events[1024];
};

#endif // EPOLLER_H
