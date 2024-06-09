#include <stdlib.h>
#include <stdio.h>
#include<string.h>

#include "faction.h"

faction_t *allocate_faction(char name[15], int resources, int power){
    faction_t *new_faction = NULL;
    new_faction = (faction_t *) malloc(sizeof(faction_t));
    if(new_faction == NULL) return NULL;
    strcpy(new_faction->name, name);
    new_faction->resources = resources;
    new_faction->power = power;
    new_faction->next = NULL;
    return new_faction;
}

void insert_faction(faction_t **factions, char name[15], int resources, int power){
    faction_t *new_faction = NULL;
    new_faction = allocate_faction(name, resources, power);
    if(new_faction == NULL) return;
    new_faction->next = *factions;
    *factions = new_faction;
}

void remove_faction(faction_t **factions, char name[15]){
    faction_t *aux = *factions;
    (*factions) = (*factions)->next;
    free(aux);
}