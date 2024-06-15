#include "file.h"

int read_dimensions(FILE *file, int *rows, int *columns) {
    if (fscanf(file, "%i %i", rows, columns) != 2) {
        return 1;
    }
    return 0;
}

int read_num_factions(FILE *file, int *num_factions) {
    if (fscanf(file, "%i", num_factions) != 1) {
        return 1;
    }
    return 0;
}

int read_part_action(FILE *file, char *part, char *action) {
    if (fscanf(file, "%s %s ", part, action) != 2) {
        return 1;
    }
    return 0;
}

int read_alliances(FILE *file, char *faction) {
    if (fscanf(file, "%s", faction) != 1) {
        return 1;
    }
    return 0;
}

int read_attack(FILE *file, char *param, int *params) {
    if (fscanf(file, "%s", param) != 1) {
        return 1;
    }
    int index = 0;
    while (fscanf(file, "%i ", &params[index]) == 1) {
        index++;
    }
    return 0;
}

int read_combat(FILE *file, char *enemy_name, int *self_value, int *enemy_value) {
    if (fscanf(file, "%i %s %i", self_value, enemy_name, enemy_value) != 3) {
        return 1;
    }
    return 0;
}

int read_others(FILE *file, char *params) {
    int index = 0;
    while (fscanf(file, "%i ", &params[index]) == 1);
    return 0;
}

#include <stdio.h>
#include <string.h>

#include "game/board.h"
#include "game/faction.h"
#include "game/building.h"
#include "game/unit.h"

int read_all_file(FILE *file) {
    board_poss_t* board = create_board();
    faction_t* factions = NULL;
    building_t* buildings = NULL;
    unit_t* units = NULL;

    int rows, columns;
    if (read_dimensions(file, &rows, &columns) != 0) {
        printf("Failed to read the dimensions of the board.\n");
        return 1;
    }

    int num_factions;
    if (read_num_factions(file, &num_factions) != 0) {
        printf("Failed to read the number of factions.\n");
        return 1;
    }

    char part[10];
    char action[10];

    while (!feof(file)) {
        if (read_part_action(file, part, action) != 0) {
            printf("Failed to read the part and action.\n");
            break;
        }

        if (strcmp(part, "FIM") == 0) {
            printf("End of file.\n");
            break;
        }

        if (strcmp(action, "alianca") == 0) {
            char faction[10];
            if (read_alliances(file, faction) == 0) {
                printf("Alliance between %s and %s\n", part, faction);
                // Code to handle the alliance
            }
        } else if (strcmp(action, "ataca") == 0) {
            char param[10];
            int params[6];
            if (read_attack(file, param, params) == 0) {
                printf("Faction %s attack %s.\n", part, param);
                // Code to handle the attack
            }
        } else if (
            strcmp(action, "combate") == 0 ||
            strcmp(action, "ganha") == 0 ||
            strcmp(action, "perde") == 0 ||
            strcmp(action, "vence") == 0
        ) {
            char enemy_name[10];
            int self_value;
            int enemy_value;
            if (read_combat(file, enemy_name, &self_value, &enemy_value) == 0) {
                printf("Init combate %s with %s.\n", part, enemy_name);
                // Code to handle the combat
            }
        }
        /**
         * Função responsável por lidar com a ação "pos".
         * 
         * @param action Ação a ser executada.
         * @param file Arquivo de entrada.
         * @param units Lista de unidades.
         * @param factions Lista de facções.
         * @param num_factions Número de facções restantes à serem alocadas.
         */
        else if(strcmp(action, "pos") == 0){
            int params[6];
            if (read_others(file, params) == 0) {
                if(num_factions <= 0){
                    insert_unit(&units, params[0], params[1], params[2]);
                } else {
                    insert_faction(&factions, part, 500, 0);
                    num_factions--;
                }
            }
        }
        else if(strcmp(action, "move") == 0){
            int params[6];
            if (read_others(file, params) == 0) {
                printf("Move unit %s.\n", part);
                // Code to handle the other actions
            }
        }
        else if(strcmp(action, "coleta") == 0){
            int params[6];
            if (read_others(file, params) == 0) {
                printf("Collect resources with %s unit.\n", part);
                // Code to handle the other actions
            }
        }
        else if(strcmp(action, "constroi") == 0){
            int params[6];
            if (read_others(file, params) == 0) {
                printf("Build a building to %s faction.\n", part);
                // Code to handle the other actions
            }
        }
        else if (strcmp(action, "defende") == 0) {
            int params[6];
            if (read_others(file, params) == 0) {
                printf("Defend: %s\n", part);
                // Code to handle the other actions
            }
        }
    }

    fclose(file);
}