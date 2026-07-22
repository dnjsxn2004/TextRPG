#ifndef ORC_H_
#define ORC_H_

#include "Monster.h"
#include <iostream>
#include <string>

class Orc : public Monster
{
public:
	Orc(std::string name = "Orc", int hp = 80, int power = 35, int defence = 10, std::string dropItemName = "Orc Tusk", int dropItemPrice = 80, int exp = 150, int level = 3)
		: Monster(name, hp, power, defence, dropItemName, dropItemPrice, exp, level)
	{
	}

	void AttackMessage() override;
};

#endif
