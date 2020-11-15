#include "ClientGame.h"


ClientGame::ClientGame()
:mIsRoop(true)
,mState(State::EInit)
,mClient(new Client(2222))
{

}

ClientGame::~ClientGame()
{

}

void ClientGame::updateInit()
{
    mPlayer->init();
    int *id;
    mClient->init(mPlayer->getName().c_str(), id);
    mPlayer->setID(*id);
}

void ClientGame::roop()
{
    while(mIsRoop)
    {
        input();
        update();
        output();
    }
}

void ClientGame::input()
{
    if(mState == State::EGame)
    {
       mPlayer->input();
       mClient->sendHand(mPlayer->getID(), mPlayer->getHand());
    }
}

void ClientGame::update()
{
    if(mState == State::EInit)
    {
        updateInit();
        mState = State::EGame;
    }
    else
    {
        updateGame();
    }
    
}

void ClientGame::output()
{
    if(mState == State::EInit)
    {

    }
    else if(mState == State::EGame)
    {
        
    }
    
}

void ClientGame::updateGame()
{
    
}




