#pragma once
#include "Server"

#define BUF_SIZE 4096

class Room : public Server
{
public:
    Room();
    void init(int port);
    void recvLoop() override;
    bool connect() override;
    bool sendAll() override;
    bool sendSelectMember() override;
};