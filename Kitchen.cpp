#include "Kitchen.h"

Kitchen * Kitchen::create(int variation)
{
	std::string spriteFile;

	switch (variation) {
	case 1: //This is where we add the Sprite image and the locations of the containers
		
		spriteFile = "KitchenAsset.jpg";
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

void Kitchen::generateVariation(int v)
{
	if (v == 1) {
		Container* temp_container1 = new Container(cocos2d::Vec2(400,100));
		totalContainers.push_back(temp_container1);
	}
}
