#include <stdlib.h>

#include "CUnit/Basic.h"
#include "unit_test.h"

#include "unit.h"

unit_t *units = NULL;

void allocate_unit_test() {
    unit_t *unit = NULL;
    unit = allocate_unit(22, 44, SOLDIER);
    CU_ASSERT_PTR_NOT_NULL(unit);
    CU_ASSERT_EQUAL(unit->x, 22);
    CU_ASSERT_EQUAL(unit->y, 44);
    CU_ASSERT_EQUAL(unit->type, SOLDIER);
    CU_ASSERT_PTR_NULL(unit->next);
    free(unit);

    unit = allocate_unit(11, 22, EXPLORER);
    CU_ASSERT_PTR_NOT_NULL(unit);
    CU_ASSERT_EQUAL(unit->x, 11);
    CU_ASSERT_EQUAL(unit->y, 22);
    CU_ASSERT_EQUAL(unit->type, EXPLORER);
    CU_ASSERT_PTR_NULL(unit->next);
    free(unit);
    unit = NULL;
}

void insert_unit_test(){
    unit_t *aux = units;
    insert_unit(units, 22, 44, EXPLORER);

    CU_ASSERT_EQUAL(aux->x, 22);
    CU_ASSERT_EQUAL(aux->y, 44);
    CU_ASSERT_EQUAL(aux->type, EXPLORER);
    CU_ASSERT_PTR_NULL(aux->next);
    
    insert_unit(units, 11, 22, SOLDIER);

    CU_ASSERT_EQUAL(aux->x, 11);
    CU_ASSERT_EQUAL(aux->y, 22);
    CU_ASSERT_EQUAL(aux->type, EXPLORER);
    CU_ASSERT_PTR_NOT_NULL(aux->next);

    if(aux->next == NULL) return;

    aux = aux->next;

    CU_ASSERT_EQUAL(aux->x, 22);
    CU_ASSERT_EQUAL(aux->y, 44);
    CU_ASSERT_EQUAL(aux->type, EXPLORER);
    CU_ASSERT_PTR_NULL(aux->next);
}

void remove_unit_test(){

}

void get_unit_test(){
  
}