#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ROMAN BITAROVSKY
    VISUAL STUDIO 2019
        SEMAP zadanie 2 */

int isPalindrome(char str[]){ //funkcia zisti ci zadany string je palindrom
    int index = 0;
    int dlzka = strlen(str)-1;
    while (dlzka > index)
        if (str[index++] != str[dlzka--])
            return 0;
    return 1;
}

int najdi_najdlhsi_palin(char text[], char slovo[], char najdhlsi_pal[]) {

    int len = strlen(text);
    int naj = 0;
    char medzera[2] = {0};
    medzera[0] = ' '; //pole s medzerou kt. sa bude vklada ak bude viac palindromov s rovnakou dlzkou
    medzera[1] = '\0';

    for (int index = 0; index <= len; index++) { //index ide od zaciatku postupne po kazdom pismenku v stringu
        for (int index2 = index; index2 <= len; index2++) { //druhy index hlada pismenko zhodne k tomu prvemu
            if (text[index] == text[index2]) { //ake sa prve a posledne pismena zhosuju je to kandidat na palindrom
                for (int i = index; i <= index2; i++) {
                    slovo[i - index] = text[i]; //do pola slovo sa da kandidat na palindrom
                }
                if (isPalindrome(slovo)) {
                    if ( strlen(slovo) == naj ) { //ak sa najdeny palindrom a ma rovnaku dlzku ako najdlhsi najdeny
                        strcat(najdhlsi_pal, medzera); //prida sa medzera
                        strcat(najdhlsi_pal, slovo); //a daju sa do jedneho pola
                    }
                    else if(strlen(slovo) > naj){ //ak je najdeny palindrom dlhsi ako dovtedy najdlhsi
                        strcpy(najdhlsi_pal, slovo); //prepise palindromy predtym
                        naj = strlen(najdhlsi_pal); //jeho dlzka sa ulozi
                    }
                }
                for (int i = 0; i < 500; i++) { //vyprazdni pole slovo
                    slovo[i] = NULL;
                }        
            }
        }
    }
    return naj;
}

int main() {
    char text[501] = {0};
    char slovo[500] = { 0 };
    char najdhlsi_pal[501] = { 0 };
    while(scanf("%s", text)>0){ //kym su vstupy tak ich scanuj
        int dlzka = najdi_najdlhsi_palin(text, slovo, najdhlsi_pal); //najdi najdlhsi palinrom a vrati jeho dlzku
        printf("%d %s\n", dlzka, najdhlsi_pal); //vypise najdlhsi palinrom aj s jeho dlzkou 
    }
    return 0;
}
