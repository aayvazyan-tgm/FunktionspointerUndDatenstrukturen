/*
  Name			: address.h
  Author		: Vennesa Belinic
  Version		: 2013-11-02
  Description	: Die Funktionen und Defines die im Addressbuch_Belinic.c verwendet werden
 */

/* Verwendete Header */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Defines */
#define my_free(x) free(x);x=NULL


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
