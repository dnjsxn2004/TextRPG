#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

class Player
{
protected:
	std::string name;
	int hp;
	int mp;
	int power;
	int defence;

public:
	
	Player(std::string name, int hp, int mp, int power, int defence) : name(name), hp(hp), mp(mp), power(power), defence(defence)
	{};
	
	virtual void Attack() = 0;

	//playerClassSelectionMessage
	virtual void printPlayerSelectionMessage() = 0;


	//getter
	std::string getname() { return name; }
	int gethp() { return hp; }
	int getmp() { return mp; }
	int getpower() { return power; }
	int getdefence() { return defence; }
	
	//setter
	void setname(std::string name);
	void sethp(int hp);
	void setmp(int mp);
	void setpower(int power);
	void setdefence(int defence);

	//printplayerStatus
	void printplayerStatus();
	
	void damageTaken(int damage, int defence, std::string name);

	virtual ~Player() {}
};

#endif // !PLAYER_H_
