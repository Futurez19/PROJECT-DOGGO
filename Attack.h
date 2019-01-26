#pragma once
#include"cocos2d.h"

class Attack : public cocos2d::Sprite {
private:
	bool atk = false;
public:
	Attack(bool a_atk);

	bool getAtk();
	void setAtk(bool a_atk);
};
