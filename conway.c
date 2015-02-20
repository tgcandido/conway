#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GRID_SIZE 20
#define MID GRID_SIZE / 2

enum game_config {
	glider = 1,
	small_exploder,
	exploder,
	ten_cell_row,
	lw_spaceship,
	tumbler,
	gosper_glider_gun,
	not_found
} typedef g_config;

g_config handle_commands(int,char**);
void set_seed();
void print_help();
void set_seed_gosper_glider_gun();
void set_seed_tumbler();
void set_seed_lw_spaceship();
void set_seed_ten_cell_row();
void set_seed_exploder();
void set_seed_small_exploder();
void set_seed_glider();
void set_from_offset(int a,int b);
void play();

int grid[GRID_SIZE][GRID_SIZE]  = { 0 };

int main(int argc,char** argv){
	
	g_config config = handle_commands(argc,argv);

	switch (config){
		case (glider):
			set_seed_glider();
			break;
		case (small_exploder):
			set_seed_small_exploder();
			break;
		case (exploder):
			set_seed_exploder();
			break;
		case (ten_cell_row):
			set_seed_ten_cell_row();
			break;
		case (lw_spaceship):
			set_seed_lw_spaceship();
			break;
		case (tumbler):
			set_seed_tumbler();
			break;
		case (gosper_glider_gun):
			set_seed_gosper_glider_gun();
			break;
		default:
			printf("config not found!\n");
			exit(EXIT_FAILURE);
			break;
	}

	play();
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
		if (strcmp(command_string,"gli"))
			return glider;
		else if (strcmp(command_string,"sex"))
			return small_exploder;
		else if (strcmp(command_string,"ex"))
			return exploder;
		else if (strcmp(command_string,"tcr"))
			return ten_cell_row;
		else if (strcmp(command_string,"lws"))
			return lw_spaceship;
		else if (strcmp(command_string,"tbl"))
			return tumbler;
		else if (strcmp(command_string,"ggg"))
			return gosper_glider_gun;
	}

	return not_found;
}

void print_help(){
	printf("\n\t commands:\n");
	printf("\t\tgli for glider\n");
	printf("\t\tsex for small exploder\n");
	printf("\t\tex for exploder\n");
	printf("\t\ttcr for ten cell row\n");
	printf("\t\tlws for lightweight spaceship\n");
	printf("\t\ttbl for tumbler\n");
	printf("\t\tggg for gospel glider gun\n\n");
}

void set_seed_gosper_glider_gun(){

}

void set_seed_tumbler(){

}

void set_seed_lw_spaceship(){
	set_from_offset(1,-2);
	set_from_offset(1,1);
	set_from_offset(0,2);
	set_from_offset(-1,2);
	set_from_offset(-2,2);
	set_from_offset(-2,1);
	set_from_offset(-2,0);
	set_from_offset(-2,-1);
	set_from_offset(-1,-2);
}

void set_seed_ten_cell_row(){
	set_from_offset(0,0);
	set_from_offset(0,1);
	set_from_offset(0,-1);
	set_from_offset(0,-2);
	set_from_offset(0,2);
	set_from_offset(0,3);
	set_from_offset(0,-3);
	set_from_offset(0,4);
	set_from_offset(0,-4);
	set_from_offset(0,5);
}

void set_seed_exploder(){
	set_from_offset(-2,-2);
	set_from_offset(-1,-2);
	set_from_offset(0,-2);
	set_from_offset(1,-2);
	set_from_offset(2,-2);
	set_from_offset(-2,2);
	set_from_offset(-1,2);
	set_from_offset(0,2);
	set_from_offset(1,2);
	set_from_offset(2,2);
	set_from_offset(-2,0);
	set_from_offset(2,0);
}

void set_seed_small_exploder(){
	set_from_offset(0,0);
	set_from_offset(0,-1);
	set_from_offset(0,1);
	set_from_offset(1,1);
	set_from_offset(1,-1);
	set_from_offset(2,0);
	set_from_offset(-1,0);
}

void set_seed_glider(){
	set_from_offset(0,0);
	set_from_offset(0,-1);
	set_from_offset(0,1);
	set_from_offset(-1,1);
	set_from_offset(-2,0);
}

void play(){
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			printf("%2d",grid[i][j]);
		}
		printf("\n");
	}
}

void set_from_offset(int a, int b){
	grid[MID+a][MID+b] = 1;
}