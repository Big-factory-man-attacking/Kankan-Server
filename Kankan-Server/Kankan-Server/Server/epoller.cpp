#include "epoller.h"
#include <iostream>

extern "C" {
    #include <sys/epoll.h>
};

epoller::epoller(int MAXNUM) : m_epollfd(epoll_create(MAXNUM)), _events{}
{

}

int epoller::Wait()
{
    int ret = epoll_wait(m_epollfd, _events, 5, -1);
    if (ret < 0) {
        std::cout << "epoll_wait 失败" << std::endl;
    }

    return ret;
}

void epoller::Addfd(int fd)
{
    epoll_event event;

    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;

    if (fd < 0) {

    }

    epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &event);
}

void epoller::Delfd(int fd)
{
    epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, nullptr);
}

epoll_event* epoller::getEvents()
{
    return _events;
}
