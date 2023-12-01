#include "enemy.h"


enemy::enemy(std::string aName, int aHealth, int aAttack, std::string aHut,int aExp):iEnemy(aName,aHealth,aAttack,aHut,aExp)
{
	this->Name = aName;
	this->Health = aHealth;
	this->Attack = aAttack;
	this->hut = aHut;
	this->Exp = aExp;
}

void enemy::huuto()
{
	std::cout << Name + " huutaa " + hut << std::endl;
}