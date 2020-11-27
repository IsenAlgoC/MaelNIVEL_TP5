#include <stdlib.h>
#include <stdio.h>
#include "tab.h"
#include <stdbool.h>

#define TAB2SIZE 100
#define TAILLEAJOUT 50 

int main() {
	printf("myTab1 :\n");

	int myTab1[10];
	initTab(myTab1, 10); //Initalisation du tableau
	afficheTab(myTab1, 10, 5); //Affichage du tableau

	int* myTab2 = NULL;
	int tabSize = TAB2SIZE;
	int nbElts = 20;
	myTab2 = (int*)malloc(TAB2SIZE * sizeof(int)); //Alocation de la mémoire nécéssaire à la création du tableau
	if (myTab2 != NULL) { initTab(myTab2, tabSize); } //test si mémoire suffisante, si oui on initialise le tableau
	else { printf("mémoire insuiffsante"); return -1; }

	for (size_t i = 0; i < nbElts; i++) // Ajout des valeurs 1 à nbElts dans le talbeau (ici 1 à 20)
	{
		*(myTab2 + i) = i + 1;
	}

	//printf("\n%d\n", nbElts);

	printf("\nmyTab2 avant modification :\n");
	afficheTab(myTab2, tabSize, nbElts);

	//ajoutElementDansTableau(myTab2, &tabSize, &nbElts, 27);
	//printf("\n%d\n", nbElts);

	printf("\nmyTab2 apres modification :\n");
	ajoutElementDansTableau(myTab2, &tabSize, &nbElts, 30);
	afficheTab(myTab2, tabSize, nbElts);

	free(myTab2);

	printf("\n");
	system("pause");
	return EXIT_SUCCESS;
}

int initTab(int* tab, int size) {//Fonction qui va remplir un tableau de 0 et renvoie -1 si erreur
	if (size < 0 || tab == NULL) { return -1; }
	for (size_t i = 0; i < size; i++)
	{
		*(tab + i) = 0;
	}
	return size;
}

int afficheTab(int* tab, int size, int nbElts) { //Fonction qui affiches nbElts du tableau et qui renvoie -1 si erreur
	if (size < 0 || size < nbElts || tab == NULL) { return -1; }
	for (int i = 0; i < nbElts; i++)
	{
		if (i % 10 == 0 && i != 0) { printf("\n"); }
		if (*(tab + i) < 10) { printf("%d  |", *(tab + i)); }
		else if (*(tab + i) < 100) { printf("%d |", *(tab + i)); }
		else { printf("%d|", *(tab + i)); }
	}
	printf("\n");
	return 0;
}

int* ajoutElementDansTableau(int* tab, int* size, int* nbElts, int element) {//Ajoute un element à la suite du tableau, modifie la taille du tableau si un agrandissement est nécessaire																			//incrémente le nombre d'element dans le tableau et retourne le pointeur nbElts ou -1 si ajout impossible
	if (size < 0 || tab == NULL) { return -1; }
	else if (*nbElts >= *size) { 
		int* save = tab;
		tab = (int*)realloc(tab, (*size + TAILLEAJOUT) * sizeof(int));
		if (tab == NULL) {
			tab = save;
			printf("\n Mémoire insuffisante \n");
			return -1;
		}
		else {
			*size += TAILLEAJOUT;
			*(tab + *nbElts) = element;
			*nbElts += 1;
		}

	}
	else { //Cas ou la taille est suffisante
		*(tab + *nbElts) = element;
		*nbElts += 1;

	}
	return *nbElts;

}
