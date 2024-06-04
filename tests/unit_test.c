#include <stdlib.h>
#include "CUnit/Basic.h"
#include "tests/unit_test.h"
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
    unit_t *units = NULL;
    insert_unit(&units, 22, 44, EXPLORER);          // Insere uma 'unit' na lista encadeada 'units'

    CU_ASSERT_PTR_NOT_NULL(units);                  // Verifica se a lista encadeada 'units' continua vazia
    if(units == NULL) return;                       // Caso a 'units' esteja vazia o teste para nesse ponto

    CU_ASSERT_EQUAL(units->x, 22);                  // Testa se 'units->x' é 22;
    CU_ASSERT_EQUAL(units->y, 44);                  // Testa se 'units->y' é 44;
    CU_ASSERT_EQUAL(units->type, EXPLORER);         // Testa se 'units->type' é EXPLORER;
    CU_ASSERT_PTR_NULL(units->next);                // Testa se 'unit->next' é 'NULL';
    
    insert_unit(&units, 11, 22, SOLDIER);           // Insere mais um 'unit' na lista encadeada 'units' (LIFO - Last in First out)

    CU_ASSERT_EQUAL(units->x, 11);                  // Testa se 'units->x' é 11;
    CU_ASSERT_EQUAL(units->y, 22);                  // Testa se 'units->y' é 22;
    CU_ASSERT_EQUAL(units->type, SOLDIER);          // Testa se 'units->type' é SOLDIER;
    CU_ASSERT_PTR_NOT_NULL(units->next);            // Testa se 'unit->next' não é 'NULL';

    CU_ASSERT_EQUAL(units->next->x, 22);            // Testa se 'units->next->x' é 22;
    CU_ASSERT_EQUAL(units->next->y, 44);            // Testa se 'units->next->y' é 44;
    CU_ASSERT_EQUAL(units->next->type, EXPLORER);   // Testa se 'units->next->type' é SOLDIER;
    CU_ASSERT_PTR_NULL(units->next->next);          // Testa se 'unit->next->next' não é 'NULL';
}

void remove_unit_test(){
    unit_t *units = NULL;                   // Insere uma 'unit' na lista encadeada 'units'
    insert_unit(&units, 11, 22, SOLDIER);   // Insere um 'unit' na lista encadeada 'units'
    insert_unit(&units, 22, 44, EXPLORER);  // Insere mais um 'unit' na lista encadeada 'units'

    if(units == NULL) {                     // Caso a 'units' esteja vazia o teste para nesse ponto
        CU_FAIL("Failed to insert units");
        return;
    };

    remove_unit(&units, 22, 44);            // Remove um 'unit' na lista encadeada 'units' (LIFO - Last in First out)

    CU_ASSERT_EQUAL(units->x, 11);          // Testa se 'units->x' é 11;
    CU_ASSERT_EQUAL(units->y, 22);          // Testa se 'units->y' é 22;
    CU_ASSERT_EQUAL(units->type, SOLDIER);  // Testa se 'units->type' é SOLDIER;
    CU_ASSERT_PTR_NULL(units->next);        // Testa se 'unit->next' é 'NULL';

    remove_unit(&units, 11, 22);            // Remove mais um 'unit' na lista encadeada 'units'

    CU_ASSERT_PTR_NULL(units);              // Testa se 'units' é 'NULL';
}
