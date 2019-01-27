//#include "Stairway.h"
//
//Stairway * Stairway::create(int variation)
//{
//	std::string spriteFile;
//
//	switch (variation) {
//	case 1: //This is where we add the Sprite image and the locations of the containers
//
//		spriteFile = "pixel_Hallway.png";
//		break;
//	}
//
//	auto stair = new (std::nothrow) Stairway;
//	if (stair && stair->initWithFile(spriteFile)) {
//		stair->autorelease();
//		return stair;
//	}
//	CC_SAFE_RELEASE(stair);
//	return nullptr;
//}
//
//bool Stairway::isStairs()
//{
//	return hasStairs;
//}
//
//void Stairway::generateVariation(int v)
//{
//	if (v == 1) {
//		Container* temp_container1 = new Container(this->getPosition());
//		totalContainers.push_back(temp_container1);
//	}
//}