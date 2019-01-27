#include "GameScene.h"
#include "cocos2d.h"

USING_NS_CC;

struct {
	bool key_up = false;
	bool key_right = false;
	bool key_down = false;
	bool key_left = false;
	bool key_space = false;
	bool key_space_p = false;
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
	player->setPosition(Vec2(80 * SCALE, 56*SCALE));
	player->setScale(SCALE);

	zombie.push_back(Zombie::create(300,1));
	zombie[0]->setPosition(Vec2(1000, 61*SCALE));
	zombie[0]->setScale(SCALE);

	auto BG = Sprite::create();
	BG->initWithFile("house_b.png");
	BG->setPosition(Vec2(BG->getBoundingBox().size.width/2 * SCALE, BG->getBoundingBox().size.height/2 * SCALE));
	BG->setScale(SCALE);
	auto FG = Sprite::create();
	FG->initWithFile("house_f.png");
	FG->setPosition(Vec2(FG->getBoundingBox().size.width / 2 * SCALE, FG->getBoundingBox().size.height / 2 * SCALE));
	FG->setScale(SCALE);

	Texture2D::TexParams tp = { GL_NEAREST , GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};

	FG->getTexture()->setTexParameters(tp);
	BG->getTexture()->setTexParameters(tp);
	player->getTexture()->setTexParameters(tp);

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
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyHandler, player);


	addChild(BG);
	addChild(player);
	addChild(zombie[0]);
	addChild(FG);

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float dt)
{
	Vec2 p_spd = { 0, 0 };

	if (timer <= 0) {
		if (invuln <= 0) {
			if (GAMEPLAY_INPUT.key_right) {
				p_spd.x += Player::PLAYER_SPEED * dt;
				player->setScale(-SCALE, SCALE);
				player->setDir(false);
				if (!player->isMoving()) {
					player->setMoving(true);
					player->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(player->getAnim(1))));
				}
			}

			if (GAMEPLAY_INPUT.key_left) {
				p_spd.x -= Player::PLAYER_SPEED * dt;
				player->setScale(SCALE);
				player->setDir(true);

				if (!player->isMoving()) {
					player->setMoving(true);
					player->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(player->getAnim(1))));
				}
			}
		}
	}

	if (player->isMoving() && !GAMEPLAY_INPUT.key_left && !GAMEPLAY_INPUT.key_right) {
		player->stopAllActions();
		player->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(player->getAnim(0))));
		player->setMoving(false);
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

	if (timer > 0) {
		timer -= dt;

		if (timer < 0.2f) {
			for (unsigned int z = 0; z < zombie.size(); z++) {
				if (player->getDir()) {
					if ((player->getPosition().x - zombie[z]->getPosition().x) <= 75) {
						if ((player->getPosition().x - zombie[z]->getPosition().x) >= 0) {
							zombie[z]->setSpd(Vec2(-2.0f, 0));
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
					if ((player->getPosition().x - zombie[z]->getPosition().x) >= -75) {
						if ((player->getPosition().x - zombie[z]->getPosition().x) <= 0) {
							zombie[z]->setSpd(Vec2(2.0f, 0));
							if (zombie[z]->getDir()) {
								zombie[z]->hurt(5);
							}
							else {
								zombie[z]->hurt(1);
							}
							zombie[z]->move();
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


		if (timer <= 0) {
			player->stopAllActions();
			player->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(player->getAnim(0))));
			player->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
		}
	}
	else if (timer <= 0) {
		if (GAMEPLAY_INPUT.key_space) {
			timer = _TIME;
			player->stopAllActions();
			player->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(player->getAnim(2))));
			player->setMoving(false);
		}
	}

	if (player->getPosition().x + p_spd.x - player->getBoundingBox().size.width/2 < 70 * SCALE) {
		p_spd.x = player->getPosition().x - player->getBoundingBox().size.width / 2 - (70 * SCALE);
	}
	else if (player->getPosition().x + p_spd.x + player->getBoundingBox().size.width/2 > (600 - 87) * SCALE) {
		p_spd.x = player->getPosition().x + player->getBoundingBox().size.width/2 - ((600 - 87) * SCALE);
	}


	if (player->getPosition().x >= 158 * SCALE && player->getPosition().x + p_spd.x < 158 * SCALE) {
		p_spd.y = -5 * SCALE;
	}else if(player->getPosition().x + p_spd.x > 158 * SCALE && player->getPosition().x <= 158 * SCALE) {
		p_spd.y = 5 * SCALE;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto cam = getDefaultCamera();
	if (player->getPosition().x > visibleSize.width / 2 && player->getPosition().x < (600 * SCALE) - (visibleSize.width/2) - 100) {
		cam->setPositionX(cam->getPositionX() + p_spd.x);
	}
	else if (player->getPosition().x < visibleSize.width / 2) {
		cam->setPositionX(0);
	}
	else{
		cam->setPositionX((600 * SCALE) - visibleSize.width - 100);
	}

	if (player->getFloor() == 1) {
		cam->setPositionY(0.0f);
	}
	else {
		cam->setPositionY(50 * SCALE);
	}


	player->move(p_spd);

	for (unsigned int z = 0; z < zombie.size(); z++) {
		zombie[z]->AI(player, dt);

		zombie[z]->move();
	}
}
