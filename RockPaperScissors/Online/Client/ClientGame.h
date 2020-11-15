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

        ClientGame();
        ~ClientGame();
        void roop();
        void input();
        void update();
        void output();
        void updateInit();
        void updateGame();

        Player* getPlayer() { return mPlayer; }
        Client* getClient() { return mClient; }

    private:
        Player *mPlayer;
        Client *mClient;

        bool mIsRoop;
        State mState;
};