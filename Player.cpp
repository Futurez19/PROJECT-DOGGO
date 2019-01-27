#include "Player.h"

Player * Player::create()
{
	auto ret = new (std::nothrow) Player;
	if (ret && ret->initWithFile("player_anim/stand_1.png")) {
		cocos2d::Texture2D::TexParams tp = { GL_NEAREST , GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };

		//still animation
		cocos2d::Vector<cocos2d::SpriteFrame *> stillframes;

		stillframes.pushBack(cocos2d::SpriteFrame::create("player_anim/stand_1.png", cocos2d::Rect(0,0,15,33) ));

		//walk animation
		cocos2d::Vector<cocos2d::SpriteFrame *> walkframes;
		//walkframes.pushBack(stillframes.at(0));
		walkframes.pushBack(cocos2d::SpriteFrame::create("player_anim/walk_1.png", cocos2d::Rect(0, 0, 15, 33)));
		walkframes.pushBack(cocos2d::SpriteFrame::create("player_anim/walk_2.png", cocos2d::Rect(0, 0, 15, 33)));
		walkframes.pushBack(cocos2d::SpriteFrame::create("player_anim/walk_3.png", cocos2d::Rect(0, 0, 15, 33)));
		walkframes.pushBack(cocos2d::SpriteFrame::create("player_anim/walk_4.png", cocos2d::Rect(0, 0, 15, 33)));
		walkframes.pushBack(cocos2d::SpriteFrame::create("player_anim/walk_5.png", cocos2d::Rect(0, 0, 15, 33)));
		walkframes.pushBack(cocos2d::SpriteFrame::create("player_anim/walk_6.png", cocos2d::Rect(0, 0, 15, 33)));

		for each (cocos2d::SpriteFrame* sprt in walkframes)
		{
			sprt->getTexture()->setTexParameters(tp);
		}


		ret->animations.pushBack(cocos2d::Animation::createWithSpriteFrames(stillframes, 0.5f));
		ret->animations.pushBack(cocos2d::Animation::createWithSpriteFrames(walkframes, 0.1f));

		ret->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(ret->animations.at(0))));

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

cocos2d::Animation * Player::getAnim(int id)
{
	if (id < 0 || id > animations.size()) {
		return nullptr;
	}
	else {
		return animations.at(id);
	}
}

bool Player::getDir() {
	return face_right;
}

void Player::setDir(bool dir) {
	face_right = dir;
}

void Player::addfood(int i)
{
	food += i;
}

void Player::addWater(int i)
{
	water += i;
}

void Player::addGas(int i)
{
	gas += i;
}

void Player::hurt(int dmg) {
	hp--;
}

int Player::getHp() {
	return hp;
}
void Player::setHp(int _hp) {
	hp = _hp;
}
