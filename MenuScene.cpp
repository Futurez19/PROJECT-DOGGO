#include "MenuScene.h"
#include "cocos2d.h"

USING_NS_CC;

static void problemLoading(const char* filename);

Scene* MenuScene::createScene() {
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto KeyHandler = EventListenerKeyboard::create();

	auto BG = Sprite::create();
	BG->initWithFile("Menu.png");
	BG->setPosition(Vec2(500, 300));
	
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	addChild(BG);

	return true;
}

void MenuScene::update(float dt)
{
		//Vec2 p_spd = { 0, 0 };
		//
		//if (GAMEPLAY_INPUT.key_right) {
		//	p_spd.x += Player::PLAYER_SPEED * dt;
		//	player->setScale(-2, 2);
		//	player->setDir(false);
		//}
	
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}