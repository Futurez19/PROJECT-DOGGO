#pragma once
#include"Container.h"
#include"cocos2d.h"
#include"Room.h"

class Kitchen : public Room {
public:
	static Kitchen * create(int);
	bool isStairs();
	void generateVariation(int);
private:
	bool hasStairs = false;
};