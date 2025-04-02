#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
	struct list_node *new = NULL;
	new = malloc(sizeof(struct list_node)); 
	new->value = value;
	new->next = NULL;
	
	return new; 
}

void insert_at_head(struct linked_list *list, size_t value) {
	struct list_node* new;
        new = new_node(value);
	new->next = list->head; 
	list->head = new; 

}

void insert_at_tail(struct linked_list *list, size_t value) {
	struct list_node* pos;
        pos = list->head;
	
	if (list->head == NULL){
		list->head = new_node(value);
		return; 
	}
	
	while (pos->next != NULL){
		pos = pos->next;}

	struct list_node* new;
       	new = new_node(value);
	pos->next = new; 
}

size_t remove_from_head(struct linked_list *list) { 
	struct list_node* old; 
	size_t value;
       	value = list->head->value; 	
	old = list->head;
	list->head = list->head->next; 
	free(old); 

	return value; 
}

size_t remove_from_tail(struct linked_list *list) { 
	struct list_node* pos;
        pos = list->head; 
	size_t value;	
	while (pos->next != NULL && pos->next->next != NULL){
		pos = pos->next;
	}
	pos->next = NULL;
	struct list_node* old;
        old = pos->next;
       	value = old->value;	
	free(old); 

	return value; 
}

void free_list(struct linked_list list) {
	while (list.head != NULL){
		struct list_node* pos; 
		pos = list.head->next;
		free(list.head);
		list.head = pos;
	}
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
