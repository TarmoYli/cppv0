#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <cmath>
#include <thread>
#include <set>
#include <utility>
#include "Player.h"
#include "csv.h"
#include "mapping.h"
#include "enemy.h"

using namespace csv;

int main()
{
    mapping map;
    Player plr(100,100, 5, 5, 0);
    plr.setName();
    map.mapSize();
    std::thread mapMove([&map]() {map.userInput();});
    std::thread mapPrinter([&map,&plr]() {map.printPlayMap(plr);});

    mapMove.join();
    mapPrinter.join();
    plr.showStatus();
    csv::saveStats(plr.getName(), plr.getExp());
    std::cout << "Tiedot tallennettu \"statistics.csv\" tiedostoon "<< std::endl;
    std::cin.get();
    return 0;
}