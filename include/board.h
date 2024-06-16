#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "faction.h"
#include "building.h"
#include "unit.h"

typedef struct node_t{
    int line;
    int col;
    unit_t *unit;
    building_t *building;
    faction_t *faction;
    struct node_t *next;
} node_t;

typedef struct board_t{
    int lines;
    int columns;
    node_t *head;
}board_t;

board_t *create_board(int lines, int columns);
node_t *allocate_node(int line, int col, unit_t* p_unit, building_t* p_building, faction_t* p_faction);
void insert_node(board_t *board, int line, int col, unit_t *p_unit, building_t *p_building, faction_t *p_factions);
faction_t *get_faction_board(board_t *board, int line, int col);
building_t *get_building_board(board_t *board, int line, int col);
unit_t *get_unit_board(board_t *board, int line, int col);
void remove_node(board_t *board_t, int row, int col);
void free_board(board_t *board);
void print_board(board_t *board);

#endif