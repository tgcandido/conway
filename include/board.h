#pragma once

#include <inttypes.h>

typedef struct conway_game_board{
	uint8_t** grid;
	int8_t size;
} game_board;
typedef game_board* p_game_board;