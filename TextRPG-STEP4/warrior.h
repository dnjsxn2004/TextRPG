#ifndef WARRIOR_H_
#define WARRIOR_H_

#include "Player.h"
#include <iostream>

class Warrior : public Player
{
public:
	Warrior(std::string name, int hp, int mp, int power, int defence, int exp, int maxExp, int level, int maxHp, int maxMp) 
		: Player(name, hp+30, mp, power, defence, exp, maxExp, level, maxHp, maxMp)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

	int SkillAttack(Monster* monster, Player* player) override;
};

#endif // !WARRIOR_H_