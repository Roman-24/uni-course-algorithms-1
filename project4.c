#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

void swap(char* x, char* y) { //funkcia na vymenenie dvoch prvkov
    int temp = *x;
    *x = *y;
    *y = temp;
}

int tsp(char* cesta, int rozmer, int** mesto, int *sucet) { //funcia prejde po domcekoch podla aktualnej permutacie cesty

    int nesucet = 0, riadok = 0;
    for (riadok = 0; riadok < rozmer; riadok++) { //prechádzanie riadkami
        nesucet += mesto[cesta[riadok] - 'A'][cesta[riadok + 1] - 'A']; //postupne zvysovanie suctu aktualnej cesty
        if (nesucet > * sucet) //ak je aktualny hladany sucet uz vacsi ako zatial najmensi najdeny sucet
            return nesucet; //tak ukonci funkciu (pre lepsiu efektivitu) 
    }
    nesucet += mesto[cesta[riadok] - 'A'][0]; //pripocitanie hodnoty cesty domov z posledneho miesta
    return nesucet; //vratenie hodnoty cesty
}

void permute(char* cesta, int parameter, int rozmer, int** mesto, int* sucet) {

    if (parameter == rozmer) { //ak sa vytvorila nova permutacia
        int nesucet = tsp(cesta, rozmer, mesto, sucet); //volanie funkcie na prejdenie aktualnej vytvorenej cesty a zistenie jej suctu
        if (*sucet == 0 || nesucet < *sucet) { //ak je sucet novej cesty mensi ako doteraz objaveny najmensi sucet
            *sucet = nesucet; //ulozi sa novy najmensi sucet
        }
    }
    else {
        for (int i = parameter; i <= rozmer; i++) {
            swap((cesta + parameter), (cesta + i)); //swap
            permute(cesta, parameter + 1, rozmer, mesto, sucet); //rekurzivne volanie funkcie na permutacie
            swap((cesta + parameter), (cesta + i)); //backtrack
        }
    }
}

int uvod(int** mesto, int rozmer) {
    int sucet = 9999999;
    char* cesta = { NULL }; //vytvorenie pole kam sa budu uklada jednolive moznosti cesty

    if ((cesta = (char*)calloc(rozmer, sizeof(char))) == NULL) { //vytvorenie pola pre ukladanie cesticiek
        printf("nepodarilo sa pridelit pamat\n");
        exit(0);
    }

    for (int i = 0; i < rozmer; i++)
        cesta[i] = i + 'A'; //naplnenie pola pismenkami od A az po koniec podla rozmeru matice

    permute(cesta, 1, rozmer - 1, mesto, &sucet); //volanie funkcie na vytvorenie permutacii vsetkych moznych ciest

    if (cesta != NULL) //uvolnenie pamate cesta
        free(cesta);

    return sucet; //vratenie vysledku
}

int main() {

    int** mesto = { NULL }; //matica
    int* sucty = (int*)calloc(1, sizeof(int)); //pole pre finalne vysledky
    int pocet = 1, rozmer = 0;
    
    char znak, znak2;
    while(1) {

        scanf("%c", &znak); //oskenuj znak

        if ( isdigit(znak) ) { //ak je znak cislo

            scanf("%c", &znak2); //oskenuj znak za tym

            if (isdigit(znak2)) { //ak je aj druhy znak cislo
                rozmer = (znak - '0') * 10 + znak2 - '0'; //urob z dvoch cislic cislo
            }
            else {
                rozmer = znak - '0'; //ak bol iba prvy znak cislo tak sa vypocita rozmer iba z toho jedneho znaku
            }

            if (rozmer < 20 && rozmer > 0) { //ak je rozme matice mensi ako 20 a viac ako 0

                if((mesto = (int**)calloc(rozmer, sizeof(int*)))==NULL){ //alokuj riadky matice
                    printf("nepodarilo sa pridelit pamat\n");
                    exit(0);
                }

                for (int i = 0; i < rozmer; i++) { //prechadzaj riadkami
                    
                    if ((mesto[i] = (int*)calloc(rozmer, sizeof(int))) == NULL) { //alokuj stlpce matice
                        printf("nepodarilo sa pridelit pamat\n");
                        exit(0);
                    }
                }

                for (int riadok = 0; riadok < rozmer; riadok++) { //naskenovanie vstupnej natice
                    char znak;
                    for (int stlpec = 0; stlpec < rozmer; stlpec++) {
                        scanf("%d%c", &mesto[riadok][stlpec], &znak);
                    }
                }

                sucty[pocet - 1] = uvod(mesto, rozmer); //spustenie riesenia problemu a ulozenie vysledku do pola
                pocet++; //pocet vysledkov v poli
                sucty = (int*)realloc(sucty, pocet * sizeof(int)); //realoknutie pola pri každom novom vysledku
            }
            else {  //ak je rozmer matice nespravny tak koniec
                printf("Nespavny rozmer\n"); 
                return 0;
            }
        }
        else //ak sa nezadal rozmer matice ale nieco ine --> koniec skenu a budu sa vypisovat vysledky
            break;
    }

    for (int i = 0; i < pocet - 1; i++) //vypisanie pola s vysledkami
        printf("%d\n", sucty[i]);
    
    //uvolnenie pamate
    for (int i = 0; i < rozmer; i++)
        if(mesto[i]!=NULL)
            free(mesto[i]);
    free(mesto);
    free(sucty);

    return 0;
}
