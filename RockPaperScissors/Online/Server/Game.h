#include "Player.h"
#include "Server.h"

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

        Player* getPlayer1() { return mP1; }
        Player* getPlayer2() { return mP2; }
        Server* getServer() { return mServer; }
        int getPlayerCount() { return mPlayerCount; }

    private:
        Player *mP1;
        Player *mP2;
        int mPlayerCount;
        bool mIsRoop;
        State mState;
        int mBattleCount;
        Server *mServer;
};