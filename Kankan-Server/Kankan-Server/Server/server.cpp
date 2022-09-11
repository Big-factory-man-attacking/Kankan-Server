#include "server.h"
#include <iostream>
#include "ThreadPool/threadpool.h"
#include "json.hpp"

extern "C" {
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <unistd.h>
};

Server::Server(int port, int threadNums) : m_port(port), m_epoller(new epoller()), m_threadpool(new ThreadPool(threadNums))
{
    initSocket();
}

void Server::start()
{
    while (1) {
        int fd = m_epoller->Wait();
        epoll_event* event = m_epoller->getEvents();
        for (int i = 0; i < fd; i++) {
            int sockfd = event[i].data.fd;
            if (sockfd == listenfd) {
                dealListen(sockfd);
            } else if (event[i].events & EPOLLIN) {
                dealRead(event[i].data.fd);
            }
        }
    }
}

void Server::initSocket()
{
    if (m_port < 1024 || m_port > 65535) {
        std::cout << "非法端口号" << std::endl;
    }

    int ret;
    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        std::cout << "创建套接字失败" << std::endl;
    }

    bzero(&m_serveraddr, sizeof(m_serveraddr));
    m_serveraddr.sin_family = AF_INET;
    m_serveraddr.sin_port = htons(m_port);
    m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(listenfd, (struct sockaddr*)&m_serveraddr, sizeof(m_serveraddr));
    if (ret < 0) {
        std::cout << "绑定失败" << std::endl;
    }

    ret = listen(listenfd, 5);
    if (ret < 0) {
        std::cout << "监听失败" << std::endl;
    }

    m_epoller->Addfd(listenfd);
    setNonBlocking(listenfd);
}

void Server::dealListen(int listenfd)
{
    if (listenfd < 0) {
        std::cout << "" << std::endl;   //应该要从epoll事件表中删除,并关闭监听套接字，
    }

    struct sockaddr_in cliaddr;
    socklen_t clientLength = sizeof(cliaddr);

    int fd = accept(listenfd, (struct sockaddr*)&cliaddr, &clientLength);
    if (fd < 0) {
        std::cout << "accpet error" << std::endl;
    }

    addClient(fd);
}

void Server::addClient(int connfd)
{
    _users[connfd] = VideoSocialControl();
    m_epoller->Addfd(connfd);
    setNonBlocking(connfd);
    std::cout << "成功添加新的客户端" << std::endl;
}

int Server::setNonBlocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, new_option);

    return old_option;
}

void Server::dealRead(int fd)
{
    if (fd < 0) {}
//    m_threadpool->enqueue([this, fd]{this->onRead(fd);});
    m_threadpool->AddTask(std::bind(&Server::onRead, this, fd));
}

void Server::onRead(int fd)
{
    std::cout << "event trigger once\n";
    while (1) {
        //清空缓冲区
        bzero(&readBuffer, sizeof(readBuffer));
        int ret = recv(fd, readBuffer, 1024, 0);
        if (ret < 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                std::cout << "read later" << std::endl;
            }
            m_epoller->Delfd(fd);
            close(fd);
            break;
        } else if (ret == 0) {
            std::cout << "read error" << std::endl;
            m_epoller->Delfd(fd);
            close(fd);
        } else {
            nlohmann::json json = nlohmann::json::parse(std::string(readBuffer));

            std::cout << json.dump(4) << std::endl;
            nlohmann::json j = _users[fd].dealPost(json);
            if (!j.empty()) {
                send(fd, j.dump().data(), strlen(j.dump().data()), 0);
            }
        }
    }
}