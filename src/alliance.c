/**
 * @file alliance.c
 * @brief Implementação das funções relacionadas às alianças do jogo.
 */

#include "alliance.h"

/**
 * @brief Aloca memória para uma nova aliança e inicializa seus atributos.
 * 
 * @param name O nome da aliança.
 * @return Um ponteiro para a nova aliança alocada.
 */
alliance_t *allocate_alliance(char name[15]){
    alliance_t *new_alliance = NULL;
    new_alliance = (alliance_t *) malloc(sizeof(alliance_t));
    if(new_alliance == NULL) return NULL;
    strcpy(new_alliance->name, name);
    new_alliance->next = NULL;
    return new_alliance;
}

/**
 * @brief Insere uma nova aliança no início da lista de alianças.
 * 
 * @param alliances Um ponteiro para o ponteiro da lista de alianças.
 * @param name O nome da aliança a ser inserida.
 */
void insert_alliance(alliance_t **alliances, char name[15]){
    alliance_t *new_alliance = NULL;
    new_alliance = allocate_alliance(name);
    if(new_alliance == NULL) return;
    new_alliance->next = *alliances;
    *alliances = new_alliance;
}

/**
 * @brief Libera a memória alocada para a lista de alianças.
 *
 * A função `free_alliances` percorre a lista encadeada de alianças,
 * liberando a memória alocada para cada nó da lista e ajustando os
 * ponteiros necessários.
 *
 * @param alliances Ponteiro para um ponteiro para o início da lista de alianças.
 *                  Ao final da função, o ponteiro `alliances` é ajustado para
 *                  apontar para `NULL`, indicando que a lista está vazia.
 *
 * @note Certifique-se de que o ponteiro `alliances` aponta para a lista de alianças
 *       corretamente. A função assume que cada nó da lista de alianças foi alocado
 *       dinamicamente (por exemplo, com `malloc`) e precisa ser liberado com `free`.
 *       Após chamar esta função, o ponteiro `alliances` é ajustado para `NULL`,
 *       indicando que a lista está vazia e os recursos foram liberados.
 */
void free_alliances(alliance_t **alliances) {
    alliance_t *current = *alliances;
    alliance_t *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        free(current);  // Libera a memória alocada para o nó atual
        current = next; // Avança para o próximo nó
    }
    
    *alliances = NULL; // Define o ponteiro de início da lista como NULL
}