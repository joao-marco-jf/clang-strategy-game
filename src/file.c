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

int read_win(FILE *file, int* type_a, char name_b[15], int* type_b)
{
    return fscanf(file, "%i %s %i", &(*type_a), name_b, &(*type_b));
}
int read_lose(FILE *file, int* type_a, char name_b[15], int* type_b)
{
    return fscanf(file, "%i %s %i", &(*type_a), name_b, &(*type_b));
}
int read_earn(FILE *file, int* param)
{
    return fscanf(file, "%i", param) == 1 ? 0 : 1;
}

/**
 * @brief Lê todos os dados do arquivo e processa as ações correspondentes.
 *
 * @param file Ponteiro para o arquivo.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int read_all_file(FILE *file) {
    FILE *log = fopen("saida.txt", "w+");
    fclose(log);

    log = fopen("saida.txt", "a");
    

    int rows, columns;
    if (read_dimensions(file, &rows, &columns) != 0) {
        printf("Falha ao ler as dimensões do tabuleiro.\n");
        return 1;
    }

    board_t *board = create_board(rows, columns);
    int map[columns][rows];
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            int random = rand() % 10;

            map[i][j] = ((random >= 0 && random < 6) ? 0 : (random >= 6 && random < 9) ? 1 : 2);
        }
    }

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
                handle_alliance(log, &factions, part, faction);
            }
        } else if (strcmp(action, "ataca") == 0) {
            char param[MAX_FACTION_NAME_LEN];
            int params[MAX_PARAMS];
            if (read_attack(file, param, params) == 0) {
                handle_attack(log, &factions, part, param);
            }
        } else if (strcmp(action, "combate") == 0) {
            char enemy_name[MAX_FACTION_NAME_LEN];
            int self_value, enemy_value;
            if (read_combat(file, enemy_name, &self_value, &enemy_value) == 0) {
                handle_combat(log,board, &units, part, enemy_name);
            }
        } 
        else if (strcmp(action, "ganha") == 0){
            int power;
            if(read_earn(file, &power) == 0){
                handle_earn(log, &factions, part, power);
            }
        }
        else if (strcmp(action, "perde") == 0)
        {
            
        }
        else if(strcmp(action, "vence") == 0)
        {

        }
        else if (strcmp(action, "pos") == 0) {
            int params[MAX_PARAMS];
            if (num_factions > 0) {
                if (read_position_faction(file, params) == 0) {
                    handle_position_faction(log, &board, &factions, part, params);
                    num_factions--;
                }
            } else {
                if (read_position_unit(file, params) == 0) {
                    handle_position_unit(log, &board, &factions, &units, part, params);
                }
            }
        } else if (strcmp(action, "move") == 0) {
            int params[MAX_PARAMS];
            if (read_move(file, params) == 0) {
                handle_move(log, board, &units, part, params);
            }
        } else if (strcmp(action, "coleta") == 0) {
            int params[MAX_PARAMS];
            if (read_collect(file, params) == 0) {
                handle_collect(log, &factions, &units, columns, rows, map, part);
            }
        } else if (strcmp(action, "constroi") == 0) {
            int params[MAX_PARAMS];
            if (read_building(file, params) == 0) {
                handle_building(log, &board, &factions, &buildings, part, params);
            }
        } else if (strcmp(action, "defende") == 0) {
            int params[MAX_PARAMS];
            if (read_defend(file, params) == 0) {
                handle_defend(log, &factions, part);
            }
        }

        fprintf(log, "=== Fim do turno ===\n");
        faction_t *temp = factions;
        while(temp != NULL){
            fprintf(log, "Turno do jogador %s finalizado.\n", temp->name);
            fprintf(log, "Recursos atualizados: %d.\n", temp->resources);
            fprintf(log, "Poder atualizado: %d.\n", temp->power);
            fprintf(log, "\n");
            temp = temp->next;
        }
    }

    fclose(file);

    faction_t *winner = NULL;
    faction_t *current_faction = factions;

    while (current_faction != NULL) {
        // Verifica se ainda não há vencedor ou se a facção atual supera o vencedor atual
        if (winner == NULL || current_faction->power + current_faction->resources > winner->power + winner->resources) {
            winner = current_faction;
        }
        current_faction = current_faction->next;
    }

    if (winner != NULL) {
        // Aqui você pode fazer o que for necessário com o vencedor, por exemplo, imprimir no log:
        fprintf(log, "A facção vencedora é: %s\n", winner->name);
        fprintf(log, "Poder: %d\n", winner->power);
        fprintf(log, "Recursos: %d\n\n", winner->resources);
    } else {
        // Caso nenhuma facção tenha poder ou recursos positivos
        fprintf(log, "Nenhuma facção tem poder ou recursos positivos. Não há vencedor.\n\n");
    }

    fprintf(log, "=== Vitória alcançada ===\n");
    fprintf(log, "Facção %s alcançou a vitória!\n", part);
    fprintf(log, "Parabéns!\n\n");

    fclose(log);

    free_factions(&factions);
    free_buildings(&buildings);
    free_units(&units);
    free_alliances(&alliances);
    free_board(board);
    free(board);
    return 0;
}