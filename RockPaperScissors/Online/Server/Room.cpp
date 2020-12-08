#include "Room.h"
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

Room::Room()
{
    for ( int i = 0; i < mClientSockfds.size(); i++ )
    {
        mClientSockfds[i] = -1;
    }
}

void Room::init(int port)
{
    // ソケット生成
    if ((mSockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
    }

    // 待ち受け用IP・ポート番号
    mAddr.sin_family = AF_INET;
    mAddr.sin_port = htons(port);
    mAddr.sin_addr.s_addr = INADDR_ANY;

    // バインド
    if (bind(mSockfd, (struct sockaddr *)&mAddr, sizeof(mAddr)) < 0)
    {
        perror("bind");
    }

    // 受信待ち
    if (listen(mSockfd, SOMAXCONN) < 0)
    {
        perror("listen");
    }
}

void Room::recvLoop()
{
    int maxFd;         // ディスクリプタの最大値
    fd_set rFds;       // 接続待ち、受信待ちをするディスクリプタの集合
    struct timeval tv; // タイムアウト時間

    while (1)
    {
        // 接続待ちのディスクリプタをディスクリプタ集合に設定する
        FD_ZERO(&rFds);
        FD_SET(mSockfd, &rFds);
        maxFd = mSockfd;

        // 受信待ちのディスクリプタをディスクリプタ集合に設定する
        for (int i = 0; i < mClientSockfds.size(); i++)
        {
            if (mClientSockfds[i] != -1)
            {
                FD_SET(mClientSockfds[i], &rFds);
                if (mClientSockfds[i] > maxFd)
                    maxFd = mClientSockfds[i];
            }
        }

        // タイムアウト時間を0secに指定する。
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        int cnt;

        cnt = select(maxFd + 1, &rFds, NULL, NULL, &tv);
        if (cnt < 0)
        {
            if (errno == EINTR)
                continue;

            break;
        }
        else if (cnt == 0)
        {
            continue;
        }
        else
        {
            // 接続待ちディスクリプタに接続があるか調べる
            if (FD_ISSET(mSockfd, &rFds))
            {
                for (int i = 0; i < mClientSockfds.size(); i++)
                {
                    if (mClientSockfds[i] == -1)
                    {
                        if (!connect(i))
                        {
                            perror("error accept");
                        }

                        printf("socket[%d] connected\n", mClientSockfds[i]);
                        break;
                    }
                }
            }

            for (int i = 0; i < mClientSockfds.size(); i++)
            {
                if (FD_ISSET(mClientSockfds[i], &rFds))
                {
                    char buf[BUF_SIZE];
                    // データがあるならパケット受信する
                    cnt = recv(mClientSockfds[i], buf, sizeof(buf), 0);
                    if (cnt > 0)
                    {
                        // パケット受信成功の場合
                        printf("recv[%d]:\"%s\"\n", mClientSockfds[i], buf);
                    }
                    else if (cnt == 0)
                    {
                        // 切断された場合、クローズする
                        printf("socket:%d  disconnected. \n", mClientSockfds[i]);
                        close(mClientSockfds[i]);
                        mClientSockfds[i] = -1;
                    }
                    else
                    {
                        perror("error recv");
                    }
                }
            }
        }
    }
}

bool Room::connect(int index)
{
    // クライアントからのコネクト要求待ち
    if ((mClientSockfds[index] = accept(mSockfd, (struct sockaddr *)&mFromAddrs[index], &len)) < 0)
    {
        perror("error connect");
        return false;
    }

    return true;
}

bool Room::sendAll(const char *sendBuf, int size)
{
    for (int i = 0; i < mClientSockfds.size(); i++)
    {
        int sendMsgSize;
        if ((sendMsgSize = send(mClientSockfds[i], sendBuf, size, 0)) < 0)
        {
            perror("send() failed.");
            return false;
        }
        else if (sendMsgSize == 0)
        {
            fprintf(stderr, "connection closed by foreign host.\n");
            close(mClientSockfds[i]);
            mClientSockfds[i] = -1;
            return false;
        }
    }
    return true;
}

bool Room::sendSelectMember(const char *sendBuf, int size)
{
    return true;
}