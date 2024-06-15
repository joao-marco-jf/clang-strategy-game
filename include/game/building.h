#ifndef BUILDING_H
#define BUILDING_H

typedef enum building_e {
    RESOURCE_BUILDING = 1,
    TRAINING_CAMP = 2,
    RESEARCH_LAB = 3
} building_e;

typedef struct building_t {
    int x;
    int y;
    int id;
    char name[15];
    building_e type;
    struct building_t *next;
} building_t;

building_t *allocate_building(int x, int y, int id, char name[15], building_e type);
void insert_building(building_t **buildings, int x, int y, int id, char name[15], building_e type);
void remove_building(building_t **buildings, int x, int y);

#endif