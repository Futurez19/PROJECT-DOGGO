#include "Highscores.h"
#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

static void problemLoading(const char* filename);

Scene* ScoreScene::createScene() {
	return ScoreScene::create();
}

bool ScoreScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto KeyHandler = EventListenerKeyboard::create();

	cocos2d::Texture2D::TexParams tp = { GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };

	auto BG = Sprite::create();
	BG->initWithFile("Game Over.png");
	BG->setPosition(Vec2(500, 300));
	BG->setScale(10);
	BG->getTexture()->setTexParameters(tp);

	auto highscores = MenuItemImage::create(
		"Exit_unclicked.PNG",
		"Exit_clicked.PNG",
		CC_CALLBACK_1(ScoreScene::scoreReturnCallback, this));

	if (highscores == nullptr ||
		highscores->getContentSize().width <= 0 ||
		highscores->getContentSize().height <= 0)
	{
		problemLoading(" 'Highscores Unselected.png' and the other one");
	}
	else
	{
		float x = 925 + highscores->getContentSize().width / 2;//origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = 575 - highscores->getContentSize().height / 2;//origin.y + closeItem->getContentSize().height / 2;
		highscores->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(highscores, NULL);
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

void ScoreScene::scoreReturnCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(MenuScene::create());
}