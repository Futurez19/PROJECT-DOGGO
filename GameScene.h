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



#include "Zombie.h"

class GameScene : public cocos2d::Scene {
private:
	Player * player;
	std::vector<Zombie *> zombie;
	const float _TIME = 1;
	float timer = _TIME;

	float lootingTime = 3.0f;

	const float SCALE = 3.0;

	Room* rooms[3][2];

	cocos2d::Vec2 position1 = cocos2d::Vec2(200, 185);
	cocos2d::Vec2 position2 = cocos2d::Vec2(510, 185);
	cocos2d::Vec2 position3 = cocos2d::Vec2(810, 185);
	cocos2d::Vec2 position4 = cocos2d::Vec2(210, 485);
	cocos2d::Vec2 position5 = cocos2d::Vec2(510, 485);
	cocos2d::Vec2 position6 = cocos2d::Vec2(810, 485);
	
public:
	static Scene* GameScene::createScene();
	cocos2d::Vec2 generateLocation(int,int);
	virtual bool init();
	void RNG(int,int);

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};