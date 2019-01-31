#include "Stairs.h"

Stairs::Stairs(cocos2d::Vec2 p,bool dir)
{
	position = p;
	up = dir;
}

Stairs::~Stairs()
{

}

cocos2d::Vec2 Stairs::getPos()
{
	return position;
}
