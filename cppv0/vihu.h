#pragma once
#ifndef VIHU
#define VIHU

#include <string>
#include <iostream>

class Vihu
{
public:
	Vihu(std::string aName, int ahealth, int aAttack, std::string aHut,int aExp);
	~Vihu();
	virtual void huuto() = 0;
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
#endif // !VIHU
