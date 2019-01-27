#pragma once
#include "2d/CCScene.h"


class MenuScene : public cocos2d::Scene {
private:
public:
	static Scene* MenuScene::createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuInstructCallback(cocos2d::Ref* pSender);

	void menuScoreCallback(cocos2d::Ref* pSender);

	void menuPlayCallback(Ref * pSender);

	void update(float dt) override;

	CREATE_FUNC(MenuScene);
};