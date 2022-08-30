TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread -lmariadbcpp

SOURCES += \
        Server/epoller.cpp \
        Server/server.cpp \
        SqlCon/commentbroker.cpp \
        SqlCon/manuscriptbroker.cpp \
        SqlCon/netizenbroker.cpp \
        SqlCon/relationalbroker.cpp \
        SqlCon/videobroker.cpp \
        ThreadPool/threadpool.cpp \
        Entity/comment.cpp \
        Entity/commentproxy.cpp \
        Entity/manuscript.cpp \
        Entity/manuscriptproxy.cpp \
        Entity/netizen.cpp \
        Entity/netizenproxy.cpp \
        Entity/video.cpp \
        Entity/videoproxy.cpp \
        main.cpp \
        Controller/videosocialcontrol.cpp

HEADERS += \
    Server/epoller.h \
    Server/server.h \
    SqlCon/commentbroker.h \
    SqlCon/manuscriptbroker.h \
    SqlCon/netizenbroker.h \
    SqlCon/relationalbroker.h \
    SqlCon/videobroker.h \
    ThreadPool/threadpool.h \
    Entity/comment.h \
    Entity/commentinterface.h \
    Entity/commentproxy.h \
    Entity/manuscript.h \
    Entity/manuscriptinterface.h \
    Entity/manuscriptproxy.h \
    Entity/netizen.h \
    Entity/netizeninterface.h \
    Entity/netizenproxy.h \
    Entity/video.h \
    Entity/videointerface.h \
    entity/videoproxy.h \
    Controller/videosocialcontrol.h
