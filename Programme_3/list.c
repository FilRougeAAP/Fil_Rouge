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

/* T_elt genElt(void) {
	static int indice = 0; 
	// produire une chaine aléatoire... 
	// On va écrire elt_<numéro>
	char buffer[15]; // elt_+<11 chiffres>
	sprintf(buffer, "elt_%d",indice++); 
	return strdup(buffer); 
} */

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
	// A faire en itératif 

	while(l != NULL) {
		printf("%s\n", toString(l->data));
		l = l->pNext; 
	}
	printf("\n"); 
}

void showPartieList(T_list l, T_node *fin) {
	// Afficher la liste en commençant par sa tête 
	// A faire en itératif 

	while(l != fin) {
		printf("%s ", toString(l->data));
		l = l->pNext; 
	}
	printf("\n"); 
}

void freeList(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 
	// A faire en itératif

	assert(l != NULL); 
	T_node * pAux; 
	// Il faut un pointeur auxiliaire : 
	// on ne doit libérer qu'après avoir enregistré quelque part
	// l'adresse de la maille suivante
	while(l != NULL) {
		printf("Libération de %s\n", toString(l->data));
		pAux = l->pNext; 
		free(l); 
		l = pAux; 
	}
	printf("NULL");
}

T_elt getFirstElt(T_list l) {
	// Renvoyer l'élément contenu dans la cellule de tête de la liste

	return l->data; 
}

T_list removeFirstNode(T_list l) {
	// Supprimer la tête de la liste 
	// Renvoyer la nouvelle liste privée de sa première cellule

	assert(l!= NULL);	
	T_node * p =l->pNext; 
	free(l); 
	return p; 
}

T_node *getLast(T_list l){
    while (l->pNext!=NULL){
        l=l->pNext;
    }
    return l;
}




// Nouvelles fonctions partie 2 en iterative
unsigned int getSize(const T_list l){
	unsigned int res = 0 ;
	T_list l_cop = l;

	while(l_cop !=NULL ){
		l_cop = l_cop->pNext;
		res ++;
	}

	return res;
}

T_list tailAddNode(T_elt e, T_list l){
	T_node *pNode;
	T_node *pAux;

	pAux=l;

	while(pAux->pNext!=NULL) pAux=pAux->pNext;
	
	pNode = newNode(e); // Creation de la nouvelle maille
	pAux->pNext = pNode; // On met le pointeur du dernier element vers la nouvelle maille 

	return l;
}

T_list sortAddNode(T_elt e, T_list l){
	T_node *pNode;
	T_node *pAux;
	T_node *pTemp;
	pAux = l;
	pNode = newNode(e);


	if (est_inf(e, l->data) ){ // Cas particulier si e est plus petit que le debut de la liste
		l = addNode(e, l); // on insere en tete de liste avec la fonction définie précédemment
		return l;
	}

	while(pAux!=NULL && est_inf(pAux->data, e) ){ // On parcours la liste et on s'arrête juste avant un élément plus grand ou le cas échéant à la fin de la liste
		pTemp=pAux; // On stock temporairement l'adresse de la valeur avant de l'incrémenter pour le test suivant
		pAux = pAux->pNext;
		
	}
	
	pTemp->pNext = pNode; // On fait pointer la maille juste avant celle du dernier test sur la maille a ajouter
	pNode->pNext = pAux; // on fait pointer la maille ajoutée sur la fin de la liste

	return l;
}

int inList(T_elt e, const T_list l){
	T_list l_cop = l;

	while(l_cop !=NULL ){
		if (sont_egaux(l_cop->data, e)) return 1;
		l_cop = l_cop->pNext;

	}

	return 0;
}

T_list removeNode(T_elt e, T_list l){ //Fait en plus mais pas utile pour la partie 2
	

	assert(l!= NULL);
	assert(inList(e, l)); // On vérifie que l'élément à enlever est bien dans la liste
	
	T_node *pAux=l, *pTemp; 


	if (sont_egaux(l->data, e)){ // Cas particulier si e est égal au premier élément de la liste
		l = removeFirstNode(l); // on supprime la node en tete de liste avec la fonction définie précédemment
		return l;
	}

	while (pAux!=NULL && !sont_egaux(pAux->data, e)){ // On cherche la maille qui est à supprimer
		pTemp=pAux;
		pAux = pAux->pNext;
	}

	pTemp->pNext = pAux->pNext; // On supprime la maille et on libère l'espace mémoire
	free(pAux);
	pAux = pTemp;
	

	return l; 
}

T_list removeDuplicates (T_list l){
	T_node *pAux =l;

	while(pAux!=NULL){
		T_elt e = pAux->data;
		

		if (inList(e, pAux->pNext)){ // On regarde si chaque valeur a un doublon dans la liste commencant a la maille d'après cette valeur
			#ifdef DEBUG
			printf("%s a ete supprime\n", toString(e));
			#endif
			
			l = removeNode(e, l); // s'il y a un doublon on le supprime et il sera en première position
			pAux =l; // On actualise la chaine sur laquelle on parcourt les éléments

		}
		else pAux = pAux->pNext; // Si on supprime rien on passe au suivant
	}
	
	return l;
}




// A produire en version récursive (+ tard dans le sujet)

void showList_rec(T_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en récursif 

	if (l == NULL) {
		// case de base
		return;
	} else {
		// cas général
		printf("%s ", toString(l->data));
		showList_rec(l->pNext); 
	}
}


void showList_inv_rec(T_list l) {
	// Afficher la liste en commençant par sa queue 
	// A faire en récursif 

	if (l == NULL) {
		// case de base
		return;
	} else {
		// cas général
		showList_inv_rec(l->pNext); 
		printf("%s\n", toString(l->data));	
	}
}


void freeList_rec(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 
	// A faire en récursif

	if (l == NULL) {
		return;
	} else {
		freeList_rec(l->pNext);
		printf("Libération de %s\n",toString(l->data));
		free(l); 
	}
}


unsigned int getSize_rec(const T_list l){  
	if (l==NULL) return 0;
	
	unsigned int res;
	res = getSize_rec(l->pNext);
	return ++res;
	
}


T_list tailAddNode_rec(T_elt e, T_list l){
	if (l->pNext==NULL){ // On ajoute le maillon en fin de chaîne
		T_node *pNode;
		pNode = newNode(e);
		l->pNext = pNode;
		return l;
	}
	else { // On va jusqu'a la fin de la liste 
		tailAddNode_rec(e, l->pNext);
		return l;
		
	}
}



T_list sortAddNode_rec(T_elt e, T_list l){ 

	if (l->pNext==NULL){
		T_node *pNode = newNode(e);
		
		l->pNext = pNode;
		return l;
	}
	else if (est_inf(l->data, e)){ // Tant que e est plus grand on va au rang d'après
		sortAddNode(e, l->pNext);
		return l;
	}
	else{  // On ajoute la maille 
		T_node *pNode = newNode(e);
		T_node *pTemp = l;
		l = pNode;
		pNode->pNext = pTemp;
	 	
		return l;
	} 
}


int inList_rec(T_elt e, const T_list l){
	if (l==NULL) return 0; // Renvoie 0 s'il n'as pas trouvé l'élément
	else if (sont_egaux(e, l->data)) return 1; // Renvoie 1 quand il trouve 2 élément égaux
	else return inList_rec(e, l->pNext );	// Parcours la liste tant qu'il ne trouve pas l'élément
}



T_list removeDuplicates_rec(T_list l){
	if (l->pNext==NULL) {
		return l;
	}

	else if (inList_rec(l->data, l->pNext)){
		#ifdef DEBUG
		printf("%s a ete supprime\n", toString(l->data));
		#endif

		l = removeFirstNode(l); // Supprime le doublons qui est la maille dont on compare la valeur
		l = removeDuplicates_rec(l); 
	}
	else {
		T_node *pAux = l;
		l = removeDuplicates_rec(l->pNext); // Renvoie la liste sans doublons des mailles restantes de la liste
		l = addNode(pAux->data, l);	// Ajoute l'élément (qui n'est pas en doublon) à la liste sans les doublons : "recontruction de la chaîne"
		free(pAux); // Libération de la mémoire pour les mailles stockées temporairement
	}

	return l;
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
    if (strlen(a->data) <= strlen(b->data))
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

