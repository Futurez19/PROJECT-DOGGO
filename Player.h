#pragma once
#include"cocos2d.h"

class Player : public cocos2d::Sprite {
private:
	bool face_right = true;
	bool is_moving = false;
	cocos2d::Vector<cocos2d::Animation *> animations;

	//Survival Parameters
	float hunger = 100;
	float thirst = 100;

	//Resources
	int food = 0;
	int	water = 0;
	int	gas = 0;
	int hp = 10;
public:
	static const int PLAYER_SPEED = 60;

	static Player * create();
	void move(cocos2d::Vec2 spd);

	bool isMoving() {
		return is_moving;
	}
	void setMoving(bool b) {
		is_moving = b;
	}

	cocos2d::Animation * getAnim(int id);

	bool getDir();
	void setDir(bool dir);

	void addfood(int);
	void addWater(int);
	void addGas(int);
	void hurt(int dmg);
	int getHp();
	void setHp(int _hp);
};

