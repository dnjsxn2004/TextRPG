#ifndef THIEF_H_
#define THIEF_H_


#include "Player.h"
#include <iostream>

class Thief : public Player
{
public:
	Thief(std::string name, int hp, int mp, int power, int defence) : Player(name, hp, mp, power+30, defence)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

};

#endif // THIEF_H_
