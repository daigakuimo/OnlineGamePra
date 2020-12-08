#include <string>
#include "Room.h"

int main()
{
    Room *room = new Room();
    room->init(1234);
    room->recvLoop();

    return 0;
}