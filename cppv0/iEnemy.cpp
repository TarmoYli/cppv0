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
																// header tiedostossa on void huuto pure virtualina
																// tässä .cpp tiedostossa ko. metodia ei ole ollenkaan
																// homma silti toimii niinkuin pitääkin eli perivä luokka pakotetaan sitä käyttämään.
																// ts. jos haluaa tehdä ns.interfacen niin olisi varmaan parempi että kaikki metodit olisivat pure virtual jotta ne olisi pakko ottaa mukaan periviin luokkiin.
void iEnemy::makeStats()
{
	srand(time(0));												// rand palauttaa arvon N-1 eli (rand()%6)-> palauttaa arvon välillä 0-5
	Health = (rand() % 5 + 1) * 10;								// ja tähän siis täytyy lisätä 1 jotta arvo ei voi koskaan olla 0
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
