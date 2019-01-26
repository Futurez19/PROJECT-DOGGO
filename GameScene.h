#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Container.h"
#include "Room.h"



class GameScene : public cocos2d::Scene {
private:
	Player * player;
	
	Container container = (cocos2d::Vec2(150, 100));
	
public:
	static Scene* GameScene::createScene();
	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};