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

	outputPath = "output_Prog2";
	
	char *filename;
	
	filename = malloc(sizeof(filename));
	sprintf(filename, "%s",argv[1]); 
    

	//Ouverture Fichier

    FILE *in_file = fopen(filename, "r");
    int nb_ligne = 0;
    int ligne_max = atoi(argv[2]);

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    //Ajout des mots à l'arbre
    

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF && nb_ligne++ < ligne_max){
        T_elt temp;
        temp.size = strlen(file_contents);
        printf("%s\n", file_contents);
        temp.signature = (char*) malloc(temp.size*sizeof(char)+1);
        temp.liste_mots = (char*) malloc(temp.size*sizeof(char)+1);
        temp.signature = cal_signature(file_contents,temp.size);
        temp.liste_mots = file_contents;
        printf("%s\n", file_contents);
        //insertAVL(&root, temp);
        
    }

    fclose(in_file);
    printAVL(root,0); 

    /* char *mot ="coucou";
    int taille = strlen(mot);
    char *sign;

    sign = cal_signature(mot, taille);
    //printf("%s\n", sign);

    char *mot2 ="bonjou";
    int taille2 = strlen(mot2);
    char *sign2;

    sign2 = cal_signature(mot2, taille2);

    T_elt test1;

    test1.size = taille;
    test1.signature = sign;
    test1.liste_mots = mot;

    T_elt test2;

    test2.size = taille2;
    test2.signature = sign2;
    test2.liste_mots = mot2;

    printf("%s\n", toString(test2));

    insertAVL(&root, test1);
    insertAVL(&root, test2);
    printAVL(root,0); */


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
