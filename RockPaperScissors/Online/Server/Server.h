#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <sys/select.h>
#include <vector>
#include "Room.h"

#define BUF_SIZE 4096

class Server
{
public:
    Server();
    void init(int port);
    void recvLoop();
    void closeSocket();

private:
    bool sendRoomList();
    bool sendRoomInfo(int sendToFd);
    std::vector<Room> getRoomInfo();


protected:
    bool connect(int index);
    bool sendAll();
    bool sendSelectMember();

    int mSockfd;
    std::vector<int> mClientSockfds;
    struct sockaddr_in mAddr;

    socklen_t len = sizeof(struct sockaddr_in);
    std::vector<struct sockaddr_in> mFromAddrs;
};