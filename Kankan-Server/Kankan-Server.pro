TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Server/epoller.cpp \
        Server/server.cpp \
        SqlCon/commentbroker.cpp \
        SqlCon/manuscriptbroker.cpp \
        SqlCon/netizenbroker.cpp \
        SqlCon/relationalbroker.cpp \
        SqlCon/videobroker.cpp \
        ThreadPool/threadpool.cpp \
        entity/comment.cpp \
        entity/commentproxy.cpp \
        entity/main.cpp \
        entity/manuscript.cpp \
        entity/manuscriptproxy.cpp \
        entity/netizen.cpp \
        entity/netizenproxy.cpp \
        entity/video.cpp \
        entity/videoproxy.cpp \
        main.cpp \
        tcpsocket.cpp \
        videosocialcontrol.cpp

HEADERS += \
    Server/epoller.h \
    Server/server.h \
    SqlCon/commentbroker.h \
    SqlCon/manuscriptbroker.h \
    SqlCon/netizenbroker.h \
    SqlCon/relationalbroker.h \
    SqlCon/videobroker.h \
    ThreadPool/threadpool.h \
    entity/comment.h \
    entity/commentinterface.h \
    entity/commentproxy.h \
    entity/manuscript.h \
    entity/manuscriptinterface.h \
    entity/manuscriptproxy.h \
    entity/netizen.h \
    entity/netizeninterface.h \
    entity/netizenproxy.h \
    entity/video.h \
    entity/videointerface.h \
    entity/videoproxy.h \
    tcpsocket.h \
    videosocialcontrol.h
