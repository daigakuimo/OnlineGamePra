#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

class Client
{
public:
    Client(int port);
    int getPort() { return mPort; }
    void init(const char* name, int *id);
    void receive();
    void sendHand(int id, int hand);

private:
    int mPort;
    int mSockfd;
    struct sockaddr_in mAddr;

    char *mBuf[BUF_SIZE];
};