#include "iEnemy.h"

//enemy statit luodaan makeStats(funktiolla) konstruktoriin syötetään oletuksena nollat.

iEnemy::iEnemy(std::string aName,int aHealth,int aAttack,std::string aHut,int aExp)
{
	this->Name = aName;
	this->Health = aHealth;
	this->Attack = aAttack;
	this->hut = aHut;
	this->Exp = aExp;
}
iEnemy::~iEnemy(){}

void iEnemy::makeStats()
{
	srand(time(0));												// rand palauttaa arvon N-1 eli (rand()%6)-> palauttaa arvon välillä 0-5
	Health = (rand() % 5 + 1) * 10;
	Attack = Health / 10 / 2;
	Exp = Health / 10;
}
void iEnemy::setHealth(int sHealth)
{
	this->Health = sHealth;
}
void iEnemy::setAttack(int sAttack)
{
	this->Attack = sAttack;
}
int iEnemy::getHealth()
{
	return Health;
}
int iEnemy::getAttack()
{
	return Attack;
}
int iEnemy::getExp()
{
	return Exp;
}
std::string iEnemy::getName()
{
	return Name;
}
