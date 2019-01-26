#include "Container.h"
#include "Container.h"
#include "Container.h"
#include "Container.h"
#include <ctime>



ContainerType Container::generateEnum()
{
	ContainerType temp_type;

	srand(time(NULL)); // seeding random
	int type = (rand() % 99) + 1; // 0-2 + 1	 aka 1-3

	if (type <= 40) {
		temp_type = NA;
	}

	if (type > 40 && type <= 60) {
		temp_type = FOOD;
	}

	if (type > 60 && type <= 80) {
		temp_type = WATER;
	}

	if (type > 80 && type <= 100) {
		temp_type = GAS;
	}

	return temp_type;
}

int Container::generateNum()
{
	srand(time(NULL));
	int temp_num = (rand() % 3) + 1;
	return temp_num;
}

bool Container::generateLocked()
{
	srand(time(NULL));
	int locked = (rand() % 99) + 1;

	if (locked <= 10) {
		return true;
	}
	else
		return false;
	
}

bool Container::getLooted()
{
	return Looted;
}

float Container::getLootingTime()
{
	return lootingTime;
}

void Container::looting(Player * player, float dt)
{
   //if looting time is completed
	lootingTime -= dt;

	if (lootingTime <= 0)
	{
		switch (type) {
		case FOOD:
			player->addfood(contains);
			break;
		case WATER:
			player->addWater(contains);
			break;
		case GAS:
			player->addGas(contains);
			break;
		}

		Looted = true;

	}

	if (!(Looted) && !(beingLooted)) {
		lootingTime = 3.0f;
	}

}

void Container::isBeingLooted(bool x)
{
	beingLooted = x;
}

float Container::getPosX() {
	return position.x;
}

float Container::getPosY() {
	return position.y;
}



Container::Container(cocos2d::Vec2 p) :position(p)
{
	type = generateEnum();
	contains = generateNum();
	Locked = generateLocked();
}


Container::~Container()
{

}
