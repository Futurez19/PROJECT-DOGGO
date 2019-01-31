#pragma once
#include "Enums.h"
#include "cocos2d.h"
#include "Player.h"


class Container {
private:
	ContainerType type;
	int contains;
	cocos2d::Vec2 position;

	bool Looted = false;
	bool beingLooted = false;

	
	cocos2d::Sprite * prompt = cocos2d::Sprite::create("E-Prompt.png");

public:
	Container(cocos2d::Vec2 p);	   //Container Type = Auto Generated, # of contained objects = Auto generated, Vec2 Position = Required.
	~Container();

	ContainerType generateEnum();
	int generateNum();
	

	

	float getPosX();
	float getPosY();

	void looting(Player* player);
	void isBeingLooted(bool);
	bool getBeingLooted();
	
	bool getLooted();
	

	cocos2d::Sprite* getPrompt() { return prompt; }
};