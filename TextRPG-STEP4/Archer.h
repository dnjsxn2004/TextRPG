#ifndef ARCHER_H_
#define ARCHER_H_


#include "Player.h"
#include <iostream>

class Archer : public Player
{
public:
	Archer(std::string name, int hp, int mp, int power, int defence, int exp, int maxExp, int level, int maxHp, int maxMp) 
		: Player(name, hp, mp, power, defence+30, exp, maxExp, level, maxHp, maxMp)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

	int SkillAttack(Monster* monster, Player* player) override;

};

#endif // !ARCHER_H_