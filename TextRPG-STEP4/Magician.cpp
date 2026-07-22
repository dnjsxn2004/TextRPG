#include "Magician.h"
#include "Monster.h"

void Magician::Attack()
{
	std::cout << "Magician's Attack!!";
}
void Magician::printPlayerSelectionMessage()
{
	std::cout << "You became a Mage! (MP +30)";
}

//Magician 1회 공격 플레이어 파워 - 몬스터 방어력
int Magician::SkillAttack(Monster* monster, Player* player)
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