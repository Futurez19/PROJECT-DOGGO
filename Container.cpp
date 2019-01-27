#include "Container.h"
#include "Container.h"
#include "Container.h"
#include "Container.h"
#include <ctime>
#include <random>



ContainerType Container::generateEnum()
{
	ContainerType temp_type;

	std::random_device gen;
	std::uniform_int_distribution<> range(1, 100);

	
	int type = (range(gen)); // 0-2 + 1	 aka 1-3

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
	std::random_device gen;
	std::uniform_int_distribution<> range(1, 4);
	
	int temp_num = (range(gen));
	return temp_num;
}



bool Container::getLooted()
{
	return Looted;
}



void Container::looting(Player * player)
{
   //if looting time is completed
	
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

void Container::isBeingLooted(bool x)
{
	beingLooted = x;
}

bool Container::getBeingLooted()
{
	return beingLooted;
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
}


Container::~Container()
{

}
