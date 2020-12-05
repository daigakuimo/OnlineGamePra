#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#define BUF_SIZE 1024

class Client
{
public:
    Client(int port);
    int getPort() { return mPort; }
    void init(const char* name, int &id);
    void receive();
    void sendHand(int id, int hand);

    std::string getReceiveStr() { return mReceiveStr; }

private:
    int mPort;
    int mSockfd;
    struct sockaddr_in mAddr;
    
    int     cnt;
    int     mMaxfd;          // ディスクリプタの最大値
    fd_set  mRfds;           // 接続待ち、受信待ちをするディスクリプタの集合
    fd_set  mSfds;           // 送信待ちをするディスクリプタの集合
    struct  timeval  mTv;    // タイムアウト時間

    std::string mReceiveStr;
};