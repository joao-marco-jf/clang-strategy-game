#include <stdlib.h>
#include "CUnit/Basic.h"
#include "tests/faction_test.h"
#include "faction.h"

faction_t *factions = NULL;

void allocate_faction_test() {
    faction_t *faction = NULL;                          // Inicializa um ponteiro do tipo 'faction_t' com valor 'NULL';
    faction = allocate_faction("Facção 01", 0, 0);      // 'faction' recebe o retorno do tipo 'faction_t' da função 'allcate_faction;
    CU_ASSERT_PTR_NOT_NULL(faction);                    // Testa se 'faction' não é um ponteiro 'NULL';
    CU_ASSERT_STRING_EQUAL(faction->name, "Facção 01"); // Testa se 'faction->name' é "Facção 01";
    CU_ASSERT_EQUAL(faction->resources, 0);             // Testa se 'faction->resources' é 0;
    CU_ASSERT_EQUAL(faction->power, 0);                 // Testa se 'faction->power' é 0;
    CU_ASSERT_PTR_NULL(faction->next);                  // Testa se 'faction->next' é 'NULL';
    free(faction);                                      // Libera memória;

    faction = allocate_faction("Facção 02", 11, 22);    // 'faction' recebe o retorno do tipo 'faction_t' da função 'allcate_faction;
    CU_ASSERT_PTR_NOT_NULL(faction);                    // Testa se 'faction' não é um ponteiro 'NULL';
    CU_ASSERT_STRING_EQUAL(faction->name, "Facção 02"); // Testa se 'faction->name' é "Facção 02";
    CU_ASSERT_EQUAL(faction->resources, 11);            // Testa se 'faction->resources' é 11;
    CU_ASSERT_EQUAL(faction->power, 22);                // Testa se 'faction->power' é 22;
    CU_ASSERT_PTR_NULL(faction->next);                  // Testa se 'faction->next' é 'NULL';
    free(faction);                                      // Libera memória;

    faction = NULL;                                     // Altera 'faction' para 'NULL';
}

void insert_faction_test(){
    faction_t *factions = NULL;
    insert_faction(&factions, "Facção 01", 22, 44);     // Insere uma 'faction' na lista encadeada 'factions'

    CU_ASSERT_PTR_NOT_NULL(factions);                   // Verifica se a lista encadeada 'factions' continua vazia
    if(factions == NULL) return;                        // Caso a 'factions' esteja vazia o teste para nesse ponto

    CU_ASSERT_STRING_EQUAL(factions->name, "Facção 01");// Testa se 'faction->name' é "Facção 02";
    CU_ASSERT_EQUAL(factions->resources, 22);           // Testa se 'factions->resources' é 22;
    CU_ASSERT_EQUAL(factions->power, 44);               // Testa se 'factions->power' é 44;
    CU_ASSERT_PTR_NULL(factions->next);                 // Testa se 'faction->next' é 'NULL';
    
    insert_faction(&factions, "Facção 02", 11, 22);     // Insere mais um 'faction' na lista encadeada 'factions' (LIFO - Last in First out)

    CU_ASSERT_STRING_EQUAL(factions->name, "Facção 02");// Testa se 'faction->name' é "Facção 02";
    CU_ASSERT_EQUAL(factions->resources, 11);           // Testa se 'factions->resources' é 11;
    CU_ASSERT_EQUAL(factions->power, 22);               // Testa se 'factions->power' é 22;
    CU_ASSERT_PTR_NOT_NULL(factions->next);             // Testa se 'factions->next' não é 'NULL';

    CU_ASSERT_STRING_EQUAL(factions->next->name, "Facção 01");       // Testa se 'faction->name' é "Facção 02";
    CU_ASSERT_EQUAL(factions->next->resources, 22);     // Testa se 'factions->next->resources' é 22;
    CU_ASSERT_EQUAL(factions->next->power, 44);         // Testa se 'factions->next->power' é 44;
    CU_ASSERT_PTR_NULL(factions->next->next);           // Testa se 'factions->next->next' não é 'NULL';
}

void remove_faction_test(){
    faction_t *factions = NULL;                         // Insere uma 'faction' na lista encadeada 'factions'
    insert_faction(&factions, "Facção 02", 11, 22);     // Insere uma 'faction' na lista encadeada 'factions'
    insert_faction(&factions, "Facção 01", 22, 44);     // Insere uma 'faction' na lista encadeada 'factions'

    if(factions == NULL) {                              // Caso a 'factions' esteja vazia o teste para nesse ponto
        CU_FAIL("Failed to insert factions");
        return;
    };

    remove_faction(&factions, "Facção 01");             // Remove um 'faction' na lista encadeada 'factions' (LIFO - Last in First out)

    CU_ASSERT_STRING_EQUAL(factions->name, "Facção 02");// Testa se 'faction->name' é "Facção 02";
    CU_ASSERT_EQUAL(factions->resources, 11);           // Testa se 'factions->resources' é 11;
    CU_ASSERT_EQUAL(factions->power, 22);               // Testa se 'factions->power' é 22;
    CU_ASSERT_PTR_NULL(factions->next);                 // Testa se 'factions->next' é 'NULL';

    remove_faction(&factions, "Facção 01");             // Remove mais um 'faction' na lista encadeada 'factions'

    CU_ASSERT_PTR_NULL(factions);                       // Testa se 'factions' é 'NULL';
}
