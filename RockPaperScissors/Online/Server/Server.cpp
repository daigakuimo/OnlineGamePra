#include "Server.h"
#include <nlohmann/json.hpp>
#include "Game.h"
#include "Player.h"

// for convenience
using json = nlohmann::json;

Server::Server(Game *game)
:mGame(game)
{

}

void Server::init(int port)
{
    // ソケット生成
    if((mSockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
    }

    // 待ち受け用IP・ポート番号
    mAddr.sin_family = AF_INET;
    mAddr.sin_port = htons(port);
    mAddr.sin_addr.s_addr = INADDR_ANY;

    // バインド
    if(bind(mSockfd, (struct sockaddr *)&mAddr, sizeof(mAddr)) < 0)
    {
        perror("bind");
    }

    // 受信待ち
    if(listen(mSockfd,SOMAXCONN) < 0)
    {
        perror("listen");
    }
}

bool Server::connect()
{
    // クライアントからのコネクト要求待ち
    if((mClientSockfd = accept(mSockfd, (struct sockaddr *)&mFromAddr, &len)) < 0)
    {
        perror("listen");
        return false;
    }

    int rsize;
    char buf[BUF_SIZE];
    rsize = recv(mClientSockfd, buf, sizeof(buf),0);

    json receiveJson = json::parse(buf);
    std::string name = receiveJson["player_name"];
    mGame->addPlayer(name);

    int id = 0;
    if(mGame->getPlayerCount() == 1)
    {
        Player *temp = mGame->getPlayer1();
        id = temp->getID();
    }
    else if(mGame->getPlayerCount() == 2)
    {
        id = mGame->getPlayer2()->getID();
    }

    json sendJson;
    sendJson["state"] = "init";
    sendJson["id"] = id;

    std::string s = sendJson.dump(); 
    const char* sendBuf = s.c_str();

    write(mClientSockfd,sendBuf,BUF_SIZE);

    return true;
}

void Server::closeSocket()
{
    // ソケットクローズ
    close(mSockfd);
}