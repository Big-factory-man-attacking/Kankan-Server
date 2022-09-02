cmake_minimum_required(VERSION 3.5)

project(Kankan-Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Kankan-Server main.cpp
    comment.cpp comment.h commentbroker.cpp commentbroker.h commentinterface.h commentproxy.cpp commentproxy.h
    netizen.cpp netizen.h netizenbroker.cpp netizenbroker.h netizeninterface.h netizenproxy.cpp netizenproxy.h
    relationalbroker.cpp relationalbroker.h manuscript.cpp manuscript.h manuscriptbroker.cpp manuscriptbroker.h video.h video.cpp videobroker.cpp
    videobroker.h videointerface.h videointerface.h videoproxy.cpp videoproxy.h manuscriptinterface.h manuscriptproxy.cpp manuscriptproxy.h
    videosocialcontrol.cpp videosocialcontrol.h tcpsocket.h tcpsocket.cpp)

link_directories(/usr/lib)

target_link_libraries(Kankan-Server mariadbcpp)


install(TARGETS Kankan-Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
