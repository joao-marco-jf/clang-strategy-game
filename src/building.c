#include <stdio.h>
#include "building.h"

building_t *allocate_building(int x, int y, building_e type){
    building_t *new_building = NULL;
    new_building = (building_t *) malloc(sizeof(building_t));
    if(new_building == NULL) return;
    new_building->x = x;
    new_building->y = y;
    new_building->type = type;
    new_building->next = NULL;
    return new_building;
}

void insert_building(building_t **buildings, int x, int y, building_e type){

}

void remove_building(building_t **buildings, int x, int y){

}