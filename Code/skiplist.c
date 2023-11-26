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
	RNG rng;
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
	slist->rng = rng;

	slist->size=0;

	// printf("sentinnelle levellllss : %d\n", slist->sentinelle->level);
	// for (int i = 0; i < slist->sentinelle->level; i++){
	// 	printf("level sentinell : %d\n", previous[i]->level);
	// }
	

	return slist;
}

void skiplist_delete(SkipList d) {
	(void)d;
}

SkipList skiplist_insert(SkipList d, int value) {
	
	Node* newNode = malloc(sizeof(Node));
	newNode->value = value;

	newNode->level = rng_get_value(&d->rng, d->nblevels);
	if(newNode->level <= 0 ) {
		newNode->level = 1;
	}

	(void)value;



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
		Node* currentNode = d->sentinelle->next[0];

		while (currentNode != d->sentinelle){
			
			if (currentNode->value > value){
				
				// previous 
				for (int j = 0; j < newNode->level; j++){
					
					if(j < currentNode->level){
						previous[j] = currentNode->previous[j];
						currentNode->previous[j] = newNode;
					
					}

					else{
						// keep going
						currentNode = currentNode->next[0];
						while (j > currentNode->level){
							currentNode = currentNode->next[0];
							
						}
						
					}	
					

				}


				// next
				currentNode = previous[0]; // have to changed currentNode->previous[0] to previous[0]
				for (int i = 0; i < newNode->level; i++){
					
					if(i < currentNode->level){

						next[i]  = currentNode->next[i];
						currentNode->next[i] = newNode;

					}

					else{

						currentNode = currentNode->previous[0];
						while (i > currentNode->level){
							
							currentNode = currentNode->previous[0];

						}
						

					}

				}

				break;
				

			}

			else if (currentNode->next[0] == d->sentinelle){
				
				for (int i = 0; i < newNode->level; i++){
					next[i] = d->sentinelle;
					d->sentinelle->previous[i] = newNode;

					previous[i] = currentNode;
					currentNode->next[i] = newNode;
				}

				break;

			}
			

			currentNode = currentNode->next[0];
			

		}
		

	}

	d->size++;
	newNode->previous = previous;
	newNode->next = next;


	// printf("sentinnelle levellllss : %d\n", d->sentinelle->level);

	// printf("newnode level : %d\n", newNode->level);
	// for (int i = 0; i < d->sentinelle->level; i++){
	// 	printf("value : %d (level : %d)\n", d->sentinelle->next[i]->value, d->sentinelle->next[i]->level);
	// }
	
	printf("afficher %d: ----------------------------------------------------------------------------------\n", d->size);
	Node* it = d->sentinelle->next[0];
	while (it != d->sentinelle){
		printf("val : %d level : %d\n", it->value, it->level);
		for (int i = 0; i < it->level; i++){
			printf("  - next[%d] : %d\n", i, it->next[i]->value);

		}

		for (int i = 0; i < it->level; i++){
			printf("  * previous[%d] : %d\n", i, it->previous[i]->value);
		}

		printf("\n");
		

		
		it = it->next[0];
	}
		it = d->sentinelle;
		printf("SENTINELLE level : %d\n", it->level);
		for (int i = 0; i < it->level; i++){
			printf("  - next[%d] : %d\n", i, it->next[i]->value);

		}

		for (int i = 0; i < it->level; i++){
			printf("  * previous[%d] : %d\n", i, it->previous[i]->value);
		}
	

	return d;
}
