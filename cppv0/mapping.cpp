#include "Player.h"
#include "enemy.h"
#include "enemyBoss.h"
#include "mapping.h"
#include "csv.h"

std::mutex mtx;
std::condition_variable cond;
                                                                                    // HUOM! jos viimeisess‰ ruudussa on taistelu ja jos sen h‰vi‰‰,
                                                                                    // peli pyyt‰‰ k‰ytt‰j‰lt‰ viel‰ koordeja uuden kartan tekoon.
                                                                                    // eli Fix It! joskus. ehk‰.
mapping::mapping() {};

void mapping::mapSize()
{
    setlocale(LC_ALL, "fi-FI");
    std::string xInput, yInput;
    for (;;) {
        std::cout << "Anna x akselin pituus: ";
        std::cin >> xInput;

        if (csv::checkInput(xInput)) {
            xForMap = std::stoi(xInput);
            break;
        }
        else {
            std::cout << "V‰‰r‰ syˆte. Anna kokonaisluku." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    for (;;) {
        std::cout << "Anna y akselin pituus: ";
        std::cin >> yInput;

        if (csv::checkInput(yInput)) {
            yForMap = std::stoi(yInput);
            break;
        }
        else {
            std::cout << "V‰‰r‰ syˆte. Anna kokonaisluku." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

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
            //system("cls");                                                //n‰m‰ system(cls) jutut saattavat aiheuttaa h‰mminki‰
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
            std::cout << "kartta l‰p‰isty. kartan loppu taistelu: " << std::endl;
            enemyKillName.push_back(bossFight(plr));
            if (plr.getHealth() > 0)
            {
                bossScaling += 2;
                printKillStats();
                std::cout << "uusi kartta" << std::endl;
                locx = 0;
                locy = 0;
                mapSize();
            }
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
        int plrHitvalue = plrAttackValue + rand() % 10+1;                                               // pelaaja lyˆ vihua
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
        int enemyHitValue = enemyAttackValue + rand() % 6+1;                                                                                               // vihu lyˆ pelaajaa
        std::cout << tier_1.getName() << " lyˆ: " << enemyHitValue << std::endl;
        if (plr.getParry() >= enemyHitValue) { std::cout << "Torjuit iskun kokonaan!"<< std::endl; enemyHitValue = 0; }                                    // if-else parryn laskemiseen
        else {
            int newPlrHealthValue = plr.getHealth() - (enemyHitValue - plr.getParry());
            plr.setHealth(newPlrHealthValue);
        }
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
    for (int i = 0; i < playMap[0].size()+2; i++)
    {
        std::cout << "* ";
    }
    std::cout << std::endl;
    for (const std::vector<char>& row : playMap)
    {
        std::cout << "* ";
        for (char item : row)
        {
            std::cout << item << " ";
        }
        std::cout << "*";
        std::cout << std::endl;
    }
    for (int i = 0; i < playMap[0].size()+2; i++)
    {
        std::cout << "* ";
    }
    std::cout << std::endl;
}

void mapping::printKillStats()
{
    std::cout << "T‰ss‰ kartassa vastukset olivat: \n" << std::endl;
    for (int i = 0; i < enemyKillName.size(); i++)
    {
        std::cout << enemyKillName[i] << std::endl;
        enemyKillCounter[enemyKillName[i]]++;
    }
    enemyKillName.clear();                              // tarvinee tehd‰ "kaikki tuhotut" omanaan pelin lopuksi.
    std::cout << "kaikki vastukset: \n" << std::endl;
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

std::string mapping::bossFight(Player& plr)
{
    enemyBoss bous = enemyBoss(csv::getEnemyName(), 0, 0, "HUAAAHUAHUA", 0);
    bous.makeStats(bossScaling);
    std::cout << "\nNimi: " << bous.getName() << "\nhealth: " << bous.getHealth() << "\nattack: " << bous.getAttack() << "\nXP value: " << bous.getExp() << std::endl;
    bous.huuto();
    int plrAttackValue = plr.getAttack();                                                           // n‰m‰ muuttujat
    int enemyAttackValue = bous.getAttack();                                                        // ovat turhia.
    do                                                                                              // koska voin suoraan k‰ytt‰‰ getAttack():ia. tyyliin:
    {                                                                                               // "int plrHitvalue = plr.getAttack() + rand() % 10 + 1;"
        int plrHitvalue = plrAttackValue + rand() % 10 + 1;
        std::cout << plr.getName() << " lyˆ: " << plrHitvalue << std::endl;
        int newEnemyHealthValue = bous.getHealth() - plrHitvalue;
        bous.setHealth(newEnemyHealthValue);
        std::cout << bous.getName() << " el‰m‰‰ j‰ljell‰: " << bous.getHealth() << std::endl;
        std::cin.get();
        if (bous.getHealth() <= 0)
        {
            std::cout << bous.getName() << " voitettu! GG!" << std::endl;
            std::cout << "sait " << bous.getExp() << "XP" << std::endl;
            int xpIncrease = plr.getExp() + bous.getExp();
            plr.setExp(xpIncrease);
            bossRewards(plr);
            plr.setHealth(plr.getInitHealth());
            std::cout << "Hahmon HP t‰ynn‰." << std::endl;
            std::cin.get();
            break;
        }
        int enemyHitValue = enemyAttackValue + rand() % 6 + 1;                                                                                                 // boussi lyˆ pelaajaa
        std::cout << bous.getName() << " lyˆ: " << enemyHitValue << std::endl;
        if (plr.getParry() >= enemyHitValue) { std::cout << "Torjuit iskun kokonaan!" << std::endl; enemyHitValue = 0; }                                       // if-else parryn laskemiseen... if lauseen bodyss‰ ehv=0 on aikalailla turha.
        else {
            int newPlrHealthValue = plr.getHealth() - (enemyHitValue - plr.getParry());
            plr.setHealth(newPlrHealthValue);
        }
        std::cout << plr.getName() << " el‰m‰‰ j‰ljell‰ " << plr.getHealth() << std::endl;
        std::cin.get();
        if (plr.getHealth() <= 0)
        {
            std::cout << bous.getName() << " Tappoi sinut!" << std::endl;
            std::cout << plr.getName() << " Kuoli!" << " XP: " << plr.getExp() << "\nGame Over Bro!" << std::endl;
            isRunning = false;
        }
    } while (plr.getHealth() > 0 && bous.getHealth() > 0);
    return bous.getName();
}

void mapping::bossRewards(Player& plr)
{
    int rewardInput = 0;
    int addParry;
    int addAttack;
    int addHealth;
    plr.showStatus();
    do
    {
        std::cout << "valitse palkinto: " << "\n1. parry +1 \n2. attack +2 \n3. max health +15" << std::endl;
        std::string choiceInput;
        std::cin >> choiceInput;
        if (csv::checkInput(choiceInput))
        {
            rewardInput = std::stoi(choiceInput);

            switch (rewardInput)
            {
            case 1:
                addParry = plr.getParry() + 1;
                plr.setParry(addParry);
                std::cout << "parry arvo nyt: " << plr.getParry() << std::endl;
                break;
            case 2:
                addAttack = plr.getAttack() + 2;
                plr.setAttack(addAttack);
                std::cout << "attack arvo nyt: " << plr.getAttack() << std::endl;
                break;
            case 3:
                addHealth = plr.getInitHealth() + 15;
                plr.setInitHealth(addHealth);
                std::cout << "maxHealth arvo nyt: " << plr.getInitHealth() << std::endl;
                break;
            default:
                std::cout << "Anna kokonaisluku v‰lill‰ 1-3" << std::endl;
            }
        }
        else
        {
            std::cout << "v‰‰r‰ syˆte. anna kokonaisluku v‰lill‰ 1-3" << std::endl;
        }
    } while (rewardInput != 1 && rewardInput != 2 && rewardInput != 3);
}