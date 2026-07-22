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
	int exp;
	int level;

	public:
		Monster(std::string name, int hp, int power, int defence, std::string dropItemName, int dropItemPrice, int exp, int level) :
			name(name), hp(hp), power(power), defence(defence), dropItemName(dropItemName), dropItemPrice(dropItemPrice), exp(exp), level(level)
		{};

		virtual ~Monster() {}

		int gethp() { return hp; }
		int getpower() { return power; }
		int getdefence() { return defence; }
		std::string getname() { return name; }
		std::string getdropItemName() { return dropItemName; }
		int getdropItemPrice() { return dropItemPrice; }
		int getexp() { return exp; }

		void sethp(int hp);
		void setpower(int power);
		void setdefence(int defence);
		void setname(std::string name);


		virtual void AttackMessage() = 0;

		virtual void damageTaken(int damage, int defence, std::string name);

		virtual void SkillDamageTaken(int damage, std::string name);

		
		

};
	



#endif // !MONSTER_H_
