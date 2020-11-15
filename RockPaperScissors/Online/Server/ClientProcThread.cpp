#include "ClientProcThread.h"
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

ClientProcThread::ClientProcThread(int clientSockfd)
:mClientSockfd(clientSockfd)
{
    // 受診バッファ初期化
    memset(buf, 0, sizeof(buf));
}

int ClientProcThread::receive()
{
    int rsize;
    rsize = recv(mClientSockfd, buf, sizeof(buf),0);

    return rsize;
}

void ClientProcThread::sendResult(char *sendBuf, int size)
{
    write(mClientSockfd,sendBuf,size);
}

void ClientProcThread::closeSocket()
{
    close(mClientSockfd);
}