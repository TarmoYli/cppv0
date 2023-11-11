#pragma once
#ifndef VIHU
#define VIHU

#include <string>
#include <iostream>

class Vihu
{
public:
	Vihu(std::string name, int hela, int isku, std::string aHut);
	~Vihu();
	virtual void huuto() = 0;
	void setHealth(int hela);
	void setAttack(int isku);
	int getHealth();
	int getAttack();
	std::string getName();

protected:
	int Health;
	int Attack;
	std::string Name;
	std::string hut;
};
#endif // !VIHU
