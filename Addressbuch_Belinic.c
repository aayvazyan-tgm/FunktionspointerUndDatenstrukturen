/*
  Name			: Addressbuch_Belinic.c
  Author		: Vennesa Belinic
  Version		: 2013-10-22
  Description	: Stellt ein einfaches Adressbuch da. Es werden zwei Structs (PERSON, ADDRESS)
   	   	   	   	  verwenden um die notwendigen Informationen abzulegen. Die Ein- und Ausgabe
   	   	   	   	  erfolgt über ein einfaches CLI-Menue. Fuer die einzelnen Funktionalitaeten
   	   	   	   	  werden auch entsprechende Funktionen verwendet, welche mittels call-by-reference
   	   	   	   	  implementiert sind.
 */


/* Verwendete Header */
#include <stdio.h>
#include <stdlib.h>


/* Defines */
//#define my_free_p(pp) free(pp);pp=NULL
//#define my_free_a(pa) free(pa);pa=NULL


/* Eigene "Datentypen" */
typedef struct
{
	char vname[50];
	char nname[50];
}person;

typedef struct
{
	char str[50];
	int strnr;
	int plz;
	char ort[50];
}address;


/* Prototypen */
void ausgabe(person*, address*, int);
void hinzufuegen(person*, address*, int);


/* main-Methode */
int main (int argsc, char** argv)
{
	char antwort[] = {' '};
	static int anzahl = 0;
	int speichern = 0;

	person* pp = NULL;
	pp = (person*) malloc(sizeof(person));
	address* pa = NULL;
	pa = (address*) malloc(sizeof(address));
	if(pp == NULL || pa == NULL) { printf("Nu such Memory left!"); return EXIT_FAILURE; }



	while(antwort[0] != 'n') {
		printf("Wollen Sie eine Person zum Adressbuch hinzufuegen? (y/n)\n");
		scanf("%s", antwort);
		if(antwort[0] == 'y') {
			if(anzahl == 0) {
				++anzahl;
				hinzufuegen(pp,pa,anzahl);//hinzufuegen
				ausgabe(pp,pa,anzahl);
			}
			else if(anzahl > 0) {
				speichern = anzahl+1;
				//my_free_p(pp);
				pp = (person*) realloc(pp,speichern * sizeof(person));
				//y
				my_free_a(pa);
				pa = (address*) realloc(pa,speichern * sizeof(address));
				++anzahl;
				hinzufuegen(pp,pa,anzahl);//hinzufuegen
				ausgabe(pp,pa,anzahl);
			}

		} else if(antwort[0] != 'n') {
			printf("Das ist keine gueltige Eingabe!\n");
		} else { goto RAUS; }
		fseek(stdin, 0, SEEK_SET);
		//printf("\n%i\n", anzahl);
	}


	RAUS: return EXIT_SUCCESS;
}


void ausgabe(person* p1, address* p2, int anzahl)
{
	int i = 0;
	while(i < anzahl) {
		printf("%i  Person: %s %s, Address: %s %i, %i %s\n", i,
				(p1+i)->vname, (p1+i)->nname, (p2+i)->str,
				(p2+i)->strnr, (p2+i)->plz, (p2+i)->ort);
		i++;
	}
}

void hinzufuegen(person* p1, address* p2, int anzahl)
{
	printf("Vorname: ");
	scanf("%s", (p1+anzahl-1)->vname);
	printf("Nachname: ");
	scanf("%s", (p1+anzahl-1)->nname);
	printf("Strasse: ");
	scanf("%s", (p2+anzahl-1)->str);
	printf("Strassennummer: ");
	scanf("%i", &((p2+anzahl-1)->strnr));
	printf("Postleitzahl: ");
	scanf("%i", &((p2+anzahl-1)->plz));
	printf("Ort: ");
	scanf("%s", (p2+anzahl-1)->ort);
	fseek(stdin, 0, SEEK_SET);
}
