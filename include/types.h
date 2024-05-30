#ifndef TYPES_H
#define TYPES_H

typedef enum unidade_e {
    SOLDADO = 1,
    EXPLORADOR = 2
} unidade_e;

typedef struct unidade_t {
    int x;
    int y;
    unidade_e tipo;
    struct unidade_t *next;
} unidade_t;

typedef enum edificio_e {
    EDIFICIO_DE_RECURSO = 1,
    CAMPO_DE_TREINAMENTO = 2,
    LABORATORIO_DE_PESQUISA = 3
} edificio_e;

typedef struct edificio_t {
    int x;
    int y;
    edificio_e tipo;
    struct edificio_t *next;
} edificio_t;

typedef struct alianca_t {
    char name[15];
    struct alianca *next;
} alianca_t;

typedef struct faccao_t {
    char name[15];
    int recursos;
    int poder;
    struct faccao_t *next;
    unidade_t *unidades;
    edificio_t *edificios;
    alianca_t *alianca_t;
} faccao_t;

#endif