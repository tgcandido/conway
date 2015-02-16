#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GRID_SIZE 10

enum game_config {
	glider = 1,
	small_exploder,
	exploder,
	ten_cell_row,
	lw_spaceship,
	tumbler,
	gosper_glider_gun
} typedef g_config;

g_config handle_commands(int,char**);
void set_seed(int**);
void print_help();
void set_seed_gosper_glider_gun(int**);
void set_seed_tumbler(int**);
void set_seed_lw_spaceship(int**);
void set_seed_ten_cell_row(int**);
void set_seed_exploder(int**);
void set_seed_small_exploder(int**);
void set_seed_glider(int**);
void play(int**);

int main(int argc,char** argv){
	int grid[GRID_SIZE][GRID_SIZE] = { 0 };

	g_config config = handle_commands(argc,argv);

	switch (config){
		case (glider):
			set_seed_glider(grid);
			break;
		case (small_exploder):
			set_seed_small_exploder(grid);
			break;
		case (exploder):
			set_seed_exploder(grid);
			break;
		case (ten_cell_row):
			set_seed_ten_cell_row(grid);
			break;
		case (lw_spaceship):
			set_seed_lw_spaceship(grid);
			break;
		case (tumbler):
			set_seed_tumbler(grid);
			break;
		case (gosper_glider_gun):
			set_seed_gosper_glider_gun(grid);
			break;
	}

	play(grid);
	printf("success \n");
	return EXIT_SUCCESS;
}


g_config handle_commands(int argc, char** argv){
	if (argc != 2){
		printf("invalid arguments, type -help\n");
		exit(EXIT_FAILURE);
	}

	char* command_string = argv[1];

	if (strcmp(command_string, "-help") == 0){
		print_help();
		exit(EXIT_SUCCESS);
	} else {
		return command_string[0];
	}
}

void print_help(){
	printf("\n\t commands:\n");
	printf("\t\t1 for glider\n");
	printf("\t\t2 for small exploder\n");
	printf("\t\t3 for exploder\n");
	printf("\t\t4 for ten cell row\n");
	printf("\t\t5 for lightweight spaceship\n");
	printf("\t\t6 for tumbler\n");
	printf("\t\t7 for gospel glider gun\n\n");
}

void set_seed_gosper_glider_gun(int** grid){

}

void set_seed_tumbler(int** grid){

}

void set_seed_lw_spaceship(int** grid){

}

void set_seed_ten_cell_row(int** grid){

}

void set_seed_exploder(int** grid){

}

void set_seed_small_exploder(int** grid){

}

void set_seed_glider(int** grid){

}

void play(int** grid){

}