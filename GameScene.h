#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Zombie.h"

class GameScene : public cocos2d::Scene {
private:
	Player * player;
	std::vector<Zombie *> zombie;
	const float _TIME = 1;
	float timer = _TIME;
	float invuln = _TIME;
public:
	static Scene* GameScene::createScene();
	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};