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

	//Ouverture Fichier
	char *filename;
	
	filename = malloc(sizeof(filename));
	sprintf(filename, "%s",argv[1]); 

    FILE *in_file = fopen(filename, "r");

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    //Paramètres dictionnaire
    int taille_mots=0;
    

    //Ajout des mots à l'arbre
    
    fscanf(in_file, "%[^\n] ", file_contents); // On récupère le premier indépendamment pour pouvoir déterminer la taille des mots
    taille_mots = strlen(file_contents);
    
    insertAVL(&root, file_contents, taille_mots);
    
    
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF ){
        insertAVL(&root, file_contents, taille_mots); // On insère chaque mot
    }    

    fclose(in_file);
    
    /*
        A cet instant le dictionnaire est crée

        On commence alors à récupérer les anagrammes :
        On va stocker les anagrammes dans un fichier, pour ne pas avoir a reparcourir l'arbre pour les afficher
    */

    // Ouverture fichier stockage
    FILE *fichier = fopen("Liste_anagrammes.txt", "w");
    int nombre_anagrammes=0;
    
    // Comptage du nombre d'anagramme en les ajoutant au fichier de stockage
    nombre_anagrammes = nb_anagramme(root, taille_mots, fichier);
    printf("%d\n", nombre_anagrammes);
   
    fclose(fichier);
    freeAVL(root); // On a plus besoin de l'arbre, on libère la mémoire
    

    // Affichage des anagrammes, pour cela on les stock temporairement dans une liste chaînée dynamique
    FILE *fichier_lec = fopen("Liste_anagrammes.txt", "r");
    T_list list_anag = NULL;

    struct stat sb_lec;
    stat("Liste_anagrammes.txt", &sb_lec);
    T_elt lignes = malloc(sb_lec.st_size);


    while (fscanf(fichier_lec, "%[^\n] ", lignes) != EOF){
        list_anag = addNode(lignes, list_anag); // On récupère chaque mot avec son / ses anagrammes
    }   
	 
	
	mergesort(&list_anag); // On trie la liste en fonction de la la longueur des listes à l'intérieur en ordre décroissant
	printf("Listes anagrammes:\n"); showList(list_anag); // On affiche la liste par le début 
    
    
    freeList(list_anag); //Libération mémoire
    fclose(fichier_lec);

	return 0;
}


int nb_anagramme(T_avl root, int taille_mots, FILE *fp){
    int compteur = 0; // Vaut 0 si pas d'anagramme pour cette maille et 1 si il y a des anagrammes

    if (root!=NULL){
        if (strlen(root->list_mots)>taille_mots){ // On regarde si la liste de mots de maille contient plus d'un mot
            compteur++; //Si c'est le cas, c'est que c'est qu'il y a des anagrammes de ce mot
            fprintf(fp, "%s\n", root->list_mots); // On ajoute les anagrammes au fichier de stockage
        }

    return compteur + nb_anagramme(root->l, taille_mots, fp) + nb_anagramme(root->r, taille_mots, fp); // Compte le nombre de mots du dictionnaire disposant d’anagrammes

    }

    return 0;
}
