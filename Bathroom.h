#pragma once
#include"Container.h"
#include"cocos2d.h"
#include"Room.h"

class Bathroom : public Room{
public:
	static Bathroom * create(int);
	bool isStairs();
	void generateVariation(int);
private:
	bool hasStairs = false;
};