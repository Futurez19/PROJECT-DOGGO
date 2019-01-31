#pragma once
#include "cocos2d.h"

class Stairs {
private:
	cocos2d::Vec2 position;
	float cooldown = 1.5f;

	bool up = false;
public:
	Stairs(cocos2d::Vec2 p,bool);
	~Stairs();

	cocos2d::Vec2 getPos();
	


};
