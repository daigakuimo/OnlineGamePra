#pragma once
#include "Server.h"

#define BUF_SIZE 4096

class Room : public Server
{
public:
    Room();
    void init(int port);
    void recvLoop();

private:
    int mRoomId;

protected:
    bool connect();
    bool sendAll();
    bool sendSelectMember();
};