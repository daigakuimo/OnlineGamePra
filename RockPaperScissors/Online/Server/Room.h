#pragma once
#include "Server.h"

#define BUF_SIZE 4096

namespace SousUnToit
{

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
        bool sendAll(const char *sendBuf, int size);
        bool sendExceptOwner(const char *sendBuf, int size, int owner);
        bool sendSelectMember(const char *sendBuf, int size);
    };
}