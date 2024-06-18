/**
 * @file unit.c
 *
 * @brief Implementações de funções para manipulação de unidades (unit_t).
 *
 * Este arquivo contém a implementação de funções para criar, modificar e gerenciar
 * uma lista encadeada de unidades (`unit_t`). Inclui operações como inserção, remoção,
 * busca e liberação de memória associada às unidades.
 *
 * As unidades são representadas pela estrutura `unit_t`, que possui campos para
 * coordenadas (x, y), nome, tipo e um ponteiro para o próximo nó na lista encadeada.
 * Operações básicas de alocação, liberação e manipulação são providas por funções
 * como `allocate_unit`, `insert_unit`, `remove_unit`, `get_unit` e `free_units`.
 *
 */

#include "unit.h"

// Implementações das funções para manipulação de unidades...


#include "unit.h"

/**
 * @brief Aloca e inicializa um novo nó do tipo unit_t com os valores especificados.
 *
 * Esta função aloca dinamicamente um novo nó do tipo `unit_t` e inicializa seus campos
 * com os valores fornecidos para as coordenadas `x` e `y`, o nome `name` e o tipo `type`.
 * O campo `next` é inicializado como NULL.
 *
 * @param x A coordenada x do novo nó.
 * @param y A coordenada y do novo nó.
 * @param name Uma string contendo o nome do novo nó. A string deve ter no máximo
 *             14 caracteres (assumindo que o campo `name` em `unit_t` é um array de 15 caracteres).
 * @param type O tipo do novo nó, representado pelo enum `unit_e`.
 *
 * @return Um ponteiro para o novo nó alocado e inicializado, ou NULL se a alocação falhar.
 */
unit_t *allocate_unit(int x, int y, char name[15], unit_e type){
    unit_t *new_unit = NULL;
    new_unit = (unit_t *) malloc(sizeof(unit_t));
    if(new_unit == NULL) return NULL;
    strcpy(new_unit->name, name);
    new_unit->x = x;
    new_unit->y = y;
    new_unit->type = type;
    new_unit->next = NULL;
    return new_unit;
}

/**
 * @brief Insere um novo nó na lista encadeada de unidades com os valores especificados.
 *
 * Esta função aloca um novo nó com as coordenadas `x` e `y`, o nome `name`, e o tipo `type`.
 * O novo nó é então inserido no início da lista encadeada de unidades.
 *
 * @param units Um ponteiro duplo para o primeiro nó da lista encadeada de unidades.
 *              Este ponteiro será atualizado para apontar para o novo nó inserido.
 * @param x A coordenada x do novo nó.
 * @param y A coordenada y do novo nó.
 * @param name Uma string contendo o nome do novo nó. A string deve ter no máximo
 *             14 caracteres (assumindo que o campo `name` em `unit_t` é um array de 15 caracteres).
 * @param type O tipo do novo nó, representado pelo enum `unit_e`.
 *
 * @note A função assume que a função `allocate_unit` aloca dinamicamente e inicializa um nó
 *       com os valores fornecidos e retorna um ponteiro para ele. Se a alocação falhar,
 *       a função retorna imediatamente sem modificar a lista.
 * @note A função não realiza verificações adicionais sobre a validade dos ponteiros ou da string.
 */
void insert_unit(unit_t **units, int x, int y, char name[15], unit_e type){
    unit_t *new_unit = NULL;
    new_unit = allocate_unit(x, y, name, type);
    if(new_unit == NULL) return;
    new_unit->next = *units;
    *units = new_unit;
}

/**
 * @brief Procura e retorna um nó na lista encadeada de unidades com o nome especificado.
 *
 * Esta função percorre uma lista encadeada de unidades, procurando por um nó cujo campo
 * `name` seja igual ao nome especificado. Se encontrar um nó com esse nome, ele é
 * retornado. Caso contrário, retorna NULL.
 *
 * @param units Um ponteiro duplo para o primeiro nó da lista encadeada de unidades.
 * @param name Uma string contendo o nome a ser procurado. A string deve ter no máximo
 *             14 caracteres (assumindo que o campo `name` em `unit_t` é um array de 15 caracteres).
 *
 * @return Um ponteiro para o nó da lista encadeada com o nome especificado, ou NULL se
 *         nenhum nó com esse nome for encontrado.
 *
 * @note A função assume que a lista foi alocada dinamicamente e que cada nó foi
 *       corretamente alocado com malloc ou uma função similar.
 * @note A função não realiza verificações adicionais sobre a validade dos ponteiros ou da string.
 */
unit_t *get_unit(unit_t **units, char name[15]){
    unit_t *current = *units;
    while(current != NULL){
        if(strcmp(current->name, name) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Remove um nó da lista encadeada de unidades com as coordenadas especificadas.
 *
 * Esta função percorre uma lista encadeada de unidades, procurando por um nó com as
 * coordenadas `x` e `y` especificadas. Se encontrar um nó com essas coordenadas, ele
 * é removido da lista e a memória alocada para esse nó é liberada.
 *
 * @param units Um ponteiro duplo para o primeiro nó da lista encadeada de unidades.
 *              Este ponteiro será atualizado se o nó removido for o primeiro da lista.
 * @param x A coordenada x do nó a ser removido.
 * @param y A coordenada y do nó a ser removido.
 *
 * @note A função assume que a lista foi alocada dinamicamente e que cada nó foi
 *       corretamente alocado com malloc ou uma função similar.
 * @note A função não realiza verificações adicionais sobre a validade dos ponteiros.
 * @note Se não houver um nó com as coordenadas especificadas, a lista permanecerá inalterada.
 */
void remove_unit(unit_t **units, int x, int y){
    unit_t *current = *units;
    unit_t *previous = NULL;
    while(current != NULL){
        if(current->x == x && current->y == y){
            if(previous == NULL){
                *units = current->next;
            }
            else{
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

/**
 * @brief Libera a memória alocada para uma lista encadeada de estruturas do tipo unit_t.
 *
 * Esta função percorre uma lista encadeada de unidades, liberando a memória alocada para
 * cada nó da lista. A lista é representada por um ponteiro duplo para o primeiro nó.
 *
 * @param units Um ponteiro duplo para o primeiro nó da lista encadeada de unidades.
 *              Após a execução da função, o ponteiro será atualizado para NULL.
 *
 * @note A função assume que a lista foi alocada dinamicamente e que cada nó foi
 *       corretamente alocado com malloc ou uma função similar.
 * @note A função não realiza verificações adicionais sobre a validade dos ponteiros.
 */
void free_units(unit_t **units){
    while(*units != NULL){
        unit_t *temp = *units;
        *units = (*units)->next;
        free(temp);
    }
}
