#include <stdlib.h>
#include<stdio.h>
#include "main.h"
#define TAILLEINITIALE 100

int main() {
	TABLEAU tab;
	tab = newArray();
	setElement(&tab, 1, 10);
	setElement(&tab, 2, 11);
	setElement(&tab, 3, 12);
	setElement(&tab, 4, 13);
	setElement(&tab, 105, 4);
	setElement(&tab, 104, 3);
	setElement(&tab, 103, 2);
	setElement(&tab, 102, 1);
	displayElements(&tab, 1, 105);
	printf("\n Suppr des elements 2 a 101 :\n");
	deleteElements(&tab, 2, 101);
	displayElements(&tab, 1, 5);
	printf("\n Suppr de tous les elements :\n");
	deleteElements(&tab, 1, 5);
	displayElements(&tab, tab.size, tab.size);
}

TABLEAU newArray() { //Renvoie une structure TABLEAU, avec un pointeur elt = NULL si allocation a échoué.
	TABLEAU tab;
	tab.elt = NULL; 
	tab.elt = (int*)malloc(TAILLEINITIALE * sizeof(int));
	tab.size = TAILLEINITIALE;
	tab.eltsCount = 0;
	initTab(tab.elt, tab.size); //Initalisation du tableau
	return tab;
}

int initTab(int* tab, int size) {//Fonction qui va remplir un tableau de 0 et renvoie -1 si erreur
	if (size < 0 || tab == NULL) { return -1; }
	for (size_t i = 0; i < size; i++)
	{
		*(tab + i) = 0;
	}
	return size;
}

int incrementArraySize(TABLEAU* tab, int incrementValue) { //Incrémente le tableau, renvoie sa nouvelle taille
	if (tab->elt == NULL || incrementValue < 1 || tab->size < 0) { return -1; } //Gere les erreurs
	int* save = tab->elt;
	tab->elt = (int*)realloc(tab->elt, (tab->size + incrementValue) * sizeof(int));
	if (tab->elt == NULL) { tab->elt = save; return -1; }
	else {
		for (size_t i = 0; i < incrementValue; i++) { tab->elt[tab->size + i] = 0; } //initaliation à 0 des nouvelles cases
		tab->size += incrementValue;
		return tab->size;
	}
}

int setElement(TABLEAU* tab, int pos, int element) { //Ajoute un element dans le tableau et renvoie sa position
	if (tab->elt == NULL || pos < 1 || tab->size < 0) { return -1; } //Gere les erreurs
	if (tab-> size > pos - 1) //Si la position se trouve dans le tableau
	{
		tab->elt[pos - 1] = element;
		tab->eltsCount++;
	}
	else { //Si la position est en dehors du tableau
		incrementArraySize(tab, pos - tab->size); //On augmente la taille du tableau
		tab->elt[pos - 1] = element;
		tab->eltsCount++;
	}
	return pos - 1;
}

int displayElements(TABLEAU* tab, int startPos, int endPos) {//Affiche une portion du tableau de l'indice début à l'inde fin, renvoie -1 si erreur, sinon 0
	if (tab->elt == NULL || startPos < 1 || endPos < 1 || startPos > tab->size || endPos > tab->size) { return -1; } //Gere les erreurs
	if (startPos >= endPos) { int temp = endPos; endPos = startPos; startPos = temp; } //Inversion de Start et End
	printf("\n");
	for (int i = startPos; i <= endPos; i++) { printf("%d ", tab->elt[i - 1]); }
	printf("\n");
	return 0;
}

int deleteElements(TABLEAU* tab, int startPos, int endPos) {//Supprime les élements avec compactage du tableau, renvoie la nouvelle taille du tableau ou -1 si erreur
	if (tab->elt == NULL || startPos < 1 || endPos < 1 || startPos > tab->size || endPos > tab->size) { return -1; } //Gere les erreurs
	if (startPos >= endPos) { int temp = endPos; endPos = startPos; startPos = temp; } //Inversion de Start et End
	int valeur = endPos - startPos + 1; // Création d'une nouvelle variable qui stock le nombre de valeur dans l'intervalle
	if (valeur == tab->size) { free(tab->elt); tab->elt = NULL; tab->size = 0; tab->eltsCount = 0; return tab->size; } //Supprime le tableau si intervalle = la taille du tableau
	for (size_t i = startPos - 1; i <= tab->size - endPos; i++) //Décale à gauche les valeurs qu'on veut garder
	{ 
		tab->elt[i] = tab->elt[i + valeur]; 
		printf("\n Position %d prends la valeur : %d qui etait a la position %d\n", i+1, tab->elt[i + valeur], i + valeur + 1);
	}
	
	int* save = tab->elt;
	tab->elt = (int*)realloc(tab->elt, ((size_t)tab->size - (size_t)valeur) * sizeof(int)); //On ajuste la taille de l'allocation dynamique
	if (tab->elt == NULL) { tab->elt = save; return - 1; }
	tab->size -= valeur;
	return tab->size;
}

