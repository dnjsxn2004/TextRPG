#ifndef DRAGON_H_
#define DRAGON_H_

#include "Monster.h"
#include <iostream>
#include <string>

class Dragon : public Monster
{
public:
	Dragon(std::string name = "Dragon", int hp = 200, int power = 60, int defence = 20, std::string dropItemName = "Dragon Scale", int dropItemPrice = 500, int exp = 1000, int level = 10)
		: Monster(name, hp, power, defence, dropItemName, dropItemPrice, exp, level)
	{
	}

	void AttackMessage() override;
};

#endif
