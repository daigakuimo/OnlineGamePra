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
    bool connect(int index);
    bool sendAll(const char *sendBuf, int size);
    bool sendSelectMember(const char *sendBuf, int size);
};