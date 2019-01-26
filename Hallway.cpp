#include "Hallway.h"

Hallway * Hallway::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "3.png";
		break;
	}

	auto hall = new (std::nothrow) Hallway;
	if (hall && hall->initWithFile(spriteFile)) {
		hall->autorelease();
		return hall;
	}
	CC_SAFE_RELEASE(hall);
	return nullptr;
}
