#include "GameScene.h"
#include "cocos2d.h"
#include "Resources.h"
#include "Highscores.h"
#include "SimpleAudioEngine.h"
#include<random>


using namespace CocosDenshion;
auto audio = SimpleAudioEngine::getInstance();

float LTIME = 3.0f;

USING_NS_CC;

struct {
	bool key_up = false;
	bool key_right = false;
	bool key_down = false;
	bool key_left = false;
	bool key_space = false;
	bool key_space_p = false;
	bool key_escape = false;
	bool key_Interact = false;
} GAMEPLAY_INPUT;


Scene* GameScene::createScene() {
	return GameScene::create();
}

cocos2d::Vec2 GameScene::generateLocation(int i,int q) {
	
	if (i == 0 && q == 0) {
		return position1;
	}

	if (i == 1 && q == 0) {
		return position2;
	}

	if (i == 2 && q == 0) {
		return position3;
	}

	if (i == 0 && q == 1) {
		return position4;
	}

	if (i == 1 && q == 1) {
		return position5;
	}

	if (i == 2 && q == 1) {
		return position6;
	}
	else
		return position1;

	
	
}

void GameScene::RNG(int i, int q)
{
	std::random_device gen;
	std::uniform_int_distribution<> range(1, 5);
	std::uniform_int_distribution<> range2(1, 3);

	int roomType = 1;//(range(gen));

	int var = (range2(gen));



	switch (roomType) {
	case 1:	// Kitchen
		
		rooms[i][q] = Kitchen::create(var);
		rooms[i][q]->setPosition(generateLocation(i,q));
		rooms[i][q]->setScale(SCALE);
		//rooms[i][q]->generateVariation(var);
		break;

	case 2:	//Living Room
		rooms[i][q] = LivingRoom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(SCALE);
		//rooms[i][q]->generateVariation(var);
		break;

	case 3:	//Bathroom
		rooms[i][q] = Bathroom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(SCALE);
		//rooms[i][q]->generateVariation(var);
		break;
		
	case 4:	//Bedroom
		rooms[i][q] = Bedroom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(SCALE);
		//rooms[i][q]->generateVariation(var);
		break;
	case 5:	//Stairs
		//for (int w = 0; w < 3; w++) {
			//for (int a = 0; a < 2; a++) {
				if (q == 1) {	//Only one set of stairs	 !(rooms[w][a]->isStairs()) && 
					RNG(i,q);
				}
				if ((i == 1 && q == 0) && (rooms[i-1][q]->isStairs()) || q == 1) {
					RNG(i, q);
				}
				if ((i == 2 && q == 0) && (rooms[i - 1][q]->isStairs()) || q == 1) {
					RNG(i, q);
				}
				else {
					rooms[i][q] = Stairway::create(var);
					rooms[i][q]->setPosition(generateLocation(i,q));
					rooms[i][q]->setScale(SCALE);
					//rooms[i][q]->generateVariation(var);
					break;
					
				}
			//}
		//}

		
	}
}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	/////// PRE LOADING AUDIO

	audio->preloadEffect("SearchSound.wav");

	/////// PRE LOADING AUDIO

	auto KeyHandler = EventListenerKeyboard::create();

	///////////////////////////////////////////////////////////////// IMPORTANT
	//for (int i = 0; i < 3; i++) {	 // Room Generator
	//	for (int q = 0; q < 2; q++) {
	//		RNG(i, q);
	//	}
	// }

	for (int i = 0; i < 3; i++) {
		for (int q = 0; q < 2; q++) {
			RNG(i, q);
		}
	}

	//testKitchen = Kitchen::create(1);
	//testKitchen->setPosition(generateLocation(0, 0));
	//testKitchen->setScale(3.0f);
	//testKitchen->generateVariation(1);

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
		case EventKeyboard::KeyCode::KEY_E:
			GAMEPLAY_INPUT.key_Interact = true;
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
		case EventKeyboard::KeyCode::KEY_E:
			GAMEPLAY_INPUT.key_Interact = false;
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyHandler, player);

	auto dog = cocos2d::Sprite::create();
	dog->initWithFile("dog_1.png");
	dog->setScale(-SCALE, SCALE);
	dog->setPosition(80 * SCALE, 49 * SCALE);

	cocos2d::Vector<cocos2d::SpriteFrame*> dog_frames;
	dog_frames.pushBack(cocos2d::SpriteFrame::create("dog_1.png", cocos2d::Rect(0, 0, 18, 18)));
	dog_frames.pushBack(cocos2d::SpriteFrame::create("dog_2.png", cocos2d::Rect(0, 0, 18, 18)));
	dog_frames.pushBack(cocos2d::SpriteFrame::create("dog_3.png", cocos2d::Rect(0, 0, 18, 18)));
	dog_frames.pushBack(cocos2d::SpriteFrame::create("dog_2.png", cocos2d::Rect(0, 0, 18, 18)));

	dog->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(dog_frames, 0.1f))));

	for each (cocos2d::SpriteFrame* sprt in dog_frames)
	{
		sprt->getTexture()->setTexParameters(tp);
	}

	cocos2d::Vector<cocos2d::SpriteFrame*> clock_frames;

	for (int i = 1; i <= 24; i++) {
		String * file_name = String::createWithFormat("clock/clock_%i.png", i);
		//file_name.append(i);
		//file_name.append(".png");

		clock_frames.pushBack(cocos2d::SpriteFrame::create(file_name->getCString(), cocos2d::Rect(0,0, 18,18)) );
		clock_frames.at(i - 1)->getTexture()->setTexParameters(tp);
	}

	clock = cocos2d::Sprite::createWithSpriteFrame(clock_frames.at(0));
	clock->runAction(cocos2d::RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(clock_frames, 2.5f))));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	clock->setPosition(visibleSize.width - (clock->getBoundingBox().size.width / 2 * SCALE), visibleSize.height - (clock->getBoundingBox().size.height / 2 * SCALE));
	clock->setScale(SCALE);

	addChild(BG);
	for (int i = 0; i < 1; i++) {
		for (int q = 0; q < 1; q++) {
			rooms[i][q]->getTexture()->setTexParameters(tp);
			rooms[i][q]->setScale(SCALE);

			addChild(rooms[i][q]);
		}
	}
	addChild(player);
	addChild(dog);
	addChild(zombie[0]);
	addChild(FG);
	addChild(clock);

	this->scheduleUpdate();

	return true;
}



void GameScene::update(float dt)
{

	total -= dt;
	if (total <= 0) {
		total = t_TIME;
		GameScene::clearBtns();
		GameScene::gameResourceCallback(player);
	}
	Vec2 p_spd = { 0, 0 };


	if (GAMEPLAY_INPUT.key_escape) {

	}

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
				if (player->getHp() <= 0) {
					GameScene::gameHighscoreCallback(NULL);
				}
			}
		}

		if (timer > 0) {
			timer -= dt;

			if (timer < 0.2f) {
				for (unsigned int z = 0; z < zombie.size(); z++) {
					if (player->getDir()) {
						if ((player->getPosition().x - zombie[z]->getPosition().x) <= 75) {
							if ((player->getPosition().x - zombie[z]->getPosition().x) >= 0 && player->getFloor() == zombie[z]->getFloor()) {
								zombie[z]->setSpd(Vec2(-2.0f, 0));
								if (!zombie[z]->getDir()) {
									zombie[z]->hurt(5);
								}
								else {
									zombie[z]->hurt(1);
								}
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

		if (player->getPosition().x + p_spd.x - player->getBoundingBox().size.width / 2 < 70 * SCALE) {
			p_spd.x = player->getPosition().x - player->getBoundingBox().size.width / 2 - (70 * SCALE);
		}
		else if (player->getPosition().x + p_spd.x + player->getBoundingBox().size.width / 2 > (600 - 87) * SCALE) {
			p_spd.x = player->getPosition().x + player->getBoundingBox().size.width / 2 - ((600 - 87) * SCALE);
		}


		if (player->getPosition().x >= 158 * SCALE && player->getPosition().x + p_spd.x < 158 * SCALE) {
			p_spd.y = -5 * SCALE;
		}
		else if (player->getPosition().x + p_spd.x > 158 * SCALE && player->getPosition().x <= 158 * SCALE) {
			p_spd.y = 5 * SCALE;
		}

		auto visibleSize = Director::getInstance()->getVisibleSize();

		auto cam = getDefaultCamera();
		if (player->getPosition().x > visibleSize.width / 2 && player->getPosition().x < (600 * SCALE) - (visibleSize.width / 2) - 100) {
			cam->setPositionX(cam->getPositionX() + p_spd.x);

			//auto origin = Director::getInstance()->getVisibleOrigin();
			clock->setPosition(cam->getPositionX() + visibleSize.width - (clock->getBoundingBox().size.width / 2), cam->getPositionY() + visibleSize.height - (clock->getBoundingBox().size.height / 2));
		}
		else if (player->getPosition().x < visibleSize.width / 2) {
			cam->setPositionX(0);
		}
		else {
			cam->setPositionX((600 * SCALE) - visibleSize.width - 100);
		}

		if (player->getFloor() == 1) {
			cam->setPositionY(0.0f);
		}
		else {
			cam->setPositionY(50 * SCALE);
		}


		//for (int i = 0; i < 3; i++) {	 //Search Prompt
		//	for (int q = 0; q < 2; q++) {
		//		for (int w = 0; w < rooms[i][q]->totalContainers.size(); w++) {
		//			float dist = rooms[i][q]->totalContainers[w]->getPosX() - player->getPositionX();
		//			if (dist >= 0 && dist <= 20) {
		//				bool soundbuff = false;
		//				//Show prompt
		//
		//				if (GAMEPLAY_INPUT.key_Interact && rooms[i][q]->totalContainers[w]->getLooted() == false) {	   //Looting
		//					soundbuff = true;
		//					lootingTime -= dt;
		//
		//					if (!(rooms[i][q]->totalContainers[w]->getBeingLooted())) {
		//						audio->playEffect("SearchSound.wav", false, 1.0f, 1.0f, 0.008f);
		//
		//						if (lootingTime <= 0) {
		//							rooms[i][q]->totalContainers[w]->looting(player);
		//							rooms[i][q]->totalContainers[w]->isBeingLooted(true);
		//						}
		//
		//					}
		//					else {
		//						rooms[i][q]->totalContainers[w]->isBeingLooted(false);
		//						lootingTime = 3.0f;
		//						//audio->stopEffect(audio->playEffect("Rummaging.wav", false, 1.0f, 1.0f, 0.01f));
		//					}
		//				}
		//			}
		//			else
		//			{
		//				//hide Prompt
		//			}
		//		}
		//	}
		//}

		//for (int i = 0; i < 2; i++) {	 //Stairs Prompt
		//	for (int q = 0; q < 1; q++) {
		//		if ((rooms[i][q]->isStairs())) {
		//			float dist = rooms[i][q]->getPositionX() - player->getPositionX();
		//			if (dist >= 0 && dist <= 20) {
		//				if (GAMEPLAY_INPUT.key_up && (player->getPositionY() < 250.0f) && player->getPositionY() < 400) {
		//
		//					player->move(cocos2d::Vec2(0, 200));
		//				}
		//
		//				if (GAMEPLAY_INPUT.key_up && (player->getPositionY() > 250.0f) && player->getPositionY() > 0) {
		//
		//					player->move(cocos2d::Vec2(0, -200));
		//				}
		//
		//
		//			}
		//		}
		//	}
		//}
		//if (GAMEPLAY_INPUT.key_Interact && (LivingRoom1->totalContainers[0]->getPosX() - player->getPositionX() >= 0 && LivingRoom1->totalContainers[0]->getPosX() - player->getPositionX() >= 10) && LivingRoom1->totalContainers[0]->getLooted() == false) {
		//	if(!(LivingRoom1->totalContainers[0]->getBeingLooted())){ audio->playEffect("Rummaging.wav", false, 1.0f, 1.0f, 1.0f); }
		//	LivingRoom1->totalContainers[0]->isBeingLooted(true);
		//	LivingRoom1->totalContainers[0]->looting(player, dt);
		//	
		//}
		//else {
		//	LivingRoom1->totalContainers[0]->isBeingLooted(false);
		//}


		player->move(p_spd);

		for (unsigned int z = 0; z < zombie.size(); z++) {
			zombie[z]->AI(player, dt);
			zombie[z]->move();
		}
	
}

void GameScene::gameResourceCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(ResourceScene::createScene(player));
}

void GameScene::gameHighscoreCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(ScoreScene::createScene());
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
