#include "vihu.h"


Vihu::Vihu(std::string aName,int aHealth,int aAttack,std::string aHut,int aExp)
{
	this->Name = aName;
	this->Health = aHealth;
	this->Attack = aAttack;
	this->hut = aHut;
	this->Exp = aExp;
}
Vihu::~Vihu()
{
	std::cout << Name << " kuoli!" << std::endl;
}
void Vihu::setHealth(int sHealth)
{
	this->Health = sHealth;
}
void Vihu::setAttack(int sAttack)
{
	this->Attack = sAttack;
}
int Vihu::getHealth()
{
	return Health;
}
int Vihu::getAttack()
{
	return Attack;
}
int Vihu::getExp()
{
	return Exp;
}
std::string Vihu::getName()
{
	return Name;
}
