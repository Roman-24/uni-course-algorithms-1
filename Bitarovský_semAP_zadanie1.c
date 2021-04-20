//Roman Bitarovskı
//Microsoft Visual Studio 2019
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

	char vojaci[1000] = {}, znak = 0;
	int pocet_mesiacov[1000] = {}, index_vstup = 0;

	//naèítanie vstupu
	while ( (znak = getchar()) != '\n' ) {
		if ( (isupper(znak))==1 ) { //naèítanie ve¾kého písmenka
			vojaci[index_vstup] = znak; //priradenie vojaka do pola s druhom vojakov
			scanf("%d", &pocet_mesiacov[index_vstup]); //naèítanie poètu skúsenosti k príslušnému vojakovi

			if (pocet_mesiacov[index_vstup] < 0 ) { //ošetrenie zápornej hodnoty
				printf("Neplatny vstup: zaporna hodnota \n");
				return 0;
			}
			else { index_vstup++; }
		}	
	}
	
	int dlzka = strlen(vojaci); //zistenie dlky pola, obe polia sú vdy rovnako dlhé

	int vymena = 0; //nasleduj dva loopy na prechádzanie poliami a podmienky kedy sa majú prehodi hodnoty
	for( int index1=0; index1 <dlzka-1; index1++ )

		for( int index2= index1 +1; index2<dlzka; index2++ ) {

			if ( pocet_mesiacov[index1] > pocet_mesiacov[index2] ) { //zistenie èi má nasta vımena vojakov

				if ( vojaci[index2] == vojaci[index1] ) { //hodnoty sa vymeniaa iba v prípade e akú na oboch miestach rovnakı vojaci
					vymena = pocet_mesiacov[index1]; //uloenie do premennej
					pocet_mesiacov[index1] = pocet_mesiacov[index2]; //pridelenie druhej hodnoty
					pocet_mesiacov[index2] = vymena; //pridelenie druhej hodnoty z druhého po¾a pomocou premennej
				}
			}
		}

	int index_vypis = 0;
	while (index_vypis != dlzka) { //vypísanie vıstupu na obrazovku cez jeden index z oboch arrays kede údaje z rovnakého indexu vdy patria jednému vojakovi
		printf("%c%d ", vojaci[index_vypis], pocet_mesiacov[index_vypis]);
		index_vypis++;
	}

	return 0;
}