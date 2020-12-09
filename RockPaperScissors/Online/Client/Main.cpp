#include "ClientGame.h"

int main(int argc, char *argv[])
{
    int port = atoi(argv[1]);
    ClientGame *game = new ClientGame(port);
    game->init();
    game->loop();

    return 0;
}