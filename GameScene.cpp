#include "GameScene.h"
#include "cocos2d.h"
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
	std::uniform_int_distribution<> range(1, 7);
	std::uniform_int_distribution<> range2(1, 3);

	int roomType =(range(gen));

	int var = (range2(gen));



	switch (roomType) {
	case 1:	// Kitchen
		
		rooms[i][q] = Kitchen::create(var);
		rooms[i][q]->setPosition(generateLocation(i,q));
		rooms[i][q]->setScale(4.0f);
		rooms[i][q]->generateVariation(var);
		break;

	case 2:	//Living Room
		rooms[i][q] = LivingRoom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(4.0f);
		rooms[i][q]->generateVariation(var);
		break;

	case 3:	//Bathroom
		rooms[i][q] = Bathroom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(4.0f);
		rooms[i][q]->generateVariation(var);
		break;
		
	case 4:	//Bedroom
		rooms[i][q] = Bedroom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(4.0f);
		rooms[i][q]->generateVariation(var);
		break;
	case 5:
	case 6:
	case 7:	//Stairs
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
					rooms[i][q]->setScale(4.0f);
					rooms[i][q]->generateVariation(var);
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
	player->setPosition(Vec2(50, 100));
	player->setScale(3.0f);


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
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyHandler, player);


	//////////////////////////////////////////////////// IMPORTANT
	for (int i = 0; i < 3; i++) {	 // Room Generator
		for (int q = 0; q < 2; q++) {
			addChild(rooms[i][q]); // Adding the rooms to background
		}
	}


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

	
	for (int i = 0; i < 2; i++) {	 //Search Prompt
		for (int q = 0; q < 1; q++) {
			for (int w = 0; w < rooms[i][q]->totalContainers.size(); w++) {

				float dist = rooms[i][q]->totalContainers[w]->getPosX() - player->getPositionX();
				if (dist >= 0 && dist <= 20) {
					bool soundbuff = false;
					//Show prompt

					if (GAMEPLAY_INPUT.key_Interact && rooms[i][q]->totalContainers[w]->getLooted() == false) {	   //Looting
						soundbuff = true;

						if (!(rooms[i][q]->totalContainers[w]->getBeingLooted())) {
							audio->playEffect("SearchSound.wav", false, 1.0f, 1.0f, 0.008f);
							rooms[i][q]->totalContainers[w]->isBeingLooted(true);
							rooms[i][q]->totalContainers[w]->looting(player, dt);
						}
						else {
							rooms[i][q]->totalContainers[w]->isBeingLooted(false);
							//audio->stopEffect(audio->playEffect("Rummaging.wav", false, 1.0f, 1.0f, 0.01f));
						}
					}
				}
				else
				{
					//hide Prompt
				}
			}
		}
	}

	for (int i = 0; i < 2; i++) {	 //Stairs Prompt
		for (int q = 0; q < 1; q++) {
			if ((rooms[i][q]->isStairs())) {
				float dist = rooms[i][q]->getPositionX() - player->getPositionX();
				if (dist >= 0 && dist <= 20) {
					if (GAMEPLAY_INPUT.key_up && (player->getPositionY() < 250.0f) && player->getPositionY() < 400) {

						player->move(cocos2d::Vec2(0, 200));
					}
					
					if (GAMEPLAY_INPUT.key_up && (player->getPositionY() > 250.0f) && player->getPositionY() > 0) {

						player->move(cocos2d::Vec2(0, -200));
					}
						

				}
			}
		}
	}
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
}
