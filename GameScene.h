#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Zombie.h"

class GameScene : public cocos2d::Scene {
private:
	Player * player;
	std::vector<Zombie *> zombie;
	const float _TIME = 1;
	const float i_TIME = 0.5;
	float timer = _TIME;
	float invuln = i_TIME;
public:
	static Scene* GameScene::createScene();
	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};