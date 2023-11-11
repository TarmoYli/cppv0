#pragma once
#ifndef PLAYER
#define PLAYER

#include <string>
#include <iostream>

class Player
{
public:
	Player(int aHealth,int aAttack,int aParry,int aExp);
	~Player();
	void setHealth(int sHealth);
	void setAttack(int sAttack);
	void setExp(int sExp);
	void setParry(int sParry);
	void setName();
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
