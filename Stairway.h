#pragma once
#include"Room.h"
#include"cocos2d.h"
#include"Container.h"

#include"Stairs.h"

class Stairway : public Room {
private:
	bool hasStairs = true;
	Stairs Stairwell;
	Stairs StairwellDown;
public:
	Stairway():Stairwell(cocos2d::Vec2(this->getPosition()),true), StairwellDown(cocos2d::Vec2(this->getPosition() + cocos2d::Vec2(0,200)), false) {};
	static Stairway * create(int);
	Stairs getStairs();
	bool isStairs();
	//void generateVariation(int);

	//CREATE_FUNC(create);
};