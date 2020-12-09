#pragma once
#include "Client.h"
#include "Player.h"

class ClientGame
{
public:
    enum State
    {
        EInit,
        EGame,
        EFinish
    };

    ClientGame(int port);
    ~ClientGame();
    void loop();
    void receive();
    void input();
    void update();
    void output();
    void init();
    void updateGame();

    Player *getPlayer() { return mPlayer; }
    SousUnToit::Client *getClient() { return mClient; }

private:
    Player *mPlayer;
    SousUnToit::Client *mClient;

    bool mIsLoop;
    State mState;
};