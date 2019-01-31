#include "Bathroom.h"

Bathroom * Bathroom::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers

		spriteFile = "Bathroom1.png";
		break;
	case 2: 

		spriteFile = "Bathroom2.png";
		break;
	case 3: 

		spriteFile = "Bathroom3.png";
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

//void Bathroom::generateVariation(int v)
//{
//	switch (v) {
//	case 1:
//		totalContainers.push_back(new Container(this->getPosition() + cocos2d::Vec2(115, 0)));
//		break;
//	case 2:
//		totalContainers.push_back(new Container(this->getPosition() + cocos2d::Vec2(120, 0)));
//		break;
//	case 3:
//		totalContainers.push_back(new Container(this->getPosition() + cocos2d::Vec2(115, 0)));
//		break;
//
//	}
//}
