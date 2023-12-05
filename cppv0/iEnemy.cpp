#include "iEnemy.h"

//enemy statit luodaan makeStats(funktiolla) konstruktoriin sy�tet��n oletuksena nollat.

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
																// t�ss� .cpp tiedostossa ko. metodia ei ole ollenkaan
																// homma silti toimii niinkuin pit��kin eli periv� luokka pakotetaan sit� k�ytt�m��n.
																// ts. jos haluaa tehd� ns.interfacen niin olisi varmaan parempi ett� kaikki metodit olisivat pure virtual jotta ne olisi pakko ottaa mukaan periviin luokkiin.
void iEnemy::makeStats()
{
	srand(time(0));												// rand palauttaa arvon N-1 eli (rand()%6)-> palauttaa arvon v�lill� 0-5
	Health = (rand() % 5 + 1) * 10;								// ja t�h�n siis t�ytyy lis�t� 1 jotta arvo ei voi koskaan olla 0
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
