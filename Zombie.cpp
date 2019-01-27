#include "Zombie.h"

Zombie * Zombie::create(int x, int floor)
{
	cocos2d::Texture2D::TexParams tp = { GL_NEAREST , GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };

	auto ret = new (std::nothrow) Zombie;
	if (ret && ret->initWithFile("player_anim/stand_1.png")) {
		cocos2d::Vector<cocos2d::SpriteFrame *> stillFrame;
		stillFrame.pushBack(cocos2d::SpriteFrame::create("zombie.png", cocos2d::Rect(0, 0, 15, 33)));
		stillFrame.at(0)->getTexture()->setTexParameters(tp);

		cocos2d::Vector<cocos2d::SpriteFrame *> walkFrame;
		walkFrame.pushBack(cocos2d::SpriteFrame::create("zombie_anim/zombie_1.png", cocos2d::Rect(0, 0, 15, 33)));
		walkFrame.pushBack(cocos2d::SpriteFrame::create("zombie_anim/zombie_2.png", cocos2d::Rect(0, 0, 15, 33)));
		walkFrame.pushBack(cocos2d::SpriteFrame::create("zombie_anim/zombie_3.png", cocos2d::Rect(0, 0, 15, 33)));
		walkFrame.pushBack(cocos2d::SpriteFrame::create("zombie_anim/zombie_4.png", cocos2d::Rect(0, 0, 15, 33)));
		walkFrame.pushBack(cocos2d::SpriteFrame::create("zombie_anim/zombie_5.png", cocos2d::Rect(0, 0, 15, 33)));
		walkFrame.pushBack(cocos2d::SpriteFrame::create("zombie_anim/zombie_6.png", cocos2d::Rect(0, 0, 15, 33)));
		walkFrame.pushBack(cocos2d::SpriteFrame::create("zombie_anim/zombie_7.png", cocos2d::Rect(0, 0, 15, 33)));

		for each(cocos2d::SpriteFrame* sprt in walkFrame) {
			sprt->getTexture()->setTexParameters(tp);
		}

		ret->animations.pushBack(cocos2d::Animation::createWithSpriteFrames(stillFrame, 0.1f));
		ret->animations.pushBack(cocos2d::Animation::createWithSpriteFrames(walkFrame, 0.1f));
		ret->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(ret->animations.at(0))));

		ret->autorelease();
		return ret;
	}

	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void Zombie::AI(Player* player, float dt) {
	z_spd = { 0, 0 };
	//bool atk = false;

	if (player->getPosition().x >= this->getPosition().x) {
		if (getDir()) {
			if ((player->getPosition().x - this->getPosition().x) <= 200) {
				z_spd.x = Zombie::ZOMBIE_SPEED * dt;
				setScale(SCALE, SCALE);
				if (!atk) {
					atk = true;
					stopAllActions();
					runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(1))));
				}
			}
			else {
				atk = false;
				stopAllActions();
				runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(0))));
			}
		}
		else if (!getDir()) {
			if ((player->getPosition().x - this->getPosition().x) <= 40) {
				z_spd.x = Zombie::ZOMBIE_SPEED * dt;
				setScale(-SCALE, SCALE);
				if (!atk) {
					atk = true;
					stopAllActions();
					runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(1))));
				}
			}
			else {
				atk = false;
				stopAllActions();
				runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(0))));
			}
		}
	}
	else if (player->getPosition().x <= this->getPosition().x) {
		if (!getDir()) {
			if ((this->getPosition().x - player->getPosition().x) <= 200) {
				z_spd.x = -Zombie::ZOMBIE_SPEED * dt;
				if (!atk) {
					atk = true;
					stopAllActions();
					runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(1))));
				}
			}
			else {
				atk = false;
				stopAllActions();
				runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(0))));
			}
		}
		else if (getDir()) {
			if ((this->getPosition().x - player->getPosition().x) <= 40) {
				z_spd.x = -Zombie::ZOMBIE_SPEED * dt;
				setScale(SCALE);
				if (!atk) {
					atk = true;
					stopAllActions();
					runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(1))));
				}
			}
			else {
				atk = false;
				stopAllActions();
				runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animations.at(0))));
			}
		}
	}

	if (timer >= 0) {
		timer -= dt;
	}
	if (timer <= 0)
	{
		if (atk == false)
		{
			std::random_device gen;
			std::uniform_int_distribution<> range(1, 40);
			turn = range(gen);
			if (turn == 1) {
				if (getDir()) {
					setDir(false);
					setScale(SCALE);
					timer = TURNT_TIME;
				}
				else if (!getDir()) {
					setDir(true);
					setScale(-SCALE, SCALE);
					timer = TURNT_TIME;
				}
			}
		}
	}

	if (getPosition().x + getSpd().x < 220 * SCALE) {
		z_spd.x = 0;
	}
}

bool Zombie::getDir() {
	return face_right;
}

void Zombie::setDir(bool dir) {
	face_right = dir;
}

void Zombie::setSpd(cocos2d::Vec2 spd) {
	z_spd.x = Zombie::ZOMBIE_SPEED * spd.x;
}

cocos2d::Vec2 Zombie::getSpd() {
	return z_spd;
}

void Zombie::hurt(int dmg) {
	hp -= dmg;
}

int Zombie::getHp() {
	return hp;
}

void Zombie::hit(int dmg) {

}

void Zombie::move()
{
	setPosition(getPosition() + getSpd());
}