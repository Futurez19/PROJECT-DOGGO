#include "DiningRoom.h"

DiningRoom * DiningRoom::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "3.png";
		break;
	}

	auto dine = new (std::nothrow) DiningRoom;
	if (dine && dine->initWithFile(spriteFile)) {
		dine->autorelease();
		return dine;
	}
	CC_SAFE_RELEASE(dine);
	return nullptr;
}
