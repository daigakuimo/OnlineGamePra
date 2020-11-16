
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
        void receive();
        void input();
        void update();
        void output();
        void updateInit();
        void updateGame();

        class Player* getPlayer1() { return mP1; }
        class Player* getPlayer2() { return mP2; }
        class Server* getServer() { return mServer; }
        int getPlayerCount() { return mPlayerCount; }

    private:
        class Player *mP1;
        class Player *mP2;
        int mPlayerCount;
        bool mIsRoop;
        State mState;
        int mBattleCount;
        class Server *mServer;
};