#ifndef ARCHER_H_
#define ARCHER_H_


#include "Player.h"
#include <iostream>

class Archer : public Player
{
public:
	Archer(std::string name, int hp, int mp, int power, int defence) : Player(name, hp, mp, power, defence+30)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

};

#endif // !ARCHER_H_