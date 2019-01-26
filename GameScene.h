#pragma once
#include "2d/CCScene.h"
#include "Player.h"
class GameScene : public cocos2d::Scene {
private:
	Player * player;
public:
	static Scene* GameScene::createScene();
	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};