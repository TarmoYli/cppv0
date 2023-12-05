#include "enemyBoss.h"



enemyBoss::enemyBoss(std::string aName, int aHealth, int aAttack, std::string aHut, int aExp):iEnemy(aName,aHealth,aAttack,aHut,aExp)
{
	this->Name = aName;
	this->Health = aHealth;
	this->Attack = aAttack;
	this->hut = aHut;
	this->Exp = aExp;
}

void enemyBoss::huuto()
{
	std::cout << "ISO PAHA" << Name + " huutaa " + hut << std::endl;
}
void enemyBoss::makeStats(int scaling)
{
	int scaleValue = scaling;
	srand(time(0));
	Health = (rand() % 6 + (5+scaleValue)) * 10;
	Attack = Health / 10 / 2 + (1+scaleValue);
	Exp = Health / 10;
}

std::string enemyBoss::getName()
{
	std::string etuliite = "ISO PAHA";
	return etuliite+" "+Name;
}
