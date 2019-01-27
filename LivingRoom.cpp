#include "LivingRoom.h"
	

	LivingRoom * LivingRoom::create(int variation)
	{
		std::string spriteFile;

		switch (variation) {
		case 1: //This is where we add the Sprite image and the locations of the containers
			
			spriteFile = "LivingRoomAsset.jpg";
			break;
		}

		auto live = new (std::nothrow) LivingRoom;
		if (live && live->initWithFile(spriteFile)) {
			live->autorelease();
			return live;
		}
		CC_SAFE_RELEASE(live);
		return nullptr;
	}



	bool LivingRoom::isStairs()
	{
		return hasStairs;
	}

	void LivingRoom::generateVariation(int v)
	{
		if (v == 1) {
			Container* temp_container1 = new Container(this->getPosition());
			totalContainers.push_back(temp_container1);
			
		}
	}

