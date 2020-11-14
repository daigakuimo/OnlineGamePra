#include "Game.h"

Game::Game()
:mPlayerCount(0)
,mIsRoop(true)
,mState(State::EInit)
,mBattleCount(0)
{

}

Game::~Game()
{

}

void Game::addPlayer(std::string name)
{
    if(mPlayerCount == 0)
    {
        mP1 = new Player(name);
    }
    else
    {
        mP2 = new Player(name);
        mState = State::EGame;
    }

    mPlayerCount++;

    
}

void Game::updateInit()
{
    addPlayer("aya");
    addPlayer("ena");
}

void Game::roop()
{
    while(mIsRoop)
    {
        input();
        update();
        output();
    }
}

void Game::input()
{
    if(mState == State::EGame)
    {
        mP1->input();
        mP2->input();
    }
}

void Game::update()
{
    if(mState == State::EInit)
    {
        updateInit();
    }
    else
    {
        updateGame();
    }
    
}

void Game::output()
{
    if(mState == State::EGame)
    {
        if(mBattleCount == 0)
        {
            std::cout << mP1->getName() << " vs " << mP2->getName() << std::endl;
        }
        else
        {
            Player::Result result = mP1->getResult();
            if(result == Player::Result::EWin)
            {
                std::cout << mP1->getName() << "の勝利  " << std::endl;
            }
            else if(result == Player::Result::ELose)
            {
                std::cout << mP2->getName() << "の勝利  " << std::endl;
            }
            else
            {
                std::cout << "あいこ " << std::endl;
            }
        }
        
    }
    
}

void Game::updateGame()
{
    Player::Hand p1Hand = mP1->getHand();
    Player::Hand p2Hand = mP2->getHand();
    if(p1Hand == Player::ERock)
    {
        if(p2Hand == Player::EScissors)
        {
            mP1->setResult(Player::Result::EWin);
            mP2->setResult(Player::Result::ELose);
        }
        else if(p2Hand == Player::EPapers)
        {
            mP1->setResult(Player::Result::ELose);
            mP2->setResult(Player::Result::EWin);
        }
        else
        {
            mP1->setResult(Player::Result::EDraw);
            mP2->setResult(Player::Result::EDraw);
        } 
    }
    else if(p1Hand == Player::EPapers)
    {
        if(p2Hand == Player::ERock)
        {
            mP1->setResult(Player::Result::EWin);
            mP2->setResult(Player::Result::ELose);
        }
        else if(p2Hand == Player::EScissors)
        {
            mP1->setResult(Player::Result::ELose);
            mP2->setResult(Player::Result::EWin);
        }
        else
        {
            mP1->setResult(Player::Result::EDraw);
            mP2->setResult(Player::Result::EDraw);
        } 
    }
    else if(p1Hand == Player::EScissors)
    {
        if(p2Hand == Player::EPapers)
        {
            mP1->setResult(Player::Result::EWin);
            mP2->setResult(Player::Result::ELose);
        }
        else if(p2Hand == Player::ERock)
        {
            mP1->setResult(Player::Result::ELose);
            mP2->setResult(Player::Result::EWin);
        }
        else
        {
            mP1->setResult(Player::Result::EDraw);
            mP2->setResult(Player::Result::EDraw);
        } 
    }

    mBattleCount++;

    if(mP1->getResult() != Player::EDraw)
    {
        mIsRoop = false;
    }
}




