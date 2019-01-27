#include "Bathroom.h"

Bathroom * Bathroom::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "pixel_Bathroom.png";
		break;
	}

	auto bath = new (std::nothrow) Bathroom;
	if (bath && bath->initWithFile(spriteFile)) {
		bath->autorelease();
		return bath;
	}
	CC_SAFE_RELEASE(bath);
	return nullptr;
}

bool Bathroom::isStairs()
{
	return hasStairs;
}

void Bathroom::generateVariation(int v)
{
	if (v == 1) {
		Container* temp_container1 = new Container(this->getPosition());
		totalContainers.push_back(temp_container1);
	}
}
