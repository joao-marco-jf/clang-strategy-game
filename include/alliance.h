#ifndef ALLIANCE_H
#define ALLIANCE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct alliance_t {
    char name[15];
    struct alliance_t *next;
} alliance_t;

alliance_t *allocate_alliance(char name[15]);
void insert_alliance(alliance_t **alliances, char name[15]);
void free_alliances(alliance_t **alliances);

#endif