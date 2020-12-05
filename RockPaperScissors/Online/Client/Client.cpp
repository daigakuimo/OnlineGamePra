#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "Client.h"

// for convenience
using json = nlohmann::json;

Client::Client(int port)
    : mPort(port)
{
    mTv.tv_sec = 0;
    mTv.tv_usec = 0;
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

    mMaxfd = mSockfd;

    // json形式でテクストデータ作成
    json j;
    j["state"] = "init";
    j["player_name"] = name;

    std::string s = j.dump();
    const char *sendBuf = s.c_str();

    if (send(mSockfd, sendBuf, BUF_SIZE, 0) < 0)
    {
        perror("send");
    }

    char recvStr[BUF_SIZE];
    recv(mSockfd, recvStr, BUF_SIZE, 0);

    json receiveJson = json::parse(recvStr);
    std::cout << receiveJson << std::endl;

    int i = receiveJson.value("id", 0);
    id = i;
}

void Client::receive()
{
    char buf[BUF_SIZE];
    recv(mSockfd, buf, BUF_SIZE, 0);
    mReceiveStr = buf;
}

void Client::sendHand(int id, int hand)
{
    // json形式でテクストデータ作成
    json sendJson;
    sendJson["state"] = "game";
    sendJson["player"]["id"] = id;
    sendJson["player"]["hand"] = hand;
    std::string s = sendJson.dump();
    const char *sendBuf = s.c_str();

    if (send(mSockfd, sendBuf, BUF_SIZE, 0) < 0)
    {
        perror("send");
    }

    std::cout << sendBuf << std::endl;
}