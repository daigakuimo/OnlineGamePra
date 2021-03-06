#pragma once
#include <string>
#include <iostream>

class Player
{
public:
    enum Hand
    {
        ERock,
        EPapers,
        EScissors,
    };

    enum Result
    {
        EWin,
        ELose,
        EDraw,
    };

    Player(std::string name);
    ~Player();

    void input();

    void init();
    std::string getName() { return mName; }
    void setName(std::string name) { mName = name; }
    Hand getHand() { return mHand; }
    void setHand(Hand hand) { mHand = hand; }
    Result getResult() { return mResult; }
    void setResult(Result result) { mResult = result; }
    int getID() { return mID; }
    void setID(int id) { mID = id; }

private:
    std::string mName;
    Hand mHand;
    Result mResult;
    int mID;
};