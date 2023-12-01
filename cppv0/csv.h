#pragma once
#ifndef CSV
#define CSV

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>

namespace csv
{
	std::string getEnemyName();
	void saveStats(std::string name, int xp);
}

#endif // !CSV
