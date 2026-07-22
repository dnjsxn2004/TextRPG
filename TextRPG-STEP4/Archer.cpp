#include "Archer.h"
#include "Monster.h"

void Archer::Attack()
{
	std::cout << "Archer's Attack!!";
}

void Archer::printPlayerSelectionMessage()
{
	std::cout << "You became a Archer! (Defence +30)";
}

//Archer 3회 공격 플레이어 파워 - 몬스터 방어력
int Archer::SkillAttack(Monster* monster, Player* player)
{
	int damage;

	if ((player->getpower() / 3) - monster->getdefence() <= 0)
	{
			damage = 1;

			return damage;
	}
	else
	{
			damage = (player->getpower() / 3) - monster->getdefence();

			return damage;
	}
}