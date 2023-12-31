#include "csv.h"


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
	int eNameCsvCap = eNames.capacity();
	int eNameCsvIndex = rand() % eNameCsvCap;
	std::string eName = eNames.at(eNameCsvIndex);
	
	allAnim.close();
	return eName;
}

void csv::saveStats(std::string name, int xp)
{
	std::fstream fout;
	fout.open("statistics.csv", std::ios::app);
	fout << name << ';' << xp << '\n';
}


bool csv::checkInput(const std::string& input) {
	if (input.empty())							// tarkistaa onko annettu sy�te tyhj�
	{											// ja
		return false;							// palauttaa falsen jos on.
	}

	for (char c : input)						// tarkistaa merkit yksi kerrallaan sy�tteest�.
	{
		if (!std::isdigit(c))					// Jos ei ole int
		{										// niin
			return false;						// false palautetaan.
		}
	}
	return true;
}