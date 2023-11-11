#include "vihu.h"


Vihu::Vihu(std::string nimi,int hela,int isku,std::string aHut)
{
	this->Name = nimi;
	this->Health = hela;
	this->Attack = isku;
	this->hut = aHut;
}
void Vihu::setHealth(int hela)
{
	this->Health = hela;
}
void Vihu::setAttack(int isku)
{
	this->Attack = isku;
}
int Vihu::getHealth()
{
	return Health;
}
int Vihu::getAttack()
{
	return Attack;
}
std::string Vihu::getName()
{
	return Name;
}