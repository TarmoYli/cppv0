#pragma once
#ifndef IENEMY
#define IENEMY

#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>

class iEnemy
{
public:
	iEnemy(std::string aName, int ahealth, int aAttack, std::string aHut,int aExp);
	~iEnemy();
	virtual void huuto() = 0;
	void makeStats();
	void setHealth(int sHealth);
	void setAttack(int sAttack);
	int getHealth();
	int getAttack();
	int getExp();
	std::string getName();

protected:
	int Health;
	int Attack;
	int Exp;
	std::string Name;
	std::string hut;
};
#endif // !IENEMY
