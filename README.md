# cppv0

Käyttäjältä pyydetään nimi, jonka jälkeen käyttäjältä pyydetään X ja Y koordinaatit
jotka määrittelevät peli kartan koon.

pelaaja liikkuu kartalla käyttäen w,a,s,d näppäimiä.

pelaajan damage lasketaan: plr.attack() + rand() % 10 + 1 
eli esim. 5 lisätään 0-10 = damage.

parry toimii automaattisesti.
esim. pelaajan parry = 3 -> vihollinen lyö 0,1,2,3 niin et ota damagea.

kartan päätteeksi jos voitat bossin,
pelaaja saa palkinnoksi valintansa mukaisesti lisää joko max health arvoa, attackia tai parryä.

pelaajan health asetetaan täyteen boss taistelun jälkeen.

bossit skaalautuvat läpäistyjen karttojen määrän mukaisesti.
joka boss taistelun jälkeen: scaleValue += 2;

bossin statit ovat:
Health = (rand() % 6 + (5+scaleValue)) * 10;
Attack = Health / 10 / 2 + (1+scaleValue);
Exp = Health / 10;

eli aluksi health on joku tasakymmen arvoasteikolla 50-100. kun yhden kartan läpäisee arvoasteikko muuttuu 70-120.
ja tästä arvosta lasketaan myös bossin damage ja sen antama xp

eli esimerkkinä kahden kartan jälkeen bossin statit:
health: 90-140 (tasakymmen)
attack: 14-17 tasaluvuin. (tässä todennäköisimmät vaihtoehdot ovat 15 tai 16 (molemmissa todennäköisyys on 2/6) koska mitään ei pyöristetä. suoraan intiksi.
exp: 9-14 tasaluvuin

pelin normi vihut eivät skaalaudu:
Health = (rand() % 5 + 1) * 10;
Attack = Health / 10 / 2;
Exp = Health / 10;

lopuksi peli tallentaa pelaajan nimen ja xpn csv tiedostoon "statistics.csv"


xp:n eli pisteiden maksimoimiseksi onko parempi selvittää useampi pieni kartta vai vähemmän isoja karttoja?
