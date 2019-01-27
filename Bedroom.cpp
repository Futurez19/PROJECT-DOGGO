#include "Bedroom.h"

Bedroom * Bedroom::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "BedroomAsset.jpg";
		break;
	case 2: 

		spriteFile = "BedroomAsset2.jpg";
		break;
	case 3:

		spriteFile = "BedroomAsset3.jpg";
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
	switch (v) {
	case 1:
		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(55, 0)));
		break;
	case 2:
		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(60, 0)));
		totalContainers.push_back(new Container(this->getPosition() + cocos2d::Vec2(70, 0)));
		break;
	case 3:
		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(150, 0)));
		break;

	}
}
