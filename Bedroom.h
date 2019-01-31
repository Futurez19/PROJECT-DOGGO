#pragma once
#include"Container.h"
#include"cocos2d.h"
#include"Room.h"

class Bedroom : public Room {
public:
	static Bedroom * create(int);

	bool isStairs();
	void generateVariation(int);
private:
	bool hasStairs = false;
};