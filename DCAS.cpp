#include <iostream>
#include <pthread.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace std;

const int board_size = 42;
const int num_drones = 4;
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
void placeDroneOnBoard(drone *drone_arg);
void instantiateBoard();
void *activateDrone(void *drone_arg);

int main(){

	int rc;
	instantiateBoard();

	int demo = 0;
	switch(demo){
		case 0:
			srand (time(NULL));
			pthread_t demo0_threads[10];
			drone drone_data[10];
			
			for (int i = 0; i<10; i++){
				char demo0_drone_img = 'A' + i;				
				char demo0_dest_img = '0' + i;
				drone_data[i].img = demo0_drone_img;
				drone_data[i].dest_img = demo0_dest_img;
				drone_data[i].curr_pos_prev_img = ' ';
				drone_data[i].id = i;
				placeDroneOnBoard(&drone_data[i]);
				printDrone(&drone_data[i]);
				rc = pthread_create(&demo0_threads[i], NULL, activateDrone, (void *) &drone_data[i]);
			}

			for (int i = 0; i<10; i++){
				rc = pthread_join(demo0_threads[i], NULL);
			}

			break;
		case 1:
			drone drone_a;
			drone *drone_0;
			drone_0 = &drone_a;
			(*drone_0).current_x = 19;
			(*drone_0).current_y = 20;
			(*drone_0).img = 'A';
			(*drone_0).dest_img = '0';
			(*drone_0).final_x = 23;
			(*drone_0).final_y = 20;
			(*drone_0).id = 0;
			drone_0->curr_pos_prev_img = ' ';
			board[(*drone_0).current_x][(*drone_0).current_y] = (*drone_0).img;
			board[(*drone_0).final_x][(*drone_0).final_y] = (*drone_0).dest_img;



			drone drone_b;
			drone *drone_1;
			drone_1 = &drone_b;
			(*drone_1).current_x = 22;
			(*drone_1).current_y = 22;
			(*drone_1).img = 'B';
			(*drone_1).dest_img = '1';
			(*drone_1).final_x = 22;
			(*drone_1).final_y = 18;
			(*drone_1).id = 1;
			drone_1->curr_pos_prev_img = ' ';
			board[(*drone_1).current_x][(*drone_1).current_y] = (*drone_1).img;
			board[(*drone_1).final_x][(*drone_1).final_y] = (*drone_1).dest_img;

			drone drone_c;
			drone *drone_2;
			drone_2 = &drone_c;
			(*drone_2).current_x = 24;
			(*drone_2).current_y = 19;
			(*drone_2).img = 'C';
			(*drone_2).dest_img = '2';
			(*drone_2).final_x = 20;
			(*drone_2).final_y = 19;
			(*drone_2).id = 2;
			drone_2->curr_pos_prev_img = ' ';
			board[(*drone_2).current_x][(*drone_2).current_y] = (*drone_2).img;
			board[(*drone_2).final_x][(*drone_2).final_y] = (*drone_2).dest_img;



			drone drone_d;
			drone *drone_3;
			drone_3 = &drone_d;
			(*drone_3).current_x = 21;
			(*drone_3).current_y = 17;
			(*drone_3).img = 'D';
			(*drone_3).dest_img = '3';
			(*drone_3).final_x = 21;
			(*drone_3).final_y = 21;
			(*drone_3).id = 3;
			drone_3->curr_pos_prev_img = ' ';
			board[(*drone_3).current_x][(*drone_3).current_y] = (*drone_3).img;
			board[(*drone_3).final_x][(*drone_3).final_y] = (*drone_3).dest_img;

			printBoard();
			pthread_t demo1_threads[4];


			rc = pthread_create(&demo1_threads[0], NULL, activateDrone, (void *)drone_0);
			rc = pthread_create(&demo1_threads[1], NULL, activateDrone, (void *)drone_1);
			rc = pthread_create(&demo1_threads[2], NULL, activateDrone, (void *)drone_2);
			rc = pthread_create(&demo1_threads[3], NULL, activateDrone, (void *)drone_3);
			rc = pthread_join(demo1_threads[0],NULL);
			rc = pthread_join(demo1_threads[1],NULL);
			rc = pthread_join(demo1_threads[2],NULL);
			rc = pthread_join(demo1_threads[3],NULL);
			break;
		case 2:
			break;
	}

	
	printBoard();
	printf("completed");


	return 0;
}

void placeDroneOnBoard(drone *drone_arg){
	bool drone_loc_set = false;
	bool drone_dest_set = false;
	while (!drone_loc_set){
		int drone_loc_x = rand() % 40 + 1;
		int drone_loc_y = rand() % 40 + 1;
		if (board[drone_loc_x][drone_loc_y] == ' '){
			drone_loc_set = true;
			drone_arg->current_x = drone_loc_x;
			drone_arg->current_y = drone_loc_y;
			board[drone_loc_x][drone_loc_y] = drone_arg->img;
		}
	}
	while (!drone_dest_set){
		int drone_dest_x = rand() % 40 + 1;
		int drone_dest_y = rand() % 40 + 1;
		if (board[drone_dest_x][drone_dest_y] == ' '){
			drone_dest_set = true;
			drone_arg->final_x = drone_dest_x;
			drone_arg->final_y = drone_dest_y;
			board[drone_dest_x][drone_dest_y] = drone_arg->dest_img;
		}
	}


}

// potential lock placement in this method
void moveDrone(drone *drone_arg){

	int drone_current_x = drone_arg->current_x;
	int drone_current_y = drone_arg->current_y;
	int drone_final_x = drone_arg->final_x;
	int drone_final_y = drone_arg->final_y;
	int drone_potential_x;
	int drone_potential_y;
	char drone_char = drone_arg->img;
	char dest_char = drone_arg->dest_img;
	int dir = rand() % 2;

	//start with x dir
	if (dir == 0){
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
				char potential_char = board [drone_current_x][drone_potential_y];
				if ((potential_char == ' ') || (potential_char == dest_char) || ((potential_char < 64) && (potential_char > 47))){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_current_x][drone_potential_y];
					board[drone_current_x][drone_potential_y] =drone_char;
					drone_arg->current_x = drone_current_x;
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

	//start with y dir
	else{
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

		//do x
		if (drone_potential_y == drone_current_y){
			// y arith
			if (drone_current_x < drone_final_x){
				drone_potential_x = drone_current_x + 1;
			}
			else if(drone_current_x > drone_final_x){
				drone_potential_x = drone_current_x - 1;
			}
			else{
				drone_potential_x = drone_current_x;
			}

			if (drone_potential_x == drone_current_x){
				//do nothing?
			}

			else{
				char potential_char = board [drone_potential_x][drone_current_y];
				if ((potential_char == ' ') || (potential_char == dest_char) || ((potential_char < 64) && (potential_char > 47))){
					board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
					drone_arg->curr_pos_prev_img = board[drone_potential_x][drone_current_y];
					board[drone_potential_x][drone_current_y] =drone_char;
					drone_arg->current_x = drone_potential_x;
					drone_arg->current_y = drone_current_y;
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
		//do y
		else{
			char potential_char = board [drone_current_x][drone_potential_y];
			
			if ((potential_char == ' ') || (potential_char == dest_char) || ((potential_char < 64) && (potential_char > 47))){
				board[drone_current_x][drone_current_y] = drone_arg->curr_pos_prev_img;
				drone_arg->curr_pos_prev_img = board[drone_current_x][drone_potential_y];
				board[drone_current_x][drone_potential_y] =drone_char;
				drone_arg->current_x = drone_current_x;
				drone_arg->current_y = drone_potential_y;
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
}

void *activateDrone(void *drone_arg){
	drone *cur_drone = (drone *)drone_arg;
	int cur_drone_id = cur_drone->id;

	while (((cur_drone->current_x)!=(cur_drone->final_x)) || ((cur_drone->current_y)!=(cur_drone->final_y))){
		pthread_mutex_lock(&lock);
		moveDrone(cur_drone);
		printBoard();
		pthread_mutex_unlock(&lock);
		usleep(250000);
	}
	board[(cur_drone->current_x)][(cur_drone->current_y)] = ' ';
	pthread_exit(NULL);
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

	int x = (*drone_arg).current_x;
	int y = (*drone_arg).current_y;
	int fx = (*drone_arg).final_x;
	int fy = (*drone_arg).final_y;
	char c = (*drone_arg).img;

	printf("%c %d %d %d %d\n",c,x,y,fx,fy  );
}