#pragma once
#include"cocos2d.h"

class Player : public cocos2d::Sprite {
private:
	bool face_right = true;
	cocos2d::Vector<cocos2d::Animation *> animations;
public:
	static const int PLAYER_SPEED = 60;

	static Player * create();
	void move(cocos2d::Vec2 spd);

};