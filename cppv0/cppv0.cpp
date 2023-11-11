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
#include "javihu.h"

using namespace csv;

int main()
{
    mapping map;
    Player plr(50, 5, 3, 0);
    plr.setName();
    map.mapSize();
    std::thread mapMove([&map]() {map.userInput();});
    std::thread mapPrinter([&map,&plr]() {map.printPlayMap(plr);});

    mapMove.join();
    mapPrinter.join();
    
    return 0;
}