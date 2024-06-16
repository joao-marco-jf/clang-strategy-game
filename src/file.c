#include "file.h"

/**
 * @brief Lê as dimensões do tabuleiro a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param rows Ponteiro para armazenar o número de linhas.
 * @param columns Ponteiro para armazenar o número de colunas.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_dimensions(FILE *file, int *rows, int *columns) {
    return fscanf(file, "%i %i", rows, columns) == 2 ? 0 : 1;
}

/**
 * @brief Lê o número de facções a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param num_factions Ponteiro para armazenar o número de facções.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_num_factions(FILE *file, int *num_factions) {
    return fscanf(file, "%i", num_factions) == 1 ? 0 : 1;
}

/**
 * @brief Lê a parte e a ação a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param part Ponteiro para armazenar a parte.
 * @param action Ponteiro para armazenar a ação.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_part_action(FILE *file, char *part, char *action) {
    return fscanf(file, "%s %s", part, action) == 2 ? 0 : 1;
}

/**
 * @brief Lê alianças a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param faction Ponteiro para armazenar a facção.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_alliances(FILE *file, char *faction) {
    return fscanf(file, "%s", faction) == 1 ? 0 : 1;
}

/**
 * @brief Lê um ataque a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param param Ponteiro para armazenar o parâmetro.
 * @param params Array para armazenar os parâmetros.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_attack(FILE *file, char *param, int *params) {
    if (fscanf(file, "%s", param) != 1) {
        return 1;
    }
    int index = 0;
    while (fscanf(file, "%i", &params[index]) == 1) {
        index++;
    }
    return 0;
}

/**
 * @brief Lê os dados de um combate a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param enemy_name Ponteiro para armazenar o nome do inimigo.
 * @param self_value Ponteiro para armazenar o valor próprio.
 * @param enemy_value Ponteiro para armazenar o valor do inimigo.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_combat(FILE *file, char *enemy_name, int *self_value, int *enemy_value) {
    return fscanf(file, "%i %s %i", self_value, enemy_name, enemy_value) == 3 ? 0 : 1;
}

/**
 * @brief Lê a posição de uma facção a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param params Array para armazenar os parâmetros.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_position_faction(FILE *file, int *params) {
    return fscanf(file, "%i %i", &params[0], &params[1]) == 2 ? 0 : 1;
}

/**
 * @brief Lê a posição de uma unidade a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param params Array para armazenar os parâmetros.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_position_unit(FILE *file, int *params) {
    return fscanf(file, "%i %i %i", &params[0], &params[1], &params[2]) == 3 ? 0 : 1;
}

/**
 * @brief Lê os dados de um edifício a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param params Array para armazenar os parâmetros.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_building(FILE *file, int *params) {
    return fscanf(file, "%i %i %i %i", &params[0], &params[1], &params[2], &params[3]) == 4 ? 0 : 1;
}

/**
 * @brief Lê os dados de um movimento a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param params Array para armazenar os parâmetros.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_move(FILE *file, int *params) {
    return fscanf(file, "%i %i %i", &params[0], &params[1], &params[2]) == 3 ? 0 : 1;
}

/**
 * @brief Lê os dados de uma coleta a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param params Array para armazenar os parâmetros.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_collect(FILE *file, int *params) {
    return fscanf(file, "%i %i", &params[0], &params[1]) == 2 ? 0 : 1;
}

/**
 * @brief Lê os dados de uma defesa a partir de um arquivo.
 *
 * @param file Ponteiro para o arquivo.
 * @param params Array para armazenar os parâmetros.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_defend(FILE *file, int *params) {
    return fscanf(file, "%i %i", &params[0], &params[1]) == 2 ? 0 : 1;
}

/**
 * @brief Lê todos os dados do arquivo e processa as ações correspondentes.
 *
 * @param file Ponteiro para o arquivo.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_all_file(FILE *file) {
    int rows, columns;
    if (read_dimensions(file, &rows, &columns) != 0) {
        printf("Falha ao ler as dimensões do tabuleiro.\n");
        return 1;
    }

    board_t *board = create_board(rows, columns);

    faction_t *factions = NULL;
    building_t *buildings = NULL;
    unit_t *units = NULL;
    alliance_t *alliances = NULL;

    int num_factions;
    if (read_num_factions(file, &num_factions) != 0) {
        printf("Falha ao ler o número de facções.\n");
        return 1;
    }

    char part[MAX_PART_LEN];
    char action[MAX_ACTION_LEN];

    while (!feof(file)) {
        srand(time(NULL));

        if (read_part_action(file, part, action) != 0) {
            printf("Falha ao ler a parte e a ação.\n");
            break;
        }

        if (strcmp(action, "alianca") == 0) {
            char faction[MAX_FACTION_NAME_LEN];
            if (read_alliances(file, faction) == 0) {
                handle_alliance(part, faction);
            }
        } else if (strcmp(action, "ataca") == 0) {
            char param[MAX_FACTION_NAME_LEN];
            int params[MAX_PARAMS];
            if (read_attack(file, param, params) == 0) {
                handle_attack(&factions, part, param);
            }
        } else if (
            strcmp(action, "combate") == 0 ||
            strcmp(action, "ganha") == 0 ||
            strcmp(action, "perde") == 0 ||
            strcmp(action, "vence") == 0
        ) {
            char enemy_name[MAX_FACTION_NAME_LEN];
            int self_value, enemy_value;
            if (read_combat(file, enemy_name, &self_value, &enemy_value) == 0) {
                handle_combat(part, enemy_name, self_value, enemy_value);
            }
        } else if (strcmp(action, "pos") == 0) {
            int params[MAX_PARAMS];
            if (num_factions > 0) {
                if (read_position_faction(file, params) == 0) {
                    handle_position_faction(&board, &factions, part, params);
                    num_factions--;
                }
            } else {
                if (read_position_unit(file, params) == 0) {
                    handle_position_unit(&board, &factions, &units, part, params);
                }
            }
        } else if (strcmp(action, "move") == 0) {
            int params[MAX_PARAMS];
            if (read_move(file, params) == 0) {
                handle_move(board, &units, part, params);
            }
        } else if (strcmp(action, "coleta") == 0) {
            int params[MAX_PARAMS];
            if (read_collect(file, params) == 0) {
                handle_collect(&factions, part);
            }
        } else if (strcmp(action, "constroi") == 0) {
            int params[MAX_PARAMS];
            if (read_building(file, params) == 0) {
                handle_building(&board, &factions, &buildings, part, params);
            }
        } else if (strcmp(action, "defende") == 0) {
            int params[MAX_PARAMS];
            if (read_defend(file, params) == 0) {
                handle_defend(&factions, part);
            }
        }
    }

    fclose(file);
    free_factions(&factions);
    free_buildings(&buildings);
    free_units(&units);
    free_alliances(&alliances);
    free_board(board);
    return 0;
}