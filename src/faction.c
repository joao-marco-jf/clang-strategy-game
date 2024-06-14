/**
 * @file faction.c
 * @brief Implementação das funções relacionadas às facções do jogo.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game/faction.h"

/**
 * @brief Aloca memória para uma nova facção e inicializa seus atributos.
 * 
 * @param name O nome da facção.
 * @param resources Os recursos da facção.
 * @param power O poder da facção.
 * @return Um ponteiro para a nova facção alocada.
 */
faction_t *allocate_faction(char name[15], int resources, int power){
    faction_t *new_faction = NULL;
    new_faction = (faction_t *) malloc(sizeof(faction_t));
    if(new_faction == NULL) return NULL;
    strcpy(new_faction->name, name);
    new_faction->resources = resources;
    new_faction->power = power;
    new_faction->next = NULL;
    new_faction->units = NULL;
    new_faction->buildings = NULL;
    return new_faction;
}

/**
 * @brief Insere uma nova facção na lista de facções.
 * 
 * @param factions Um ponteiro para a lista de facções.
 * @param name O nome da facção.
 * @param resources Os recursos da facção.
 * @param power O poder da facção.
 */
void insert_faction(faction_t **factions, char name[15], int resources, int power){
    faction_t *new_faction = NULL;
    new_faction = allocate_faction(name, resources, power);
    if(new_faction == NULL) return;
    new_faction->next = *factions;
    *factions = new_faction;
}

/**
 * @brief Remove uma facção da lista de facções.
 * 
 * @param factions Um ponteiro para a lista de facções.
 * @param name O nome da facção a ser removida.
 */
void remove_faction(faction_t **factions, char name[15]){
    // TODO: Implementar a função remove_faction   
}