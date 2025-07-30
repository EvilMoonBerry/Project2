# Käyttöjärjestelmä ja systeemiohjelmointi projekti 2: Unix Utilities
## Tämän tehtävän tarkoitus on tehdä useampi pieni ohjelma jotka matkivat UNIX:sta tuttuja toimintoja

Pohjustus:
```
gcc -o my-cat my-cat.c -Wall -Werror
gcc -o my-grep my-grep.c -Wall -Werror
gcc -o my-zip my-zip.c -Wall -Werror
gcc -o my-unzip my-unzip.c -Wall -Werror

```
My-cat: Tulostaa kättäjän antamat tiedstot sisällön suoraan käyttäjälle.
```
./my-cat input.txt input2.txt...
```

My-grep: Etsii annetuista tiedostoista käyttäjän antamaa sanaa ja tulostaatälle kaikki rivit missä sana ilmenee.
```
my-grep: searchterm input.txt input2.txt
```

My-zip: Muutta annettujen tiedostojen sisällön nelitavuisen kokonaisluvun binäärimuotoon jota seuraa Ascii muotoinen yksittäinen merkki ja kirjoittaa tämän toiseen tiedostoon. Näin toivottavasti pienentäen tiedsoton kokoa.
```
./my-zip input.txt input2.txt > testzip.z
```

My-unzip: Muuttaa annettujen tiedostojen nelitavuisen kokonaisluvun binäärimuotoon jota seuraa ASCII merkki takaisin normaalliin tekstimuotoon ja tulostaa tämän tekstin suoraan käyttäjälle. 
```
./my-unzip testzip.z
```
