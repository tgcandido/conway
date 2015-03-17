#pragma once

#include <stdbool.h>
#include "board.h"
#include "lexical_analyzer.h"

bool analyze_and_set_positions(p_config_pair, p_game_board);
bool C(p_config_pair, p_game_board);
bool L(p2_config_pair, p_game_board);
bool P(p2_config_pair, p_game_board);
bool R(p2_config_pair, p_game_board);
void next_pair(p2_config_pair);
bool set_position(p_game_board, int32_t, int32_t);