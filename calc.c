/*
  Name of file	: Taschenrechner.c
  Author	: Ari Ayvazyan
  Version	: 20131018.1
  Description	: This Program implements a calc using pointers for functions.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int addition(int,int);
int subtraktion(int,int);
int division(int,int);
int multiplikation(int,int);
#define SYNOPSIS "Parameter: all | multiplizieren a b | subtrahieren a b | addieren a b | dividieren a b\n wobei a und b integer werte sind und all schritt fuer schritt alle rechenoperationen durchgeht."
/*
 * calculates using pointers for functions
 */
int main(int arc, char* argv[])//argv[0] returns the execution path
{
	printf("arc: %d\n",arc);
	int i;
	for(i=0;i<arc;i++){
		printf("%s Parameter[%d]\n",argv[i],i);
	}
	if(arc==1||arc>4){
		printf(SYNOPSIS);
		return EXIT_FAILURE;
	}
	int (*fPtrs[4])(int,int);// Defines a pointer to a function that returns int and receives 2 int
		fPtrs[0] = addition;//Gets the pointer of the addition function and sets it to
		fPtrs[1] = subtraktion;
		fPtrs[2] = division;
		fPtrs[3] = multiplikation;
	if(strcmp(argv[1],"all")==0){//checks if the first parameter equals all
		char buf[300];
		int a,b;
		//addition
		printf("Es wird Addiert\n");
		printf("Geben sie den Integer wert fuer a an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &a);
		printf("Geben sie den Integer wert fuer b an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &b);
		int erg=(*fPtrs[0])(a, b);
		printf("result: %i\n",erg);

		//Subtraction
		printf("Es wird substraktion\n");
		printf("Geben sie den Integer wert fuer a an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &a);
		printf("Geben sie den Integer wert fuer b an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &b);
		erg=(*fPtrs[1])(a, b);
		printf("result: %i\n",erg);

		//Division
		printf("Es wird dividiert\n");
		printf("Geben sie den Integer wert fuer a an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &a);
		printf("Geben sie den Integer wert fuer b an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &b);
		if(b==0){
			printf("Division durch 0\n");
		}else{
			erg=(*fPtrs[2])(a, b);
			printf("result: %i\n",erg);
		}

		//multiplication
		printf("Es wird multiplikation\n");
		printf("Geben sie den Integer wert fuer a an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &a);
		printf("Geben sie den Integer wert fuer b an\n");
		fgets(buf, 300, stdin);
		sscanf(buf, "%i", &b);
		erg=(*fPtrs[3])(a, b);
		printf("result: %i\n",erg);
		return EXIT_SUCCESS;
	}
	if(arc<4||arc>4){
			printf(SYNOPSIS);
			return EXIT_FAILURE;
		}
	if(strcmp(argv[1],"addieren")==0){ //compares two char arrays
		int a=atoi(argv[2]);
		int b=atoi(argv[3]);
		int erg=(*fPtrs[0])(a, b);
		printf("result: %i\n",erg);
		return EXIT_SUCCESS;

	}
	if(strcmp(argv[1],"subtrahieren")==0){
		int a=atoi(argv[2]);
		int b=atoi(argv[3]);
		int erg=(*fPtrs[1])(a, b);
		printf("result: %i\n",erg);
		return EXIT_SUCCESS;
	}
	if(strcmp(argv[1],"multiplizieren")==0){
		int a=atoi(argv[2]);
		int b=atoi(argv[3]);
		int erg=(*fPtrs[3])(a, b);
		printf("result: %i\n",erg);
		return EXIT_SUCCESS;
	}
	if(strcmp(argv[1],"dividieren")==0){
		int a=atoi(argv[2]);
		int b=atoi(argv[3]);
		int erg=(*fPtrs[2])(a, b);
		printf("result: %i\n",erg);
		return EXIT_SUCCESS;
	}
	printf(SYNOPSIS);
	return EXIT_FAILURE;
}
/*
 * adds a to b and returns the result
 */
int addition(int a,int b){
	return a+b;
}
/*
 * subtracts b from a and returns the result
 */
int subtraktion(int a,int b){
	return a-b;
}
/*
 * divides a by b and returns the result
 */
int division(int a,int b){
	if(b==0)return 0;//In the case of a division by 0, return 0
	return a/b;
}
/*
 * Multiply a and b and returns the result
 */
int multiplikation(int a,int b){
	return a*b;
}
