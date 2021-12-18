//#include"test_utils.h"
#include"elt.h"


typedef struct node {
	T_elt data;
	struct node *pNext;
} T_node, * T_list;

char *toString(T_elt e); 
int est_inf(T_elt a, T_elt b);
int sont_egaux(T_elt a, T_elt b);
T_node *getLast(T_list l);
void showPartieList(T_list l, T_node *fin) ;

T_node * addNode (T_elt e, T_node * n);
void showList(T_list l);
void freeList(T_list l);

void mergeSort_list(T_list l, T_node *pg, T_node *pd);
void frontBackSplit( T_node* source,  T_node** frontRef, T_node** backRef);
void mergesort( T_node** head);