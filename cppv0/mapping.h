#pragma once
#ifndef MAPPING
#define MAPPING

#include <vector>


namespace mapping
{
	void mapSize();

	std::vector<std::vector<char>> userInput();

	void printPlayMap();

	std::string combat();

	bool checkForEnemy(int y,int x);

	void printMap(std::vector<std::vector<char>>& playMap);

	void setEnemyLocation();

	void printKillStats();

	bool checkMap(std::vector<std::vector<char>>& playMap);
}

#endif // !MAPPING_H