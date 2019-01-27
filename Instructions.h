#pragma once
#include "2d/CCScene.h"


class InstructScene : public cocos2d::Scene {
private:
public:
	static Scene* InstructScene::createScene();
	virtual bool init();
	void instructReturnCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(InstructScene);
};
