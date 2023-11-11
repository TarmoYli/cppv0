#include "javihu.h"


JaVihu::JaVihu(std::string aName, int aHealth, int aAttack, std::string aHut,int aExp):Vihu(aName,aHealth,aAttack,aHut,aExp)
{
	this->Name = aName;
	this->Health = aHealth;
	this->Attack = aAttack;
	this->hut = aHut;
	this->Exp = aExp;
}

void JaVihu::huuto()
{
	std::cout << Name + " huutaa " + hut << std::endl;
}