#include "Bedroom.h"

Bedroom * Bedroom::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "BedroomAsset.jpg";
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

bool Bedroom::isStairs()
{
	return hasStairs;
}

void Bedroom::generateVariation(int v)
{
	if (v == 1) {
		Container* temp_container1 = new Container(this->getPosition());
		totalContainers.push_back(temp_container1);
	}
}
