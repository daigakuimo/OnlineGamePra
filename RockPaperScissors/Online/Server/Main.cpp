#include <string>
#include "Room.h"

int main()
{
    SousUnToit::Room *room = new SousUnToit::Room();
    room->init(1234);
    room->recvLoop();

    return 0;
}