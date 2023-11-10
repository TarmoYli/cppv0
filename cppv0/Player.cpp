#include "Player.h"

Player::Player(int aHealth, int aAttack, int aParry, int aExp, std::string aName)
{
	this->Health = aHealth;
	this->Attack = aAttack;
	this->Parry = aParry;
	this->Exp = aExp;
	this->Name = aName;
}
void Player::setHealth(int sHealth)
{
	this->Health = sHealth;
}
void Player::setAttack(int sAttack)
{
	this->Attack = sAttack;
}
void Player::setExp(int sExp)
{
	this->Exp = sExp;
}
void Player::setParry(int sParry)
{
	this->Parry = sParry;
}

int Player::getHealth()
{
	return Health;
}

int Player::getAttack()
{
	return Attack;
}

int Player::getParry()
{
	return Parry;
}

int Player::getExp()
{
	return Exp;
}

std::string Player::getName()
{
	return Name;
}
