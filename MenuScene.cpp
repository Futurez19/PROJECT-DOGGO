#include "MenuScene.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "Instructions.h"
#include "Highscores.h"

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
	
	auto playGame = MenuItemImage::create(
		"PLAY_Unselect.PNG",
		"PLAY_Select.PNG",
		CC_CALLBACK_1(MenuScene::menuPlayCallback, this));

	if (playGame == nullptr ||
		playGame->getContentSize().width <= 0 ||
		playGame->getContentSize().height <= 0)
	{
		problemLoading(" 'PLAY Unselected.png' and the other one");
	}
	else
	{
		float x = 100 + playGame->getContentSize().width / 2;//origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = 520 - playGame->getContentSize().height / 2;//origin.y + closeItem->getContentSize().height / 2;
		playGame->setPosition(Vec2(x, y));
	}

	auto quitGame = MenuItemImage::create(
		"Quit_Unselect.PNG",
		"Quit_Select.PNG",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	if (quitGame == nullptr ||
		quitGame->getContentSize().width <= 0 ||
		quitGame->getContentSize().height <= 0)
	{
		problemLoading(" 'Quit Unselected.png' and the other one");
	}
	else
	{
		float x = 740 + quitGame->getContentSize().width / 2;//origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = 153 - quitGame->getContentSize().height / 2;//origin.y + closeItem->getContentSize().height / 2;
		quitGame->setPosition(Vec2(x, y));
	}

	auto instructions = MenuItemImage::create(
		"Instructions_Unselect.PNG",
		"Instructions_Select.PNG",
		CC_CALLBACK_1(MenuScene::menuInstructCallback, this));

	if (instructions == nullptr ||
		instructions->getContentSize().width <= 0 ||
		instructions->getContentSize().height <= 0)
	{
		problemLoading(" 'Instructions Unselected.png' and the other one");
	}
	else
	{
		float x = 710 + instructions->getContentSize().width / 2;//origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = 486 - instructions->getContentSize().height / 2;//origin.y + closeItem->getContentSize().height / 2;
		instructions->setPosition(Vec2(x, y));
	}


	// create menu, it's an autorelease object
	auto menu = Menu::create(playGame, quitGame, instructions, NULL);
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

void MenuScene::menuPlayCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(GameScene::create());
}

void MenuScene::menuInstructCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(InstructScene::create());
}

void MenuScene::menuScoreCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(ScoreScene::create());
}