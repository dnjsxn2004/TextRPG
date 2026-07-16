#ifndef WARRIOR_H_
#define WARRIOR_H_

#include "Player.h"
#include <iostream>

class Warrior : public Player
{
public:
	Warrior(std::string name, int hp, int mp, int power, int defence) : Player(name, hp+30, mp, power, defence)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

	
};

#endif // !WARRIOR_H_