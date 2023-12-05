#pragma once
#pragma once
#ifndef ENEMYBOSS
#define ENEMYBOSS

#include "iEnemy.h"

class enemyBoss :public iEnemy
{
public:
	enemyBoss(std::string aName, int aHealth, int aAttack, std::string aHut, int aExp);
	void huuto();
	void makeStats(int scaling);
	std::string getName();
};

#endif // !ENEMYBOSS