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
#include "address.h"


/* main-Methode */
int main (int argsc, char** argv)
{
	//Alle Variablen die im Lauf der Main-Funktion benoetig werden
	char antwort[] = {' '};
	char funktion[] = {' '};
	static int anzahl = 0;
	int zuloeschen = 0;
	int speichern = 0;

	//Es wird ein Person-Pointer und ein Address-Pointer erstellt
	//die auch Vectoren sind, und auch so verwendet werden
	person* pp = NULL;
	pp = (person*) malloc(sizeof(person));	//hier wird dem Pointer/Vector die Groeße von einem Element gegeben
	address* pa = NULL;
	pa = (address*) malloc(sizeof(address));	//hier wird dem Pointer/Vector die Groeße von einem Element gegeben
	//wenn den Pointern kein Speicher zugewiesen werden kann,
	//ist keiner vorhanden, dies wird auch ausgegeben
	if(pp == NULL || pa == NULL) { printf("Kein Speicher verfuegbar!"); return EXIT_FAILURE; }



	while(antwort[0] != 'n') {	//dies wird solange widerholt bis der User ein 'n' eingibt
		if(anzahl == 0)
		{
			printf("Wollen Sie eine Person zum Adressbuch hinzufuegen? (y/n)\n");
			//Wenn keine Elemente vorhanden sind wird der User gefragt ob der eine Person
			//hinzfuegen will. Da keine Eintraege vorhanden sind, koennte er auch nichts loeschen.

		}
		else if(anzahl > 0)
		{
			printf("\nWollen Sie eine Person zum Adressbuch hinzufuegen oder loeschen? (y/n)\n");
			//Wenn die Anzahl groesser 0 ist wird er auch gefragt ob er Eintraege loeschen will.
		}
		scanf("%s", antwort);
		if(antwort[0] == 'y') {		//wenn der User 'y', also Yes eingibt

			//Hier wird wieder unterschieden ob der Vector leer ist oder schon Werte vorhanden sind
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
						case 'h':	speichern = anzahl+1;
									pp = (person*) realloc(pp,speichern * sizeof(person));
									pa = (address*) realloc(pa,speichern * sizeof(address));
									//vergroessert den Speicher um 1 Element, es haengt hinten Speicher an
									//in diesem Fall immer nur fuer ein weiteres Element
									++anzahl;
									hinzufuegen(pp,pa,anzahl); //hinzufuegen eines Elements
									ausgabe(pp,pa,anzahl);	//Ausgabe der aktuellen Elemente
									break;

						case 'l':	speichern = anzahl-1;
									ausgabe(pp,pa,anzahl);
									//es werden die Elemnete ausgegeben damit der User sich an
									//dem Index aussuchen kann welches Element er loeschen will
									printf("\nGeben Sie den Index an der geloescht werden soll!\n");
									scanf("%i", &zuloeschen);
									//wenn der Index gueltig ist wird der untere Code-Block ausgefuehrt
									if(zuloeschen >= 0 && zuloeschen < anzahl)
									{
										loeschen(pp,pa,anzahl,zuloeschen);
										--anzahl;
										pp = (person*) realloc(pp, anzahl * sizeof(person));
										pa = (address*) realloc(pa, anzahl * sizeof(address));
										//verkleinert den Vector um ein Element, gibt den Speicher des letzten
										//Elementes frei, somit wird es geloescht
									} else printf("\nKein gueltiger Index!\n\n");
									ausgabe(pp,pa,anzahl);
									break;

						default:	printf("Das ist keine gueltige Eingabe!\n");
									break;
					}
					fseek(stdin, 0, SEEK_SET);	//Standartinput wird auf den Anfang (0) gesetzt
				}
			}

		} else if(antwort[0] != 'n') {
			printf("Das ist keine gueltige Eingabe!\n");
		} else {
			my_free(pp);	//wenn der Benutzer 'n' eingibt, wird der Speicher
			my_free(pa);	//der beiden Pointer freigegeben
			goto RAUS;		//und das Programm beendet
		}
		fseek(stdin, 0, SEEK_SET);	//Standartinput wird auf den Anfang (0) gesetzt
	}


	RAUS: return EXIT_SUCCESS;
}



/* Funktionen */

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

/*
 * Die hinufuegen-Funktion, fuegt einen Eintrag in das Addressbuch hinzu,
 * mittels Eingaben des Users. Wenn dieser unguletig Werte eingibt, wird
 * dies auch so im Addressbuch abgespeichert. Hier ist die Ueberpruefung
 * auf gueltige Werte nicht noetig, da der User den fehlerhaften Eintrag
 * einfach wieder loeschen kann.
 */
void hinzufuegen(person* p1, address* p2, int anzahl)
{
	int temp = -1;

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

	printf("\n");
	fseek(stdin, 0, SEEK_SET);
}

/*
 * Die loeschen-Funktion, funktioniert ueber der Index.
 * Das loesch funktioniert folgender Maße: Der Vector wird durchgegangen,
 * und es werden immer das aktuelle Element mit dem Element mit dem uebergebenem
 * Index, verglichen. Wenn das gesuchte Elemt gefunden wurde, wird es
 * "uebersprungen", und alle Werte danach um eins nachvor kopiert.
 */
void loeschen(person* p1, address* p2, int anzahl, int index)
{
	int i = 0;
	int k = 0;

	while(i < anzahl)
	{
		if(strcmp((p1+i)->vname, (p1+index)->vname) == 0 &&
			strcmp((p1+i)->nname, (p1+index)->nname) == 0 &&	//vergleicht 2 Strings miteinander
			strcmp((p2+i)->str, (p2+index)->str) == 0 &&
			(p2+i)->strnr == (p2+index)->strnr &&
			(p2+i)->plz == (p2+index)->plz &&
			strcmp((p2+i)->ort, (p2+index)->ort) == 0)
		{
			k = i;
			while(k < anzahl-1)
			{
				strcpy((p1+k)->vname,(p1+k+1)->vname);	//kopiert den Wert eines Strings in den anderen
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

