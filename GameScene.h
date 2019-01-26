#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Zombie.h"
class GameScene : public cocos2d::Scene {
private:
	Player * player;
	Zombie * zombie;
public:
	static Scene* GameScene::createScene();
	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};