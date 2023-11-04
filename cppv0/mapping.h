#pragma once
#ifndef MAPPING
#define MAPPING

#include <vector>


namespace mapping
{
	std::vector<std::vector<char>> mapSize();

	std::vector<std::vector<char>> userInput(std::vector<std::vector<char>>& playMap);

	void printPlayMap(std::vector<std::vector<char>>& playMap);

	void combat();

	bool checkForEnemy(int y,int x);

	void printMap(std::vector<std::vector<char>>& playMap);
}

#endif // !MAPPING_H