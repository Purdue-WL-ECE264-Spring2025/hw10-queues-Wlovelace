#include "queue.h"
#include "tile_game.h"
#include "stdio.h"

//void insert_at_tail(struct linked_list *list, size_t value);
//size_t remove_from_head(struct linked_list *list); 
//void free_list(struct linked_list list); 
//struct queue {
//  struct linked_list data;
//};
//struct game_state {
//  uint8_t tiles[4][4];
//  uint8_t empty_row, empty_col;
//  uint16_t num_steps;
//};
//uint64_t serialize(struct game_state state);
//struct game_state deserialize(uint64_t state);
//void move_up(struct game_state *state);
//void move_down(struct game_state *state);
//void move_left(struct game_state *state);
//void move_right(struct game_state *state);
bool check_correct(struct game_state c);
bool check(struct game_state c, struct queue q);

void enqueue(struct queue *q, struct game_state state) {
	insert_at_tail(&q->data,serialize(state)); 	
}

struct game_state dequeue(struct queue *q) { 
	return deserialize(remove_from_head(&q->data));
}

int number_of_moves(struct game_state start) { 
	struct queue q;
	q.data.head = NULL;
	enqueue(&q, start); 

	while (q.data.head != NULL){
		
		struct game_state c = dequeue(&q); 		

		if(check_correct(c) == true){
			free_list(q.data); 
			return c.num_steps;
		}

		if(c.empty_row != 0){
			struct game_state new = c; 
			move_down(&new);
			//enqueue(&q, new);
			if(check(new,q)){
				enqueue(&q, new);
			}   		
		}
		if(c.empty_row != 3){
			struct game_state new = c;
                        move_up(&new);
			enqueue(&q, new);
                        //if(check(new,q)){enqueue(&q, new);}
                }
		if(c.empty_col != 0){
			struct game_state new = c;
                        move_right(&new);
			enqueue(&q, new);
                        //if(check(new,q)){enqueue(&q, new);}
                }
		if(c.empty_col != 3){
			struct game_state new = c;
                        move_left(&new);
                        enqueue(&q, new);
			//if(check(new,q)){enqueue(&q, new);}
                }

		c.num_steps++;

	}



	return -1; 
}

bool check_correct(struct game_state c){
	if((serialize(c)>>15) == 2501999725154){
		return true;
	}else{
		return false;
	}
	
	/*
	
	for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                        if(c.tiles[i][j] != ((4*(i) + (j+1))%16)){
                                return false;
                        }
                }
        }
	printf("serialized correct: %zu", (serialize(c)>>15));
	return true;
	*/
}

bool check(struct game_state c, struct queue q){
	//int i = 0; 
	//printf("flag");
	size_t temp = serialize(c)>>15;
	while(q.data.head != NULL){
		//printf("flag2");
		if (temp == (q.data.head->value>>15)){
			//printf("aha!");
			return false;
		}
		q.data.head = q.data.head->next; 
		//i++;
	}
	return true; 
}

