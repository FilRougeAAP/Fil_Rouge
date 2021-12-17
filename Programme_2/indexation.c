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
#include"indexation.h"

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
    int taille_mots=strlen(file_contents);
    clock_t start = clock(), stop;
    int hauteur, nb_noeud;
    int nb_noeud_temp, h_min=1; // On initialise h_min pour la hauteur minimale contenant le même nombre de noeud à 1 pour compter le premier noeud
    float duree;


    //Ajout des mots à l'arbre
    
    fscanf(in_file, "%[^\n] ", file_contents);
    insertAVL(&root, file_contents, taille_mots);
    
    taille_mots = strlen(file_contents);
    

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF){
        insertAVL(&root, file_contents, taille_mots);
        compteur_mots++;
    }

    stop = clock();

    fclose(in_file);
    
    
    // Paramètres de l'arbre
    duree = (stop-start)* 1000.0 / CLOCKS_PER_SEC;
    nb_noeud = nbNodesAVL(root);
    hauteur = heightAVL(root);

    nb_noeud_temp = nb_noeud;
    while ((nb_noeud_temp/=2)>0) h_min++;

    printf("Taille des mots : %d\nNombre de mots: %ld\nDurée de construction: %.2f \n"
        "Nombre de noeuds: %d\nHauteur: %d\nHauteur minimale d’un arbre contenant %ld noeuds: %d\n",
        taille_mots, compteur_mots, duree, nb_noeud, hauteur, nb_noeud, h_min
        );
  
    //printf("%s et %d\n", file_contents, strlen(file_contents)* sizeof(char*));

    

	return 0;
}
