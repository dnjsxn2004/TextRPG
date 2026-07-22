#include "Player.h"
#include "warrior.h"
#include "Monster.h"

void Warrior::Attack()
{
		std::cout << "warrior's Attack!!";
}

void Warrior::printPlayerSelectionMessage()
{
	std::cout << "You became a Warrior! (HP +30)";
}


//Warrior 1회 공격 플레이어 파워 - 몬스터 방어력
int Warrior::SkillAttack(Monster* monster, Player* player)
{
	int damage;

	if (player->getpower() - monster->getdefence() <= 0)
	{
		damage = 1;

		return 1;
	}
	else
	{
		damage = player->getpower() - monster->getdefence();

		return damage;
	}
}