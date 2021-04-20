#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

/* ROMAN BITAROVSKY
    VISUAL STUDIO 2019
        SEMAP zadanie 3 */

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* vracia dlzku LCS pre 'vstup'
 LCS ako Longest Common Subsequence Problem */
int lcs(char* vstup, char* opak, int dlzka, int dlzka_n) {
    dlzka_n += 1;
    int** pole;
    pole = (int**)malloc(dlzka_n * sizeof(int*)); //tu si urobím riadky
    for (int i = 0; i < dlzka_n; i++) { //tu prechádzam riadkami aby som do nich mohol robi ståpce
        pole[i] = (int*)malloc(dlzka_n * sizeof(int)); //tu do každého riadku vytvorím stlpce
    }

    /* ideme cez 'pole' kt. obsahuje dlzku LCS 'vstup' */
    for (int index = 0; index <= dlzka; index++) {
        for (int index2 = 0; index2 <= dlzka_n; index2++) { 
            if (index == 0 || index2 == 0) //nastavenie pociatocnych hodnot na nulu
                pole[index][index2] = 0;

            else if (vstup[index - 1] == opak[index2 - 1]) //ak sa hodnoty rovnaju
                pole[index][index2] = pole[index - 1][index2 - 1] + 1; //hodnota pre dany index sa zvysi o 1 a ak su rozdieli tak vieme vycitat kolko znakov sa najviac rovna

            else
                pole[index][index2] = max(pole[index - 1][index2], pole[index][index2 - 1]); //zistenie kde je najdlhsia postupnost
        }
    }

    /* 'pole' obsahuje pocet zhodnych znakov */
    return pole[dlzka][dlzka_n];
}

// funkcia zalozena na LCS na najdenie minimalneho poctu zmien
int najdi_zmenuLCS(char vstup[], int dlzka) {
    // urobime pole kt. bude opakom 'vstup' takze ho pomenujem 'opak'
    char* opak = 0;
    opak = (char*)malloc((dlzka + 1) * sizeof(char));
    strcpy(opak, vstup);
    _strrev(opak);
    // vystup je dlzka minus LCS vstupu
    return (dlzka - lcs(vstup, opak, dlzka, dlzka));
}

int main() {
    char vstup[1001];
    while (scanf("%s", vstup) > 0) {
        printf("%d\n", najdi_zmenuLCS(vstup, strlen(vstup)));
    }
    return 0;
}
