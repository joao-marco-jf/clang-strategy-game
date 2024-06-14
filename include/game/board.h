#ifndef BOARD_H
#define BOARD_H

#include "faction.h"
#include "building.h"
#include "unit.h"

typedef struct board_poss_t
{
    int line;
    int column;
    unit_t* p_unit_t;
    building_t* p_building_t;
    faction_t* p_faction_t;
    struct board_poss_t *right;
    struct board_poss_t *bellow;
}board_poss_t;

board_poss_t *allocate_board(int line, int column, unit_t *p_unit_t, building_t *p_building_t, faction_t *p_faction_t);

#endif