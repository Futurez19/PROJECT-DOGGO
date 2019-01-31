#include "Stairway.h"

Stairway * Stairway::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "pixel_Hallway.png";
		break;
	case 2: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "HallwayAsset2.jpg";
		break;
	case 3: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "HallwayAsset3.png";
		break;
	}

	auto stair = new (std::nothrow) Stairway;
	if (stair && stair->initWithFile(spriteFile)) {
		stair->autorelease();
		return stair;
	}
	CC_SAFE_RELEASE(stair);
	return nullptr;
}

Stairs Stairway::getStairs()
{
	return Stairwell;
}

bool Stairway::isStairs()
{
	return hasStairs;
}

//void Stairway::generateVariation(int v)
//{
//	switch (v) {
//	case 1:
//		
//		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(120, 0)));
//
//		totalContainers.push_back(new Container(this->getPosition()));//The Stair
//		break;
//	case 2:
//		
//		totalContainers.push_back(new Container(this->getPosition() + cocos2d::Vec2(75, 0)));
//
//		totalContainers.push_back(new Container(this->getPosition()));//
//		break;
//	case 3:
//		totalContainers.push_back(new Container(this->getPosition()));//
//		break;
//
//	}
//}