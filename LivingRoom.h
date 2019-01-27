#pragma once
#include"Container.h"
#include"cocos2d.h"

class LivingRoom : public cocos2d::Sprite{
public:
	static LivingRoom * create(int);
	int variation;
	std::vector<Container*> totalContainers;


	void generateVariation(int);
private:
	
};