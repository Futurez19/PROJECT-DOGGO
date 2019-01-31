#include "LivingRoom.h"
	

	LivingRoom * LivingRoom::create(int variation)
	{
		std::string spriteFile;

		switch (variation) {
		case 1: //This is where we add the Sprite image and the locations of the containers
			
			spriteFile = "LivingRoomAsset.jpg";
			break;
		case 2:

			spriteFile = "LivingRoomAsset2.jpg";
			break;
		case 3:

			spriteFile = "LivingRoomAsset3.jpg";
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

	//void LivingRoom::generateVariation(int v)
	//{
	//	switch(v){
	//	case 1:
	//		totalContainers.push_back(new Container(this->getPosition()));
	//		break;
	//	case 2:
	//		
	//		break;
	//	case 3:
	//		totalContainers.push_back(new Container(this->getPosition() - cocos2d::Vec2(20, 0)));
	//		break;
	//
	//	}
	//}
	//
	//