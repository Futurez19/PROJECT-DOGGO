#include "Player.h"

Player * Player::create()
{
	auto ret = new (std::nothrow) Player;
	if (ret && ret->initWithFile("player.png")) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void Player::move(cocos2d::Vec2 spd)
{
	setPosition(getPosition() + spd);
}

bool Player::getDir() {
	return face_right;
}

void Player::setDir(bool dir) {
	face_right = dir;
}