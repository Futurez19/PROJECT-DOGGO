#pragma once
#include"Container.h"
#include"cocos2d.h"

class Hallway : public cocos2d::Sprite {
public:
	static Hallway * create(int);
	int variation;
	std::vector<Container*> totalContainers;


	void generateVariation(int);
private:

};