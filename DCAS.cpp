#include <iostream>
#include <pthread.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

const int board_size = 42;
const int num_drones = 2;
char board[board_size][board_size];
volatile int drone_turn = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct drone
{
	int current_x;
	int current_y;
	int final_x;
	int final_y;
	int id;
	char img;
	char dest_img;
	char curr_pos_prev_img;

};

// function declarations
void printBoard();
void moveDrone( drone *drone_arg);
void printDrone( drone *drone_arg);
void instantiateBoard();
void *activateDrone(void *drone_arg);

int main(){

	int rc;
	instantiateBoard();

	drone drone_a;
	drone *drone_0;
	drone_0 = &drone_a;
	(*drone_0).current_x = 20;
	(*drone_0).current_y = 1;
	(*drone_0).img = 'A';
	(*drone_0).dest_img = '0';
	(*drone_0).final_x = 20;
	(*drone_0).final_y = 35;
	(*drone_0).id = 0;
	drone_0->curr_pos_prev_img = ' ';
	board[(*drone_0).current_x][(*drone_0).current_y] = (*drone_0).img;
	board[(*drone_0).final_x][(*drone_0).final_y] = (*drone_0).dest_img;



	drone drone_b;
	drone *drone_1;
	drone_1 = &drone_b;
	(*drone_1).current_x = 20;
	(*drone_1).current_y = 40;
	(*drone_1).img = 'B';
	(*drone_1).dest_img = '1';
	(*drone_1).final_x = 20;
	(*drone_1).final_y = 15;
	(*drone_1).id = 1;
	drone_1->curr_pos_prev_img = ' ';
	board[(*drone_1).current_x][(*drone_1).current_y] = (*drone_1).img;
	board[(*drone_1).final_x][(*drone_1).final_y] = (*drone_1).dest_img;


	printBoard();
	pthread_t threads[2];


	rc = pthread_create(&threads[0], NULL, activateDrone, (void *)drone_0);
	rc = pthread_create(&threads[1], NULL, activateDrone, (void *)drone_1);
	rc = pthread_join(threads[0],NULL);
	rc = pthread_join(threads[1],NULL);
	printBoard();
	printf("completed");


	return 0;
}

// potential lock placement in this method
void moveDrone(drone *drone_arg){
	int drone_id = drone_arg->id;
	int drone_current_x = drone_arg->current_x;
	int drone_current_y = drone_arg->current_y;
	int drone_final_x = drone_arg->final_x;
	int drone_final_y = drone_arg->final_y;
	int drone_potential_x;
	int drone_potential_y;
	char drone_char = drone_arg->img;
	char dest_char = drone_arg->dest_img;

	// x arith
	if (drone_current_x < drone_final_x){
		drone_potential_x = drone_current_x + 1;
	}
	else if(drone_current_x > drone_final_x){
		drone_potential_x = drone_current_x - 1;
	}
	else{
		drone_potential_x = drone_current_x;
	}

	//do y
	if (drone_potential_x == drone_current_x){
		// y arith
		if (drone_current_y < drone_final_y){
			drone_potential_y = drone_current_y + 1;
		}
		else if(drone_current_y > drone_final_y){
			drone_potential_y = drone_current_y - 1;
		}
		else{
			drone_potential_y = drone_current_y;
		}

		if (drone_potential_y == drone_current_y){
			//do nothing?
		}

		else{
			char potential_char = board [drone_potential_x][drone_potential_y];
			if ((potential_char == ' ') || (potential_char == dest_char) || ((potential_char < 64) && (potential_char > 47))){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_potential_x][drone_potential_y];
				board[drone_potential_x][drone_potential_y] =drone_char;
				drone_arg->current_x = drone_potential_x;
				drone_arg->current_y = drone_potential_y;
			}
			else{
				if ((board[drone_current_x + 1][drone_current_y] == ' ') || ((potential_char < 64) && (potential_char > 47))){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x+1][drone_current_y];
					board[drone_current_x + 1][drone_current_y] =drone_char;
					drone_arg->current_x = drone_current_x + 1;
					drone_arg->current_y = drone_current_y;
				}
				else if ((board[drone_current_x - 1][drone_current_y] == ' ') || ((potential_char < 64) && (potential_char > 47))){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x-1][drone_current_y];
					board[drone_current_x - 1][drone_current_y] =drone_char;
					drone_arg->current_x = drone_current_x - 1;
					drone_arg->current_y = drone_current_y;
				}
				else if ((board[drone_current_x][drone_current_y - 1] == ' ') || ((potential_char < 64) && (potential_char > 47))){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x][drone_current_y-1];
					board[drone_current_x][drone_current_y - 1] =drone_char;
					drone_arg->current_x = drone_current_x;
					drone_arg->current_y = drone_current_y - 1;
				}
				else if ((board[drone_current_x][drone_current_y + 1] == ' ') || ((potential_char < 64) && (potential_char > 47))){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x][drone_current_y+1];
					board[drone_current_x][drone_current_y + 1] =drone_char;
					drone_arg->current_x = drone_current_x;
					drone_arg->current_y = drone_current_y + 1;
				}
				else{
					//wait do nothing
				}
			}			
		}

	}
	//do x
	else{
		char potential_char = board [drone_potential_x][drone_current_y];
		// printf("%c %c %d %d",potential_char, dest_char, drone_potential_x, drone_current_y);
		if ((potential_char == ' ') || (potential_char == dest_char) || ((potential_char < 64) && (potential_char > 47))){
			board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
			drone_arg->curr_pos_prev_img = board[drone_potential_x][drone_current_y];
			board[drone_potential_x][drone_current_y] =drone_char;
			drone_arg->current_x = drone_potential_x;
			drone_arg->current_y = drone_current_y;
		}
		else{
			if ((board[drone_current_x][drone_current_y - 1] == ' ') || ((potential_char < 64) && (potential_char > 47))){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x][drone_current_y-1];
				board[drone_current_x][drone_current_y - 1] =drone_char;
				drone_arg->current_x = drone_current_x;
				drone_arg->current_y = drone_current_y - 1;
			}
			else if((board[drone_current_x][drone_current_y + 1] == ' ') || ((potential_char < 64) && (potential_char > 47))){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x][drone_current_y+1];
				board[drone_current_x][drone_current_y + 1] =drone_char;
				drone_arg->current_x = drone_current_x;
				drone_arg->current_y = drone_current_y + 1;
			}
			else if((board[drone_current_x + 1][drone_current_y] == ' ') || ((potential_char < 64) && (potential_char > 47))){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x+1][drone_current_y];
				board[drone_current_x + 1][drone_current_y] =drone_char;
				drone_arg->current_x = drone_current_x + 1;
				drone_arg->current_y = drone_current_y;
			}
			else if((board[drone_current_x - 1][drone_current_y] == ' ') || ((potential_char < 64) && (potential_char > 47))){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x-1][drone_current_y];
				board[drone_current_x - 1][drone_current_y] =drone_char;
				drone_arg->current_x = drone_current_x - 1;
				drone_arg->current_y = drone_current_y;
			}
			else{
				//wait do nothing
			}
		}
	}

}

void *activateDrone(void *drone_arg){
	drone *cur_drone = (drone *)drone_arg;
	int cur_drone_id = cur_drone->id;

	while (((cur_drone->current_x)!=(cur_drone->final_x)) || ((cur_drone->current_y)!=(cur_drone->final_y))){
		printf("thread %d active\n",cur_drone_id);
		// if (cur_drone_id == (drone_turn%num_drones)){
			pthread_mutex_lock(&lock);
			printf("thread %d has locked moveDrone\n",cur_drone_id);
			moveDrone(cur_drone);
			// usleep(1000000);
			printBoard();
			drone_turn++;
			printf("%d\n",drone_turn);
			pthread_mutex_unlock(&lock);
			usleep(1000000);
		// }
		// else{
		// 	drone_turn;
		// 	// printf("%d\n",drone_turn);
		// 	usleep(10000000);
			printf("thread %d has woken up with drone turn %d\n", cur_drone_id, drone_turn );
		// }
	}
	board[(cur_drone->current_x)][(cur_drone->current_y)] = ' ';
	printf("Exiting Thread id: %d \n", cur_drone_id );
	usleep(10000000);
	pthread_exit(NULL);
	//loop

	//mutex lock
	//move drone
	//increment turn
	//mutex unlock

}

void instantiateBoard(){
	for (int i =0; i<board_size; i++){
		board[(board_size - board_size)][i] = '-';
	}
	for (int i =0; i<board_size; i++){
		board[(board_size - 1)][i] = '-';
	}
	for (int x = 1; x < (board_size - 1); x++){
		board[x][board_size - board_size] = '|';
		for (int y = 1; y < (board_size - 1); y++){
			board[x][y] = ' ';
		}
		board[x][(board_size - 1)] = '|';
	}
}

void printBoard(){
	for (int x = 0; x < board_size; x++){
		for (int y = 0; y < board_size; y++){
			printf("%c", board[x][y]);
		}
		printf("\n");;
	}
}



void printDrone(drone *drone_arg){
	// drone *drone2;
	// drone2 = drone_arg;
	// (*drone_arg).current_x = (*drone_arg).current_x + 1;
	int x = (*drone_arg).current_x;
	int y = (*drone_arg).current_y;
	int fx = (*drone_arg).final_x;
	int fy = (*drone_arg).final_y;
	char c = (*drone_arg).id;

	printf("%d %d %d %d\n",x,y,fx,fy  );
}