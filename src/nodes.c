/*
** EPITECH PROJECT, 2019
** CPE_lemin_2019
** File description:
** nodes.c
*/

#include "../include/my.h"

void print_list(nodes_t *nodes)
{
    for (nodes_t *copy = nodes; copy; copy = copy->next)
        my_printf("%d %d %d\n", copy->cellule.index, \
        copy->cellule.x, copy->cellule.y);
}

void add_front(nodes_t **nodes, cell_t cellule)
{
    nodes_t *new = my_malloc(sizeof(nodes_t));

    new->cellule = cellule;
    new->previous = NULL;
    if (*nodes)
        (*nodes)->previous = new;
    new->next = *nodes;
    *nodes = new;
}

void add_node_back(nodes_t **nodes, cell_t cellule)
{
    nodes_t *new_node = my_malloc(sizeof(nodes_t));
    nodes_t *save = *nodes;

    new_node->cellule = cellule;
    new_node->cellule.visited = false;
    new_node->next = NULL;
    if (!*nodes) {
        new_node->previous = NULL;
        *nodes = new_node;
        return;
    }
    while (save->next)
        save = save->next;
    save->next = new_node;
    new_node->previous = save;
}