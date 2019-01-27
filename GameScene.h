#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Zombie.h"

class GameScene : public cocos2d::Scene {
private:
	Player * player;
	std::vector<Zombie *> zombie;
	const float _TIME = 0.8;
	const float i_TIME = 0.5;
	float timer = 0;

	const float SCALE = 4.0;
	float invuln = i_TIME;
public:
	static Scene* GameScene::createScene();
	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};