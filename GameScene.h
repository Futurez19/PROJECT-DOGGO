#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Container.h"
#include "Kitchen.h"
#include "Bedroom.h"
#include "Stairway.h"
#include "LivingRoom.h"
#include "Bathroom.h"
#include <ctime>



class GameScene : public cocos2d::Scene {
private:
	Player * player;

	Room* rooms[3][2];

	Kitchen * testKitchen;

	cocos2d::Vec2 position1 = cocos2d::Vec2(200, 135);
	cocos2d::Vec2 position2 = cocos2d::Vec2(400, 135);
	cocos2d::Vec2 position3 = cocos2d::Vec2(600, 135);
	cocos2d::Vec2 position4 = cocos2d::Vec2(200, 235);
	cocos2d::Vec2 position5 = cocos2d::Vec2(400, 235);
	cocos2d::Vec2 position6 = cocos2d::Vec2(600, 235);
	
public:
	static Scene* GameScene::createScene();
	cocos2d::Vec2 generateLocation(int,int);
	virtual bool init();
	void RNG(int,int);

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};