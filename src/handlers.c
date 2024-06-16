/**
 * @file handlers.c
 * @brief Contém a implementação de diversos manipuladores para um jogo de estratégia.
 *
 * Este arquivo define funções que lidam com diferentes ações em um jogo de estratégia, como alianças, ataques, combates, posicionamento de facções e unidades, movimentação, coleta de recursos, construção de edifícios e defesa.
 * Cada função manipuladora executa ações específicas relacionadas à ação correspondente no jogo.
 * As funções neste arquivo são usadas para manipular o estado do jogo e imprimir informações relevantes no console.
 */

#include "handlers.h"

history_t history = {"", "", 0};

void handle_alliance(char *part, char *faction) {
    printf("Aliança entre %s e %s\n", part, faction);
    // Código para lidar com a aliança
}

/**
 * Lida com o ataque entre duas facções.
 *
 * Esta função recebe um array de ponteiros para facções, o nome da facção atacante, o nome da facção defensora,
 * e um array de inteiros representando parâmetros adicionais. Ela realiza o ataque gerando aleatoriamente
 * a quantidade de recursos roubados da facção defensora e atualiza os recursos de ambas as facções de acordo.
 * A função também atualiza o histórico de ataques armazenando o nome da facção atacante, o nome da facção defensora,
 * e a quantidade de recursos roubados.
 *
 * @param factions Um array de ponteiros para facções.
 * @param part O nome da facção atacante.
 * @param param O nome da facção defensora.
 * @param params Um array de inteiros representando parâmetros adicionais.
 */
void handle_attack(faction_t **factions, char *part, char *param) {
    // Imprime a mensagem de ataque
    printf("A facção %s ataca %s.\n", part, param);
    
    // Gera uma quantidade aleatória de recursos roubados
    int random_resources = rand() % 50;
    
    // Obtém as facções atacantes e defensoras
    faction_t *attacking_faction = get_faction(&(*factions), part);
    faction_t *defending_faction = get_faction(&(*factions), param);

    // Verifica se as facções foram encontradas
    if(attacking_faction == NULL || defending_faction == NULL) {
        printf("Facção não encontrada.\n");
        return;
    }

    // Atualiza o histórico de ataques
    strcpy(history.attacking_faction, part);
    strcpy(history.defending_faction, param);
    history.stolen_resources = random_resources;

    // Atualiza os recursos das facções
    attacking_faction->resources += random_resources;
    defending_faction->resources -= random_resources;

    // Imprime os recursos atualizados das facções
    printf("A facção %s agora tem %d recursos.\n", attacking_faction->name, attacking_faction->resources);
    printf("A facção %s agora tem %d recursos.\n", defending_faction->name, defending_faction->resources);
}

void handle_combat(char *part, char *enemy_name, int self_value, int enemy_value) {
    printf("Iniciar combate: %s com %s (próprio: %d, inimigo: %d)\n", part, enemy_name, self_value, enemy_value);
    // Código para lidar com o combate
}

/**
 * Lida com a posição de uma facção no tabuleiro.
 *
 * Esta função insere uma nova facção na lista de facções e insere um novo nó no tabuleiro
 * com os parâmetros especificados. Em seguida, imprime o tabuleiro atualizado.
 *
 * @param board     Um ponteiro para o tabuleiro.
 * @param factions  Um ponteiro para a lista de facções.
 * @param part      O nome da facção.
 * @param params    Um array contendo as coordenadas x e y para o novo nó.
 */
void handle_position_faction(board_t **board, faction_t **factions, char *part, int *params) {
    insert_faction(&(*factions), part, 100, 100);
    insert_node(*board, params[0], params[1], NULL, NULL, *factions);
    print_board(*board);
    printf("\n");
}

/**
 * Lida com o posicionamento de uma unidade no tabuleiro do jogo.
 *
 * Esta função insere uma unidade no tabuleiro do jogo na posição especificada.
 * Também atualiza o poder da facção e imprime o tabuleiro atualizado.
 *
 * @param board     Um ponteiro para o tabuleiro do jogo.
 * @param factions  Um ponteiro para o array de facções.
 * @param units     Um ponteiro para o array de unidades.
 * @param part      O tipo de unidade a ser inserida.
 * @param params    Um array contendo os parâmetros para inserção da unidade.
 *                  params[0] - O índice da facção.
 *                  params[1] - A coordenada x da posição.
 *                  params[2] - A coordenada y da posição.
 */
void handle_position_unit(board_t **board, faction_t **factions, unit_t **units, char *part, int *params) {
    printf("Inserir unidade %s no tabuleiro em %d, %d.\n", part, params[1], params[2]);
    insert_unit(&(*units), params[1], params[2], part, params[0]);
    insert_node(*board, params[1], params[2], *units, NULL, NULL);

    char faction_name[3];
    sprintf(faction_name, "F%c", part[0]);
    faction_t *faction = get_faction(&(*factions), faction_name);
    if(faction == NULL) {
        printf("Facção não encontrada.\n");
        return;
    }

    faction->power += 10;
    printf("A facção %s agora tem %d poder.\n", faction->name, faction->power);

    print_board(*board);
    printf("\n");
}

/**
 * Move uma unidade no tabuleiro do jogo para uma posição especificada.
 *
 * @param board O tabuleiro do jogo.
 * @param units O array de unidades.
 * @param part O nome da unidade a ser movida.
 * @param params O array de parâmetros contendo as coordenadas da nova posição.
 */
void handle_move(board_t *board, unit_t **units, char part[MAX_PART_LEN], int *params) {
    printf("Mover unidade %s para %d, %d.\n", part, params[1], params[2]);
    unit_t *unit = get_unit(&(*units), part);
    if(unit == NULL) {
        printf("Unidade não encontrada.\n");
        return;
    }

    faction_t *faction = get_faction_board(board, unit->x, unit->y);
    building_t *building = get_building_board(board, unit->x, unit->y);

    remove_node(board, unit->x, unit->y);
    if(faction || building) insert_node(board, unit->x, unit->y, NULL, building, faction);
    insert_node(board, params[1], params[2], unit, NULL, NULL);
    unit->x = params[1];
    unit->y = params[2];
    
    print_board(board);
    printf("\n");
}

/**
 * Lida com a coleta de recursos com uma unidade específica.
 *
 * Esta função coleta recursos com a unidade especificada e atualiza os recursos da facção de acordo.
 *
 * @param factions Um ponteiro para o array de facções.
 * @param part O identificador da unidade.
 * @param params Um array de parâmetros (não utilizado nesta função).
 */
void handle_collect(faction_t **factions, char part[MAX_PART_LEN]) {
    printf("Coletar recursos com a unidade %s.\n", part);
    char faction_name[3];
    sprintf(faction_name, "F%c", part[0]);
    faction_t *faction = get_faction(&(*factions), faction_name);
    if(faction == NULL) {
        printf("Facção não encontrada.\n");
        return;
    }

    faction->resources += 10;
    printf("A facção %s agora tem %d recursos.\n", faction->name, faction->resources);
}

/**
 * Lida com o processo de construção de um novo edifício para uma facção específica no tabuleiro do jogo.
 *
 * @param board Um ponteiro para o tabuleiro do jogo.
 * @param factions Um ponteiro para o array de facções.
 * @param buildings Um ponteiro para o array de edifícios.
 * @param part O nome da facção para a qual o edifício está sendo construído.
 * @param params Um array de dois inteiros representando as coordenadas do edifício no tabuleiro do jogo.
 */
void handle_building(board_t **board, faction_t **factions, building_t **buildings, char *part, int *params) {
    printf("Construir um edifício para a facção %s em %d, %d.\n", part, params[0], params[1]);
    insert_building(&(*buildings), params[0], params[1], part, params[0]);
    insert_node(*board, params[0], params[1], NULL, *buildings, NULL);

    faction_t *faction = get_faction(&(*factions), part);
    if(faction == NULL) {
        printf("Facção não encontrada.\n");
        return;
    }

    faction->resources -= 10;
    faction->power += 10;

    printf("A facção %s agora tem %d recursos.\n", faction->name, faction->resources);
    printf("A facção %s agora tem %d poder.\n", faction->name, faction->power);

    print_board(*board);
    printf("\n");
}

/**
 * Lida com a ação de defesa no jogo de estratégia.
 *
 * Esta função é responsável por lidar com a ação de defesa no jogo de estratégia.
 * Ela recebe um array de ponteiros para facções, uma string representando parte do nome da facção defensora,
 * e um array de inteiros representando parâmetros adicionais.
 *
 * @param factions Um array de ponteiros para facções.
 * @param part Uma string representando parte do nome da facção defensora.
 * @param params Um array de inteiros representando parâmetros adicionais.
 */
void handle_defend(faction_t **factions, char part[MAX_PART_LEN]) {
    printf("Defender: %s\n", part);
    faction_t *defending_faction = get_faction(&(*factions), part);

    if(defending_faction == NULL) {
        printf("Facção não encontrada.\n");
        return;
    }

    if(strcmp(history.defending_faction, part) == 0) {
        faction_t *attacking_faction = get_faction(&(*factions), history.attacking_faction);

        if(attacking_faction == NULL) {
            printf("Facção não encontrada.\n");
            return;
        }

        defending_faction->resources += history.stolen_resources;
        attacking_faction->resources -= history.stolen_resources;

        printf("Recursos roubados: %d\n", history.stolen_resources);
        printf("A facção %s agora tem %d recursos.\n", defending_faction->name, defending_faction->resources);
        printf("A facção %s agora tem %d recursos.\n", attacking_faction->name, attacking_faction->resources);
    }
}