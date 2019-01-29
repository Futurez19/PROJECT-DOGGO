#pragma once
#include"cocos2d.h"

class Player : public cocos2d::Sprite {
private:
	bool face_right = true;
	bool is_moving = false;
	cocos2d::Vector<cocos2d::Animation *> animations;
	int floor = 1;
	int hp = 10;
public:
	static const int PLAYER_SPEED = 100;

	static Player * create();
	void move(cocos2d::Vec2 spd);

	bool isMoving() {
		return is_moving;
	}
	void setMoving(bool b) {
		is_moving = b;
	}

	void setFloor(int i) {
		floor = i;
		if (i == 1) {
			setPositionY(114 * 4);
		}
		else {
			setPositionY(46 * 4);
		}
	}

	int getFloor() {
		return floor;
	}

	cocos2d::Animation * getAnim(int id);

	bool getDir();
	void setDir(bool dir);
	void hurt(int dmg);
	int getHp();
	void setHp(int _hp);

};

