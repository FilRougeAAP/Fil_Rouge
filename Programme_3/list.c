#include "list.h" // prototypes 
#include "elt.h"
#include "stdlib.h"

#include <assert.h>
/*
typedef struct node {
	T_elt data;
	struct node *pNext;
} T_node, * T_list;
*/



int est_inf(T_elt a, T_elt b){ // Relation d'ordre en fonction du type T_elt
	return eltcmp(a,b)<0;
}

int sont_egaux(T_elt a, T_elt b){
	return eltcmp(a,b)==0;
}



static T_node * newNode(T_elt e); 

T_node * addNode (T_elt e, T_node * n) {
	// Créer une maille (node), la remplir 
	// et l'accrocher en tête d'une liste existante (ou vide)
	// Renvoyer la nouvelle tête

	T_node * pNode; 
	pNode = newNode(e); 
	pNode->pNext = n; 
	return pNode;
}

static T_node * newNode(T_elt e) {
	// Créer une nouvelle cellule contenant l'élément e

	T_node * pNode; 
	pNode = malloc(sizeof(T_node));
	pNode->data = eltdup(e); 
	pNode->pNext = NULL;

	return pNode;
}



void showList(T_list l) {
	// Afficher la liste en commençant par sa tête 

	if (l == NULL) return;
	else 
	{
		printf("%s\n", toString(l->data));
		showList(l->pNext); 
	}
}



void showList_inv(T_list l) {
	// Afficher la liste en commençant par sa queue 

	if (l == NULL) return;
	else {
		showList_inv(l->pNext); 
		printf("%s\n", toString(l->data));	
	}
}


void freeList(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 

	if (l == NULL) {
		return;
	} else {
		freeList(l->pNext);
		//printf("Libération de %s\n",toString(l->data));
		free(l); 
	}
}


// Tri fusion
// bibliographie : https://www.techiedelight.com/merge-sort-singly-linked-list/


// Renvoie la fusion des mailles de 2 listes triées dans l'ordre croissant
T_node* sortedMerge( T_node* a,  T_node* b)
{
	T_node* result = NULL;

    // Cas terminaux
    if (a == NULL) return b;
    else if (b == NULL) return a;
 
	
 
    // On insère les éléments récursivement pour fusion les 2 listes
    if (strlen(a->data) >= strlen(b->data))
    {
        result = a;
        result->pNext = sortedMerge(a->pNext, b);
    }
    else {
        result = b;
        result->pNext = sortedMerge(a, b->pNext);
    }
 
    return result;
}
 
/*
	Sépare la liste source en deux parties : frontRef (du début jusqu'au milieu)
	et backRef (du milieu à la fin). 
	Renvoie les pointeur des 2 débuts de chaque partie.
	Si la taille de la liste est paire, la maille en plus va dans la partie du 
	début de liste (front).
*/

void frontBackSplit( T_node* source,  T_node** frontRef, T_node** backRef){
    // Si la liste possède 2 mailles ou moins, on la sépare manuellement
    if (source == NULL || source->pNext == NULL)
    {
        *frontRef = source;
        *backRef = NULL;
        return;
    }
 
    T_node* slow = source;
    T_node* fast = source->pNext;
 
    // On récupère le milieu de la liste en incrément une (fast) 2 fois plus vite que l'autre (slow)
    while (fast != NULL)
    {
        fast = fast->pNext;
        if (fast != NULL)
        {
            slow = slow->pNext;
            fast = fast->pNext;
        }
    }
 
    // slow est donc le pointeur au milieu du milieu de la liste
    *frontRef = source;
    *backRef = slow->pNext;
    slow->pNext = NULL;

}
 

void mergesort( T_node** head)
{
    //Cas terminaux
    if (*head == NULL || (*head)->pNext == NULL) {
        return;
    }
 
    T_node* a;
    T_node* b;
 
    // On sépare la liste à trier en 2
    frontBackSplit(*head, &a, &b);
 
    // On trie récursivement les 2 sous listes
    mergesort(&a);
    mergesort(&b);
 
    // On fusion les 2 sous listes triées
    *head = sortedMerge(a, b);
}

