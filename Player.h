#pragma once
#include"cocos2d.h"

class Player : public cocos2d::Sprite {
private:
	bool face_right = false;
	int hp = 10;
public:
	static const int PLAYER_SPEED = 60;

	static Player * create();
	void move(cocos2d::Vec2 spd);
	bool getDir();
	void setDir(bool dir);
	void hurt(int dmg);

};

