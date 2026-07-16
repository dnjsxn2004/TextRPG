#ifndef MAGICIAN_H_
#define MAGICIAN_H_


#include "Player.h"
#include <iostream>

class Magician : public Player
{
public:
	Magician(std::string name, int hp, int mp, int power, int defence) : Player(name, hp, mp+30, power, defence)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

};

#endif // !MAGICIAN_H_
