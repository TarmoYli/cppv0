#include "csv.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>

std::string csv::getEnemyName()
{
	std::vector<std::string> eNames;
	setlocale(LC_ALL, "fi-FI");
	std::string Animalia = "elukat.csv";
	std::ifstream allAnim;
	allAnim.open(Animalia);

	while (allAnim.peek() != EOF)
	{
		std::string nimi;
		std::getline(allAnim, nimi, ';');
		eNames.push_back(nimi);
	}

	srand(time(0));
	int y = eNames.capacity();
	int z = rand() % y;
	std::string eName = eNames.at(z);
	
	allAnim.close();
	return eName;
}

std::string csv::setRecord()
{
	return std::string();
}