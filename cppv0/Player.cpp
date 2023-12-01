#include "Player.h"

Player::Player(int aHealth, int aAttack, int aParry, int aExp)
{
	this->Health = aHealth;
	this->Attack = aAttack;
	this->Parry = aParry;
	this->Exp = aExp;
}
Player::~Player(){}
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

void Player::setName()
{
	std::string plrName;
	std::cout << "Anna pelaajan nimi: " << std::endl;
	std::cin >> plrName;
	this->Name = plrName;
}

void Player::showStatus()
{
	std::cout << Name << std::endl;
	std::cout << "Health: " << Health << std::endl;
	std::cout << "Attack: " << Attack << std::endl;
	std::cout << "XP: " << Exp << std::endl;
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