#include <assert.h>
#include <sys/stat.h>
#include <string.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h"

//#define DEBUG
#include "../include/check.h"

#include "elt.h" // T_elt
#include "avl.h" // prototypes

char *outputPath = ".";

/*
typedef enum {
	DOUBLE_RIGHT = -2,
	RIGHT = -1,
	BALANCED,
	LEFT,
	DOUBLE_LEFT
} T_bal;

typedef struct aNode{
	T_elt val; // signature du mot
	char *list_mot; // liste des mots
	T_bal bal; // facteur de déséquilibre
	struct aNode *l; // pointeur vers sous-arbre gauche
	struct aNode *r; // pointeur vers sous-arbre droit
} T_avlNode, *T_avl;
*/

static T_avl newNodeAVL(T_elt e, int taille_mots);
static T_avlNode *rotateLeftAVL(T_avlNode *A);
static T_avlNode *rotateRightAVL(T_avlNode *B);
static T_avlNode *balanceAVL(T_avlNode *A);

static T_avl newNodeAVL(T_elt e, int taille_mots)
{

	T_avl nodeAvl;
	nodeAvl = (T_avlNode *)malloc(sizeof(T_avlNode));
	CHECK_IF(nodeAvl, NULL, "erreur malloc dans newNode");
	nodeAvl->list_mots = eltdup(e);
	nodeAvl->val = cal_signature(e, taille_mots);
	nodeAvl->bal = 0;
	nodeAvl->l = NULL;
	nodeAvl->r = NULL;

	return nodeAvl;
}

int insertAVL(T_avlNode **pRoot, T_elt e, int taille_mots)
{

	T_elt sign = cal_signature(e, taille_mots);

	int deltaH = 0;
	if (*pRoot == NULL)
	{
		*pRoot = newNodeAVL(e, taille_mots); // Ajout d'une nouvelle maille
		return 1;							 // Modification de hauteur : on renvoie 1
	}
	else if (eltcmp(sign, (*pRoot)->val) == 0) // Si e à la même signature qu'un mot déjà présent dans le dictionnaire,
	{										   // on ajoute e a la liste de mot correspondant à cette signature
		// on rajoute de la place mémoire quand on ajoute des mots a la liste de mots

		(*pRoot)->list_mots = (T_elt)realloc((*pRoot)->list_mots, sizeof(char *) * (strlen((*pRoot)->list_mots) + taille_mots + 2)); // Le +2 correspond à la longueur de ", "
		strcat(strcat((*pRoot)->list_mots, ", "), toString(e));																		 // Fusion des chaines de caractère de la liste de mots, de ", " (pour de la lisibilité) et de e
	}
	else if (eltcmp(sign, (*pRoot)->val) < 0) // On compare sur la signature
	{
		deltaH = insertAVL(&(*pRoot)->l, e, taille_mots); // insertion dans sous-arbre gauche
		(*pRoot)->bal += deltaH;						  // mise à jour du facteur de déséquilibre
	}
	else
	{
		deltaH = insertAVL(&(*pRoot)->r, e, taille_mots); // insertion dans sous-arbre droit
		(*pRoot)->bal -= deltaH;						  // mise à jour du facteur de déséquilibre
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

// Calculer la signature

static int compare (char const *a, char const *b){
	char const *pa = a, *pb = b;
	return *pa-*pb;
}

T_elt cal_signature(T_elt mot, int taille_mots)
{
	// Le calcul de la signature revient à trier la chaîne de caractère par ordre alphabétique
	char *sign;

	sign = (char *) malloc(sizeof(char *) * taille_mots);
	memcpy(sign, mot, taille_mots);

	//mergeSort_tab(sign, 0, taille_mots - 1); // On ne trie pas le caractère de fin \0, 

	qsort(sign, taille_mots, sizeof(char), compare); // qsort est plus rapide que mergeSort_tab donc on l'utilise

	return sign;
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

// Tri fusion de tableau

void mergeSort_tab(char t[], int debut, int fin)
{
	int milieu;

	if (debut < fin)
	{
		milieu = (debut + fin) / 2;
		mergeSort_tab(t, debut, milieu);
		mergeSort_tab(t, milieu + 1, fin);
		fusionner_tab(t, debut, milieu, fin);
	}
}

void fusionner_tab(char t[], int d, int m, int f)
{
	char aux[f - d + 1]; // !! Allocation dynamique sur la pile (standard C99)
	int i, j, k;

	memcpy(aux, &t[d], (f - d + 1) * sizeof(char)); // Copie des données à fusionner

	i = 0;
	j = m - d + 1;
	k = 0;
	while (i <= m - d && j <= f - d)
	{

		if (aux[i] <= aux[j])
		{
			t[d + k++] = aux[i++]; // aux[i] est plus petit : on le place dans t
		}
		else
		{
			t[d + k++] = aux[j++]; // aux[j] est plus petit : on le place dans t
		}
	}
	for (; i <= m - d; t[d + k++] = aux[i++])
		; // le reste du tableau gauche
	for (; j <= f - d; t[d + k++] = aux[j++])
		; // le reste du tableau droit
}

// IDEM pour ABR

void printAVL(T_avl root, int indent)
{
	int i;
	// ordre de la récurrence : hauteur de l'arbre
	// Affiche la racine de l'arbre passé en paramètre avec un niveau d'indentation proportionnel à la profondeur du sous-arbre

	if (root != NULL)
	{
		printAVL(root->r, indent + 1); // afficher le sous-arbre droit avec indentation+1

		for (i = 0; i < indent; i++)printf("\t");
		printf("%s\n", toString(root->list_mots)); // afficher le noeud racine
		for (i = 0; i < indent; i++)printf("\t");
		printf("sign %s\n", root->val);

		printAVL(root->l, indent + 1); // afficher le sous-arbre gauche avec indentation+1
	}
}

int heightAVL(T_avl root)
{
	// hauteur d'un arbre
	int l, r;
	if (root == NULL)
		return -1;

	l = heightAVL(root->l);
	r = heightAVL(root->r);

	return 1 + ((l >= r) ? l : r);
}

int nbNodesAVL(T_avl root)
{
	// nb de noeuds d'un arbre (y compris les feuilles)
	if (root == NULL)
		return 0;

	return 1 + nbNodesAVL(root->l) + nbNodesAVL(root->r);
}

T_avlNode *searchAVL_rec(T_avl root, T_elt e, int taille_mots, int *p)
{
	// recherche récursive

	// ordre de récurrence : hauteur de l'arbre
	int test;

	(*p)++;

	// base
	if (root == NULL)
		return NULL;
	else
	{
		test = eltcmp(cal_signature(e, taille_mots), root->val);
		if (test == 0)
			return root; // trouvé !
		else if (test <= 0)
			return searchAVL_rec(root->l, e, taille_mots, p);
		else
			return searchAVL_rec(root->r, e, taille_mots, p);
	}
}
