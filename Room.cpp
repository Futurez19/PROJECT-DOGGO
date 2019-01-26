#include "Room.h"

Room * Room::create()
{
	auto room = new (std::nothrow) Room;
	if (room && room->initWithFile("2.png")) {
		room->autorelease();
		return room;
	}
	CC_SAFE_RELEASE(room);
	return nullptr;

	
}
