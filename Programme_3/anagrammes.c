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

int main(int argc, char ** argv) {
	T_avl root = NULL; 
	

    
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
    int taille_mots=0;
    clock_t start = clock(), stop;
    int hauteur;
    long int nb_noeud, nb_noeud_temp;
    int h_min=1; // On initialise h_min pour la hauteur minimale contenant le même nombre de noeud à 1 pour compter le premier noeud
    float duree;


    //Ajout des mots à l'arbre
    
    fscanf(in_file, "%[^\n] ", file_contents);
    taille_mots = strlen(file_contents);
    
    insertAVL(&root, file_contents, taille_mots);
    
    
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF){
        insertAVL(&root, file_contents, taille_mots);
        compteur_mots++;
    }    

    stop = clock();

    
    
    
    
  
    //printAVL(root,0);




    fclose(in_file);
    

	return 0;
}
