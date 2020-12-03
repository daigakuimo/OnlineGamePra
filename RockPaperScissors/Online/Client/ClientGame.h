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
        void roop();
        void receive();
        void input();
        void update();
        void output();
        void init();
        void updateGame();

        Player* getPlayer() { return mPlayer; }
        Client* getClient() { return mClient; }

    private:
        Player *mPlayer;
        Client *mClient;

        bool mIsRoop;
        State mState;
};