#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Container.h"
#include "Kitchen.h"
#include "Bedroom.h"
#include "Hallway.h"
#include "LivingRoom.h"



class GameScene : public cocos2d::Scene {
private:
	Player * player;
	
	LivingRoom * LivingRoom1;
	Kitchen * KitchenRoom1;
	Bathroom * Bathroom1;
	
public:
	static Scene* GameScene::createScene();
	virtual bool init();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};