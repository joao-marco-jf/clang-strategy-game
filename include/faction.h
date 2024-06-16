#ifndef FACTION_H
#define FACTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "unit.h"
#include "building.h"
#include "alliance.h"

typedef struct faction_t {
    char name[15];
    int resources;
    int power;
    unit_t *units;
    building_t *buildings;
    alliance_t *alliance;
    struct faction_t *next;
} faction_t;

faction_t *allocate_faction(char name[15], int resources, int power);
void insert_faction(faction_t **factions, char name[15], int resources, int power);
faction_t *get_faction(faction_t **factions, char name[2]);
void free_factions(faction_t **factions);

#endif