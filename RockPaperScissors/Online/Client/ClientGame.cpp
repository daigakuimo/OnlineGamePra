#include <string>
#include "ClientGame.h"
#include <iostream>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

ClientGame::ClientGame(int port)
    : mIsLoop(true), mState(State::EInit), mClient(new SousUnToit::Client(port))
{
    mPlayer = new Player("ena");
}

ClientGame::~ClientGame()
{
}

void ClientGame::init()
{
    mPlayer->init();
    int id;
    mClient->init(mPlayer->getName().c_str(), id);
    id = 0;
    mPlayer->setID(id);
    mState = State::EGame;
}

void ClientGame::loop()
{
    while (mIsLoop)
    {
        receive();
        input();
    }
}

void ClientGame::receive()
{

    mClient->receive();
    if(mClient->getIsReceive())
    {
        std::cout << mClient->getReceiveStr() << std::endl;
        json receiveJson = json::parse(mClient->getReceiveStr());
    }
    // std::string state = receiveJson["state"];
    // if (state == "start")
    // {
    // }
    // else if (state == "result")
    // {
    //     std::string result = receiveJson["result"];
    //     if (result == "win")
    //     {
    //         std::cout << "プレイヤーの勝利 " << std::endl;
    //         mIsLoop = false;
    //         mState = State::EFinish;
    //     }
    //     else if (result == "lose")
    //     {
    //         std::cout << "プレイヤーの負け " << std::endl;
    //         mIsLoop = false;
    //         mState = State::EFinish;
    //     }
    //     else
    //     {
    //         std::cout << "あいこ" << std::endl;
    //     }
    // }
}

void ClientGame::input()
{
    if (mState == State::EGame)
    {
        mPlayer->input();
        json data;
        data["Hand"] = mPlayer->getHand();
        std::string s = data.dump();
        const char *sendData = s.c_str();
        mClient->sendAll(sendData);
    }
}
