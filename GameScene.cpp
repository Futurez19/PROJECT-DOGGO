#include "GameScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
auto audio = SimpleAudioEngine::getInstance();

USING_NS_CC;

struct {
	bool key_up = false;
	bool key_right = false;
	bool key_down = false;
	bool key_left = false;
	bool key_space = false;
	bool key_space_p = false;
	bool key_Interact = false;
} GAMEPLAY_INPUT;

Scene* GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	

	audio->preloadEffect("Rummaging.wav");

	auto KeyHandler = EventListenerKeyboard::create();

	KitchenRoom1 = Kitchen::create(1);
	KitchenRoom1->setPosition(400, 125);
	KitchenRoom1->setScale(2.0f);
	KitchenRoom1->generateVariation(1);

	LivingRoom1 = LivingRoom::create(1);
	LivingRoom1->setPosition(200,125);
	LivingRoom1->setScale(2.0f);
	LivingRoom1->generateVariation(1);

	Bathroom1 = Bathroom::create(1);
	Bathroom1->setPosition(600, 125);
	Bathroom1->setScale(2.0f);
	Bathroom1->generateVariation(1);

	player = Player::create();
	player->setPosition(Vec2(50, 100));
	player->setScale(2.0f);
	/*
	*	Key Down Event Handler
	*
	*/
	KeyHandler->onKeyPressed = [](EventKeyboard::KeyCode key, Event * event) {
		switch (key) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			GAMEPLAY_INPUT.key_left = true;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			GAMEPLAY_INPUT.key_up = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			GAMEPLAY_INPUT.key_right = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			GAMEPLAY_INPUT.key_down = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			GAMEPLAY_INPUT.key_space = true;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			GAMEPLAY_INPUT.key_Interact = true;
			break;
		}
	};								 

	KeyHandler->onKeyReleased = [](EventKeyboard::KeyCode key, Event * event) {
		switch (key) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			GAMEPLAY_INPUT.key_left = false;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			GAMEPLAY_INPUT.key_up = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			GAMEPLAY_INPUT.key_right = false;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			GAMEPLAY_INPUT.key_down = false;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			GAMEPLAY_INPUT.key_space = false;
			GAMEPLAY_INPUT.key_space_p = false;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			GAMEPLAY_INPUT.key_Interact = false;
			audio->stopEffect(audio->playEffect("Rummaging.wav", false, 1.0f, 1.0f, 1.0f));
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyHandler, player);


	

	addChild(LivingRoom1);
	addChild(KitchenRoom1);
	addChild(Bathroom1);
	addChild(player);

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float dt)
{
	

	Vec2 p_spd = { 0, 0 };

	if (GAMEPLAY_INPUT.key_right) {
		p_spd.x += Player::PLAYER_SPEED * dt;
	}

	if (GAMEPLAY_INPUT.key_left) {
		p_spd.x -= Player::PLAYER_SPEED * dt;
	}

	
	if (GAMEPLAY_INPUT.key_Interact && (LivingRoom1->totalContainers[0]->getPosX() - player->getPositionX() >= 0 && LivingRoom1->totalContainers[0]->getPosX() - player->getPositionX() >= 10) && LivingRoom1->totalContainers[0]->getLooted() == false) {
		if(!(LivingRoom1->totalContainers[0]->getBeingLooted())){ audio->playEffect("Rummaging.wav", false, 1.0f, 1.0f, 1.0f); }
		LivingRoom1->totalContainers[0]->isBeingLooted(true);
		LivingRoom1->totalContainers[0]->looting(player, dt);
		
	}
	else {
		LivingRoom1->totalContainers[0]->isBeingLooted(false);
	}


	player->move(p_spd);
}
