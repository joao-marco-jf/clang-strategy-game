#ifndef FACTION_H
#define FACTION_H

#include "unit.h"
#include "building.h"
#include "alliance.h"

typedef struct faction_t {
    char name[15];
    int resources;
    int power;
    struct faction_t *next;
    unit_t *units;
    building_t *buildings;
    alliance_t *alliance;
} faction_t;

faction_t *allocate_faction(char name[15], int resources, int power);
void insert_faction(faction_t **factions, char name[15], int resources, int power);
void remove_faction(faction_t **factions, char name[15]);

#endif