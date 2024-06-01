#include <stdlib.h>
#include "CUnit/Basic.h"
#include "alliance_test.h"
#include "alliance.h"

alliance_t *alliances = NULL;

void allocate_alliance_test() {
    alliance_t *alliance = NULL;                            // Inicializa um ponteiro do tipo 'alliance_t' com valor 'NULL';
    alliance = allocate_alliance("Aliação 01");             // 'alliance' recebe o retorno do tipo 'alliance_t' da função 'allocate_alliance;
    CU_ASSERT_PTR_NOT_NULL(alliance);                       // Testa se 'alliance' não é um ponteiro 'NULL';
    CU_ASSERT_STRING_EQUAL(alliance->name, "Aliação 01");   // Testa se 'alliance->name' é "Aliação 01";
    CU_ASSERT_PTR_NULL(alliance->next);                     // Testa se 'alliance->next' é 'NULL';
    free(alliance);                                         // Libera memória;

    alliance = allocate_alliance("Aliança 02");             // 'alliance' recebe o retorno do tipo 'alliance_t' da função 'allcate_alliance;
    CU_ASSERT_PTR_NOT_NULL(alliance);                       // Testa se 'alliance' não é um ponteiro 'NULL';
    CU_ASSERT_STRING_EQUAL(alliance->name, "Aliança 02");   // Testa se 'alliance->name' é "Aliança 02";
    CU_ASSERT_PTR_NULL(alliance->next);                     // Testa se 'alliance->next' é 'NULL';
    free(alliance);                                         // Libera memória;

    alliance = NULL;                                        // Altera 'alliance' para 'NULL';
}

void insert_alliance_test(){
    alliance_t *alliances = NULL;
    insert_alliance(&alliances, "Aliação 01");              // Insere uma 'alliance' na lista encadeada 'alliances'

    CU_ASSERT_PTR_NOT_NULL(alliances);                      // Verifica se a lista encadeada 'alliances' continua vazia
    if(alliances == NULL) return;                           // Caso a 'alliances' esteja vazia o teste para nesse ponto

    CU_ASSERT_STRING_EQUAL(alliances->name, "Aliação 01");  // Testa se 'alliance->name' é "Aliança 02";
    CU_ASSERT_PTR_NULL(alliances->next);                    // Testa se 'alliance->next' é 'NULL';
    
    insert_alliance(&alliances, "Aliança 02");              // Insere mais um 'alliance' na lista encadeada 'alliances' (LIFO - Last in First out)

    CU_ASSERT_STRING_EQUAL(alliances->name, "Aliança 02");  // Testa se 'alliance->name' é "Aliança 02";
    CU_ASSERT_PTR_NOT_NULL(alliances->next);                // Testa se 'alliances->next' não é 'NULL';

    CU_ASSERT_STRING_EQUAL(alliances->name, "Aliação 01");  // Testa se 'alliance->name' é "Aliança 02";
    CU_ASSERT_PTR_NULL(alliances->next->next);              // Testa se 'alliances->next->next' não é 'NULL';
}

void remove_alliance_test(){
    alliance_t *alliances = NULL;                           // Insere uma 'alliance' na lista encadeada 'alliances'
    insert_alliance(&alliances, "Aliança 02");              // Insere uma 'alliance' na lista encadeada 'alliances'
    insert_alliance(&alliances, "Aliação 01");              // Insere uma 'alliance' na lista encadeada 'alliances'

    if(alliances == NULL) {                                 // Caso a 'alliances' esteja vazia o teste para nesse ponto
        CU_FAIL("Failed to insert alliances");
        return;
    };

    remove_alliance(&alliances, "Aliação 01");              // Remove um 'alliance' na lista encadeada 'alliances' (LIFO - Last in First out)

    CU_ASSERT_STRING_EQUAL(alliances->name, "Aliança 02");  // Testa se 'alliance->name' é "Aliança 02";
    CU_ASSERT_PTR_NULL(alliances->next);                    // Testa se 'alliances->next' é 'NULL';

    remove_alliance(&alliances, "Aliação 01");              // Remove mais um 'alliance' na lista encadeada 'alliances'

    CU_ASSERT_PTR_NULL(alliances);                          // Testa se 'alliances' é 'NULL';
}
