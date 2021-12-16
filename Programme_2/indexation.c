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
    int nb_ligne = 0;
    int ligne_max = atoi(argv[2]);

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    //Ajout des mots à l'arbre
    

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF && nb_ligne++ < ligne_max){
        //insertAVL(&root, temp);
        
    }

    fclose(in_file);
    printAVL(root,0); 
    printf("oui"); */

    char *mot ="coucou";
    int taille = strlen(mot);
    char *sign;
    printf("%s\n", mot);

    sign = cal_signature(mot);
    printf("%s\n", mot);
    printf("%s\n", sign);

    T_elt test;
    test = (T_elt) malloc(sizeof(char*)*20);
    sprintf(test, "%s \n%s", "aaaa", "bbbb");
    sprintf(test, "%s \n%s", "cccc", "dddd");
    printf("%s\n", test);

    insertAVL(&root, "oui");
    insertAVL(&root, "non");
    printAVL(&root, "uio");
    printAVL(root,0);


	return 0;
}
