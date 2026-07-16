#include "Player.h"
#include <iostream>


void Player::setname(std::string name)
{
	this->name = name;
};

void Player::sethp(int hp)
{
	this->hp = hp;
};

void Player::setmp(int mp)
{
	this->mp = mp;
};

void Player::setpower(int power)
{
	this->power = power;
};

void Player::setdefence(int defence)
{
	this->defence = defence;
};

void Player::printplayerStatus()
{
	std::cout << "================================" << std::endl;
	std::cout << "        " << name << "'s Stats" << std::endl;
	std::cout << "================================" << std::endl;

	std::cout << "HP : " << hp << "      " << "MP : " << mp << std::endl;
	std::cout << "Attack : " << power << "      " << "Defense : " << defence << std::endl;
};

void Player::damageTaken(int damage, int defence, std::string name)
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
