#pragma once
#ifndef ENEMY
#define ENEMY

#include "iEnemy.h"

class enemy :public iEnemy
{
public:
	enemy(std::string aName, int aHealth, int aAttack, std::string aHut,int aExp);
	void huuto();
};

#endif // !ENEMY
