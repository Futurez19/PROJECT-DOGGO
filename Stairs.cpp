#include "Stairs.h"

Stairs::Stairs(cocos2d::Vec2 p)
{
	position = p;
}

Stairs::~Stairs()
{

}

cocos2d::Vec2 Stairs::getPos()
{
	return position;
}
