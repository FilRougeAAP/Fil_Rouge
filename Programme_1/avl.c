#include <assert.h>
#include <sys/stat.h>
#include <string.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

//#define DEBUG
#include "../include/check.h"

#include "elt.h" // T_elt 
#include "avl.h" // prototypes 

char * outputPath = "."; 

/*
typedef enum {
    DOUBLE_RIGHT = -2,
    RIGHT = -1,
    BALANCED,
    LEFT,
    DOUBLE_LEFT
} T_bal;

typedef struct aNode{
	T_elt val; // élément contenu dans le noeud 
	T_bal bal; // facteur de déséquilibre
	struct aNode *l; // pointeur vers sous-arbre gauche
	struct aNode *r; // pointeur vers sous-arbre droit 
} T_avlNode, *T_avl;
*/

static T_avl newNodeAVL(T_elt e); 
static T_avlNode * rotateLeftAVL (T_avlNode * A); 
static T_avlNode * rotateRightAVL (T_avlNode * B);
static T_avlNode * balanceAVL(T_avlNode * A);

static T_avl newNodeAVL(T_elt e) {

	T_avl nodeAvl;
	nodeAvl = (T_avlNode*) malloc(sizeof(T_avlNode));
	CHECK_IF(nodeAvl, NULL,"erreur malloc dans newNode");
	nodeAvl->val = eltdup(e);
	nodeAvl->bal = 0;
	nodeAvl->l = NULL;
	nodeAvl->r = NULL;

	return nodeAvl; 
}

 

int	insertAVL (T_avlNode ** pRoot, T_elt e) {
	
	
	int deltaH=0;
	if (*pRoot==NULL)
	{
		*pRoot = newNodeAVL(e); // Ajout d'une nouvelle maille
		return 1;				// Modification de hauteur : on renvoie 1
	}
	else if (eltcmp(e, (*pRoot)->val)<=0)
	{
		deltaH = insertAVL(&(*pRoot)->l, e);	// insertion dans sous-arbre gauche
		(*pRoot)->bal += deltaH;				// mise à jour du facteur de déséquilibre
	}
	else 
	{
		deltaH = insertAVL(&(*pRoot)->r, e);	// insertion dans sous-arbre droit
		(*pRoot)->bal -= deltaH;				// mise à jour du facteur de déséquilibre
	}
	

	if (deltaH == 0)
		return 0; // pas de modification de hauteur : on renvoie 0
	else		  // le sous-arbre renvoyé par l’appel récursif a grandi
	{
		*pRoot = balanceAVL(*pRoot); // on rééquilibre
	}

	if ((*pRoot)->bal != 0)
		return 1; // Si l'arbre n'est pas rééquilibré, on renvoie 1 pour qu'il soit lors de l'appel récursif
	else
		return 0;

}


static T_avlNode *rotateLeftAVL(T_avlNode *B)
{
	// rotation gauche

	T_avlNode *A;
	T_bal a, b;

	A = B->r;

	a = A->bal; // On récupère les facteurs de déséquilibre avant rotation
	b = B->bal;

	B->r = A->l; // Rotation simple à gauche
	A->l = B;

	B->bal = 1 + b - MIN2(0, a); // Mise à jour des facteurs de déséquilibre
	A->bal = 1 + a + MAX2(B->bal, 0);

	return A;
}


static T_avlNode *rotateRightAVL(T_avlNode *A)
{
	// rotation droite
	T_avlNode *B;
	T_bal a, b;

	B = A->l;

	a = A->bal;	// On récupère les facteurs de déséquilibre avant rotation
	b = B->bal;

	A->l = B->r; // Rotation simple à droite
	B->r = A;

	A->bal = a - 1 - MAX2(0, b);	// Mise à jour des facteurs de déséquilibre
	B->bal = b - 1 + MIN2(0, A->bal);

	return B;
}

 /*  
	A->bal 	< 0 \Leftrightarrow arbre penche à droite;
		 	= 0 \Leftrightarrow arbre équilibré 
			> 0 \Leftrightarrow arbre penche à gauche
*/

static T_avlNode *balanceAVL(T_avlNode *A)
{
	// rééquilibrage de A

	if (A->bal == 2) // Penche à gauche
	{
		if (A->l->bal <= 0) // Penche à droite
		{
			A->l = rotateLeftAVL(A->l); // Rotation double : 
			return rotateRightAVL(A);	// Gauche puis droite
		}
		else				// Si ne penche pas
			return rotateRightAVL(A);	// Rotation simple à droite
	}
	else if (A->bal == -2)	// Penche à droite
	{
		if (A->r->bal >= 0) // Penche à gauche
		{
			A->r = rotateRightAVL(A->r); 	// Rotation double : 
			return rotateLeftAVL(A);		// Droite puis Gauche  
		}
		else				// Si ne penche pas
			return rotateLeftAVL(A);	// Rotation simple à gauche
	}
	else
		return A;
	return NULL;
}

// IDEM pour ABR 

void printAVL(T_avl root, int indent) {
	int i; 
	// ordre de la récurrence : hauteur de l'arbre 
	// Affiche la racine de l'arbre passé en paramètre avec un niveau d'indentation proportionnel à la profondeur du sous-arbre 

	// pas de cas de base...
	 
	if (root!=NULL) {
		
		// afficher le sous-arbre droit avec indentation+1
		printAVL(root->r, indent+1);
		// afficher le noeud racine 
		for(i=0;i<indent;i++) printf("\t");
		printf("%s\n", toString(root->val));
		//printf("desi = %d\n", root->bal);
		// afficher le sous-arbre gauche avec indentation+1
		printAVL(root->l, indent+1);
	}
}


void freeAVL(T_avl root)
{
	// Libérer la mémoire de toutes les mailles de l'arbre

	if (root != NULL)
	{
		freeAVL(root->r);
		freeAVL(root->l);
		// printf("Libération de %s\n", root->list_mots);
		free(root);
	}
}


int heightAVL(T_avl root){
	// hauteur d'un arbre 
	int l,r; 
	if (root == NULL) return -1;

	l = heightAVL(root->l);
	r = heightAVL(root->r);

	return 1+ ((l >= r) ? l : r); 
}

int nbNodesAVL(T_avl root){
	// nb de noeuds d'un arbre (y compris les feuilles) 
	if (root == NULL) 
		return 0;
	
	return 1+ nbNodesAVL(root->l) + nbNodesAVL(root->r);
}


T_avlNode * searchAVL_rec(T_avl root, T_elt e){
	// recherche récursive

	// ordre de récurrence : hauteur de l'arbre 	
	int test; 

	if (root== NULL) return NULL; 
	else {
		test = eltcmp(e,root->val); 
		if (test == 0) return root; // trouvé ! 
		else if (test <= 0) return searchAVL_rec(root->l,e);
		else return searchAVL_rec(root->r,e);
	}
}




static void  genDotAVL(T_avl root, FILE *fp) {
	// Attention : les fonction toString utilisent un buffer alloué comme une variable statique 
	// => elles renvoient toujours la même adresse 
	// => on ne peut pas faire deux appels à toString dans le même printf()

    fprintf(fp, "\t\"%s\"",toString(root->val)); 
    fprintf(fp, " [label = \"{{<g> %s | <d> %d } | { <g> | <d>}}\"];\n",toString(root->val), root->bal);
    if (root->r == NULL && root->l == NULL) {
        fprintf(fp, "\t\"%s\"", toString(root->val)); 
		fprintf(fp, " [label = \"{{<g> %s | <d> %d }| { <g> NULL | <d> NULL}}\"];\n", toString(root->val), root->bal);
	}
    else if (root->r == NULL) {
        fprintf(fp, "\t\"%s\"", toString(root->val));
		fprintf(fp, " [label = \"{{<g> %s | <d> %d }| { <g> | <d> NULL}}\"];\n", toString(root->val), root->bal);
	}
	else if ( root->l == NULL) {
        fprintf(fp, "\t\"%s\"",toString(root->val));
		fprintf(fp, " [label = \"{{<g> %s | <d> %d }| { <g> NULL | <d> }}\"];\n", toString(root->val), root->bal);
	}
	
    if (root->l) {
        fprintf(fp, "\t\"%s\"",toString(root->val));
		fprintf(fp, ":g -> \"%s\";\n", toString(root->l->val));
        genDotAVL(root->l, fp);
    }

    if (root->r) {
        fprintf(fp, "\t\"%s\"",toString(root->val));
		fprintf(fp,":d -> \"%s\";\n", toString(root->r->val));
        genDotAVL(root->r, fp);
    }
}


void createDotAVL(const T_avl root, const char *basename) {
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char	cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	

	// Au premier appel, création (si nécessaire) des répertoires
	// où seront rangés les fichiers .dot et .png générés par cette fonction	

	// il faut créer le répertoire outputPath s'il n'existe pas 
	printf("%s\n", outputPath);
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    }

	// il faut créer les répertoires outputPath/png et /dot 
	sprintf(DOSSIER_DOT, "%s/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/png/",outputPath);
	

	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	 // S'il y a changement de nom de base alors recommencer à zéro
	 // la numérotation des fichiers 

	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
	
	noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
 	fprintf(fp, 
		"\tnode [\n"
			"\t\tfontname  = \"Arial bold\" \n"
			"\t\tfontsize  = \"14\"\n"
			"\t\tfontcolor = \"red\"\n"
			"\t\tstyle     = \"rounded, filled\"\n"
			"\t\tshape     = \"record\"\n"
			"\t\tfillcolor = \"grey90\"\n"
			"\t\tcolor     = \"blue\"\n"
			"\t\twidth     = \"2\"\n"
			"\t]\n"
		"\n"
		"\tedge [\n"
			"\t\tcolor     = \"blue\"\n"
		"\t]\n\n"
	);

    if (root == NULL)
        fprintf(fp, "\n");
    else
        genDotAVL(root, fp);

    fprintf(fp, "}\n");	
    fclose(fp);

    sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
    system(cmdLine);

    printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}

