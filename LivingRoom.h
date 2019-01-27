#pragma once
#include"Container.h"
#include"cocos2d.h"
#include"Room.h"

class LivingRoom : public Room{
public:
	static LivingRoom * create(int);

	bool isStairs();
	void generateVariation(int);
private:
	bool hasStairs = false;
};