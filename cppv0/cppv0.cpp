#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <cmath>
#include <thread>
#include <set>
#include <utility>
#include "csv.h"
#include "mapping.h"
#include "javihu.h"

using namespace mapping;
using namespace csv;


int main()
{
    std::vector<std::vector<char>> komap = mapSize();
    std::thread mapMove(userInput, std::ref(komap));
    std::thread mapPrinter(printPlayMap, std::ref(komap));

    mapMove.join();
    mapPrinter.join();
    
    return 0;
}