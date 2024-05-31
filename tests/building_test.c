#include <stdlib.h>
#include "CUnit/Basic.h"
#include "building_test.h"
#include "building.h"

building_t *buildings = NULL;

void allocate_building_test() {
    building_t *building = NULL;                                // Inicializa um ponteiro do tipo 'building_t' com valor 'NULL';
    building = allocate_building(22, 44, RESOURCE_BUILDING);    // 'building' recebe o retorno do tipo 'building_t' da função 'allcate_building;
    CU_ASSERT_PTR_NOT_NULL(building);                           // Testa se 'building' não é um ponteiro 'NULL';
    CU_ASSERT_EQUAL(building->x, 22);                           // Testa se 'building->x' é 22;
    CU_ASSERT_EQUAL(building->y, 44);                           // Testa se 'building->y é 44';
    CU_ASSERT_EQUAL(building->type, RESOURCE_BUILDING);         // Testa se 'building->type' é RESOURCE_BUILDING;
    CU_ASSERT_PTR_NULL(building->next);                         // Testa se 'building->next' é 'NULL';
    free(building);                                             // Libera memória;

    building = allocate_building(11, 22, TRAINING_CAMP);        // 'building' recebe o retorno do tipo 'building_t' da função 'allcate_building;
    CU_ASSERT_PTR_NOT_NULL(building);                           // Testa se 'building' não é um ponteiro 'NULL';
    CU_ASSERT_EQUAL(building->x, 11);                           // Testa se 'building->x' é 11;
    CU_ASSERT_EQUAL(building->y, 22);                           // Testa se 'building->y' é 22;
    CU_ASSERT_EQUAL(building->type, TRAINING_CAMP);             // Testa se 'building->type' é TRAINING_CAMP;
    CU_ASSERT_PTR_NULL(building->next);                         // Testa se 'building->next' é 'NULL';
    free(building);                                             // Libera memória;
    building = NULL;                                            // Altera 'building' para 'NULL';
}

void insert_building_test(){
    building_t *buildings = NULL;
    insert_building(&buildings, 22, 44, TRAINING_CAMP);         // Insere uma 'building' na lista encadeada 'buildings'

    CU_ASSERT_PTR_NOT_NULL(buildings);                          // Verifica se a lista encadeada 'buildings' continua vazia
    if(buildings == NULL) return;                               // Caso a 'buildings' esteja vazia o teste para nesse ponto

    CU_ASSERT_EQUAL(buildings->x, 22);                          // Testa se 'buildings->x' é 22;
    CU_ASSERT_EQUAL(buildings->y, 44);                          // Testa se 'buildings->y' é 44;
    CU_ASSERT_EQUAL(buildings->type, TRAINING_CAMP);            // Testa se 'buildings->type' é TRAINING_CAMP;
    CU_ASSERT_PTR_NULL(buildings->next);                        // Testa se 'building->next' é 'NULL';
    
    insert_building(&buildings, 11, 22, RESOURCE_BUILDING);     // Insere mais um 'building' na lista encadeada 'buildings' (LIFO - Last in First out)

    CU_ASSERT_EQUAL(buildings->x, 11);                          // Testa se 'buildings->x' é 11;
    CU_ASSERT_EQUAL(buildings->y, 22);                          // Testa se 'buildings->y' é 22;
    CU_ASSERT_EQUAL(buildings->type, RESOURCE_BUILDING);        // Testa se 'buildings->type' é RESOURCE_BUILDING;
    CU_ASSERT_PTR_NOT_NULL(buildings->next);                    // Testa se 'buildings->next' não é 'NULL';

    CU_ASSERT_EQUAL(buildings->next->x, 22);                    // Testa se 'buildings->next->x' é 22;
    CU_ASSERT_EQUAL(buildings->next->y, 44);                    // Testa se 'buildings->next->y' é 44;
    CU_ASSERT_EQUAL(buildings->next->type, TRAINING_CAMP);      // Testa se 'buildings->next->type' é RESOURCE_BUILDING;
    CU_ASSERT_PTR_NULL(buildings->next->next);                  // Testa se 'buildings->next->next' não é 'NULL';
}

void remove_building_test(){
    building_t *buildings = NULL;                               // Insere uma 'building' na lista encadeada 'buildings'
    insert_building(&buildings, 11, 22, RESOURCE_BUILDING);     // Insere um 'building' na lista encadeada 'buildings'
    insert_building(&buildings, 22, 44, TRAINING_CAMP);         // Insere mais um 'building' na lista encadeada 'buildings'

    if(buildings == NULL) {                                     // Caso a 'buildings' esteja vazia o teste para nesse ponto
        CU_FAIL("Failed to insert buildings");
        return;
    };

    remove_building(&buildings, 22, 44);                        // Remove um 'building' na lista encadeada 'buildings' (LIFO - Last in First out)

    CU_ASSERT_EQUAL(buildings->x, 11);                          // Testa se 'buildings->x' é 11;
    CU_ASSERT_EQUAL(buildings->y, 22);                          // Testa se 'buildings->y' é 22;
    CU_ASSERT_EQUAL(buildings->type, RESOURCE_BUILDING);        // Testa se 'buildings->type' é RESOURCE_BUILDING;
    CU_ASSERT_PTR_NULL(buildings->next);                        // Testa se 'buildings->next' é 'NULL';

    remove_building(&buildings, 11, 22);                        // Remove mais um 'building' na lista encadeada 'buildings'

    CU_ASSERT_PTR_NULL(buildings);                              // Testa se 'buildings' é 'NULL';
}
