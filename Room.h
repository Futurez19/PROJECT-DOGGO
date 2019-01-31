#pragma once
#include "cocos2d.h"
#include "Container.h"
#include <ctime>

class Room : public cocos2d::Sprite {
public:
	std::vector<Container*> totalContainers;
	

	int variation;

	
	virtual bool isStairs() = 0;
	//virtual void generateVariation(int) = 0;
private:
	
	
};