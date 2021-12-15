#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"
#include"indexation.h"

int main(int argc, char ** argv) {
	T_avl root = NULL; 
	T_avlNode * pAux = NULL;


	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	/* outputPath = "output_Prog2";
	
	char *filename;
	
	filename = malloc(sizeof(filename));
	sprintf(filename, "%s",argv[1]); 
    

	//Ouverture Fichier

    FILE *in_file = fopen(filename, "r");

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    //Ajout des mots à l'arbre

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        insertAVL(&root, file_contents);
        
    }

    fclose(in_file);
    printAVL(root,0); */

    char *mot ="coucou";
    int taille = strlen(mot);
    char *sign;

    sign = cal_signature(mot, taille);
    printf("%s\n", sign);

	return 0;
}

char * cal_signature(char *mot, int taille){
    char * sign;
    
    sign = (char*) malloc(sizeof(mot));
    memcpy(sign, mot, taille);
    mergeSort_tab(sign, 0, taille-1); // On ne trie pas le caractère de fin \0

    return sign;
}


     

void mergeSort_tab(char t[], int debut, int fin){
	int milieu;

	if (debut < fin)
	{
		milieu = (debut + fin)/2;
		mergeSort_tab(t, debut, milieu);
		mergeSort_tab(t, milieu + 1, fin);
		fusionner_tab(t, debut, milieu, fin);
	}
}


void fusionner_tab(char t[], int d, int m, int f){
	char aux[f - d + 1]; // !! Allocation dynamique sur la pile (standard C99) 
	int i, j, k;
	

	memcpy(aux, &t[d], (f - d + 1) * sizeof(char));	// Copie des données à fusionner
	

	i = 0; j = m - d + 1; k = 0;
	while (i <= m - d && j <= f - d) {
		
		if (aux[i] <= aux[j]) 	{
			t[d + k++] = aux[i++];	// aux[i] est plus petit : on le place dans t 
		}
		else {
	 		t[d + k++] = aux[j++];	// aux[j] est plus petit : on le place dans t 
		}
	}
	for (; i <= m - d; t[d + k++] = aux[i++]); // le reste du tableau gauche
	for (; j <= f - d; t[d + k++] = aux[j++]); // le reste du tableau droit
}
