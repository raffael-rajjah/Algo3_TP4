#include <stdlib.h>
#include <assert.h>

#include "skiplist.h"
#include "rng.h"
#include <stdio.h>


typedef struct s_Node{
	struct s_Node **previous;
	struct s_Node **next;
	int level;
	int value;

} Node;

struct s_SkipList{
	Node *sentinelle;
	RNG *rng;
	int nblevels;
	int size;

};


SkipList skiplist_create(int nblevels) {
	SkipList slist = malloc(sizeof(SkipList));
	slist->nblevels = nblevels;

	Node* sentinelle = malloc(sizeof(Node));
	sentinelle->level = nblevels;
	slist->sentinelle = sentinelle;
	
	Node** previous = malloc(sizeof(Node) * nblevels);
	Node** next = malloc(sizeof(Node) * nblevels);

	for (int i = 0; i < nblevels; i++){
		previous[i] = slist->sentinelle;
		next[i] = slist->sentinelle;
	}
	

	sentinelle->previous = previous;
	sentinelle->next = next;


	RNG rng = rng_initialize(0);
	slist->rng = &rng;

	slist->size=0;


	return slist;
}

void skiplist_delete(SkipList d) {
	(void)d;
}

SkipList skiplist_insert(SkipList d, int value) {
	
	Node* newNode = malloc(sizeof(Node));
	newNode->value = value;

	newNode->level = rng_get_value(d->rng, d->nblevels) + 1;

	Node** previous = malloc(sizeof(Node*) * newNode->level); 
	Node** next = malloc(sizeof(Node*) * newNode->level);


	if (d->size == 0){

		for (int i = 0; i < newNode->level; i++){	
			previous[i] = d->sentinelle;
			next[i] = d->sentinelle;

			d->sentinelle->previous[i] = newNode;
			d->sentinelle->next[i] = newNode;
		}

	}
	
	else {
		Node* currentNode = d->sentinelle->next;

		while (currentNode != d->sentinelle){
			
			

		}
		

	}



	return d;
}
