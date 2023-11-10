#pragma once
#ifndef PLAYER
#define PLAYER

#include <string>

class Player
{
public:
	Player(int aHealth,int aAttack,int aParry,int aExp, std::string aName);

	void setHealth(int sHealth);
	void setAttack(int sAttack);
	void setExp(int sExp);
	void setParry(int sParry);
	int getHealth();
	int getAttack();
	int getParry();
	int getExp();
	std::string getName();

protected:
	int Health;
	int Attack;
	int Parry;
	int Exp;
	std::string Name;
};

#endif // !PLAYER
