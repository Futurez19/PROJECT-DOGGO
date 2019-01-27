#pragma once
#include "2d/CCScene.h"
#include "Player.h"
#include "Zombie.h"

class GameScene : public cocos2d::Scene {
private:
	Player * player;
	std::vector<Zombie *> zombie;
	int hp = 10;
	const float _TIME = 1;
	const float i_TIME = 0.5;
	const float t_TIME = 60;
	float timer = 0; //_TIME
	float invuln = 0; //i_TIME
	float total = t_TIME;
public:
	static Scene* GameScene::createScene();
	virtual bool init();
	void gameResourceCallback(cocos2d::Ref* pSender);
	void gameHighscoreCallback(cocos2d::Ref* pSender);
	void GameScene::clearBtns();

	void update(float dt) override;

	CREATE_FUNC(GameScene);
};