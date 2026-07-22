#ifndef THIEF_H_
#define THIEF_H_


#include "Player.h"
#include <iostream>

class Thief : public Player
{
public:
	Thief(std::string name, int hp, int mp, int power, int defence, int exp, int maxExp, int level, int maxHp, int maxMp) 
		: Player(name, hp, mp, power+30, defence, exp, maxExp, level, maxHp, maxMp)
	{ }

	void Attack() override;

	void printPlayerSelectionMessage() override;

	int SkillAttack(Monster* monster, Player* player) override;

};



#endif // THIEF_H_
