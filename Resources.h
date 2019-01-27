#pragma once
#include "2d/CCScene.h"


class ResourceScene : public cocos2d::Scene {
private:
public:
	static Scene* ResourceScene::createScene();
	virtual bool init();
	void resourceReturnCallback(cocos2d::Ref* pSender);
	void resourceMenuCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(ResourceScene);
};