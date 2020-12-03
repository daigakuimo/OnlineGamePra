#include "ClientProcThread.h"

#define BUF_SIZE 4096

class Server
{
public:
    Server(class Game *game);
    void init(int port);
    bool connect();
    void closeSocket();

private:
    int mSockfd;
    int mClientSockfd;
    struct sockaddr_in mAddr;

    socklen_t len = sizeof( struct sockaddr_in );
    struct sockaddr_in mFromAddr;
    class Game *mGame;
};