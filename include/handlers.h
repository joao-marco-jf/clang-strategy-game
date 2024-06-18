#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#define MAX_PART_LEN 15

// Handlers
void handle_alliance(FILE *log, faction_t **factions, char *part, char *faction);
void handle_attack(FILE *log, faction_t **factions, char *part, char *param);
void handle_combat(FILE *log, board_t *board, unit_t **units, char *part, char *enemy_name);
void handle_position_faction(FILE *log, board_t **board, faction_t **factions, char *part, int *params);
void handle_position_unit(FILE *log, board_t **board, faction_t **factions, unit_t **units, char *part, int *params);
void handle_move(FILE *log, board_t *board, unit_t **units, char part[MAX_PART_LEN], int *params);
void handle_collect(FILE *log, faction_t **factions, unit_t **units, int columns, int rows, int map[columns][rows], char part[MAX_PART_LEN]);
void handle_building(FILE *log, board_t **board, faction_t **factions, building_t **buildings, char *part, int *params);
void handle_defend(FILE *log, faction_t **factions, char part[MAX_PART_LEN]);
void handle_earn(FILE *log, faction_t **factions, char faction_name[MAX_PART_LEN], int power);

#endif // HANDLERS_H
