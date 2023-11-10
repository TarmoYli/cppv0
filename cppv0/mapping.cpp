
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <conio.h>                      //t��lt� _getch
#include <string>
#include <cstdlib>
#include <ctime>                        //k�ytet��n randissa
#include <set>                          //koska halutaan uniikkeja arvoja kokoelmaan t�m� tekee sen mukavasti
#include <chrono>
#include <unordered_map>

#include "javihu.h"
#include "mapping.h"
#include "csv.h"

std::mutex mtx;
std::condition_variable cond;

bool inputReady = false;                 //n�iden muuttujien n�kyvyyksien tarvinee olla laajempia joten alustetaan t�ss�.
bool isRunning = true;                   //(muista lis�t� vihollisen kohtaaminen) -> (on varmaan ehk� toimiva nyt) -> onkin, eli nyt vaan se itse taistelu eli plr class mukaan
int locx = 0;                            //lokaatio x   n�ist� koordeista l�hdet��n liikkeelle
int locy = 0;                            //lokaatio y   n�ist� koordeista l�hdet��n liikkeelle
int xForMap;                             //kuinka monta alkiota (#) per vektori eli x-akseli
int yForMap;                             //kuinka monta vektoria vektorissa eli y-akseli

std::set<std::pair<int, int>> enemyCoords;          // k�ytet��n setti� koska se voi sis�lt�� VAIN uniikkeja arvoja ja me emme halua t�h�n duplikaatteja.
std::vector<std::pair<int, int>> enemyKillCoords;   // t�m�n voinee poistaa ellei sit� sitten halua k�ytt�� joka mapin j�lkeen ett� miss� mik�kin tapettiin... kaipa se on yksi toiminnallisuus sekin.
std::vector<std::string> enemyKillName;
std::unordered_map<std::string, int> enemyKills;    // nimet on uniikkeja (keys), m��r�t inttej� (values)
std::vector<std::vector<char>> playMap;

void mapping::mapSize()
{
    std::cout << "Anna x akselin pituus: " << std::endl;
    std::cin >> xForMap;
    std::cout << "Anna y akselin pituus: " << std::endl;
    std::cin >> yForMap;

    playMap = std::vector<std::vector<char>>(yForMap, std::vector<char>(xForMap, '#'));
    setEnemyLocation(enemyCoords);
}

void mapping::setEnemyLocation(std::set<std::pair<int,int>> &enemyCoords)           // suoritettava ennen checkForEnemy() funktiota.
{
    int Amount = round(sqrt(yForMap * xForMap));
    srand(time(0));
    std::pair<int, int> crds;
    while (enemyCoords.size() != Amount)                                            // toistetaan kunnes .size on sama kuin Amount.      
    {                                                                
        do
        {
            crds = std::make_pair(rand() % xForMap, rand() % yForMap);
        } while (crds == std::make_pair(0, 0));                                     // jos crds arvo(t) on 0,0 while looppi toistuu joten insertiin ei koskaan mene 0,0
        enemyCoords.insert(crds);
    }
}

std::vector<std::vector<char>> mapping::userInput()
{
    char ch;

    while (isRunning) // jos "isRunning = false" lopettaa threadin.
    {
        std::cout << "liiku w,a,s,d paina enter aloittaaksesi ('q' lopettaa ohjelman):";
        ch = _getch();                                // ennen getchi� ehk� printtaa kartan jotta getch tulee vasta printin j�lkeen eik� odota inputtia
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
                if (locy >= playMap.size() - 1)                         //n�it� ei varmaan saa funktioitua kun tarvii varmistaa
                    locy = playMap.size() - 1;                          //ettei mene vektorit out-of-boundsiin.
                playMap[locy][locx] = 'O';                              //jokaisessa iffiss� muuttujien k�sittely liev�sti erilaista
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

void mapping::printPlayMap()
{
    
    while (isRunning)
    {    
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [] { return inputReady; });
        system("cls");
        playMap[locy][locx] = 'X';
        printMap(playMap);
        std::cout << "y-akseli: " << locy << "\nx-akseli: " << locx << std::endl;
        if (checkForEnemy(locy,locx))
        {
            //system("cls");
            enemyKillCoords.push_back(std::make_pair(locy,locx));
            enemyKillName.push_back(combat());
            system("cls");
            printMap(playMap);
            std::cout << "y-akseli: " << locy << "\nx-akseli: " << locx << std::endl;
        }
        if (checkMap())
        {
            std::cout << "kartta l�p�isty." << std::endl;
            printKillStats();
            std::cout << "uusi kartta" << std::endl;
            locx = 0;
            locy = 0;
            mapSize();
        }
        inputReady = false;
        cond.notify_one();
    }
}

std::string mapping::combat()
{    
    JaVihu normi = JaVihu(csv::getEnemyName(), 20, 5, "hauhahuh");
    std::cout << "\nNimi: " << normi.getName() << "\nh��ki: " << normi.getAttack() << "\nhealth: " << normi.getHealth() << std::endl;
    normi.huuto();
    //char testi;                                                             // t�st� asti poistoon kaikki
    //std::cout << "\nT�h�n joku juttu koita vaikka aa: " << std::endl;       
    //std::cin >> testi;
    //switch (testi)                                                          // poista t�m� koko switch case testi
    //{
    //case 'a':
    //    std::cout << "se oli A" << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(2));               // Poista n�m� sleepit ja <chrono> jos ei k�ytet�.
    //    break;
    //case 'b':
    //    std::cout << "se oli B" << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(2));
    //    break;
    //default:
    //    std::cout << "se oli joku muu kuin a tai b" << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(2));
    //    break;
    //}
    return normi.getName();
}

bool mapping::checkForEnemy(int locy, int locx)
{
    std::pair<int, int> verrokki = std::make_pair(locy, locx);              // tehd��n verrokki muuttuja jonka arvot otetaan muuttujista locy & locx (eli miss� pelaaja on)
    bool hit = enemyCoords.find(verrokki) != enemyCoords.end();             // Jos find palauttaa NOT .end() on arvo TRUE, silloin find on osunut eik� palauta endi�.
    enemyCoords.erase(verrokki);                                            // poistaa setist� ko. arvoparin.
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

void mapping::printKillStats()
{
    std::cout << "T�ss� kartassa tuhosit: \n" << std::endl;
    for (int i = 0; i < enemyKillName.size(); i++)
    {
        std::cout << enemyKillName[i] << std::endl;
        enemyKills[enemyKillName[i]]++;
    }
    enemyKillName.clear();                              // tarvii tehd� "kaikki tuhotut" omanaan pelin lopuksi.
    std::cout << "kaikki tuhotut: \n" << std::endl;
    for (auto j : enemyKills)
    {
        std::cout << j.first << " " << j.second << std::endl;
    }
}

bool mapping::checkMap()                                // jotta toimii if-lauseessa oletuksena palautetaan true eli haussa ei l�ydy '#' merkki� ja if toteutuu,
{                                                       // jos haku t�rpp�� eli vektoreista l�ytyy '#' niin palautetaan false jolloin if ei toteudu.
    char target = '#';                                  
    bool mapHit = true;
    for (const std::vector<char>& row : playMap)
    {
        //mapHit = std::find(row.begin(), row.end(), target) == row.end(); t�m� ei toimi loopissa
        
        if (std::find(row.begin(), row.end(), target) != row.end())
        {
            mapHit = false;
            break;
        }
    }
    return mapHit;
}