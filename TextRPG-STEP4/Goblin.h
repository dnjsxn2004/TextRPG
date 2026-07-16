#ifndef GOBLIN_H_
#define GOBLIN_H_

#include "Monster.h"
#include <iostream>
#include <string>

class Goblin : public Monster
{
public:
	Goblin(std::string name = "Goblin", int hp = 1000, int power = 10, int defence = 5, std::string dropItemName = "Goblin Tendon", int dropItemPrice = 10) : Monster(name, hp, power, defence, dropItemName, dropItemPrice)
	{
	}

	void AttackMessage() override;






};


#endif // !GOBLIN_H_