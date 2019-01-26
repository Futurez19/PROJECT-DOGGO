#include "LivingRoom.h"
	

	LivingRoom * LivingRoom::create(int variation)
	{
		std::string spriteFile;

		switch (variation) {
		case 1: //This is where we add the Sprite image and the locations of the containers

			spriteFile = "3.png";
			break;
		}

		auto live = new (std::nothrow) LivingRoom;
		if (live && live->initWithFile(spriteFile)) {
			live->autorelease();
			return live;
		}
		CC_SAFE_RELEASE(live);
		return nullptr;
	}
