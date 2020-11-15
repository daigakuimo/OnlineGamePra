#include "ClientProcThread.h"

class Server
{
public:
    Server(Game *game);
    void init(int port);
    bool connect();
    void closeSocket();

private:
    int mSockfd;
    int mClientSockfd;
    struct sockaddr_in mAddr;

    socklen_t len = sizeof( struct sockaddr_in );
    struct sockaddr_in mFromAddr;
    Game *mGame;
};