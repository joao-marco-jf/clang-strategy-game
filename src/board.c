#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game/board.h"

board_poss_t *create_board()
{
    board_poss_t *new_board_poss = NULL;
    new_board_poss = (board_poss_t *) malloc(sizeof(board_poss_t));
    if(new_board_poss == NULL) return NULL;
    new_board_poss->line = -1;
    new_board_poss->column = -1;
    new_board_poss->p_unit_t = NULL;
    new_board_poss->p_building_t = NULL;
    new_board_poss->p_faction_t = NULL;
    new_board_poss->right = NULL;
    new_board_poss->bellow = NULL;
    return new_board_poss;
}

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

void insert_board(int column_lim, int line_lim, board_poss_t** board, int line, int column, unit_t* p_unit_t, building_t* p_building_t, faction_t* p_faction_t)
{   
    board_poss_t* new_board_poss = allocate_board(line, column, p_unit_t, p_building_t, p_faction_t);
    if(new_board_poss == NULL) return;

    //CASO 0
    board_poss_t* aux = *board;
    if(aux->line == -1 && aux->column == -1)
    {
        *board = new_board_poss;
        return;
    }

    //CASO 1
    if(line == 0 && column == 0)
    {
        (*board)->right = new_board_poss;
        (*board)->bellow = new_board_poss;
        return;
    }

    //CASO 2
    if(line == 0)
    {
        while(aux->right->column < column){
            aux = aux->right;
        }
        (*board)->bellow = new_board_poss;
        aux->right = new_board_poss;
        return;
    }

    //CASO 3
    if(column == 0)
    {
        while(aux->bellow->line < line)
        {
            aux = aux->bellow;
        }
        (*board)->right = new_board_poss;
        aux->bellow = new_board_poss;
        return;
    }

    //CASO 4
    for(int i = 0; i < line - 1; i++)
    {
        aux = aux->bellow;
    }
    for(int i = 0; i < column - 1; i++)
    {
        aux = aux->right;
    }
    new_board_poss->right = aux->right;
    aux->right = new_board_poss;
}