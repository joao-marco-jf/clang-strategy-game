#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>

int read_dimensions(FILE *file, int *rows, int *columns);
int read_num_factions(FILE *file, int *num_factions);
int read_part_action(FILE *file, char *part, char *action);
int read_alliances(FILE *file, char *faction);
int read_attack(FILE *file, char *param, int *params);
int read_combat(FILE *file, char *enemy_name, int *self_value, int *enemy_value);
int read_others(FILE *file, char *params);
int read_all_file(FILE *file);

#endif