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
    
    
    

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF&& compteur_mots<10){
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
        "Nombre de noeuds: %ld\nHauteur: %d\nHauteur minimale d’un arbre contenant %ld noeuds: %d\n",
        taille_mots, compteur_mots, duree, nb_noeud, hauteur, nb_noeud, h_min
        );
  
    printAVL(root,0);
    //printf("%s et %d\n", file_contents, strlen(file_contents)* sizeof(char*));

    //Recherche de mots

    T_elt mot_ecris = (T_elt) malloc(27*sizeof(char*)), mot_cherche ; // Taille maximale mot 26 + 1 pour "\0"
    clock_t start_rech = clock(), stop_rech;
    int profondeur;
    T_avlNode * search = NULL;
    
    printf("Entrer le mot à rechercher (Ctrl+D) pour terminer: ");

    fgets(mot_ecris, 27, stdin);
    mot_cherche = strndup(mot_ecris, strcspn(mot_ecris, "\n"));
    char *mot = strdup(file_contents);
    //mot = file_contents;
    printf("%s de signature %s\n", mot, toString(cal_signature(mot, taille_mots)));

    profondeur = 0;
    start_rech = clock();

    search = searchAVL_rec(root, cal_signature(mot_cherche, taille_mots));
    stop_rech = clock();

    if (search == NULL) printf("Mot non trouvé\n");
    else
    {
        printf("%s\n", toString(search->list_mots));
    }

    /* while (fgets(mot_ecris, 27, stdin)!=NULL)
    {
        mot_cherche = strndup(mot_ecris, strcspn(mot_ecris, "\n"));
        printf("%s de signature %s\n", mot_cherche, cal_signature(mot_cherche, taille_mots-1));

        profondeur = 0;
        start_rech = clock();

        search = searchAVL_rec(root, mot_cherche);
        stop_rech = clock();

        if (search == NULL) printf("Mot non trouvé\n");
        else
        {
            printf("%s\n", toString(search->list_mots));
        }

        
        printf("Entrer le mot à rechercher (Ctrl+D) pour terminer: ");
    } */
    
    

	return 0;
}
