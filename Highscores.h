#pragma once
#include "2d/CCScene.h"


class ScoreScene : public cocos2d::Scene {
private:
public:
	static Scene* ScoreScene::createScene();
	virtual bool init();
	void scoreReturnCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(ScoreScene);
};