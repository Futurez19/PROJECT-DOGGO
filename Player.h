#pragma once
#include"cocos2d.h"

class Player : public cocos2d::Sprite {
private:
	bool face_right = true;

	//Survival Parameters
	float hunger = 100;
	float thirst = 100;

	//Resources
	int food = 0;
	int	water = 0;
	int	gas = 0;
public:
	static const int PLAYER_SPEED = 60;

	static Player * create();
	void move(cocos2d::Vec2 spd);

	void addfood(int);
	void addWater(int);
	void addGas(int);
};