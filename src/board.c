#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game/board.h"

void init_board(int lines, int columns, board_t board[lines][columns]){
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            board[i][j].p_faction_t = NULL;
            board[i][j].p_building_t = NULL;
            board[i][j].p_unit_t = NULL;
        }
    }
}

void print_board(int lines, int columns, board_t board[lines][columns]){
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            if(board[i][j].p_faction_t != NULL && board[i][j].p_building_t != NULL && board[i][j].p_unit_t != NULL){
                printf("[3]");
            }
            else if(board[i][j].p_faction_t != NULL && board[i][j].p_building_t != NULL){
                printf("[2]");
            }
            else if(board[i][j].p_faction_t != NULL && board[i][j].p_unit_t != NULL){
                printf("[2]");
            }
            else if(board[i][j].p_building_t != NULL && board[i][j].p_unit_t != NULL){
                printf("[2]");
            }
            else if(board[i][j].p_faction_t != NULL){
                printf("[F]", board[i][j].p_faction_t->name);
            }
            else if(board[i][j].p_building_t != NULL){
                printf("[B]");
            }
            else if(board[i][j].p_unit_t != NULL){
                printf("[U]");
            }
            else{
                printf("[ ]");
            }
        }
        printf("\n");
    }
}

void insert_faction_on_board(int lines, int columns, board_t board[columns][lines], faction_t** factions, char name[15], int x, int y){
    insert_faction(*(&factions), name, 100, 100);
    board[x][y].p_faction_t = factions;
}

void insert_building_on_board(int lines, int columns, board_t board[columns][lines], building_t** buildings, int x, int y, building_e type){
    insert_building(*(&buildings), x, y, type);
    board[x][y].p_building_t = buildings;
}

void insert_unit_on_board(int lines, int columns, board_t board[columns][lines], unit_t** units, int x, int y, unit_e type){
    insert_unit(*(&units), x, y, type);
    board[x][y].p_unit_t = units;
}


void remove_unit_on_board(int lines, int columns, board_t board[columns][lines], unit_t** units, int x, int y){
    remove_unit(*(&units), x, y);
    board[x][y].p_unit_t = NULL;
}