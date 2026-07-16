#ifndef MONSTER_H_
#define MONSTER_H_

#include <iostream>
#include <string>

class Monster
{
protected:
	std::string name;
	int hp;
	int power;
	int defence;
	std::string dropItemName;
	int dropItemPrice;

	public:
		Monster(std::string name, int hp, int power, int defence, std::string dropItemName, int dropItemPrice) :
			name(name), hp(hp), power(power), defence(defence), dropItemName(dropItemName), dropItemPrice(dropItemPrice)
		{};

		int gethp() { return hp; }
		int getpower() { return power; }
		int getdefence() { return defence; }
		std::string getname() { return name; }
		std::string getdropItemName() { return dropItemName; }
		int getdropItemPrice() { return dropItemPrice; }

		void sethp(int hp);
		void setpower(int power);
		void setdefence(int defence);
		void setname(std::string name);


		virtual void AttackMessage() = 0;

		virtual void damageTaken(int damage, int defence, std::string name);

		


};
	



#endif // !MONSTER_H_
