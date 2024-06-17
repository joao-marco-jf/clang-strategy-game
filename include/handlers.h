#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#define MAX_PART_LEN 15

// Handlers
void handle_alliance(faction_t **factions, char *part, char *faction);
void handle_attack(faction_t **factions, char *part, char *param);
void handle_combat(char *part, char *enemy_name, int self_value, int enemy_value);
void handle_position_faction(board_t **board, faction_t **factions, char *part, int *params);
void handle_position_unit(board_t **board, faction_t **factions, unit_t **units, char *part, int *params);
void handle_move(board_t *board, unit_t **units, char part[MAX_PART_LEN], int *params);
void handle_collect(faction_t **factions, char part[MAX_PART_LEN]);
void handle_building(board_t **board, faction_t **factions, building_t **buildings, char *part, int *params);
void handle_defend(faction_t **factions, char part[MAX_PART_LEN]);
void handle_earn(faction_t **factions, char faction_name[MAX_PART_LEN], int power);

#endif // HANDLERS_H
