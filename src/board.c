#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "board.h"

board_poss_t *allocate_board(int line, int column, unit_t *p_unit_t, building_t *p_building_t, faction_t *p_faction_t)
{
    board_poss_t *new_board_poss = NULL;
    new_board_poss = (board_poss_t *) malloc(sizeof(board_poss_t));
    if(new_board_poss == NULL) return NULL;
    new_board_poss->line = line;
    new_board_poss->column = column;
    new_board_poss->p_unit_t = p_unit_t;
    new_board_poss->p_building_t = p_building_t;
    new_board_poss->p_faction_t = p_faction_t;
    new_board_poss->right = NULL;
    new_board_poss->bellow = NULL;
    return new_board_poss;
}