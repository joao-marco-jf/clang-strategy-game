#include <stdlib.h>
#include "CUnit/Basic.h"
#include "unit_test.h"
#include "unit.h"

unit_t *units = NULL;

void allocate_unit_test() {
    unit_t *unit = NULL;                      // Inicializa um ponteiro do tipo 'unit_t' com valor 'NULL';
    unit = allocate_unit(22, 44, SOLDIER);    // 'unit' recebe o retorno do tipo 'unit_t' da função 'allcate_unit;
    CU_ASSERT_PTR_NOT_NULL(unit);             // Testa se 'unit' não é um ponteiro 'NULL';
    CU_ASSERT_EQUAL(unit->x, 22);             // Testa se 'unit->x' é 22;
    CU_ASSERT_EQUAL(unit->y, 44);             // Testa se 'unit->y é 44';
    CU_ASSERT_EQUAL(unit->type, SOLDIER);     // Testa se 'unit->type' é SOLDIER;
    CU_ASSERT_PTR_NULL(unit->next);           // Testa se 'unit->next' é 'NULL';
    free(unit);                               // Libera memória;

    unit = allocate_unit(11, 22, EXPLORER);   // 'unit' recebe o retorno do tipo 'unit_t' da função 'allcate_unit;
    CU_ASSERT_PTR_NOT_NULL(unit);             // Testa se 'unit' não é um ponteiro 'NULL';
    CU_ASSERT_EQUAL(unit->x, 11);             // Testa se 'unit->x' é 11;
    CU_ASSERT_EQUAL(unit->y, 22);             // Testa se 'unit->y' é 22;
    CU_ASSERT_EQUAL(unit->type, EXPLORER);    // Testa se 'unit->type' é EXPLORER;
    CU_ASSERT_PTR_NULL(unit->next);           // Testa se 'unit->next' é 'NULL';
    free(unit);                               // Libera memória;
    unit = NULL;                              // Altera 'unit' para 'NULL';
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
