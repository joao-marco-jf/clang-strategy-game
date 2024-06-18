/**
 * @file faction.c
 * @brief Implementação das funções relacionadas às facções do jogo.
 */

#include "faction.h"

/**
 * @brief Aloca memória para uma nova facção e inicializa seus atributos.
 * 
 * @param name O nome da facção.
 * @param resources Os recursos da facção.
 * @param power O poder da facção.
 * @return Um ponteiro para a nova facção alocada.
 */
faction_t *allocate_faction(char name[15], int resources, int power){                 //Esta função aloca memória para uma nova instância de uma aliança, inicializa seu nome e a insere na lista ligada.
    faction_t *new_faction = NULL;
    new_faction = (faction_t *) malloc(sizeof(faction_t));
    if(new_faction == NULL) return NULL;
    strcpy(new_faction->name, name);
    new_faction->resources = resources;
    new_faction->power = power;
    new_faction->next = NULL;
    new_faction->units = NULL;
    new_faction->buildings = NULL;
    return new_faction;
}

/**
 * @brief Insere uma nova facção na lista de facções.
 * 
 * @param factions Um ponteiro para a lista de facções.
 * @param name O nome da facção.
 * @param resources Os recursos da facção.
 * @param power O poder da facção.
 */
void insert_faction(faction_t **factions, char name[15], int resources, int power){  //Esta função insere uma nova facção no início da lista ligada de facções.
    faction_t *new_faction = NULL;
    new_faction = allocate_faction(name, resources, power);
    if(new_faction == NULL) return;
    new_faction->next = *factions;
    *factions = new_faction;
}

/**
 * @brief Busca uma facção na lista encadeada de facções pelo nome.
 *
 * A função `get_faction` percorre a lista encadeada de facções (`faction_t`) apontada
 * por `*factions`, buscando por uma facção cujo nome seja igual ao nome especificado
 * pelo parâmetro `name`. Se encontrar a facção, retorna um ponteiro para ela. Caso contrário,
 * retorna NULL.
 *
 * @param factions Ponteiro para o ponteiro da lista encadeada de facções.
 * @param name Nome da facção a ser buscada.
 * 
 * @return Retorna um ponteiro para a facção encontrada ou NULL se não encontrada.
 */
faction_t *get_faction(faction_t **factions, char name[2]){
    faction_t *current = *factions; // Inicializa o ponteiro `current` com o início da lista
    while(current != NULL){
        // Compara o nome da facção atual com `name`
        if(strcmp(current->name, name) == 0){
            return current; // Retorna a facção atual se o nome corresponder
        }
        current = current->next; // Avança para o próximo nó da lista encadeada
    }
    return NULL; // Retorna NULL se a facção não for encontrada
}

/**
 * @brief Libera a memória alocada para todos os nós de uma lista encadeada de facções.
 *
 * A função `free_factions` percorre a lista encadeada de facções (`faction_t`) apontada
 * por `*factions` e libera a memória alocada para cada nó. Após a liberação de cada nó,
 * o ponteiro do início da lista (`*factions`) é atualizado para apontar para o próximo nó.
 * Quando todos os nós são liberados, o ponteiro é definido como NULL.
 *
 * @param factions Ponteiro para o ponteiro da lista encadeada de facções.
 */
void free_factions(faction_t **factions){
    while(*factions != NULL){
        faction_t *temp = *factions;    // Armazena o nó atual em `temp`
        *factions = (*factions)->next;  // Atualiza `*factions` para apontar para o próximo nó
        free(temp);                     // Libera a memória alocada para o nó atual
    }
}