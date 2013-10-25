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


/* Eigene "Datentypen" */
typedef struct
{
	char vname[50];
	char nname[50];
}person;

typedef struct
{
	char str[100];
	unsigned int strnr;
	unsigned int plz;
}address;


/* Prototypen */
void ausgabe(person*, address*);
void hinzufuegen(person*, address*, int);
void loeschen(person*, address*, int);


/* main-Methode */
int main (int argsc, char** argv)
{
	char antwort[] = {' '};
	char funktion[] = {' '};
	static int anzahl = 0;


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
			printf("Das ist eine gueltige Eingabe!\n");

			if(anzahl == 0)
			{
				//hinzufuegen
				anzahl++;

			}
			else if(anzahl > 0)
			{
				funktion[0] = ' ';
				while(funktion[0] != 'h' && funktion[0] != 'l')  {
					printf("Hinzufuegen oder loeschen? (h/l)\n");
					scanf("%s", funktion);
					switch(funktion[0])
					{
						case 'h': //hinzufuegen
								  anzahl++;
								  break;
						case 'l': //loeschen
								  anzahl--;
								  break;
						default: printf("Das ist eine gueltige Eingabe!\n");
								 break;
					}
					fseek(stdin, 0, SEEK_SET);
				}
			}

		} else if(antwort[0] != 'n') {
			printf("Das ist keine gueltige Eingabe!\n");
		} else { goto RAUS; }
		fseek(stdin, 0, SEEK_SET);
		printf("\n%i\n", anzahl);
	}


	RAUS: return EXIT_SUCCESS;
}


void ausgabe(person* p1, address* p2)
{

}

void hinzufuegen(person* p1, address* p2, int index)
{

}

void loeschen(person* p1, address* p2, int index)
{

}
