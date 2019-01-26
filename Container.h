#pragma once
#include "Enums.h"
#include "cocos2d.h"
#include "Player.h"


class Container {
private:
	ContainerType type;
	int contains;
	cocos2d::Vec2 position;

	bool Locked = false;
	bool Looted = false;
	bool beingLooted = false;

	float lootingTime = 3.0f;

public:
	Container(cocos2d::Vec2 p);	   //Container Type = Auto Generated, # of contained objects = Auto generated, Vec2 Position = Required.
	~Container();

	ContainerType generateEnum();
	int generateNum();
	bool generateLocked();

	

	float getPosX();
	float getPosY();

	void looting(Player* player, float);
	void isBeingLooted(bool);
	
	bool getLooted();
	
	float getLootingTime();
};