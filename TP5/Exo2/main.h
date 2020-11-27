#pragma once
typedef struct Tableau TABLEAU;
typedef struct Tableau {
	int* elt; // le tableau d’entiers
	int size; // la taille de ce tableau d’entiers
	int eltsCount; // le nombre d’éléments dans le tableau
} TABLEAU;
TABLEAU newArray();
int initTab(int* tab, int size);
int incrementArraySize(TABLEAU* tab, int incrementValue);
int setElement(TABLEAU* tab, int pos, int element);
int displayElements(TABLEAU* tab, int startPos, int endPos);
int deleteElements(TABLEAU* tab, int startPos, int endPos);