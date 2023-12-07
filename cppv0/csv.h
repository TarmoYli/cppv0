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
#include <ctype.h>			//tarvinee isdigittiin checkInput()ssa

namespace csv
{
	std::string getEnemyName();
	void saveStats(std::string name, int xp);
	bool checkInput(const std::string& question);
}

#endif // !CSV
