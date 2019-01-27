#include "Resources.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "MenuScene.h"

USING_NS_CC;

static void problemLoading(const char* filename);

Scene* ResourceScene::createScene() {
	return ResourceScene::create();
}

bool ResourceScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto KeyHandler = EventListenerKeyboard::create();

	auto BG = Sprite::create();
	BG->initWithFile("RMenu.png");
	BG->setPosition(Vec2(500, 300));

	auto scavenge = MenuItemImage::create(
		"scavenge_unclick.png",
		"scavenge_click.png",
		CC_CALLBACK_1(ResourceScene::resourceReturnCallback, this));

	if (scavenge == nullptr ||
		scavenge->getContentSize().width <= 0 ||
		scavenge->getContentSize().height <= 0)
	{
		problemLoading(" 'Highscores Unselected.png' and the other one");
	}
	else
	{
		float x = 595 + scavenge->getContentSize().width / 2;//origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = 456 - scavenge->getContentSize().height / 2;//origin.y + closeItem->getContentSize().height / 2;
		scavenge->setPosition(Vec2(x, y));
	}

	auto exitMenu = MenuItemImage::create(
		"Exit_unclicked.png",
		"Exit_clicked.png",
		CC_CALLBACK_1(ResourceScene::resourceMenuCallback, this));

	if (exitMenu == nullptr ||
		exitMenu->getContentSize().width <= 0 ||
		exitMenu->getContentSize().height <= 0)
	{
		problemLoading(" 'Highscores Unselected.png' and the other one");
	}
	else
	{
		float x = 916 + exitMenu->getContentSize().width / 2;//origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = 78 - exitMenu->getContentSize().height / 2;//origin.y + closeItem->getContentSize().height / 2;
		exitMenu->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(exitMenu, scavenge, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	addChild(BG);

	return true;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void ResourceScene::resourceReturnCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(GameScene::create());
}

void ResourceScene::resourceMenuCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(MenuScene::create());
}