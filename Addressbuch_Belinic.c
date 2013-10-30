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
#include <string.h>


/* Defines */
#define my_free_p(pp) free(pp);pp=NULL
#define my_free_a(pa) free(pa);pa=NULL


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
void loeschen(person*, address*, int, int);


/* main-Methode */
int main (int argsc, char** argv)
{
	char antwort[] = {' '};
	char funktion[] = {' '};
	static int anzahl = 0;
	int zuloeschen = 0;
	int speichern = 0;

	person* pp = NULL;
	pp = (person*) malloc(sizeof(person));
	address* pa = NULL;
	pa = (address*) malloc(sizeof(address));
	if(pp == NULL || pa == NULL) { printf("Nu such Memory left!"); return EXIT_FAILURE; }



	while(antwort[0] != 'n') {
		if(anzahl == 0)
		{
			printf("Wollen Sie eine Person zum Adressbuch hinzufuegen? (y/n)\n");

		}
		else if(anzahl > 0)
		{
			printf("Wollen Sie eine Person zum Adressbuch hinzufuegen oder loeschen? (y/n)\n");
		}
		scanf("%s", antwort);
		if(antwort[0] == 'y') {
			//printf("Das ist eine gueltige Eingabe!\n");

			if(anzahl == 0)
			{
				anzahl++;
				hinzufuegen(pp,pa,anzahl); //hinzufuegen
				ausgabe(pp,pa,anzahl);

			}
			else if(anzahl > 0)
			{
				funktion[0] = ' ';
				while(funktion[0] != 'h' && funktion[0] != 'l')  {
					printf("Hinzufuegen oder loeschen? (h/l)\n");
					scanf("%s", funktion);
					switch(funktion[0])
					{
						case 'h': speichern = anzahl+1;
								  //my_free_p(pp);
								  pp = (person*) realloc(pp,speichern * sizeof(person));
								  //my_free_a(pa);
								  pa = (address*) realloc(pa,speichern * sizeof(address));
								  ++anzahl;
								  hinzufuegen(pp,pa,anzahl);//hinzufuegen
								  ausgabe(pp,pa,anzahl);
								  break;
						case 'l': speichern = anzahl-1;
								  ausgabe(pp,pa,anzahl);
								  scanf("%i", &zuloeschen);
								  loeschen(pp,pa,anzahl,zuloeschen);
								  --anzahl;
								  pp = (person*) realloc(pp, anzahl * sizeof(person));
								  //my_free_p(pp);
								  pa = (address*) realloc(pa, anzahl * sizeof(address));
								  //my_free_a(pa);
								  ausgabe(pp,pa,anzahl);
								  break;
						default: printf("Das ist KEINE gueltige Eingabe!\n");
								 break;
					}
					fseek(stdin, 0, SEEK_SET);
				}
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
	scanf("%s", ((p1+anzahl-1)->vname));
	printf("Nachname: ");
	scanf("%s", ((p1+anzahl-1)->nname));
	printf("Strasse: ");
	scanf("%s", ((p2+anzahl-1)->str));
	printf("Strassennummer: ");
	scanf("%u", &((p2+anzahl-1)->strnr));
	printf("Postleitzahl: ");
	scanf("%u", &((p2+anzahl-1)->plz));
	printf("Ort: ");
	scanf("%s", ((p2+anzahl-1)->ort));
	fseek(stdin, 0, SEEK_SET);
}

void loeschen(person* p1, address* p2, int anzahl, int index)
{
	int i = 0;
	int k = 0;
	while(i < anzahl) {
		if(strcmp((p1+i)->vname, (p1+index)->vname) == 0 &&
			strcmp((p1+i)->nname, (p1+index)->nname) == 0 &&
			strcmp((p2+i)->str, (p2+index)->str) == 0 &&
			(p2+i)->strnr == (p2+index)->strnr &&
			(p2+i)->plz == (p2+index)->plz &&
			strcmp((p2+i)->ort, (p2+index)->ort) == 0)
		{
			k = i;
			while(k < anzahl-1) {
				strcpy((p1+k)->vname,(p1+k+1)->vname);
				strcpy((p1+k)->nname, (p1+k+1)->nname);
				strcpy((p2+k)->str, (p2+k+1)->str);
				(p2+k)->strnr = (p2+k+1)->strnr;
				(p2+k)->plz = (p2+k+1)->plz;
				strcpy((p2+k)->ort, (p2+k+1)->ort);
				k++;
			}
		}
		i++;
	}
}
