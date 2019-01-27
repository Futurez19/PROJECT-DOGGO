#pragma once
#include"Container.h"
#include"cocos2d.h"

class Bathroom : public cocos2d::Sprite{
public:
	static Bathroom * create(int);
	int variation;
	std::vector<Container*> totalContainers;


	void generateVariation(int);
private:

};