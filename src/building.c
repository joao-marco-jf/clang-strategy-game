#include <stdio.h>
#include <stdlib.h>
#include "building.h"

building_t *allocate_building(int x, int y, building_e type){
    building_t *new_building = NULL;
    new_building = (building_t *) malloc(sizeof(building_t));
    if(new_building == NULL) return NULL;
    new_building->x = x;
    new_building->y = y;
    new_building->type = type;
    new_building->next = NULL;
    return new_building;
}

void insert_building(building_t **buildings, int x, int y, building_e type){
    building_t *new_building = NULL;
    new_building = allocate_building(x, y, type);
    if(new_building == NULL) return;
    new_building->next = *buildings;
    *buildings = new_building;
}

void remove_building(building_t **buildings, int x, int y){
    building_t *aux = *buildings;
    *buildings = (*buildings)->next;
    free(aux);
}