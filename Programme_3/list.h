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
T_elt getFirstElt(T_list l);
T_list removeFirstNode(T_list l);
unsigned int getSize(const T_list l);
T_list tailAddNode(T_elt e, T_list l);
T_list sortAddNode(T_elt e, T_list l);
int inList(T_elt e, const T_list l);
T_list removeNode(T_elt e, T_list l);
T_list removeDuplicates(T_list l);


void showList_rec(T_list l);
void showList_inv_rec(T_list l);
void freeList_rec(T_list l);
unsigned int getSize_rec(const T_list l);
T_list tailAddNode_rec(T_elt e, T_list l);
T_list sortAddNode_rec(T_elt e, T_list l);
int inList_rec(T_elt e, const T_list l);
T_list removeNode_rec(T_elt e, T_list l);
T_list removeDuplicates_rec(T_list l);

void mergeSort_list(T_list l, T_node *pg, T_node *pd);
void mergesort( T_node** head);