#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>

using namespace std;

const int board_size = 42;
const int num_drones = 10;
char board[board_size][board_size];
volatile int drone_turn = 0;

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
	// printBoard();
	// board[20][20] = '1';
	// board[20][21] = board[20][20] + 1;
	// printBoard();

	//test drone struct
	drone drone_a;
	drone *drone_0;
	drone_0 = &drone_a;
	(*drone_0).current_x = 20;
	(*drone_0).current_y = 20;
	(*drone_0).img = 'A';
	(*drone_0).dest_img = '0';
	(*drone_0).final_x = 20;
	(*drone_0).final_y = 23;
	(*drone_0).id = 0;
	drone_0->curr_pos_prev_img = ' ';
	board[(*drone_0).current_x][(*drone_0).current_y] = (*drone_0).img;
	board[(*drone_0).final_x][(*drone_0).final_y] = (*drone_0).dest_img;
	// board[20][22] = 'B';
	board[20][21] = '1';

	printBoard();

	pthread_t threads[1];
	// drone *drone_arr;
	// drone_arr = new drone[1];
	// drone_arr[0] = drone_0;

	rc = pthread_create(&threads[0], NULL, activateDrone, (void *)drone_0);
	rc = pthread_join(threads[0],NULL);
	printf("completed");

	// printDrone(drone_0);

	
	// while (((drone_0->current_x)!=(drone_0->final_x)) || ((drone_0->current_y)!=(drone_0->final_y))){

	// 	moveDrone(drone_0);
	// 	usleep(1000000);
	// 	printBoard();
	// 	printDrone(drone_0);

	// }
	// moveDrone(drone_0);
	// printBoard();
	// printDrone(drone_0);
	
	// moveDrone(drone_0);
	// printBoard();
	// printDrone(drone_0);
	
	// moveDrone(drone_0);
	// printBoard();
	// printDrone(drone_0);
	
	// moveDrone(drone_0);
	// printBoard();
	// printDrone(drone_0);
	// (*drone_0).current_x = (*drone_0).current_x + 1;
	
	// moveDrone(drone_0);

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
			if ((potential_char == ' ') || (potential_char == dest_char) || (potential_char < 64) || (potential_char > 47)){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_potential_x][drone_potential_y];
				board[drone_potential_x][drone_potential_y] =drone_char;
				drone_arg->current_x = drone_potential_x;
				drone_arg->current_y = drone_potential_y;
			}
			else{
				if ((board[drone_current_x + 1][drone_current_y] == ' ') || (potential_char < 64) || (potential_char > 47)){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x+1][drone_current_y];
					board[drone_current_x + 1][drone_current_y] =drone_char;
					drone_arg->current_x = drone_current_x + 1;
					drone_arg->current_y = drone_current_y;
				}
				else if ((board[drone_current_x - 1][drone_current_y] == ' ') || (potential_char < 64) || (potential_char > 47)){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x-1][drone_current_y];
					board[drone_current_x - 1][drone_current_y] =drone_char;
					drone_arg->current_x = drone_current_x - 1;
					drone_arg->current_y = drone_current_y;
				}
				else if ((board[drone_current_x][drone_current_y - 1] == ' ') || (potential_char < 64) || (potential_char > 47)){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x][drone_current_y-1];
					board[drone_current_x][drone_current_y - 1] =drone_char;
					drone_arg->current_x = drone_current_x;
					drone_arg->current_y = drone_current_y - 1;
				}
				else if ((board[drone_current_x][drone_current_y + 1] == ' ') || (potential_char < 64) || (potential_char > 47)){
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
		if ((potential_char == ' ') || (potential_char == dest_char) || (potential_char < 64) || (potential_char > 47)){
			board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
			drone_arg->curr_pos_prev_img = board[drone_potential_x][drone_current_y];
			board[drone_potential_x][drone_current_y] =drone_char;
			drone_arg->current_x = drone_potential_x;
			drone_arg->current_y = drone_current_y;
		}
		else{
			if ((board[drone_current_x][drone_current_y - 1] == ' ') || (potential_char < 64) || (potential_char > 47)){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x][drone_current_y-1];
				board[drone_current_x][drone_current_y - 1] =drone_char;
				drone_arg->current_x = drone_current_x;
				drone_arg->current_y = drone_current_y - 1;
			}
			else if((board[drone_current_x][drone_current_y + 1] == ' ') || (potential_char < 64) || (potential_char > 47)){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x][drone_current_y+1];
				board[drone_current_x][drone_current_y + 1] =drone_char;
				drone_arg->current_x = drone_current_x;
				drone_arg->current_y = drone_current_y + 1;
			}
			else if((board[drone_current_x + 1][drone_current_y] == ' ') || (potential_char < 64) || (potential_char > 47)){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x+1][drone_current_y];
				board[drone_current_x + 1][drone_current_y] =drone_char;
				drone_arg->current_x = drone_current_x + 1;
				drone_arg->current_y = drone_current_y;
			}
			else if((board[drone_current_x - 1][drone_current_y] == ' ') || (potential_char < 64) || (potential_char > 47)){
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
	while (((cur_drone->current_x)!=(cur_drone->final_x)) || ((cur_drone->current_y)!=(cur_drone->final_y))){
		moveDrone(cur_drone);
		usleep(1000000);
		printBoard();
	}
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