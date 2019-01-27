#pragma once
#include "2d/CCScene.h"
#include "2d/CCDrawNode.h"
#include"Player.h"


class ResourceScene : public cocos2d::Scene {
private:
	std::vector<cocos2d::DrawNode *> healthBar;
	int hp = 10;
	float hpBar = 388.0f;
public:
	static Scene* ResourceScene::createScene(Player* p);
	virtual bool init();
	void resourceReturnCallback(cocos2d::Ref* pSender);
	void resourceMenuCallback(cocos2d::Ref* pSender);
	int getHp();
	void setHp(int _hp);

	virtual void update(float dt) override;

	

	CREATE_FUNC(ResourceScene);
};