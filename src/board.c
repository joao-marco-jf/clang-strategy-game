#include "board.h"

board_t *create_board(int lines, int columns){
    board_t *new_board = (board_t *) malloc(sizeof(board_t));
    if(new_board == NULL) return NULL;
    new_board->lines = lines;
    new_board->columns = columns;
    new_board->head = NULL;
    return new_board;
}

node_t *allocate_node(int line, int col, unit_t* unit, building_t* building, faction_t* faction){
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if(new_node == NULL) return NULL;
    new_node->line = line;
    new_node->col = col;
    new_node->unit = unit;
    new_node->building = building;
    new_node->faction = faction;
    new_node->next = NULL;
    return new_node;
}

void insert_node(board_t *board, int line, int col, unit_t *unit, building_t *building, faction_t *faction){
    /*
    if(!unit && !building && !faction){
        printf("Error: Node cannot have unit, building and faction at the same time.\n");
        return;
    }
    */

    node_t *current = board->head;
    while(current != NULL){
        if(current->line == line && current->col == col){
            current->faction = current->faction == NULL ? faction : current->faction; 
            current->building = current->building == NULL ? building : current->building;
            current->unit = current->unit == NULL ? unit : current->unit;

            /*
            if(unit && current->unit) {
                unit->x++;
                insert_node(board, line + 1, col, unit, NULL, NULL);
            }
            */

            return;
        }
        current = current->next;
    }

    node_t *new_node = allocate_node(line, col, unit, building, faction);
    if(new_node == NULL) return;
    new_node->next = board->head;
    board->head = new_node;
}

faction_t *get_faction_board(board_t *board, int line, int col){
    node_t *current = board->head;
    while(current != NULL){
        if(current->line == line && current->col == col){
            return current->faction;
        }
        current = current->next;
    }
    return NULL;
}

building_t *get_building_board(board_t *board, int line, int col){
    node_t *current = board->head;
    while(current != NULL){
        if(current->line == line && current->col == col){
            return current->building;
        }
        current = current->next;
    }
    return 0;
}
unit_t *get_unit_board(board_t *board, int line, int col){
    node_t *current = board->head;
    while(current != NULL){
        if(current->line == line && current->col == col){
            return current->unit;
        }
        current = current->next;
    }
    return 0;
}

void remove_node(board_t *board, int row, int col){
    node_t *current = board->head;
    node_t *prev = NULL;

    while(current != NULL){
        if(current->line == row && current->col == col){
            if(prev == NULL){
                board->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void free_board(board_t *board){
    node_t *current = board->head;
    while(current != NULL){
        node_t *temp = current;
        current = current->next;
        free(temp);
    }
}

void print_board(board_t *board){
    for(int i = 0; i < board->lines; i++){
        for(int j = 0; j < board->columns; j++){
            if(get_unit_board(board, i, j) && get_building_board(board, i, j) && get_faction_board(board, i, j)) printf("[FBU]");
            else if(get_unit_board(board, i, j) && get_building_board(board, i, j)) printf("[ BU]");
            else if(get_unit_board(board, i, j) && get_faction_board(board, i, j)) printf("[FU ]");
            else if(get_building_board(board, i, j) && get_faction_board(board, i, j)) printf("[F B]");
            else if(get_faction_board(board, i, j)) printf("[F  ]");
            else if(get_building_board(board, i, j)) printf("[  B]");
            else if(get_unit_board(board, i, j)) printf("[ U ]");
            else printf("[   ]");
        }
        printf("\n");
    }
}