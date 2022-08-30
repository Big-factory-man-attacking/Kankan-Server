#include <iostream>
#include "Server/server.h"

using namespace std;

int main()
{
    // 端口为9877， 线程池线程数为10
    Server server(9877,10);

    // 启动服务器
    server.start();

    return 0;
}
