#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

class Monster;

class Player
{
protected:
	std::string name;
	int hp;
	int mp;
	int power;
	int defence;
	int exp;
	int maxExp;
	int level;
	int maxHp;
	int maxMp;
	


public:

	Player(std::string name, int hp, int mp, int power, int defence, int exp, int maxExp, int level, int maxHp, int maxMp) 
		: name(name), hp(hp), mp(mp), power(power), defence(defence), exp(exp), maxExp(maxExp), level(level), maxHp(maxHp), maxMp(maxMp)
	{};
	
	virtual void Attack() = 0;

	virtual int SkillAttack(Monster* monster, Player* player) = 0;

	//playerClassSelectionMessage
	virtual void printPlayerSelectionMessage() = 0;


	//getter
	std::string getname() { return name; }
	int gethp() { return hp; }
	int getmp() { return mp; }
	int getpower() { return power; }
	int getdefence() { return defence; }
	int getexp() const { return exp; }
	int getmaxExp() const { return maxExp; }
	int getlevel() { return level; }
	int getMaxHp() const { return maxHp; }
	int getMaxMp() const { return maxMp; }
	
	//setter
	void setname(std::string name);
	void sethp(int hp);
	void setmp(int mp);
	void setpower(int power);
	void setdefence(int defence);
	void setlevel(int level);
	void setMaxExp(int MaxExp);
	void setMaxHp(int maxHp);
	void setExp(int exp);
	void setMaxMp(int maxMp);

	//printplayerStatus
	void printplayerStatus();
	
	void damageTaken(int damage, int defence, std::string name);


	virtual ~Player() {}


};

#endif // !PLAYER_H_
