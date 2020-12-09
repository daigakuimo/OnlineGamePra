#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#define BUF_SIZE 4096

namespace SousUnToit
{

    class Client
    {
    public:
        Client(int port);
        int getPort() { return mPort; }
        void init(const char *name, int &id);
        void receive();
        bool sendAll(const char *sendData);
        bool sendSelectMember(const char *sendData, std::vector<int> sendToList);

        std::string getReceiveStr() { return mReceiveStr; }
        bool getIsReceive() { return mIsReceive; }

    private:
        int mPort;
        int mSockfd;
        struct sockaddr_in mAddr;

        int mMaxfd; // ディスクリプタの最大値

        std::string mReceiveStr;

        bool mIsReceive;
    };
} // namespace SousUnToit