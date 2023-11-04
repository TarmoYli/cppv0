
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <time.h>
#include <set>
#include <chrono>

#include "javihu.h"
#include "mapping.h"
#include "csv.h"

std::mutex mtx;
std::condition_variable cond;

bool inputReady = false;
bool isRunning = true;                   //(muista lis‰t‰ vihollisen kohtaaminen) -> (on varmaan ehk‰ toimiva nyt) -> onkin, eli nyt vaan se itse taistelu eli plr class mukaan

int locx = 0;                            //lokaatio x   n‰ist‰ koordeista l‰hdet‰‰n liikkeelle
int locy = 0;                            //lokaatio y   n‰ist‰ koordeista l‰hdet‰‰n liikkeelle
int xForMap;                             //kuinka monta alkiota (#) per vektori eli x-akseli
int yForMap;                             //kuinka monta vektoria vektorissa eli y-akseli

std::set<std::pair<int, int>> uni;      

std::vector<std::vector<char>> mapping::mapSize()
{
    std::cout << "Anna x akselin pituus: " << std::endl;
    std::cin >> xForMap;
    std::cout << "Anna y akselin pituus: " << std::endl;
    std::cin >> yForMap;

    std::vector<std::vector<char>> playMap(yForMap, std::vector<char>(xForMap, '#'));

    return playMap;
}

std::vector<std::vector<char>> mapping::userInput(std::vector<std::vector<char>>& playMap) {

    char ch;

    while (isRunning) // jos "isRunning = false" lopettaa threadin.
    {
        std::cout << "liiku w,a,s,d paina enter aloittaaksesi ('q' lopettaa ohjelman):";
        ch = _getch();                                //ennen getchi‰ ehk‰ printtaa kartan jotta getch tulee vasta printin j‰lkeen eik‰ odota inputtia
        {
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [] { return !inputReady; });
            playMap[locy][locx] = 'O';
            if (ch == 'w')
            {
                locy -= 1;
                if (locy <= 0)
                    locy = 0;
                playMap[locy][locx] = 'O';
            }
            else if (ch == 's')
            {
                locy += 1;
                if (locy >= playMap.size() - 1)
                    locy = playMap.size() - 1;
                playMap[locy][locx] = 'O';
            }
            else if (ch == 'd')
            {
                locx += 1;
                if (locx >= playMap[0].size() - 1)
                    locx = playMap[0].size() - 1;
                playMap[locy][locx] = 'O';
            }
            else if (ch == 'a')
            {
                locx -= 1;
                if (locx <= 0)
                    locx = 0;
                playMap[locy][locx] = 'O';
            }
            else if (ch == 'q')
            {
                isRunning = false;
            }

            inputReady = true;
        }
        cond.notify_one();
    }
    return playMap;
}

void mapping::printPlayMap(std::vector<std::vector<char>>& playMap) {
    while (isRunning) {
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [] { return inputReady; });

        system("cls");
        playMap[locy][locx] = 'X';
        for (const std::vector<char>& row : playMap)                    // t‰st‰ oma funktio? tarvitaan kahdessa muussakin paikkaa ja ehk‰ lopuksi.
        {
            for (char item : row)
            {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "y-akseli: " << locy << "\nx-akseli: " << locx << std::endl;   // lis‰‰ t‰h‰n tapetut viholliset ja/tai miss‰ ne on tapettu tee ehk‰ infoOut funktio
        if (checkForEnemy(locy,locx))
        {
            system("cls");
            combat();
            system("cls");
            for (const std::vector<char>& row : playMap)                
            {
                for (char item : row)
                {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "y-akseli: " << locy << "\nx-akseli: " << locx << std::endl;
        }
        inputReady = false;
        cond.notify_one();
    }
}

void mapping::combat()
{    
    JaVihu normi = JaVihu(csv::getEnemyName(), 20, 5, "hauhahuh");
    std::cout << "\nNimi: " << normi.getName() << "\nhˆˆki: " << normi.getAttack() << "\nhealth: " << normi.getHealth() << std::endl;
    normi.huuto();
    char testi;
    std::cout << "\nT‰h‰n joku juttu koita vaikka aa: " << std::endl;
    std::cin >> testi;
    switch (testi)                                                          // poista t‰m‰ koko switch case testi
    {
    case 'a':
        std::cout << "se oli A" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));               // Poista n‰m‰ sleepit ja <chrono> jos ei k‰ytet‰.
        break;
    case 'b':
        std::cout << "se oli B" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        break;
    default:
        std::cout << "se oli joku muu kuin a tai b" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        break;
    }  
}
bool mapping::checkForEnemy(int y, int x)                           // tee eri funktio alkuun "make enemy location" jossa tehd‰‰n set, jotta siit‰ voi poistaa arvoja.
{
    int Amount = round(sqrt(yForMap * xForMap));
    srand(time(0));
    std::pair<int, int> crds;
    while (uni.size() != Amount)                                    // t‰m‰ looppi ei k‰y jos setist‰ poistellaan arvoja. eli t‰m‰n loopin pit‰‰ olla omassa funktiossaan.
    {                                                               // jos halutaan poistaa setist‰ arvoja.
        do
        {
            crds = std::make_pair(rand() % xForMap, rand() % yForMap);
        } while (crds == std::make_pair(0, 0));
        uni.insert(crds);
    }
    std::pair<int, int> verrokki = std::make_pair(y, x);
    bool hit = uni.find(verrokki) != uni.end();                       // Jos find palauttaa NOT .end() on arvo TRUE, silloin find on osunut ja palauttaa iterin eik‰ palauta endi‰.
    //uni.erase(verrokki);                                            // poistaa setist‰ ko. arvoparin.
    return hit;
}

void mapping::printMap(std::vector<std::vector<char>>& playMap)
{
    for (const std::vector<char>& row : playMap)
    {
        for (char item : row)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}