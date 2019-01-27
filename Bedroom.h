#pragma once
#include"Container.h"
#include"cocos2d.h"

class Bedroom : public cocos2d::Sprite {
public:
	static Bedroom * create(int);
	int variation;
	std::vector<Container*> totalContainers;


	void generateVariation(int);
private:

};