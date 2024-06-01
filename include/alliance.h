#ifndef ALLIANCE_H
#define ALLIANCE_H

typedef struct alliance_t {
    char name[15];
    struct alliance_t *next;
} alliance_t;

alliance_t *allocate_alliance(char name[15]);
void insert_alliance(alliance_t **alliances, char name[15]);
void remove_alliance(alliance_t **alliances, char name[15]);

#endif