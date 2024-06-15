#ifndef BOARD_H
#define BOARD_H

#include "faction.h"
#include "building.h"
#include "unit.h"

typedef struct board_t{
    unit_t* p_unit_t;
    building_t* p_building_t;
    faction_t* p_faction_t;
}board_t;

void init_board(int lines, int columns, board_t board[lines][columns]);
void print_board(int lines, int columns, board_t board[lines][columns]);
void insert_faction_on_board(int lines, int columns, board_t board[columns][lines], faction_t** factions, char name[15], int x, int y);
void insert_building_on_board(int lines, int columns, board_t board[columns][lines], building_t** buildings, int x, int y, building_e type);
void insert_unit_on_board(int lines, int columns, board_t board[columns][lines], unit_t** units, int x, int y, unit_e type);

void remove_unit_on_board(int lines, int columns, board_t board[columns][lines], unit_t** units, int x, int y);

#endif