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
		Container* temp_container1 = new Container(this->getPosition());
		totalContainers.push_back(temp_container1);

		break;

	}
}
