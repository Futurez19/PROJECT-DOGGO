#pragma once
#include"cocos2d.h"
#include "Player.h"

class Zombie : public cocos2d::Sprite {
private:
	bool face_right = true;
	int turn;
	cocos2d::Vec2 z_spd = { 0, 0 };
	const float TURNT_TIME =3;
	float timer = TURNT_TIME;
	int hp = 5;
	const float SCALE = 3.0;
public:
	//Zombie(int x, int floor);

	static const int ZOMBIE_SPEED = 10;

	static Zombie * create(int x, int floor);
	void AI(Player* player, float dt);
	bool getDir();
	void setDir(bool dir);
	cocos2d::Vec2 getSpd();
	void setSpd(cocos2d::Vec2 spd);
	void hurt(int dmg);
	void move();
};