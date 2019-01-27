#include "Zombie.h"

Zombie * Zombie::create(int x, int floor)
{
	auto ret = new (std::nothrow) Zombie;
	if (ret && ret->initWithFile("player_anim/stand_1.png")) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void Zombie::AI(Player* player, float dt) {
	z_spd = { 0, 0 };
	bool atk = false;

	if (player->getPosition().x >= this->getPosition().x) {
		if (getDir()) {
			if ((player->getPosition().x - this->getPosition().x) <= 200) {
				z_spd.x = Zombie::ZOMBIE_SPEED * dt;
				atk = true;
			}
		}
		else if (!getDir()) {
			if ((player->getPosition().x - this->getPosition().x) <= 40) {
				z_spd.x = Zombie::ZOMBIE_SPEED * dt;
				setScale(SCALE);
				atk = true;
			}
		}
	}
	else if (player->getPosition().x <= this->getPosition().x) {
		if (!getDir()) {
			if ((this->getPosition().x - player->getPosition().x) <= 200) {
				z_spd.x = -Zombie::ZOMBIE_SPEED * dt;
				atk = true;
			}
		}
		else if (getDir()) {
			if ((this->getPosition().x - player->getPosition().x) <= 40) {
				z_spd.x = -Zombie::ZOMBIE_SPEED * dt;
				setScale(-SCALE, SCALE);
				atk = true;
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
					setScale(-SCALE, SCALE);
					timer = TURNT_TIME;
				}
				else if (!getDir()) {
					setDir(true);
					setScale(SCALE);
					timer = TURNT_TIME;
				}
			}
		}
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