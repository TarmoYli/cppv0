#include "Player.h"
#include "enemy.h"
#include "mapping.h"
#include "csv.h"

std::mutex mtx;
std::condition_variable cond;

mapping::mapping() {};

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
    int Amount = round(sqrt(yForMap * xForMap));                                    // vihollisten m‰‰r‰
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
        std::cout << "liiku w,a,s,d. paina enter aloittaaksesi ('q' lopettaa ohjelman):";
        ch = _getch();                                                  // ennen getchi‰ ehk‰ printtaa kartan?
        {
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [&] { return !inputReady; });               // odottaa ett‰ inputready on false
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
                if (locy >= playMap.size() - 1)                         //n‰it‰ ei varmaan saa funktioitua kun tarvii varmistaa
                    locy = playMap.size() - 1;                          //ettei mene vektorit out-of-boundsiin.
                playMap[locy][locx] = 'O';                              //jokaisessa iffiss‰ muuttujien k‰sittely liev‰sti erilaista
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
            else if (ch == 'q')                                         // Q lopettaa loopin -> ohjelman
            {
                isRunning = false;
            }
            inputReady = true;
        }
        cond.notify_one();
    }
    return playMap;
}

void mapping::printPlayMap(Player& plr)
{
    
    while (isRunning)
    {    
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [&] { return inputReady; });
        system("cls");
        playMap[locy][locx] = 'X';                                         // ei tallenna 'X' mihink‰‰n
        printMap(playMap);
        std::cout << "y-akseli: " << locy << "\nx-akseli: " << locx << std::endl;
        std::cout << "tapot yht: " << counter << std::endl;
        if (checkForEnemy(locy,locx))
        {
            //system("cls");                                                //joko n‰m‰ system(cls) jutut taitaa aiheuttaa h‰mminki‰
            enemyKillCoords.push_back(std::make_pair(locy,locx));
            enemyKillName.push_back(combat(plr));
            counter += 1;
            //system("cls");
            //printMap(playMap);
            //std::cout << "y-akseli: " << locy << "\nx-akseli: " << locx << std::endl;
            //std::cout << "tapot yht: " << counter << std::endl;
        }
        if (checkMap())
        {
            std::cout << "kartta l‰p‰isty." << std::endl;
            printKillStats();
            std::cout << "uusi kartta" << std::endl;
            locx = 0;
            locy = 0;
            mapSize();
        }
        inputReady = false;
    }
    cond.notify_one();
}

std::string mapping::combat(Player& plr)
{
    std::cout << "taistelu!" << std::endl;
    enemy tier_1 = enemy(csv::getEnemyName(), 0, 0, "hauhauhau", 0);
    tier_1.makeStats();
    std::cout << "\nNimi: " << tier_1.getName() << "\nhealth: " << tier_1.getHealth() << "\nattack: " << tier_1.getAttack() << "\nXP value: " << tier_1.getExp() << std::endl;
    tier_1.huuto();
    int plrAttackValue = plr.getAttack();
    int enemyAttackValue = tier_1.getAttack();
    do
    {
        int plrHitvalue = plrAttackValue + rand() % 10+1;
        std::cout << plr.getName() << " lyˆ: " << plrHitvalue << std::endl;
        int newEnemyHealthValue = tier_1.getHealth() - plrHitvalue;
        tier_1.setHealth(newEnemyHealthValue);
        std::cout << tier_1.getName() << " el‰m‰‰ j‰ljell‰: "<< tier_1.getHealth() << std::endl;
        std::cin.get();
        if (tier_1.getHealth() <= 0)
        {
            std::cout << tier_1.getName() << " voitettu! GG!" << std::endl;
            int xpIncrease = plr.getExp() + tier_1.getExp();
            plr.setExp(xpIncrease);

            break;
        }
        int enemyHitValue = enemyAttackValue += rand() % 6+1;
        std::cout << tier_1.getName() << " lyˆ: " << enemyHitValue << std::endl;
        int newPlrHealthValue = plr.getHealth() - enemyHitValue;
        plr.setHealth(newPlrHealthValue);
        std::cout << plr.getName() << " el‰m‰‰ j‰ljell‰ " << plr.getHealth() << std::endl;
        std::cin.get();
        if (plr.getHealth() <= 0)
        {
            std::cout << tier_1.getName() << " Tappoi sinut!" << std::endl;
            std::cout << plr.getName() << " Kuoli!" << " XP: " << plr.getExp() << "\nGame Over Bro!" << std::endl;
            isRunning = false;
        }

    } while (plr.getHealth() > 0 && tier_1.getHealth() > 0);


    return tier_1.getName();
}

bool mapping::checkForEnemy(int locy, int locx)
{
    std::pair<int, int> verrokki = std::make_pair(locy, locx);              // tehd‰‰n verrokki muuttuja jonka arvot otetaan muuttujista locy & locx (eli miss‰ pelaaja on)
    bool hit = enemyCoords.find(verrokki) != enemyCoords.end();             // Jos find palauttaa NOT .end() on arvo TRUE, silloin find on osunut eik‰ palauta endi‰.
    enemyCoords.erase(verrokki);                                            // poistaa setist‰ ko. arvoparin.
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
    std::cout << "T‰ss‰ kartassa tuhosit: \n" << std::endl;
    for (int i = 0; i < enemyKillName.size(); i++)
    {
        std::cout << enemyKillName[i] << std::endl;
        enemyKillCounter[enemyKillName[i]]++;
    }
    enemyKillName.clear();                              // tarvinee tehd‰ "kaikki tuhotut" omanaan pelin lopuksi.
    std::cout << "kaikki tuhotut: \n" << std::endl;
    for (auto j : enemyKillCounter)
    {
        std::cout << j.first << " " << j.second << std::endl;
    }
}

bool mapping::checkMap()                                // jotta toimii if-lauseessa oletuksena palautetaan true eli haussa ei lˆydy '#' merkki‰ ja if toteutuu,
{                                                       // jos haku t‰rpp‰‰ eli vektoreista lˆytyy '#' niin palautetaan false jolloin if ei toteudu.
    char target = '#';                                  
    bool mapHit = true;
    for (const std::vector<char>& row : playMap)
    {
        //mapHit = std::find(row.begin(), row.end(), target) == row.end();  <-- t‰m‰ ei toimi t‰ss‰ loopissa tarvittavalla tavalla
        
        if (std::find(row.begin(), row.end(), target) != row.end())     // t‰t‰ ei saa suoraviivaistettua laittamalla
        {                                                               // maphit = false; == row.end(); maphit = true;
            mapHit = false;                                             // t‰m‰ on luultavasti ainut keino t‰ss‰tapauksessa saada t‰m‰ oikein.
            break;
        }
    }
    return mapHit;
}
