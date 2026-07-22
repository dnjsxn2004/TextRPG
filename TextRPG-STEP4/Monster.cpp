#include "Monster.h"
#include <string>
#include <iostream>


void Monster::sethp(int hp)
{
	this->hp = hp;
};

void Monster::setpower(int power)
{
	this->power = power;
};

void Monster::setdefence(int defence)
{
	this->defence = defence;
};

void Monster::setname(std::string name)
{
	this->name = name;
};

void Monster::damageTaken(int damage, int defence, std::string name)
{
	if ((damage - defence) <= 0)
	{
		this->hp -= 1;

		std::cout << "1 damage to " << name << " !!" << std::endl;
	}
	else
	{
		this->hp -= (damage - defence);

		std::cout << (damage - defence) << " damage to " << name << " !!" << std::endl;
	}

};

void Monster::SkillDamageTaken(int damage, std::string name)
{
	if ((damage - defence) <= 0)
	{
		this->hp -= 1;

		std::cout << "1 damage to " << name << " !!" << std::endl;
	}
	else
	{
		this->hp -= (damage - defence);

		std::cout << (damage - defence) << " damage to " << name << " !!" << std::endl;
	}
};


