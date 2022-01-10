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
	
	//Ouverture Fichier
	char *filename;
	
	filename = malloc(sizeof(filename));
	sprintf(filename, "%s",argv[1]); 


    FILE *in_file = fopen(filename, "r");

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    //Initialisation paramètres à afficher
    long int compteur_mots =0;
    int taille_mots=0;
    clock_t start, stop;
    int hauteur;
    long int nb_noeud, nb_noeud_temp;
    int h_min=1; // On initialise h_min pour la hauteur minimale contenant le même nombre de noeud à 1 pour compter le premier noeud
    float duree;


    //Ajout des mots à l'arbre
    
    fscanf(in_file, "%[^\n] ", file_contents);
    taille_mots = strlen(file_contents);
    
    start = clock();

    insertAVL(&root, file_contents, taille_mots);
    
    
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF){
        insertAVL(&root, file_contents, taille_mots);
        compteur_mots++;
    }    

    stop = clock();
    
    //printAVL(root, 0);
    
    // Paramètres de l'arbre
    duree = (stop-start)* 1000.0 / CLOCKS_PER_SEC;
    nb_noeud = nbNodesAVL(root);
    hauteur = heightAVL(root);

    nb_noeud_temp = nb_noeud;
    while ((nb_noeud_temp/=2)>0) h_min++; //La hauteur revient à h_min = round(log_2(nb_noeud)) ou encore en comptant le nombre de fois que l'on peut diviser nb_noeud par 2.

    printf("Taille des mots : %d\nNombre de mots: %ld\nDurée de construction: %.2f ms\n"
        "Nombre de noeuds: %ld\nHauteur: %d\nHauteur minimale d’un arbre contenant %ld noeuds: %d\n",
        taille_mots, compteur_mots, duree, nb_noeud, hauteur, nb_noeud, h_min);
  

    //Recherche de mots

    T_elt mot_ecris = (T_elt) malloc(27*sizeof(char*)), mot_cherche ; // Taille maximale mot de 26 caractère + 1 pour "\0"
    clock_t start_rech = clock(), stop_rech;
    int profondeur=0;
    T_avlNode * search = NULL;
    
    printf("Entrer le mot à rechercher (Ctrl+D) pour terminer: ");
   

    while (fgets(mot_ecris, 27, stdin)!=NULL) //Récupération mot donné par l'utilisateur en boucle
    {

        mot_cherche = strndup(mot_ecris, strcspn(mot_ecris, "\n")); // On garde seulement les caractères avec le retour à la ligne pour la recherche
        

        profondeur = 0; // Initialisation de la profondeur pour chaque recherche

        start_rech = clock();
        search = searchAVL_rec(root, mot_cherche, taille_mots, &profondeur); 
        stop_rech = clock();

        // Affichage résultats de la recherche
        if (search == NULL) printf("Mot non trouvé\n");
        else
        {
            printf("%s\n", toString(search->list_mots));
            printf("Profondeur: %d\n", profondeur);
            printf("Temps de recherche: %.2f\n", (stop_rech-start_rech)* 1000.0 / CLOCKS_PER_SEC);
        }

        
        printf("Entrer le mot à rechercher (Ctrl+D) pour terminer: ");
    } 


    freeAVL(root);
    fclose(in_file);
    

	return 0;
}
