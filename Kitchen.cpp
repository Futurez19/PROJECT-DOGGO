#include "Kitchen.h"

Kitchen * Kitchen::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers
		
		spriteFile = "KitchenAsset.jpg";
		break;
	case 2: 
		spriteFile = "KitchenAsset2.jpg";
		break;
	case 3:
		spriteFile = "KitchenAsset3.jpg";
		break;
	}

	auto kitch = new (std::nothrow) Kitchen;
	if (kitch && kitch->initWithFile(spriteFile)) {
		kitch->autorelease();
		return kitch;
	}
	CC_SAFE_RELEASE(kitch);
	return nullptr;
}

bool Kitchen::isStairs()
{
	return hasStairs;
}

void Kitchen::generateVariation(int v)
{
	switch(v){
	case 1:
		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(80, 0)));
		break;
	case 2:
		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(80, 0)));
		totalContainers.push_back(new Container(this->getPosition() + cocos2d::Vec2(40, 0)));
		break;
	case 3:
		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(20, 0)));
		break;

	}
}
