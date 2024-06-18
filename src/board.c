#include "board.h"

/**
 * @brief Cria um novo tabuleiro com as dimensões especificadas.
 *
 * A função `create_board` aloca dinamicamente memória para um novo tabuleiro
 * e inicializa suas dimensões com os valores fornecidos. O tabuleiro criado
 * inicialmente não contém nenhum elemento (a lista `head` é inicializada como NULL).
 *
 * @param lines Número de linhas do tabuleiro.
 * @param columns Número de colunas do tabuleiro.
 * 
 * @return Retorna um ponteiro para o tabuleiro criado (`board_t *`).
 *         Se houver falha na alocação de memória, retorna NULL.
 *         
 * @note Certifique-se de liberar a memória alocada para o tabuleiro utilizando
 *       `free_board` quando não precisar mais dele para evitar vazamentos de memória.
 *       O tabuleiro criado contém informações sobre suas dimensões e uma lista inicialmente vazia.
 */
board_t *create_board(int lines, int columns) {
    board_t *new_board = (board_t *) malloc(sizeof(board_t));
    if (new_board == NULL) return NULL; // Verifica se a alocação de memória foi bem-sucedida
    
    // Inicializa as dimensões do tabuleiro
    new_board->lines = lines;
    new_board->columns = columns;
    
    // Inicializa a lista de elementos do tabuleiro como vazia
    new_board->head = NULL;
    
    return new_board; // Retorna o ponteiro para o tabuleiro criado
}

/**
 * @brief Aloca memória para um novo nó da lista encadeada.
 *
 * A função `allocate_node` aloca dinamicamente memória para um novo nó da lista encadeada
 * (`node_t`) e inicializa seus campos com os valores fornecidos.
 *
 * @param line Número da linha onde o nó está localizado no tabuleiro.
 * @param col Número da coluna onde o nó está localizado no tabuleiro.
 * @param unit Ponteiro para a unidade associada ao nó. Pode ser NULL se não houver unidade.
 * @param building Ponteiro para o prédio associado ao nó. Pode ser NULL se não houver prédio.
 * @param faction Ponteiro para a facção associada ao nó. Pode ser NULL se não houver facção.
 * 
 * @return Retorna um ponteiro para o nó alocado (`node_t *`).
 *         Se houver falha na alocação de memória, retorna NULL.
 *         
 * @note Certifique-se de liberar a memória alocada para cada nó da lista quando não for mais necessário,
 *       utilizando métodos apropriados para evitar vazamentos de memória.
 *       Cada nó da lista pode conter informações sobre uma unidade, prédio e/ou facção associados à sua posição
 *       no tabuleiro, além de informações sobre a própria posição.
 */
node_t *allocate_node(int line, int col, unit_t* unit, building_t* building, faction_t* faction) {
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) return NULL; // Verifica se a alocação de memória foi bem-sucedida
    
    // Inicializa os campos do novo nó com os valores fornecidos
    new_node->line = line;
    new_node->col = col;
    new_node->unit = unit;
    new_node->unit1 = NULL;
    new_node->unit2 = NULL;
    new_node->building = building;
    new_node->faction = faction;
    new_node->next = NULL;
    
    return new_node; // Retorna o ponteiro para o nó alocado
}

/**
 * @brief Insere um novo nó na lista encadeada do tabuleiro ou atualiza um nó existente.
 *
 * A função `insert_node` insere um novo nó na lista encadeada do tabuleiro (`board->head`)
 * ou atualiza um nó existente se já houver um nó na posição especificada (`line`, `col`).
 * Se um nó já existir na posição especificada, ele verifica e atualiza a facção, prédio e unidades
 * associadas a esse nó. Caso contrário, cria um novo nó com os parâmetros fornecidos e insere
 * esse novo nó no início da lista encadeada.
 *
 * @param board Ponteiro para o tabuleiro onde o nó será inserido.
 * @param line Número da linha onde o nó será inserido/atualizado no tabuleiro.
 * @param col Número da coluna onde o nó será inserido/atualizado no tabuleiro.
 * @param unit Ponteiro para a unidade a ser associada ao nó. Pode ser NULL se não houver unidade.
 * @param building Ponteiro para o prédio a ser associado ao nó. Pode ser NULL se não houver prédio.
 * @param faction Ponteiro para a facção a ser associada ao nó. Pode ser NULL se não houver facção.
 * 
 * @note Certifique-se de utilizar métodos apropriados para liberar a memória alocada para a lista encadeada
 *       e seus nós quando não forem mais necessários, para evitar vazamentos de memória.
 *       A função assume que a função `allocate_node` é utilizada para criar um novo nó quando necessário.
 */
void insert_node(board_t *board, int line, int col, unit_t *unit, building_t *building, faction_t *faction) {
    node_t *current = board->head;
    
    // Procura por um nó na posição especificada (line, col)
    while (current != NULL) {
        if (current->line == line && current->col == col) {
            // Se o nó já existe na posição, atualiza as informações associadas a ele
            current->faction = (current->faction == NULL) ? faction : current->faction;
            current->building = (current->building == NULL) ? building : current->building;
            
            // Insere a unidade no primeiro espaço disponível (unit, unit1, unit2)
            if (current->unit == NULL) {
                current->unit = unit;
            } else if (current->unit1 == NULL) {
                current->unit1 = unit;
            } else if (current->unit2 == NULL) {
                current->unit2 = unit;
            }
            
            return; // Retorna após atualizar o nó existente
        }
        current = current->next;
    }
    
    // Se não encontrou um nó na posição especificada, cria um novo nó
    node_t *new_node = allocate_node(line, col, unit, building, faction);
    if (new_node == NULL) return; // Verifica se a alocação de memória foi bem-sucedida
    
    // Insere o novo nó no início da lista encadeada do tabuleiro
    new_node->next = board->head;
    board->head = new_node;
}

/**
 * @brief Obtém a facção associada a um nó específico do tabuleiro.
 *
 * A função `get_faction_board` percorre a lista encadeada do tabuleiro (`board->head`)
 * procurando por um nó na posição especificada (`line`, `col`). Se encontrar um nó nessa
 * posição, retorna o ponteiro para a facção associada a esse nó. Caso contrário, retorna NULL.
 *
 * @param board Ponteiro para o tabuleiro onde será feita a busca.
 * @param line Número da linha onde o nó está localizado no tabuleiro.
 * @param col Número da coluna onde o nó está localizado no tabuleiro.
 * 
 * @return Retorna um ponteiro para a facção associada ao nó encontrado na posição especificada.
 *         Se não encontrar um nó na posição especificada, retorna NULL.
 *         
 * @note Esta função não aloca memória adicional. A facção retornada pertence ao nó encontrado na posição especificada.
 *       Certifique-se de utilizar métodos apropriados para liberar a memória alocada para a lista encadeada e seus nós
 *       quando não forem mais necessários, para evitar vazamentos de memória.
 */
faction_t *get_faction_board(board_t *board, int line, int col) {
    node_t *current = board->head;
    
    // Percorre a lista encadeada procurando por um nó na posição (line, col)
    while (current != NULL) {
        if (current->line == line && current->col == col) {
            return current->faction; // Retorna a facção associada ao nó encontrado
        }
        current = current->next;
    }
    
    return NULL; // Retorna NULL se não encontrar um nó na posição especificada
}

/**
 * @brief Obtém o prédio associado a um nó específico do tabuleiro.
 *
 * A função `get_building_board` percorre a lista encadeada do tabuleiro (`board->head`)
 * procurando por um nó na posição especificada (`line`, `col`). Se encontrar um nó nessa
 * posição, retorna o ponteiro para o prédio associado a esse nó. Caso contrário, retorna NULL.
 *
 * @param board Ponteiro para o tabuleiro onde será feita a busca.
 * @param line Número da linha onde o nó está localizado no tabuleiro.
 * @param col Número da coluna onde o nó está localizado no tabuleiro.
 * 
 * @return Retorna um ponteiro para o prédio associado ao nó encontrado na posição especificada.
 *         Se não encontrar um nó na posição especificada, retorna NULL.
 *         
 * @note Esta função não aloca memória adicional. O prédio retornado pertence ao nó encontrado na posição especificada.
 *       Certifique-se de utilizar métodos apropriados para liberar a memória alocada para a lista encadeada e seus nós
 *       quando não forem mais necessários, para evitar vazamentos de memória.
 */
building_t *get_building_board(board_t *board, int line, int col){
    node_t *current = board->head;
    // Percorre a lista encadeada procurando por um nó na posição (line, col)
    while(current != NULL){
        if(current->line == line && current->col == col){
            return current->building;
        }
        current = current->next;
    }
    return 0;
}

/**
 * @brief Obtém a unidade associada a um nó específico do tabuleiro.
 *
 * A função `get_unit_board` percorre a lista encadeada do tabuleiro (`board->head`)
 * procurando por um nó na posição especificada (`line`, `col`). Se encontrar um nó nessa
 * posição, retorna o ponteiro para a unidade associada a esse nó. Caso contrário, retorna NULL.
 *
 * @param board Ponteiro para o tabuleiro onde será feita a busca.
 * @param line Número da linha onde o nó está localizado no tabuleiro.
 * @param col Número da coluna onde o nó está localizado no tabuleiro.
 * 
 * @return Retorna um ponteiro para a unidade associada ao nó encontrado na posição especificada.
 *         Se não encontrar um nó na posição especificada, retorna NULL.
 *         
 * @note Esta função não aloca memória adicional. A unidade retornada pertence ao nó encontrado na posição especificada.
 *       Certifique-se de utilizar métodos apropriados para liberar a memória alocada para a lista encadeada e seus nós
 *       quando não forem mais necessários, para evitar vazamentos de memória.
 */
unit_t *get_unit_board(board_t *board, int line, int col){
    node_t *current = board->head;
    // Percorre a lista encadeada procurando por um nó na posição (line, col)
    while(current != NULL){
        if(current->line == line && current->col == col){
            return current->unit;
        }
        current = current->next;
    }
    return 0;
}

/**
 * @brief Obtém a primeira unidade adicional associada a um nó específico do tabuleiro.
 *
 * A função `get_unit1_board` percorre a lista encadeada do tabuleiro (`board->head`)
 * procurando por um nó na posição especificada (`line`, `col`). Se encontrar um nó nessa
 * posição, retorna o ponteiro para a primeira unidade adicional associada a esse nó.
 * Caso contrário, retorna NULL.
 *
 * @param board Ponteiro para o tabuleiro onde será feita a busca.
 * @param line Número da linha onde o nó está localizado no tabuleiro.
 * @param col Número da coluna onde o nó está localizado no tabuleiro.
 * 
 * @return Retorna um ponteiro para a primeira unidade adicional associada ao nó encontrado na posição especificada.
 *         Se não encontrar um nó na posição especificada, retorna NULL.
 *         
 * @note Esta função não aloca memória adicional. A unidade retornada pertence ao nó encontrado na posição especificada.
 *       Certifique-se de utilizar métodos apropriados para liberar a memória alocada para a lista encadeada e seus nós
 *       quando não forem mais necessários, para evitar vazamentos de memória.
 */
unit_t *get_unit1_board(board_t *board, int line, int col){
    node_t *current = board->head;
    // Percorre a lista encadeada procurando por um nó na posição (line, col)
    while(current != NULL){
        if(current->line == line && current->col == col){
            return current->unit1; // Retorna a primeira unidade adicional associada ao nó encontrado
        }
        current = current->next;
    }
    return 0;
}

/**
 * @brief Obtém a segunda unidade adicional associada a um nó específico do tabuleiro.
 *
 * A função `get_unit2_board` percorre a lista encadeada do tabuleiro (`board->head`)
 * procurando por um nó na posição especificada (`line`, `col`). Se encontrar um nó nessa
 * posição, retorna o ponteiro para a segunda unidade adicional associada a esse nó.
 * Caso contrário, retorna NULL.
 *
 * @param board Ponteiro para o tabuleiro onde será feita a busca.
 * @param line Número da linha onde o nó está localizado no tabuleiro.
 * @param col Número da coluna onde o nó está localizado no tabuleiro.
 * 
 * @return Retorna um ponteiro para a segunda unidade adicional associada ao nó encontrado na posição especificada.
 *         Se não encontrar um nó na posição especificada, retorna NULL.
 *         
 * @note Esta função não aloca memória adicional. A unidade retornada pertence ao nó encontrado na posição especificada.
 *       Certifique-se de utilizar métodos apropriados para liberar a memória alocada para a lista encadeada e seus nós
 *       quando não forem mais necessários, para evitar vazamentos de memória.
 */
unit_t *get_unit2_board(board_t *board, int line, int col){
    node_t *current = board->head;
    // Percorre a lista encadeada procurando por um nó na posição (line, col)
    while(current != NULL){
        if(current->line == line && current->col == col){
            return current->unit2;// Retorna a segunda unidade adicional associada ao nó encontrado
        }
        current = current->next;
    }
    return 0;
}



/**
 * @brief Remove um nó específico do tabuleiro, liberando sua memória.
 *
 * A função `remove_node` percorre a lista encadeada do tabuleiro (`board->head`)
 * procurando por um nó na posição especificada (`row`, `col`). Se encontrar um nó nessa
 * posição, remove o nó da lista encadeada, ajustando os ponteiros adequados e liberando
 * sua memória. Caso contrário, a função não faz nada.
 *
 * @param board Ponteiro para o tabuleiro onde será removido o nó.
 * @param row Número da linha onde o nó está localizado no tabuleiro.
 * @param col Número da coluna onde o nó está localizado no tabuleiro.
 * 
 * @note Esta função libera a memória alocada para o nó removido. Certifique-se de não utilizar
 *       o nó removido após chamar esta função para evitar comportamento indefinido.
 */
void remove_node(board_t *board, int row, int col) {
    node_t *current = board->head;
    node_t *prev = NULL;

    // Percorre a lista encadeada procurando por um nó na posição (row, col)
    while (current != NULL) {
        if (current->line == row && current->col == col) {
            if (prev == NULL) {
                board->head = current->next; // Atualiza o ponteiro head se o nó removido for o primeiro da lista
            } else {
                prev->next = current->next; // Liga o nó anterior ao próximo nó após o nó removido
            }
            free(current); // Libera a memória alocada para o nó removido
            return;
        }
        prev = current;
        current = current->next;
    }
}

/**
 * @brief Libera toda a memória alocada para o tabuleiro e seus nós.
 *
 * A função `free_board` libera a memória alocada para todos os nós da lista encadeada
 * do tabuleiro (`board->head`), incluindo o próprio tabuleiro. Após chamar esta função,
 * o ponteiro `board` não deve ser utilizado, pois sua memória também é liberada.
 *
 * @param board Ponteiro para o tabuleiro que será liberado da memória.
 * 
 * @note Esta função não retorna nenhum valor, pois seu objetivo é liberar a memória
 *       alocada para o tabuleiro e seus nós. Após chamar esta função, o ponteiro `board`
 *       não deve mais ser utilizado para evitar comportamento indefinido.
 */
void free_board(board_t *board){
    node_t *current = board->head;
    while(current != NULL){
        node_t *temp = current;
        current = current->next;
        free(temp); // Libera a memória alocada para o nó atual
    }
}
/**
 * @brief Imprime o estado atual do tabuleiro em um arquivo de log.
 *
 * A função `print_board` imprime o estado atual do tabuleiro em um arquivo de log
 * chamado "saida.txt". Cada célula do tabuleiro é representada por um conjunto de
 * caracteres que indicam a presença de unidades, construções e facções.
 *
 * @param board Ponteiro para o tabuleiro que será impresso.
 * 
 * @note Esta função não retorna nenhum valor. Ela abre o arquivo "saida.txt" no modo
 *       de adição ("a"), escreve o estado do tabuleiro no arquivo e fecha o arquivo
 *       após a impressão.
 */
void print_board(FILE *log, board_t *board){
    fprintf(log, "_____________________________________________________________\n");
    for(int i = 0; i < board->lines; i++){
        for(int j = 0; j < board->columns; j++){
            fprintf(log, "|  ");
            if(
                get_unit_board(board, i, j) && 
                get_unit1_board(board, i, j) &&
                get_unit2_board(board, i, j) && 
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "F3B ");
            else if(
                get_unit_board(board, i, j) && 
                get_unit1_board(board, i, j) &&
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "F2B");
            else if(
                get_unit1_board(board, i, j) && 
                get_unit2_board(board, i, j) &&
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "F2B");
            else if(
                get_unit_board(board, i, j) && 
                get_unit2_board(board, i, j) &&
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "F2B");
            else if(
                get_unit_board(board, i, j) && 
                get_unit1_board(board, i, j) &&
                get_unit2_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "F3 ");
            else if(
                get_unit_board(board, i, j) && 
                get_unit1_board(board, i, j) &&
                get_faction_board(board, i, j)
            ) fprintf(log, "F2 ");
            else if(
                get_unit_board(board, i, j) && 
                get_unit2_board(board, i, j) &&
                get_faction_board(board, i, j)
            ) fprintf(log, "F2 ");
            else if(
                get_unit1_board(board, i, j) && 
                get_unit2_board(board, i, j) &&
                get_faction_board(board, i, j)
            ) fprintf(log, "F2 ");
            else if(
                get_unit_board(board, i, j) &&
                get_faction_board(board, i, j)
            ) fprintf(log, "FU ");
            else if(
                get_unit1_board(board, i, j) &&
                get_faction_board(board, i, j)
            ) fprintf(log, "FU ");
            else if(
                get_unit2_board(board, i, j) &&
                get_faction_board(board, i, j)
            ) fprintf(log, "FU ");
            else if(
                get_unit_board(board, i, j) && 
                get_unit1_board(board, i, j) &&
                get_building_board(board, i, j)
            ) fprintf(log, " 2B");
            else if(
                get_unit_board(board, i, j) && 
                get_unit2_board(board, i, j) &&
                get_building_board(board, i, j)
            ) fprintf(log, " 2B");
            else if(
                get_unit1_board(board, i, j) && 
                get_unit2_board(board, i, j) &&
                get_building_board(board, i, j)
            ) fprintf(log, " 2B");
            else if(
                get_unit_board(board, i, j) && 
                get_building_board(board, i, j)
            ) fprintf(log, " UB");
            else if(
                get_unit1_board(board, i, j) && 
                get_building_board(board, i, j)
            ) fprintf(log, " UB");
            else if(
                get_unit2_board(board, i, j) && 
                get_building_board(board, i, j)
            ) fprintf(log, " UB");
            else if(
                get_unit_board(board, i, j) && 
                get_unit1_board(board, i, j) &&
                get_unit2_board(board, i, j)
            ) fprintf(log, " 3 ");
            else if(
                get_unit_board(board, i, j) && 
                get_unit1_board(board, i, j)
            ) fprintf(log, " 2 ");
            else if(
                get_unit_board(board, i, j) && 
                get_unit2_board(board, i, j)
            ) fprintf(log, " 2 ");
            else if(
                get_unit1_board(board, i, j) && 
                get_unit2_board(board, i, j)
            ) fprintf(log, " 2 ");
            else if(
                get_unit_board(board, i, j) && 
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "FUB");
            else if(
                get_unit1_board(board, i, j) && 
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "FUB");
            else if(
                get_unit2_board(board, i, j) && 
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "FUB");
            else if(
                get_building_board(board, i, j) && 
                get_faction_board(board, i, j)
            ) fprintf(log, "F B");
            else if(
                get_faction_board(board, i, j)
            ) fprintf(log, "F  ");
            else if(
                get_building_board(board, i, j)
            ) fprintf(log, "  B");
            else if(
                get_unit_board(board, i, j)
            ) fprintf(log, " U ");
            else if(
                get_unit1_board(board, i, j)
            ) fprintf(log, " U ");
            else if(
                get_unit2_board(board, i, j)
            ) fprintf(log, " U ");
            else fprintf(log, "   ");
        }
        fprintf(log, "|\n");
        fprintf(log, "|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
    }
}