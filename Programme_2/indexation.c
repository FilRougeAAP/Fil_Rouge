#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	//outputPath = "output_Prog2";
	
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
    int taille_mots=strlen(file_contents);


    //Ajout des mots à l'arbre
    
    fscanf(in_file, "%[^\n] ", file_contents);
    insertAVL(&root, file_contents, taille_mots);
    
    taille_mots = strlen(file_contents);

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF){
        insertAVL(&root, file_contents, taille_mots);
        compteur_mots++;

        
    }

    fclose(in_file);
    //printAVL(root,0); 
    printf("Taille des mots : %d\nNombre de mots: %ld\n", taille_mots, compteur_mots);
    


  
    //printf("%s et %d\n", file_contents, strlen(file_contents)* sizeof(char*));
  
    

	return 0;
}
