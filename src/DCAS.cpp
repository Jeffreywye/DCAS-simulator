#include <iostream>
#include <pthread.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <queue>
#include <string>

using namespace std;
//Global Variables
const int board_size = 42;
const int num_drones = 4;
char board[board_size][board_size];
volatile int drone_turn = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
queue<int> available_drones;
int airport_x;
int airport_y;
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
void deployDroneFromAirport(drone *drone_arg);
void printBoard();
void placeAirport();
void moveDrone( drone *drone_arg);
void printDrone( drone *drone_arg);
void placeDroneOnBoard(drone *drone_arg);
void instantiateBoard();
void *activateDrone(void *drone_arg);

int main(){
	printf("Hello\n");
	int rc;
	instantiateBoard();
	string input;
	int demo;
	char temp;
	bool prompt_flag = true;
	while (prompt_flag){
		printf ("Welcome to DCAS simulator\nPlease select a drone case to run by pressing a number then hit the enter key\n");
		printf ("[0] - Run the simulator spawning 10 drones at random locations\n");
		printf ("[1] - Run the 4 drone collision simulator\n");
		printf ("[2] - Run the 2 drone vertical collision simulator\n");
		printf ("[3] - Run the simulator deploying drones from an airport to deliver packages\n");
		printf ("[4] - Run the simulator to continuously deploy the drones (MAX 10) from the airport to deliver packages\n");
		printf ("Press the [ctrl] AND [c] keys together to exit anytime during the simulations\n");
		cin >> input;
		printf("%d\n",input);
		temp = input.at(0);
		printf("%c\n", temp);
		if (((temp < 53)&&(temp >= 48))&&(input.length() == 1)){
			prompt_flag = false;
		}
	}

	demo = temp - 48;
	printf("demo: %d\n",demo);
	srand (time(NULL));
	
	switch(demo){
		case 0:
			
			pthread_t demo0_threads[10];
			drone drone_data[10];
			placeAirport();

			for (int i = 0; i<10; i++){
				char demo0_drone_img = 'A' + i;				
				char demo0_dest_img = '0' + i;
				drone_data[i].img = demo0_drone_img;
				drone_data[i].dest_img = demo0_dest_img;
				drone_data[i].curr_pos_prev_img = ' ';
				drone_data[i].id = i;
				placeDroneOnBoard(&drone_data[i]);
				// printDrone(&drone_data[i]);
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
			(*drone_0).current_x = 17;
			(*drone_0).current_y = 20;
			(*drone_0).img = 'A';
			(*drone_0).dest_img = '0';
			(*drone_0).final_x = 25;
			(*drone_0).final_y = 20;
			(*drone_0).id = 0;
			drone_0->curr_pos_prev_img = ' ';
			board[(*drone_0).current_x][(*drone_0).current_y] = (*drone_0).img;
			board[(*drone_0).final_x][(*drone_0).final_y] = (*drone_0).dest_img;

			drone drone_b;
			drone *drone_1;
			drone_1 = &drone_b;
			(*drone_1).current_x = 22;
			(*drone_1).current_y = 24;
			(*drone_1).img = 'B';
			(*drone_1).dest_img = '1';
			(*drone_1).final_x = 22;
			(*drone_1).final_y = 16;
			(*drone_1).id = 1;
			drone_1->curr_pos_prev_img = ' ';
			board[(*drone_1).current_x][(*drone_1).current_y] = (*drone_1).img;
			board[(*drone_1).final_x][(*drone_1).final_y] = (*drone_1).dest_img;

			drone drone_c;
			drone *drone_2;
			drone_2 = &drone_c;
			(*drone_2).current_x = 26;
			(*drone_2).current_y = 19;
			(*drone_2).img = 'C';
			(*drone_2).dest_img = '2';
			(*drone_2).final_x = 18;
			(*drone_2).final_y = 19;
			(*drone_2).id = 2;
			drone_2->curr_pos_prev_img = ' ';
			board[(*drone_2).current_x][(*drone_2).current_y] = (*drone_2).img;
			board[(*drone_2).final_x][(*drone_2).final_y] = (*drone_2).dest_img;

			drone drone_d;
			drone *drone_3;
			drone_3 = &drone_d;
			(*drone_3).current_x = 21;
			(*drone_3).current_y = 15;
			(*drone_3).img = 'D';
			(*drone_3).dest_img = '3';
			(*drone_3).final_x = 21;
			(*drone_3).final_y = 23;
			(*drone_3).id = 3;
			drone_3->curr_pos_prev_img = ' ';
			board[(*drone_3).current_x][(*drone_3).current_y] = (*drone_3).img;
			board[(*drone_3).final_x][(*drone_3).final_y] = (*drone_3).dest_img;

			placeAirport();
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
			drone drone_e;
			drone *drone_4;
			drone_4 = &drone_e;
			(*drone_4).current_x = 1;
			(*drone_4).current_y = 20;
			(*drone_4).img = 'E';
			(*drone_4).dest_img = '4';
			(*drone_4).final_x = 30;
			(*drone_4).final_y = 20;
			(*drone_4).id = 4;
			drone_4->curr_pos_prev_img = ' ';
			board[(*drone_4).current_x][(*drone_4).current_y] = (*drone_4).img;
			board[(*drone_4).final_x][(*drone_4).final_y] = (*drone_4).dest_img;

			drone drone_f;
			drone *drone_5;
			drone_5 = &drone_f;
			(*drone_5).current_x = 40;
			(*drone_5).current_y = 20;
			(*drone_5).img = 'F';
			(*drone_5).dest_img = '5';
			(*drone_5).final_x = 10;
			(*drone_5).final_y = 20;
			(*drone_5).id = 5;
			drone_5->curr_pos_prev_img = ' ';
			board[(*drone_5).current_x][(*drone_5).current_y] = (*drone_5).img;
			board[(*drone_5).final_x][(*drone_5).final_y] = (*drone_5).dest_img;

			placeAirport();
			printBoard();
			pthread_t demo2_threads[2];

			rc = pthread_create(&demo2_threads[0], NULL, activateDrone, (void *)drone_4);
			rc = pthread_create(&demo2_threads[1], NULL, activateDrone, (void *)drone_5);
			rc = pthread_join(demo2_threads[0],NULL);
			rc = pthread_join(demo2_threads[1],NULL);

			break;
		case 3:
			pthread_t demo3_threads[10];
			drone demo3_drone_data[10];
			placeAirport();
			printBoard();
			usleep(1000000);
			for (int i = 0; i<10; i++){
				char demo3_drone_img = 'A' + i;
				char demo3_dest_img = '0' + i;
				demo3_drone_data[i].img = demo3_drone_img;
				demo3_drone_data[i].dest_img = demo3_dest_img;
				demo3_drone_data[i].id = i;
				deployDroneFromAirport(&demo3_drone_data[i]);
				// printDrone(&demo3_drone_data[i]);
				rc = pthread_create(&demo3_threads[i], NULL, activateDrone, (void *) &demo3_drone_data[i]);
			}

			for (int i = 0; i<10; i++){
				rc = pthread_join(demo3_threads[i], NULL);
			}
			break;

		case 4:
			pthread_t demo4_threads[10];
			drone demo4_drone_data[10];
			placeAirport();
			printBoard();
			usleep(1000000);
			for (int i = 0; i<10; i++){
				demo4_drone_data[i].id = i;
				available_drones.push(i);
			}
			while(true){
				if (!available_drones.empty()){
					int drone_id = available_drones.front();
					available_drones.pop();
					usleep(1000000);
					char demo4_drone_img = 'A' +drone_id;
					char demo4_dest_img = '0' + drone_id;
					demo4_drone_data[drone_id].img = demo4_drone_img;
					demo4_drone_data[drone_id].dest_img = demo4_dest_img;
					deployDroneFromAirport(&demo4_drone_data[drone_id]);
					rc = pthread_create(&demo4_threads[drone_id], NULL, activateDrone, (void *) &demo4_drone_data[drone_id]);
				}

			}
			break;
	}

	
	printBoard();
	printf("completed");


	return 0;
}

void placeAirport(){
	bool airport_loc_set = false;
	while(!airport_loc_set){
		airport_x = rand() % 40 + 1;
		airport_y = rand() % 40 + 1;
		if (board[airport_x][airport_y] == ' '){
			airport_loc_set = true;
			board[airport_x][airport_y] = 'X';
		}
	}
}

void deployDroneFromAirport(drone *drone_arg){
	bool airport_free = false;
	bool drone_dest_set = false;

	while (!airport_free){
		if (board[airport_x][airport_y]== 'X'){
			airport_free = true;
			drone_arg->current_x = airport_x;
			drone_arg->current_y = airport_y;
			drone_arg->curr_pos_prev_img = 'X';
			board[airport_x][airport_y] = drone_arg->img;
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
	srand (time(NULL));
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
		usleep(500000);
		pthread_mutex_lock(&lock);
		usleep(75000);
		moveDrone(cur_drone);
		printBoard();
		pthread_mutex_unlock(&lock);
	}
	// board[(cur_drone->current_x)][(cur_drone->current_y)] = ' ';
	cur_drone->final_x = airport_x;
	cur_drone->final_y = airport_y;
	cur_drone->dest_img = 'X';
	cur_drone->curr_pos_prev_img = ' ';

	while (((cur_drone->current_x)!=(cur_drone->final_x)) || ((cur_drone->current_y)!=(cur_drone->final_y))){
		usleep(500000);
		pthread_mutex_lock(&lock);
		usleep(75000);
		moveDrone(cur_drone);
		printBoard();
		pthread_mutex_unlock(&lock);
	}
	board[(cur_drone->current_x)][(cur_drone->current_y)] = 'X';
	available_drones.push((cur_drone->id));

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