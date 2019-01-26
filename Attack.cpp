#include "Attack.h"

Attack::Attack(bool a_atk) {
	atk = a_atk;
}

bool Attack::getAtk() {
	return atk;
}

void Attack::setAtk(bool a_atk) {
	atk = a_atk;
}