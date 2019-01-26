#include "Bedroom.h"

Bedroom * Bedroom::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "3.png";
		break;
	}

	auto bed = new (std::nothrow) Bedroom;
	if (bed && bed->initWithFile(spriteFile)) {
		bed->autorelease();
		return bed;
	}
	CC_SAFE_RELEASE(bed);
	return nullptr;
}
