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

void free_buildings(building_t **buildings){
    while(*buildings != NULL){
        building_t *temp = *buildings;
        *buildings = (*buildings)->next;
        free(temp);
    }
}