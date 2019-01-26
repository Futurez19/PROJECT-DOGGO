#pragma once
#include"cocos2d.h"
#include"Container.h"
#include <vector>

class Room : public cocos2d::Sprite
{
public:
	static Room * create();
	
private:
	
	std::vector<Container> totalContainers;

};

