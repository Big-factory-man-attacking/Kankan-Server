cmake_minimum_required(VERSION 3.5)

project(Kankan-Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Kankan-Server main.cpp)

install(TARGETS Kankan-Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
