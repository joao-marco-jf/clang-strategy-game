/**
 * @file handlers.c
 * @brief Contém a implementação de diversos manipuladores para um jogo de estratégia.
 *
 * Este arquivo define funções que lidam com diferentes ações em um jogo de estratégia, como alianças, ataques, combates, posicionamento de facções e unidades, movimentação, coleta de recursos, construção de edifícios e defesa.
 * Cada função manipuladora executa ações específicas relacionadas à ação correspondente no jogo.
 * As funções neste arquivo são usadas para manipular o estado do jogo e imprimir informações relevantes no console.
 */

#include "handlers.h"

/**
 * @brief Estrutura de histórico para armazenar detalhes de ações no jogo.
 * 
 * Esta estrutura é utilizada para manter um registro das ações realizadas no jogo,
 * incluindo informações como as facções envolvidas em ataques, e a quantidade de
 * recursos roubados durante esses ataques.
 * 
 * A estrutura contém os seguintes campos:
 * - attacking_faction: Nome da facção que está realizando o ataque.
 * - defending_faction: Nome da facção que está sendo atacada.
 * - stolen_resources: Quantidade de recursos roubados durante o ataque.
 */

history_t history = {"", "", 0};

/**
 * @brief Estabelece uma aliança entre duas facções e atualiza seus poderes.
 * 
 * Esta função estabelece uma aliança entre duas facções no jogo. Ela insere cada facção na lista de
 * alianças da outra facção e atualiza o poder das facções conforme o poder da facção aliada é adicionado.
 * A função registra a aliança no log, junto com os novos valores de poder das facções envolvidas.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto para escrita.
 * @param factions Um ponteiro para um ponteiro da lista de facções. A função assume que essa lista está corretamente inicializada.
 * @param part O nome da primeira facção que está estabelecendo a aliança. Deve ser uma string válida correspondente a uma facção existente.
 * @param faction O nome da segunda facção que será aliada. Deve ser uma string válida correspondente a uma facção existente.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre O ponteiro para a lista de facções (`factions`) deve apontar para uma lista inicializada e não ser nulo.
 * @pre Os nomes das facções (`part` e `faction`) devem ser strings válidas que correspondem a facções existentes no jogo.
 * 
 * @post As facções `part` e `faction` estarão aliadas entre si, com seus poderes atualizados de acordo com a soma dos poderes.
 * @post A aliança entre as facções será registrada no log, incluindo os novos valores de poder das facções envolvidas.
 */
void handle_alliance(FILE *log, faction_t **factions, char *part, char *faction) {
    faction_t *faction0 = get_faction(factions, part);
    faction_t *faction1 = get_faction(factions, faction);
    insert_alliance(&(faction0->alliance), faction);
    insert_alliance(&(faction1->alliance), part);

    int temp0 = faction0->power;
    faction0->power += faction1->power;
    faction1->power += temp0;

    fprintf(log, "=== Aliança estabelecida ===\n");
    fprintf(log, "Facção %s e Facção %s estão agora aliadas.\n", faction0->name, faction1->name);
    fprintf(log, "%s agora possui %d de poder.\n", faction0->name, faction0->power);
    fprintf(log, "%s agora possui %d de poder.\n\n", faction1->name, faction1->power);
}

/**
 * @brief Realiza um ataque entre facções e registra o resultado no log.
 * 
 * Esta função simula um ataque entre duas facções no jogo. Ela gera uma quantidade aleatória de recursos
 * roubados durante o ataque, atualiza os recursos das facções envolvidas e registra as mudanças no log.
 * Além disso, mantém um histórico do ataque, armazenando as facções envolvidas e a quantidade de recursos roubados.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto para escrita.
 * @param factions Um ponteiro para um ponteiro da lista de facções. A função assume que essa lista está corretamente inicializada.
 * @param part O nome da facção que está realizando o ataque. Deve ser uma string válida.
 * @param param O nome da facção que está sendo atacada. Deve ser uma string válida.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre O ponteiro para a lista de facções (`factions`) deve apontar para uma lista inicializada e não ser nulo.
 * @pre Os nomes das facções (`part` e `param`) devem ser strings válidas que correspondem a facções existentes.
 * 
 * @post As facções envolvidas no ataque terão seus recursos atualizados de acordo com a quantidade roubada.
 * @post O histórico do ataque será atualizado com as facções envolvidas e a quantidade de recursos roubados.
 */
void handle_attack(FILE *log, faction_t **factions, char *part, char *param) {
    int random_resources = rand() % 50;

    faction_t *attacking_faction = get_faction(&(*factions), part);
    faction_t *defending_faction = get_faction(&(*factions), param);

    if(attacking_faction == NULL || defending_faction == NULL) {
        fprintf(log, "Erro: Facção não encontrada.\n");
        return;
    }

    strcpy(history.attacking_faction, part);
    strcpy(history.defending_faction, param);
    history.stolen_resources = random_resources;

    attacking_faction->resources += random_resources;
    defending_faction->resources -= random_resources;

    fprintf(log, "=== Ataque realizado ===\n");
    fprintf(log, "Facção %s atacou Facção %s.\n", part, param);
    fprintf(log, "Recursos roubados: %d.\n", random_resources);
    fprintf(log, "%s agora possui %d recursos.\n", attacking_faction->name, attacking_faction->resources);
    fprintf(log, "%s agora possui %d recursos.\n\n", defending_faction->name, defending_faction->resources);
}

/**
 * @brief Inicia um combate entre duas unidades no tabuleiro.
 * 
 * Esta função inicia um combate entre duas unidades, determina o resultado do combate com base em valores
 * de ataque aleatórios e atualiza o estado do tabuleiro e das unidades em consequência do resultado.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto para escrita.
 * @param board Um ponteiro para o tabuleiro onde o combate ocorre. A função assume que o tabuleiro está corretamente inicializado.
 * @param units Um ponteiro para um ponteiro da lista de unidades. A função assume que essa lista está corretamente inicializada.
 * @param part O nome da unidade que está iniciando o combate. Deve ser uma string válida correspondente a uma unidade existente.
 * @param enemy_name O nome da unidade inimiga. Deve ser uma string válida correspondente a uma unidade existente.
 * @param self_value Um valor representando algum atributo ou condição da unidade que está iniciando o combate (não usado diretamente na lógica atual).
 * @param enemy_value Um valor representando algum atributo ou condição da unidade inimiga (não usado diretamente na lógica atual).
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre O ponteiro para o tabuleiro (`board`) deve apontar para um tabuleiro inicializado e não ser nulo.
 * @pre O ponteiro para a lista de unidades (`units`) deve apontar para uma lista inicializada e não ser nulo.
 * 
 * @post O estado do tabuleiro e das unidades pode ser modificado dependendo do resultado do combate.
 * 
 * @details
 * O combate é resolvido gerando valores aleatórios de ataque para cada unidade envolvida.
 * - Se a unidade atacante tiver um valor de ataque maior que a unidade inimiga, a unidade inimiga é removida do tabuleiro.
 * - Se a unidade inimiga tiver um valor de ataque maior que a unidade atacante, a unidade atacante é removida do tabuleiro.
 * - Se os valores de ataque forem iguais, o combate termina em empate e nenhuma unidade é removida.
 * 
 * O estado do tabuleiro é atualizado após o combate, e o resultado é registrado no arquivo de log.
 * 
 * @param log O arquivo de log onde os detalhes do combate serão registrados.
 * @param board O tabuleiro onde o combate ocorre.
 * @param units A lista de unidades presentes no jogo.
 * @param part O nome da unidade que está iniciando o combate.
 * @param enemy_name O nome da unidade inimiga.
 * @param self_value Um valor representando um atributo ou condição da unidade atacante.
 * @param enemy_value Um valor representando um atributo ou condição da unidade inimiga.
 * 
 */
void handle_combat(FILE *log, board_t *board, unit_t **units, char *part, char *enemy_name) {
    fprintf(log, "=== Combate iniciado ===\n");
    fprintf(log, "Unidade %s atacando unidade %s\n", part, enemy_name);

    unit_t *self_unit = get_unit(units, part);
    unit_t *enemy_unit = get_unit(units, enemy_name);

    if(self_unit == NULL) {
        fprintf(log, "Unidade não encontrada.\n");
        return;
    }

    if(enemy_unit == NULL) {
        fprintf(log, "Unidade inimiga não encontrada.\n");
        return;
    }

    // Cria dois valores aleatórios para o potencial de ataque de cada unidade
    int self_attack = self_unit->type == SOLDIER ? rand() % 10 : rand() % 6;
    int enemy_attack = enemy_unit->type == SOLDIER ? rand() % 10 : rand() % 6;

    // Imprime os valores de ataque
    fprintf(log, "Potencial de ataque de %s: %d\n", part, self_attack);
    fprintf(log, "Potencial de ataque de %s: %d\n", enemy_name, enemy_attack);
    fprintf(log, "Resultado: ");

    if(self_attack > enemy_attack) {
        unit_t *unit = get_unit(units, enemy_name);
        faction_t *faction_on = get_faction_board(board, unit->x, unit->y);
        building_t *building_on = get_building_board(board, unit->x, unit->y);
        unit_t *unit_on = get_unit_board(board, unit->x, unit->y);
        unit_t *unit1_on = get_unit1_board(board, unit->x, unit->y);
        unit_t *unit2_on = get_unit2_board(board, unit->x, unit->y);

        remove_node(board, unit->x, unit->y);
        insert_node(board, unit->x, unit->y, NULL, building_on, faction_on);
        if(strcmp(unit->name, unit_on->name) == 0){
            insert_node(board, unit->x, unit->y, unit1_on, NULL, NULL);
            insert_node(board, unit->x, unit->y, unit2_on, NULL, NULL);
        }
        else if(strcmp(unit->name, unit1_on->name) == 0){
            insert_node(board, unit->x, unit->y, unit_on, NULL, NULL);
            insert_node(board, unit->x, unit->y, unit2_on, NULL, NULL);
        }
        else if(strcmp(unit->name, unit2_on->name) == 0){
            insert_node(board, unit->x, unit->y, unit_on, NULL, NULL);
            insert_node(board, unit->x, unit->y, unit1_on, NULL, NULL);
        }
        remove_unit(units, unit->x, unit->y);
        fprintf(log, "Unidade %s venceu o combate.\n", part);
    } else if(self_attack < enemy_attack) {
        unit_t *unit = get_unit(units, part);
        faction_t *faction_on = get_faction_board(board, unit->x, unit->y);
        building_t *building_on = get_building_board(board, unit->x, unit->y);
        unit_t *unit_on = get_unit_board(board, unit->x, unit->y);
        unit_t *unit1_on = get_unit1_board(board, unit->x, unit->y);
        unit_t *unit2_on = get_unit2_board(board, unit->x, unit->y);

        remove_node(board, unit->x, unit->y);
        insert_node(board, unit->x, unit->y, NULL, building_on, faction_on);
        if(strcmp(unit->name, unit_on->name) == 0){
            insert_node(board, unit->x, unit->y, unit1_on, NULL, NULL);
            insert_node(board, unit->x, unit->y, unit2_on, NULL, NULL);
        }
        else if(strcmp(unit->name, unit1_on->name) == 0){
            insert_node(board, unit->x, unit->y, unit_on, NULL, NULL);
            insert_node(board, unit->x, unit->y, unit2_on, NULL, NULL);
        }
        else if(strcmp(unit->name, unit2_on->name) == 0){
            insert_node(board, unit->x, unit->y, unit_on, NULL, NULL);
            insert_node(board, unit->x, unit->y, unit1_on, NULL, NULL);
        }
        remove_unit(units, unit->x, unit->y);
        fprintf(log, "Unidade %s perdeu o combate.\n", part);
    } else {
        fprintf(log, "Combate entre %s e %s terminou em empate.\n", part, enemy_name);
    }

    print_board(log, board);
}

/**
 * @brief Insere uma facção no tabuleiro em uma posição específica e registra as mudanças no log.
 * 
 * Esta função insere uma nova facção no tabuleiro de jogo em uma posição especificada pelas coordenadas,
 * atualiza o estado do tabuleiro e registra as mudanças no log.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto.
 * @param board Um ponteiro para um ponteiro do tabuleiro de jogo. A função assume que o tabuleiro está corretamente inicializado.
 * @param factions Um ponteiro para um ponteiro da lista de facções. A função assume que essa lista está corretamente inicializada.
 * @param part O identificador da facção que está sendo posicionada. Deve ser uma string válida.
 * @param params Um array de inteiros contendo os parâmetros da posição da facção:
 *               - params[0]: Coordenada x onde a facção será posicionada.
 *               - params[1]: Coordenada y onde a facção será posicionada.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre O ponteiro para o tabuleiro de jogo (`board`) deve apontar para um tabuleiro inicializado e não ser nulo.
 * @pre O ponteiro para a lista de facções (`factions`) deve apontar para uma lista inicializada e não ser nulo.
 * @pre O identificador da facção (`part`) deve ser uma string válida.
 * @pre Os parâmetros (`params`) devem conter as coordenadas válidas para a posição da facção no tabuleiro.
 * 
 * @post A facção será inserida no tabuleiro na posição especificada.
 * @post O estado atualizado do tabuleiro será impresso no log.
 */
void handle_position_faction(FILE *log, board_t **board, faction_t **factions, char *part, int *params) {
    insert_faction(&(*factions), part, 100, 100);
    insert_node(*board, params[0], params[1], NULL, NULL, *factions);
    fprintf(log, "=== Inserir facção ===\n");
    fprintf(log, "Facção %s inserida no tabuleiro em posição (%d, %d).\n", part, params[0], params[1]);
    print_board(log, *board);
    fprintf(log, "\n");
}

/**
 * @brief Insere uma unidade no tabuleiro em uma posição específica e registra as mudanças no log.
 * 
 * Esta função insere uma nova unidade no tabuleiro de jogo em uma posição especificada pelas coordenadas,
 * atualiza o estado do tabuleiro e registra as mudanças no log. Além disso, aumenta o poder da facção
 * correspondente à unidade e registra essa atualização no log.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto.
 * @param board Um ponteiro para um ponteiro do tabuleiro de jogo. A função assume que o tabuleiro está corretamente inicializado.
 * @param factions Um ponteiro para um ponteiro da lista de facções. A função assume que essa lista está corretamente inicializada.
 * @param units Um ponteiro para um ponteiro da lista de unidades. A função assume que essa lista está corretamente inicializada.
 * @param part O identificador da unidade que está sendo posicionada. Deve ser uma string válida.
 * @param params Um array de inteiros contendo os parâmetros da posição da unidade:
 *               - params[1]: Coordenada x onde a unidade será posicionada.
 *               - params[2]: Coordenada y onde a unidade será posicionada.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre O ponteiro para o tabuleiro de jogo (`board`) deve apontar para um tabuleiro inicializado e não ser nulo.
 * @pre O ponteiro para a lista de facções (`factions`) deve apontar para uma lista inicializada e não ser nulo.
 * @pre O ponteiro para a lista de unidades (`units`) deve apontar para uma lista inicializada e não ser nulo.
 * @pre O identificador da unidade (`part`) deve ser uma string válida.
 * @pre Os parâmetros (`params`) devem conter as coordenadas válidas para a posição da unidade no tabuleiro.
 * 
 * @post A unidade será inserida no tabuleiro na posição especificada.
 * @post O poder da facção correspondente à unidade será aumentado em 10 unidades.
 * @post O estado atualizado do tabuleiro será impresso no log.
 */
void handle_position_unit(FILE *log, board_t **board, faction_t **factions, unit_t **units, char *part, int *params) {
    fprintf(log, "=== Inserir unidade ===\n");

    insert_unit(&(*units), params[1], params[2], part, params[0]);
    insert_node(*board, params[1], params[2], *units, NULL, NULL);

    fprintf(log, "Unidade %s inserida no tabuleiro em posição (%d, %d).\n", part, params[1], params[2]);

    char faction_name[3];
    sprintf(faction_name, "F%c", part[0]);
    faction_t *faction = get_faction(&(*factions), faction_name);
    if(faction == NULL) {
        fprintf(log, "Facção não encontrada.\n");
        return;
    }

    faction->power += params[0] == SOLDIER ? 25 : 10;
    fprintf(log, "Poder da facção %s aumentado em %d unidades.\n", faction->name, params[0] == SOLDIER ? 25 : 10);

    print_board(log, *board);
    fprintf(log, "\n");
}

/**
 * @brief Move uma unidade para uma nova posição no tabuleiro e registra as mudanças no log.
 * 
 * Esta função move uma unidade específica para uma nova posição no tabuleiro de jogo,
 * atualiza sua localização e registra as mudanças no log. Além disso, atualiza o estado
 * do tabuleiro após o movimento da unidade.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto.
 * @param board Um ponteiro para o tabuleiro de jogo. A função assume que o tabuleiro está corretamente inicializado.
 * @param units Um ponteiro para um ponteiro da lista de unidades. A função assume que essa lista está corretamente inicializada.
 * @param part O nome da unidade que está sendo movida. Deve ser uma string válida.
 * @param params Um array de inteiros contendo os parâmetros do movimento:
 *               - params[1]: Nova coordenada x da unidade.
 *               - params[2]: Nova coordenada y da unidade.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre O tabuleiro (`board`) deve estar inicializado e não ser nulo.
 * @pre A lista de unidades (`units`) deve estar inicializada e não ser nula.
 * @pre O nome da unidade (`part`) deve ser uma string válida e existente na lista de unidades.
 * @pre Os parâmetros (`params`) devem conter as coordenadas válidas para o movimento da unidade.
 * 
 * @post A unidade será movida para a nova posição especificada.
 * @post O estado atualizado do tabuleiro será impresso no log.
 */
void handle_move(FILE *log, board_t *board, unit_t **units, char part[MAX_PART_LEN], int *params) {
    fprintf(log, "=== Movimento de unidade ===\n");
    fprintf(log, "Unidade %s movida para posição (%d, %d).\n", part, params[1], params[2]);
    unit_t *unit = get_unit(units, part);
    if(unit == NULL) {
        fprintf(log, "Unidade não encontrada.\n");
        return;
    }

    faction_t *faction_on = get_faction_board(board, unit->x, unit->y);
    building_t *building_on = get_building_board(board, unit->x, unit->y);
    unit_t *unit_on = get_unit_board(board, unit->x, unit->y);
    unit_t *unit1_on = get_unit1_board(board, unit->x, unit->y);
    unit_t *unit2_on = get_unit2_board(board, unit->x, unit->y);

    remove_node(board, unit->x, unit->y);
    insert_node(board, unit->x, unit->y, NULL, building_on, faction_on);
    if(strcmp(unit->name, unit_on->name) == 0){
        insert_node(board, unit->x, unit->y, unit1_on, NULL, NULL);
        insert_node(board, unit->x, unit->y, unit2_on, NULL, NULL);
    }
    else if(strcmp(unit->name, unit1_on->name) == 0){
        insert_node(board, unit->x, unit->y, unit_on, NULL, NULL);
        insert_node(board, unit->x, unit->y, unit2_on, NULL, NULL);
    }
    else if(strcmp(unit->name, unit2_on->name) == 0){
        insert_node(board, unit->x, unit->y, unit_on, NULL, NULL);
        insert_node(board, unit->x, unit->y, unit1_on, NULL, NULL);
    }
    
    insert_node(board, params[1], params[2], unit, NULL, NULL);
    unit->x = params[1];
    unit->y = params[2];
    
    print_board(log, board);
    fprintf(log, "\n");
}

/**
 * @brief Coleta recursos para a facção usando uma unidade específica.
 * 
 * Esta função permite que uma unidade específica colete recursos do mapa. A quantidade de recursos
 * coletados depende do tipo de unidade e do tipo de terreno onde a unidade está localizada.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto para escrita.
 * @param factions Um ponteiro para um ponteiro da lista de facções. A função assume que essa lista está corretamente inicializada.
 * @param units Um ponteiro para um ponteiro da lista de unidades. A função assume que essa lista está corretamente inicializada.
 * @param columns O número de colunas no mapa.
 * @param rows O número de linhas no mapa.
 * @param map Uma matriz que representa o mapa, onde os valores indicam o tipo de terreno.
 * @param part O nome da unidade que está coletando recursos. Deve ser uma string válida correspondente a uma unidade existente.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre O ponteiro para a lista de facções (`factions`) deve apontar para uma lista inicializada e não ser nulo.
 * @pre O ponteiro para a lista de unidades (`units`) deve apontar para uma lista inicializada e não ser nulo.
 * @pre O mapa (`map`) deve ser uma matriz válida com dimensões `columns` x `rows`.
 * @pre O nome da unidade (`part`) deve ser uma string válida que corresponde a uma unidade existente no jogo.
 * 
 * @post A função atualizará os recursos da facção à qual a unidade pertence, com base no tipo de unidade e no tipo de terreno onde a unidade está localizada.
 * @post A coleta de recursos será registrada no log, incluindo os novos valores de recursos da facção.
 */
void handle_collect(FILE *log, faction_t **factions, unit_t **units, int columns, int rows, int map[columns][rows], char part[MAX_PART_LEN]) {
    fprintf(log, "=== Coleta de recursos ===\n");
    unit_t *unit = get_unit(&(*units), part);
    if(unit == NULL) {
        fprintf(log, "Unidade não encontrada.\n");
        return;
    }
    char faction_name[3];
    sprintf(faction_name, "F%c", part[0]);
    faction_t *faction = get_faction(&(*factions), faction_name);
    if(faction == NULL) {
        fprintf(log, "Facção não encontrada.\n");
        return;
    }

    int resources; 

    if(unit->type == SOLDIER) {
        resources = map[unit->x][unit->y] == 0 ? 30 : map[unit->x][unit->y] == 1 ? 20 : 10;
        faction->resources +=  resources;
    }
    else if(unit->type == EXPLORER){
        resources = map[unit->x][unit->y] == 0 ? 50 : map[unit->x][unit->y] == 1 ? 40 : 30;
        faction->resources += resources;
    }
    
    fprintf(log, "Facção %s coletou %d recursos.\n", part, resources);
    fprintf(log, "%s agora possui %d recursos.\n\n", faction->name, faction->resources);
}

/**
 * @brief Constrói um edifício para uma facção e atualiza os recursos e poder da facção.
 * 
 * Esta função registra a construção de um edifício para uma facção específica no log,
 * insere o edifício no tabuleiro e atualiza os recursos e poder da facção envolvida. 
 * Também imprime o estado atual do tabuleiro no log.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto.
 * @param board Um ponteiro para um ponteiro para o tabuleiro de jogo. A função assume que o tabuleiro está corretamente inicializado.
 * @param factions Um ponteiro para um ponteiro da lista de facções. A função assume que essa lista está corretamente inicializada.
 * @param buildings Um ponteiro para um ponteiro para a lista de edifícios. A função assume que essa lista está corretamente inicializada.
 * @param part O nome da facção que está construindo o edifício. Deve ser uma string válida.
 * @param params Um array de inteiros contendo os parâmetros da construção. Espera-se que:
 *               - params[0]: Tipo do edifício.
 *               - params[2]: Coordenada x da construção.
 *               - params[3]: Coordenada y da construção.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre A lista de facções deve estar inicializada e não nula.
 * @pre A lista de edifícios deve estar inicializada e não nula.
 * @pre O tabuleiro deve estar inicializado e não nulo.
 * @pre O nome da facção deve ser uma string válida e existente na lista de facções.
 * @pre O array de parâmetros deve conter os valores necessários para a construção (tipo do edifício, coordenadas x e y).
 * 
 * @post A tentativa de construção será registrada no log.
 * @post O edifício será inserido no tabuleiro nas coordenadas especificadas.
 * @post Os recursos e o poder da facção serão atualizados.
 * @post O estado atual do tabuleiro será impresso no log.
 */
void handle_building(FILE *log, board_t **board, faction_t **factions, building_t **buildings, char *part, int *params) {
    fprintf(log, "=== Construção de Edifício ===\n");
    fprintf(log, "Construir um edifício para a facção %s em (%d, %d).\n", part, params[2], params[3]);

    // Inserir o edifício no registro de edifícios
    insert_building(&(*buildings), params[2], params[3], part, params[0]);

    // Inserir o edifício na placa do jogo
    insert_node(*board, params[2], params[3], NULL, *buildings, NULL);

    // Encontrar a facção correspondente
    faction_t *faction = get_faction(&(*factions), part);
    if (faction == NULL) {
        fprintf(log, "Facção %s não encontrada. Construção cancelada.\n", part);
        return;
    }

    // Calcular e aplicar custo e benefício da construção
    int cost = 0, power_increase = 0;
    switch ((*buildings)->type) {
        case RESOURCE_BUILDING:
            cost = 10;
            power_increase = 10;
            break;
        case TRAINING_CAMP:
            cost = 30;
            power_increase = 30;
            break;
        default:
            cost = 20;
            power_increase = 20;
            break;
    }

    faction->resources -= cost;
    faction->power += power_increase;

    // Registrar os recursos e poder atualizados da facção
    fprintf(log, "Recursos da facção %s após a construção: %d\n", faction->name, faction->resources);
    fprintf(log, "Poder da facção %s após a construção: %d\n", faction->name, faction->power);

    // Imprimir o estado atualizado do tabuleiro no log
    fprintf(log, "Estado atualizado do tabuleiro:\n");
    print_board(log, *board);

    // Espaço em branco para separar entradas no log
    fprintf(log, "\n");
}

/**
 * @brief Processa a defesa de uma facção e registra as ações no log.
 * 
 * Esta função registra a tentativa de defesa de uma facção e atualiza os recursos das facções envolvidas
 * se a facção defendida corresponder à facção atacada no histórico de combate. As atualizações são registradas no log.
 * 
 * @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto.
 * @param factions Um ponteiro para um ponteiro da lista de facções. A função assume que essa lista está corretamente inicializada.
 * @param part O nome da facção que está se defendendo. Deve ser uma string com no máximo MAX_PART_LEN caracteres.
 * 
 * @pre O arquivo de log deve estar aberto para escrita.
 * @pre A lista de facções deve estar inicializada e não nula.
 * @pre O nome da facção deve ser uma string válida e existente na lista de facções.
 * @pre O histórico de combate (history) deve estar inicializado corretamente e conter informações válidas.
 * 
 * @post A tentativa de defesa será registrada no log.
 * @post Se a facção defendida for a mesma que a facção atacada no histórico, os recursos serão atualizados conforme o histórico.
 * @post Atualizações nos recursos das facções envolvidas serão registradas no log.
 */
void handle_defend(FILE *log, faction_t **factions, char part[MAX_PART_LEN]) {
    fprintf(log, "=== Defesa iniciada ===\n");
    fprintf(log, "Facção defendendo: %s\n", part);

    faction_t *defending_faction = get_faction(&(*factions), part);

    if (defending_faction == NULL) {
        fprintf(log, "Facção %s não encontrada.\n", part);
        return;
    }

    if (strcmp(history.defending_faction, part) == 0) {
        fprintf(log, "Recursos roubados na última rodada de ataque: %d\n", history.stolen_resources);

        faction_t *attacking_faction = get_faction(&(*factions), history.attacking_faction);

        if (attacking_faction == NULL) {
            fprintf(log, "Facção atacante %s não encontrada.\n", history.attacking_faction);
            return;
        }

        defending_faction->resources += history.stolen_resources;
        attacking_faction->resources -= history.stolen_resources;

        fprintf(log, "Recursos da facção %s após a defesa: %d\n", defending_faction->name, defending_faction->resources);
        fprintf(log, "Recursos da facção %s após o ataque: %d\n\n", attacking_faction->name, attacking_faction->resources);
    } else {
        fprintf(log, "Nenhuma ação de defesa executada nesta rodada.\n\n");
    }
}


/**
    @brief Atualiza o poder de uma facção e registra essa alteração em um arquivo de log.
    Esta função busca uma facção específica a partir do nome fornecido, atualiza o valor de poder
    dessa facção e registra essa alteração em um arquivo de log.
    @param log Um ponteiro para um arquivo onde o log será escrito. Deve estar previamente aberto.
    @param factions Um ponteiro para um ponteiro da lista de facções. A função assumirá que essa lista está corretamente inicializada.
    @param faction_name O nome da facção cujo poder será atualizado. Deve ser uma string com no máximo MAX_PART_LEN caracteres.
    @param power O novo valor de poder a ser atribuído à facção especificada.
    @pre O arquivo de log deve estar aberto para escrita.
    @pre A lista de facções deve estar inicializada e não nula.
    @pre O nome da facção deve ser uma string válida e existente na lista de facções.
    @pre O valor de poder deve ser um número válido a ser atribuído à facção.
    @post O valor de poder da facção especificada será atualizado com o novo valor.
    @post Um registro será adicionado ao arquivo de log informando a alteração do poder.
    @param log
    Um ponteiro para um arquivo onde o log será escrito. Este arquivo deve estar previamente aberto para escrita.
    @param factions
    Um ponteiro para um ponteiro para a lista de facções. A lista de facções deve estar corretamente inicializada.
    @param faction_name
    O nome da facção cujo poder será atualizado. Deve ser uma string com no máximo MAX_PART_LEN caracteres.
    @param power
    O valor de poder a ser agregado ao poder de uma facção especificada.
    @return void
*/
void handle_earn(FILE *log, faction_t **factions, char faction_name[MAX_PART_LEN], int power)
{
    faction_t* faction = get_faction(&(*factions), faction_name);
    faction->power += power;
    fprintf(log, "A facção %s agora tem %d poder.\n", faction->name, faction->power);
}