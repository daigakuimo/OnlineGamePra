#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class ClientProcThread
{
public:
    ClientProcThread(int clientSockfd);
    int receive();
    void sendResult(char *sendBuf, int size);
    void closeSocket();

private:
    int mClientSockfd;
    char buf[4096];
};