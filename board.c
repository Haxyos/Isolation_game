#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author you
 */

/**
 * @brief The board of the game.
 */

struct board_s {
	cell tab[MAX_DIMENSION][MAX_DIMENSION];
	player tour;
	bool num_turn;
	bool hex;
	bool range;
};

board new_game(){
	board new_board = malloc(sizeof(struct board_s));
	for (int l = 0; l < NB_LINES; l++){
		for (int c = 0; c < NB_COLS; c++){
			if (l == 0 && c == NB_COLS/2){
				new_board->tab[l][c] = NORTH_KING;
			}
			else if (l == NB_LINES -1 && c == NB_COLS/2){
				new_board->tab[l][c] = SOUTH_KING;
			}
			else {
				new_board->tab[l][c] = EMPTY;
			}
		}
	}
	new_board->tour = NORTH;
	new_board->num_turn = 0;
	new_board->hex = 0;
	new_board->range = 0;
	return new_board;
}

board new_special_game(bool is_hex, bool use_range){
	board new_board = malloc(sizeof(struct board_s));

	if(is_hex == 0){
		for (int l = 0; l < NB_LINES; l++){
			for (int c = 0; c < NB_COLS; c++){
				if (l == 0 && c == NB_COLS/2){
					new_board->tab[l][c] = NORTH_KING;
				}
				else if (l == NB_LINES -1 && c == NB_COLS/2){
					new_board->tab[l][c] = SOUTH_KING;
				}
				else {
					new_board->tab[l][c] = EMPTY;
				}
			}
		}
	}
	else {
		int compteur1 = 0;
		for (int l = 0; l < MAX_DIMENSION; l++){
			if(l > MAX_DIMENSION / 2){
				compteur1 += 1;
			}
			for (int c = 0; c < MAX_DIMENSION; c++){
				if (l == 0 && c == MAX_DIMENSION/4){
					new_board->tab[l][c] = NORTH_KING;
				}
				else if (l == MAX_DIMENSION - 1 && c == MAX_DIMENSION / 2 + MAX_DIMENSION / 4){
					new_board->tab[l][c] = SOUTH_KING;
				}
				else if((l < MAX_DIMENSION / 2) && (c > MAX_DIMENSION/2 + l)){
					new_board->tab[l][c] = KILLED;
				}
				else if ((l > MAX_DIMENSION	/ 2) && (c <  compteur1)){
					new_board->tab[l][c] = KILLED;
				}
				else {
					new_board->tab[l][c] = EMPTY;
				}
			}
		}
	}
	new_board->tour = NORTH;
	new_board->num_turn = 0;
	new_board->hex = is_hex;
	new_board->range = use_range;
	return new_board;
}

board copy_game(board original_game){
	board new_board = malloc(sizeof(struct board_s));
	for (int l = 0; l < NB_LINES; l++){
		for (int c = 0; c < NB_COLS; c++){
			new_board->tab[l][c] = original_game->tab[l][c];
		}
	}
	new_board->tour = original_game->tour;
	new_board->hex = original_game->hex;
	new_board->range = original_game->range;
	return new_board;
}

void destroy_game(board game){
	free(game);
};

bool is_hex(board game){
	return game->hex;
}

bool uses_range(board game){
	return game->range;
}

player current_player(board game){
	return game->tour;
}

cell get_content(board game, int line, int column){
	if(is_hex(game) == 0){
		if((line < 0 || column < 0) || (line >= NB_LINES || column >= NB_COLS)){
			return KILLED;
		}
	}
	else {
		if((line < 0 || column < 0) || (line >= MAX_DIMENSION || column >= MAX_DIMENSION)){
			return KILLED;
		}
	}
	return game->tab[line][column];
}

void get_player_coordonate(board game, int tab[]){
	cell turn_current_player;
	if (game->tour == NORTH) turn_current_player = NORTH_KING;
	else turn_current_player = SOUTH_KING;

	if(is_hex(game) == 0){
		for (int l = 0; l < NB_LINES; l++){
			for (int c = 0; c < NB_COLS; c++){
				if(turn_current_player == game->tab[l][c]){
					tab[0] = l;
					tab[1] = c;
					return;
				}
			}
		}
	}
	else {
		for (int l = 0; l < MAX_DIMENSION; l++){
			for (int c = 0; c < MAX_DIMENSION; c++){
				if(turn_current_player == game->tab[l][c]){
					tab[0] = l;
					tab[1] = c;
					return;
				}
			}
		}
	}
}

player get_winner(board game){
	player tour_du_joueur = current_player(game);
	int coordonate[2];
	get_player_coordonate(game, coordonate);
	if (game->hex == 0){
		for (int l = coordonate[0]-1; l <= coordonate[0]+1; l++){
			for (int c = coordonate[1]-1; c <= coordonate[1]+1; c++){
				if (get_content(game, l, c) == EMPTY){
					return NO_PLAYER;
				}
			}
		}
	}
	else {
		for (int l = coordonate[0]-1; l <= coordonate[0]+1; l++){
			for (int c = coordonate[1]-1; c <= coordonate[1]+1; c++){
				if ((l == coordonate[0]-1 && c == coordonate[1]+1) || (l == coordonate[0]+1 && c == coordonate[1]-1));
				else if (get_content(game, l, c) == EMPTY){
					return NO_PLAYER;
				}
			}
		}
	}

	player winner_player;
	if(tour_du_joueur == NORTH) winner_player = SOUTH;
	else winner_player = NORTH;
	return winner_player;
}

enum return_code move_toward(board game, direction direction){
	//établissement des variables nécessaires
	int tab[2];
	get_player_coordonate(game, tab);
	int tmp_l = tab[0];
	int tmp_c = tab[1];
	int l = tab[0];
	int c = tab[1];
	cell opposing_player;
	if(game->tour == NORTH) opposing_player = SOUTH_KING;
	else opposing_player = NORTH_KING;

	if (direction < 0 || direction > 8){
		return RULES;
	}
	if (game->hex == 0){
		switch (direction){
			case SW :
				l += 1;
				c -= 1;
				break;
			case S :
				l += 1;
				break;
			case SE :
				l += 1;
				c += 1;
				break;
			case W :
				c -= 1;
				break;
			case E :
				c += 1;
				break;
			case NW :
				l -= 1;
				c -= 1;
				break;
			case N :
				l -= 1;
				break;
			case NE :
				l -= 1;
				c += 1;
				break;
		}

		if (l < 0 || c < 0 || l >= NB_LINES || c >= NB_COLS	|| get_content(game, l, c) == KILLED){
		return OUT;
		}
		else if (get_content(game, l, c) == opposing_player){
			return BUSY;
		}
		else if (game->num_turn != 0){
			return RULES;
		}
	}
	else {
		switch (direction){
			case SW :
				l += 1;
				break;
			case S :
				return RULES;
			case SE :
				l += 1;
				c += 1;
				break;
			case W :
				c -= 1;
				break;
			case E :
				c += 1;
				break;
			case NW :
				l -= 1;
				c -= 1;
				break;
			case N :
				return RULES;
			case NE :
				l -= 1;
				break;
			default :
				return RULES;
		}

		if (l < 0 || c < 0 || l >= MAX_DIMENSION || c >= MAX_DIMENSION	|| get_content(game, l, c) == KILLED){
			return OUT;
		}
		else if (get_content(game, l, c) == opposing_player){
			return BUSY;
		}
		else if (game->num_turn != 0){
			return RULES;
		}
	}

	game->num_turn = 1;
	game->tab[l][c] = current_player(game);
	game->tab[tmp_l][tmp_c] = EMPTY;
	return OK;
	
}

enum return_code kill_cell(board game, int line, int column){
	int coordonate[2];
	get_player_coordonate(game, coordonate);
	if(is_hex(game) == 0){
		if (game->num_turn != 1 || (game->range == 1 && (coordonate[0] - line < -3 || coordonate[0] - line > 3 || coordonate[1] - column < -3 || coordonate[1] - column > 3))){
		return RULES;
		}
		else if (line < 0 || column < 0 || line >= NB_LINES || column >= NB_COLS || get_content(game, line, column) == KILLED){
			return OUT;
		}
		else if (get_content(game, line, column) == NORTH_KING || get_content(game, line, column) == SOUTH_KING){
			return BUSY;
		}
	}
	else {
		if (game->num_turn != 1 || (game->range == 1 && (coordonate[0] - line < -3 || coordonate[0] - line > 3 || coordonate[1] - column < -3 || coordonate[1] - column > 3))){
			return RULES;
		}
		else if (line < 0 || column < 0 || line >= MAX_DIMENSION || column >= MAX_DIMENSION || get_content(game, line, column) == KILLED){
			return OUT;
		}
		else if (get_content(game, line, column) == NORTH_KING || get_content(game, line, column) == SOUTH_KING){
			return BUSY;
		}
	}

	game->num_turn = 0;
	game->tab[line][column] = KILLED;
	if(game->tour == NORTH) game->tour = SOUTH;
	else game->tour = NORTH;
	return OK;
}
