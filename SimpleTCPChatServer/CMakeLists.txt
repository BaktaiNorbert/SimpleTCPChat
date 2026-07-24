cmake_minimum_required(VERSION 3.16)

project(SimpleTCPChatServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SimpleTCPChatServer main.cpp
    sessionmanager.h sessionmanager.cpp
    Client.h)

include(GNUInstallDirs)
install(TARGETS SimpleTCPChatServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
