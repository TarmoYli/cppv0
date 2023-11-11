#pragma once
#ifndef MAPPING
#define MAPPING

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <conio.h>                      //t‰‰lt‰ _getch
#include <string>
#include <cstdlib>
#include <ctime>                        //k‰ytet‰‰n randissa
#include <set>                          //koska halutaan uniikkeja arvoja kokoelmaan t‰m‰ tekee sen mukavasti
#include <chrono>
#include <unordered_map>


class mapping
{
public:
	mapping();
	void mapSize();
	std::vector<std::vector<char>> userInput();
	void printPlayMap(Player& plr);
	std::string combat(Player& plr);
	bool checkForEnemy(int y, int x);
	void printMap(std::vector<std::vector<char>>& playMap);
	void setEnemyLocation(std::set<std::pair<int, int>>& enemyCoords);
	void printKillStats();
	bool checkMap();
	
protected:	
	bool inputReady = false;							//n‰iden muuttujien n‰kyvyyksien tarvinee olla laajempia joten alustetaan t‰ss‰.
	bool isRunning = true;								//(muista lis‰t‰ vihollisen kohtaaminen) -> (on varmaan ehk‰ toimiva nyt) -> onkin, eli nyt vaan se itse taistelu eli plr class mukaan
	int locx = 0;										//lokaatio x   n‰ist‰ koordeista l‰hdet‰‰n liikkeelle
	int locy = 0;										//lokaatio y   n‰ist‰ koordeista l‰hdet‰‰n liikkeelle
	int xForMap = 0;									//kuinka monta alkiota (#) per vektori eli x-akseli
	int yForMap = 0;									//kuinka monta vektoria vektorissa eli y-akseli
	
	std::set<std::pair<int, int>> enemyCoords;          // k‰ytet‰‰n setti‰ koska se voi sis‰lt‰‰ VAIN uniikkeja arvoja ja me emme halua t‰h‰n duplikaatteja.
	std::vector<std::pair<int, int>> enemyKillCoords;   // t‰m‰n voinee poistaa ellei sit‰ sitten halua k‰ytt‰‰ joka mapin j‰lkeen ett‰ miss‰ mik‰kin tapettiin... kaipa se on yksi toiminnallisuus sekin.
	std::vector<std::string> enemyKillName;				// joka kartan j‰lkeen tulostetaan, siirret‰‰n enemyKills mappiin ja tyhjennet‰‰n.
	std::unordered_map<std::string, int> enemyKills;    // nimet on uniikkeja (keys), m‰‰r‰t inttej‰ (values)
	std::vector<std::vector<char>> playMap;
};

#endif // !MAPPING