#include "building.h"

/**
 * Aloca memória para uma nova estrutura de edifício e inicializa seus campos.
 * 
 * @param x A coordenada x do edifício.
 * @param y A coordenada y do edifício.
 * @param type O tipo de edifício.
 * @return Um ponteiro para a estrutura de edifício alocada, ou NULL se a alocação falhar.
 */
building_t *allocate_building(int x, int y, char name[15], building_e type){       //Esta função aloca memória para uma nova instância de um edifício, inicializa suas coordenadas e tipo.
    building_t *new_building = NULL;
    new_building = (building_t *) malloc(sizeof(building_t));
    if(new_building == NULL) return NULL;
    strcpy(new_building->name, name);
    new_building->x = x;
    new_building->y = y;
    new_building->type = type;
    new_building->next = NULL;
    return new_building;
}

/**
 * Insere um novo edifício no início da lista de edifícios.
 * 
 * @param buildings Um ponteiro para o ponteiro da lista de edifícios.
 * @param x A coordenada x do edifício.
 * @param y A coordenada y do edifício.
 * @param type O tipo de edifício.
 */
void insert_building(building_t **buildings, int x, int y, char name[15],  building_e type){    //Esta função insere um novo edifício no início da lista ligada de edifícios.
    building_t *new_building = NULL;
    new_building = allocate_building(x, y, name, type);
    if(new_building == NULL) return;
    new_building->next = *buildings;
    *buildings = new_building;
}

/**
 * @brief Libera a memória alocada para a lista encadeada de construções.
 *
 * A função `free_buildings` libera a memória alocada para a lista encadeada de
 * construções (`building_t`). Ela percorre a lista encadeada a partir do início
 * indicado por `*buildings`, libera cada nó da lista e atualiza o ponteiro `*buildings`
 * para apontar para NULL após liberar todos os nós.
 *
 * @param buildings Ponteiro para o ponteiro da lista encadeada de construções.
 *                  Após a execução da função, `*buildings` será NULL.
 * 
 * @note Esta função não retorna nenhum valor. Ela libera a memória alocada dinamicamente
 *       para cada nó da lista encadeada de construções, incluindo o próprio nó.
 */
void free_buildings(building_t **buildings){
    while(*buildings != NULL){
        building_t *temp = *buildings;      // Armazena o nó atual em `temp`
        *buildings = (*buildings)->next;    // Atualiza `*buildings` para o próximo nó
        free(temp);                         // Libera a memória do nó atual
    }
}