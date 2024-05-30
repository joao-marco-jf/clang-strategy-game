#ifndef UNIT_H
#define UNIT_H

typedef enum unit_e {
    SOLDIER = 1,
    EXPLORER = 2
} unit_e;

typedef struct unit_t {
    int x;
    int y;
    unit_e type;
    struct unit_t *next;
} unit_t;

unit_t *alocate_unit(int x, int y, unit_e type);
void insert_unit(unit_t **units, int x, int y, unit_e type);
void remove_unit(unit_t **units, int x, int y);
void get_unit(unit_t *units, int x, int y);

#endif