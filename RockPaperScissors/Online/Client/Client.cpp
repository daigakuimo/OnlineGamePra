#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "Client.h"

// for convenience
using json = nlohmann::json;

namespace SousUnToit
{

    Client::Client(int port)
        : mPort(port)
    {
        mIsReceive = false;
    }

    void Client::init(const char *name, int &id)
    {
        // ソケット作成
        if ((mSockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("socket");
        }

        // 送信先アドレス・ポート番号設定
        mAddr.sin_family = AF_INET;
        mAddr.sin_port = htons(mPort);
        mAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // サーバ接続
        connect(mSockfd, (struct sockaddr *)&mAddr, sizeof(struct sockaddr_in));

        printf("connected\n");
    }

    void Client::receive()
    {
        mIsReceive = false;
        int maxFd;         // ディスクリプタの最大値
        fd_set rFds;       // 接続待ち、受信待ちをするディスクリプタの集合
        struct timeval tv; // タイムアウト時間

        // 接続待ちのディスクリプタをディスクリプタ集合に設定する
        FD_ZERO(&rFds);
        FD_SET(mSockfd, &rFds);
        maxFd = mSockfd;

        // タイムアウト時間を0secに指定する。
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        int cnt;

        cnt = select(maxFd + 1, &rFds, NULL, NULL, &tv);
        if (cnt < 0)
        {
            if (errno != EINTR)
                return;
        }
        else if (cnt == 0)
        {
            return;
        }
        else
        {
            // 接続待ちディスクリプタに接続があるか調べる
            if (FD_ISSET(mSockfd, &rFds))
            {
                char buf[BUF_SIZE];
                // データがあるならパケット受信する
                cnt = recv(mSockfd, buf, sizeof(buf), 0);
                if (cnt > 0)
                {
                    // パケット受信成功の場合
                    printf("recv[%d]:\"%s\"\n", mSockfd, buf);
                    mReceiveStr = buf;

                    mIsReceive = true;
                }
                else if (cnt == 0)
                {
                    // 切断された場合、クローズする
                    printf("socket:%d  disconnected. \n", mSockfd);
                    close(mSockfd);
                }
                else
                {
                    perror("error recv");
                }
            }
        }
    }

    bool Client::sendAll(const char *sendData)
    {
        // クライアントからのコネクト要求待ち
        int sendTo[1];
        sendTo[0] = -1;

        json sendJson;
        sendJson["function_name"] = "sendAll";
        sendJson["owner"] = 0;
        sendJson["send_to"] = sendTo;
        sendJson["data"] = sendData;
        std::string s = sendJson.dump();
        const char *sendBuf = s.c_str();
        printf("%s\n", sendBuf);

        if (send(mSockfd, sendBuf, BUF_SIZE, 0) < 0)
        {
            perror("send");
        }

        return true;
    }

    bool Client::sendSelectMember(const char *sendData, std::vector<int> sendToList)
    {
        json sendJson;
        sendJson["function_name"] = "sendSelectMember";
        sendJson["owner"] = 0;
        sendJson["send_to"] = sendToList;
        sendJson["data"] = sendData;

        std::string s = sendJson.dump();
        const char *sendBuf = s.c_str();

        if (send(mSockfd, sendBuf, sizeof(sendBuf), 0) < 0)
        {
            perror("send");
        }

        return true;
    }

} // namespace SousUnToit