#include "Player.h"

class Game
{
    public:
        enum State
        {
            EInit,
            EGame,
            EFinish
        };

        Game();
        ~Game();
        void addPlayer(std::string name);
        void roop();
        void input();
        void update();
        void output();
        void updateInit();
        void updateGame();

    private:
        Player *mP1;
        Player *mP2;
        int mPlayerCount;
        bool mIsRoop;
        State mState;
        int mBattleCount;
};