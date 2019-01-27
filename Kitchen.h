#pragma once
#include"Container.h"
#include"cocos2d.h"

class Kitchen : public cocos2d::Sprite {
public:
	static Kitchen * create(int);
	int variation;
	std::vector<Container*> totalContainers;


	void generateVariation(int);
private:

};