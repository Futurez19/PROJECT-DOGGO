#include "Hallway.h"

Hallway * Hallway::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "pixel_Hallway.png";
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

void Hallway::generateVariation(int v)
{
	if (v == 1) {
		Container* temp_container1 = new Container(this->getPosition());
		totalContainers.push_back(temp_container1);
	}
}
