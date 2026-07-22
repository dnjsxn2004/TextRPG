#ifndef MAGICIAN_H_
#define MAGICIAN_H_


#include "Player.h"
#include <iostream>

class Magician : public Player
{
public:
	Magician(std::string name, int hp, int mp, int power, int defence, int exp, int maxExp, int level, int maxHp, int maxMp) 
		: Player(name, hp, mp+30, power, defence, exp, maxExp, level, maxHp, maxMp)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

	int SkillAttack(Monster* monster, Player* player) override;

};

#endif // !MAGICIAN_H_
