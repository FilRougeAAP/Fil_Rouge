#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <time.h> 


//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"
#include "list.h"



int main(int argc, char ** argv) {
	T_avl root = NULL; 
	

    
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	
	char *filename;
	
	filename = malloc(sizeof(filename));
	sprintf(filename, "%s",argv[1]); 
    

	//Ouverture Fichier

    FILE *in_file = fopen(filename, "r");

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    //Initialisation paramètres à afficher
    long int compteur_mots =0;
    int taille_mots=0;
    

    //Ajout des mots à l'arbre
    
    fscanf(in_file, "%[^\n] ", file_contents);
    taille_mots = strlen(file_contents);
    
    insertAVL(&root, file_contents, taille_mots);
    
    
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF ){
        insertAVL(&root, file_contents, taille_mots);
        compteur_mots++;
    }    



    fclose(in_file);
    
  
    //printAVL(root,0);


    FILE *fichier = fopen("Liste_anagrammes.txt", "w");
    int nombre_anagrammes=0;
    

    nombre_anagrammes = nb_anagramme(root, taille_mots, fichier);
    printf("%d\n", nombre_anagrammes);
   
    fclose(fichier);
    

    FILE *fichier_lec = fopen("Liste_anagrammes.txt", "r");
    T_list list_anag = NULL;

    struct stat sb_lec;
    stat("Liste_anagrammes.txt", &sb_lec);
    T_elt lignes = malloc(sb_lec.st_size);

    

    while (fscanf(fichier_lec, "%[^\n] ", lignes) != EOF){
        list_anag = addNode(lignes, list_anag);
    }   

    
    

	 
	
	mergesort(&list_anag); 
	printf("Listes anagrammes:\n"); showList_inv_rec(list_anag);

    fclose(fichier_lec);

	return 0;
}


// un mot possede 2 au moins anagrammes si la liste de mots dans la cellule d'un mot est plus grande que la taille d'un mot
// nb_anna renvoie le nombre de mot possede ana et ajoute dans un fichier les ana


int nb_anagramme(T_avl root, int taille_mots, FILE *fp){
    int compteur = 0; // Vaut 0 si pas d'anagramme pour cette maille et 1 si il y a des anagrammes

    if (root!=NULL){
        if (strlen(root->list_mots)>taille_mots){
            compteur++;
            fprintf(fp, "%s\n", root->list_mots);
        }

    return compteur + nb_anagramme(root->l, taille_mots, fp) + nb_anagramme(root->r, taille_mots, fp);

    }

    return 0;
}


void mergeSort_tab_str(char* t[], int debut, int fin){
	int milieu;

	if (debut < fin)
	{
		milieu = (debut + fin)/2;
		mergeSort_tab_str(t, debut, milieu);
		mergeSort_tab_str(t, milieu + 1, fin);
		fusionner_tab_str(t, debut, milieu, fin);
	}
}


void fusionner_tab_str(char* t[], int d, int m, int f){
	char* aux[f - d + 1]; // !! Allocation dynamique sur la pile (standard C99) 
	int i, j, k;
	

	memcpy(aux, &t[d], (f - d + 1) * sizeof(char*));	// Copie des données à fusionner
	

	i = 0; j = m - d + 1; k = 0;
	while (i <= m - d && j <= f - d) {
		
		if (eltcmp(aux[i],  aux[j])) 	{
			t[d + k++] = aux[i++];	// aux[i] est plus petit : on le place dans t 
		}
		else {
	 		t[d + k++] = aux[j++];	// aux[j] est plus petit : on le place dans t 
		}
	}
	for (; i <= m - d; t[d + k++] = aux[i++]); // le reste du tableau gauche
	for (; j <= f - d; t[d + k++] = aux[j++]); // le reste du tableau droit
}