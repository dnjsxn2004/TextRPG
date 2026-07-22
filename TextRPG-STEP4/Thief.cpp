#include "Thief.h"
#include "Monster.h"

void Thief::Attack()
{
	std::cout << "Thief's Attack!!";
}
void Thief::printPlayerSelectionMessage()
{
	std::cout << "You became a Rogue! (Power +30)";
}


//Thief 5회 공격 플레이어 파워 - 몬스터 방어력
int Thief::SkillAttack(Monster* monster, Player* player)
{
	int damage;

	if ((player->getpower() / 5) - monster->getdefence() <= 0)
	{
			damage = 1;

			return damage;
	}
	else
	{
			damage = (player->getpower() / 5) - monster->getdefence();

			return damage;
	}
}