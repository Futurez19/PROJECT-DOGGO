#include "GameScene.h"
#include "cocos2d.h"
#include "Resources.h"

USING_NS_CC;

struct {
	bool key_up = false;
	bool key_right = false;
	bool key_down = false;
	bool key_left = false;
	bool key_space = false;
	bool key_space_p = false;
	bool key_escape = false;
} GAMEPLAY_INPUT;


Scene* GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto KeyHandler = EventListenerKeyboard::create();

	player = Player::create();
	player->setPosition(Vec2(50, 100));
	player->setScale(2.0f);

	zombie.push_back(Zombie::create(300,1));
	zombie[0]->setPosition(Vec2(300, 100));
	zombie[0]->setScale(2.0f);

	auto BG = Sprite::create();
	BG->initWithFile("ground.png");
	BG->setPosition(Vec2(550, -30));
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
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			GAMEPLAY_INPUT.key_escape = true;
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
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			GAMEPLAY_INPUT.key_escape = false;
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyHandler, player);


	addChild(player);
	addChild(BG);
	addChild(zombie[0]);

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float dt)
{
	Vec2 p_spd = { 0, 0 };

	if (GAMEPLAY_INPUT.key_escape) {
		GameScene::clearBtns();
		GameScene::gameResourceCallback(player);
	}

	if (timer <= 0) {
		if (invuln <= 0) {
			if (GAMEPLAY_INPUT.key_right) {
				p_spd.x += Player::PLAYER_SPEED * dt;
				player->setScale(-2, 2);
				player->setDir(false);
			}

			if (GAMEPLAY_INPUT.key_left) {
				p_spd.x -= Player::PLAYER_SPEED * dt;
				player->setScale(2);
				player->setDir(true);
			}
		}
	}

	if (invuln >= 0) {
		invuln -= dt;
	}
	else if (invuln <= 0) {
			for (unsigned int z = 0; z < zombie.size(); z++) {
				if ((player->getPosition().x - zombie[z]->getPosition().x) <= 0) {
					if ((player->getPosition().x - zombie[z]->getPosition().x) >= -25) {
						p_spd.x = Player::PLAYER_SPEED * -0.2f;
						player->hurt(1);
						player->move(p_spd);
						invuln = i_TIME;
					}
				}
				else if ((player->getPosition().x - zombie[z]->getPosition().x) >= 0) {
					if ((player->getPosition().x - zombie[z]->getPosition().x) >= 25) {
						p_spd.x = Player::PLAYER_SPEED * 0.2f;
						player->hurt(1);
						player->move(p_spd);
						invuln = i_TIME;
					}
			}
		}
	}

	if (timer >= 0) {
		timer -= dt;
	}
	else if (timer <= 0) {
		if (GAMEPLAY_INPUT.key_space) {
			timer = _TIME;
			for (unsigned int z = 0; z < zombie.size(); z++) {
				if (player->getDir()) {
					if ((player->getPosition().x - zombie[z]->getPosition().x) <= 50) {
						if ((player->getPosition().x - zombie[z]->getPosition().x) >= 0) {
							zombie[z]->setSpd(Vec2(-1.0f, 0));
							if (!zombie[z]->getDir()) {
								zombie[z]->hurt(5);
							}
							else {
								zombie[z]->hurt(1);
							}
							zombie[z]->move();
						}
					}
				}
				else if (!player->getDir()) {
					if ((player->getPosition().x - zombie[z]->getPosition().x) >= -50) {
						if ((player->getPosition().x - zombie[z]->getPosition().x) <= 0) {
							zombie[z]->setSpd(Vec2(1.0f, 0));
							if (zombie[z]->getDir()) {
								zombie[z]->hurt(5);
							}
							else {
								zombie[z]->hurt(1);
							}
							zombie[z]->move();
							timer = _TIME;
							if (zombie[z]->getHp() <= 0) {
								removeChild(zombie[z]);
								zombie[z]->release();
								auto it = zombie.begin();
								zombie.erase(it + z);
							}
						}
					}
				}
			}
		}
	}

	player->move(p_spd);

	for (unsigned int z = 0; z < zombie.size(); z++) {
		zombie[z]->AI(player, dt);
		zombie[z]->move();
	}
}

void GameScene::gameResourceCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(ResourceScene::createScene(player));
}

void GameScene::clearBtns() {
	GAMEPLAY_INPUT.key_up = false;
	GAMEPLAY_INPUT.key_right = false;
	GAMEPLAY_INPUT.key_down = false;
	GAMEPLAY_INPUT.key_left = false;
	GAMEPLAY_INPUT.key_space = false;
	GAMEPLAY_INPUT.key_space_p = false;
	GAMEPLAY_INPUT.key_escape = false;
}
