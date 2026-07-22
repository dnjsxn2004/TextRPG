#ifndef SLIME_H_
#define SLIME_H_

#include "Monster.h"
#include <iostream>
#include <string>

class Slime : public Monster
{
public:
	Slime(std::string name = "Slime", int hp = 500, int power = 10, int defence = 5, std::string dropItemName = "Slime Jelly!", int dropItemPrice = 5, int exp = 100, int level = 1)
		: Monster(name, hp, power, defence, dropItemName, dropItemPrice, exp, level)
	{	
	}

	void AttackMessage() override;






};


#endif // !SLIME_H_
