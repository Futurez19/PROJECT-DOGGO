#pragma once
#include "cocos2d.h"

class Stairs {
private:
	cocos2d::Vec2 position;
	float cooldown = 1.5f;

public:
	Stairs(cocos2d::Vec2 p);
	~Stairs();

	cocos2d::Vec2 getPos();
	


};
