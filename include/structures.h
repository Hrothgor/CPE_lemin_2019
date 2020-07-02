/*
** EPITECH PROJECT, 2019
** CPE_lemin_2019
** File description:
** structures.h
*/

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "./my.h"

typedef struct cell_s
{
    int index;
    int y;
    int x;
    int distance;
    bool visited;
} cell_t;

typedef struct nodes_s
{
    cell_t cellule;
    struct nodes_s *next;
    struct nodes_s *previous;
} nodes_t;

typedef struct ants_s
{
    int position;
    int index;
} ants_t;

typedef struct storage_s
{
    int nb_ants;
    int nb_nodes;
    int **links;
    cell_t *start;
    cell_t *end;
    nodes_t *nodes;
}storage_t;

#endif /* STRUCTURES_H_ */