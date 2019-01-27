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

	
	
}

void GameScene::RNG(int i, int q)
{
	srand(time(NULL));
	int roomType = (rand() % 3) + 1;

	srand(time(NULL));
	int var = ((rand() % 2) + 1);

	switch (roomType) {
	case 1:	// Kitchen
		
		rooms[i][q] = Kitchen::create(var);
		rooms[i][q]->setPosition(generateLocation(i,q));
		rooms[i][q]->setScale(3.0f);
		rooms[i][q]->generateVariation(var);

	case 2:	//Living Room
		rooms[i][q] = LivingRoom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(3.0f);
		rooms[i][q]->generateVariation(var);

	case 3:	//Bathroom
		rooms[i][q] = Bathroom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(3.0f);
		rooms[i][q]->generateVariation(var);
		
	case 4:	//Bedroom
		rooms[i][q] = Bedroom::create(var);
		rooms[i][q]->setPosition(generateLocation(i, q));
		rooms[i][q]->setScale(3.0f);
		rooms[i][q]->generateVariation(var);

	//case 5:	//Stairs
	//	for (int w = 0; w < 3; w++) {
	//		for (int a = 0; a < 2; a++) {
	//			if (rooms[w][a]->isStairs() && a > 0) {	//Only one set of stairs
	//				RNG(i,q);
	//			}
	//			else {
	//				rooms[i][q] = Stairway::create(var);
	//				rooms[i][q]->setPosition(generateLocation(i,q));
	//				rooms[i][q]->setScale(3.0f);
	//				rooms[i][q]->generateVariation(var);
	//				break;
	//				break;
	//			}
	//		}
	//	}

		
	}
}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	audio->preloadEffect("Rummaging.wav");

	auto KeyHandler = EventListenerKeyboard::create();

	///////////////////////////////////////////////////////////////// IMPORTANT
	//for (int i = 0; i < 3; i++) {	 // Room Generator
	//	for (int q = 0; q < 2; q++) {
	//		RNG(i, q);
	//	}
	// }

	testKitchen = Kitchen::create(1);
	testKitchen->setPosition(generateLocation(0, 0));
	testKitchen->setScale(3.0f);
	testKitchen->generateVariation(1);


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
			audio->stopEffect(audio->playEffect("Rummaging.wav", false, 1.0f, 1.0f, 1.0f));
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyHandler, player);


	//////////////////////////////////////////////////// IMPORTANT
	//for (int i = 0; i < 3; i++) {	 // Room Generator
	//	for (int q = 0; q < 2; q++) {
	//		addChild(rooms[i][q]); // Adding the rooms to background
	//	}
	//}


	addChild(testKitchen);
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
				if (dist >= 0 && dist <= 7) {

					//Show prompt

					if (GAMEPLAY_INPUT.key_Interact && rooms[i][q]->totalContainers[w]->getLooted() == false) {	   //Looting

						if (!(rooms[i][q]->totalContainers[w]->getBeingLooted())) {
							audio->playEffect("Rummaging.wav", false, 1.0f, 1.0f, 1.0f);
							rooms[i][q]->totalContainers[w]->isBeingLooted(true);
							rooms[i][q]->totalContainers[w]->looting(player, dt);
						}
						else {
							rooms[i][q]->totalContainers[w]->isBeingLooted(true);
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
