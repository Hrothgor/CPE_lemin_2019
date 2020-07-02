/*
** EPITECH PROJECT, 2019
** CPE_lemin_2019
** File description:
** check_end.c
*/

#include "../include/my.h"

ants_t *update_struct(storage_t *storage, int *list)
{
    ants_t *position = my_malloc(sizeof(ants_t) * storage->nb_ants);

    for (int i = 0; i < storage->nb_ants; i += 1) {
        position[i].index = 0;
        position[i].position = list[0];
    }
    return (position);
}

void update_graph_d(nodes_t **graph, int index, int \
new_distance, nodes_t *current)
{
    for (int i = 0; graph[i]; i += 1)
        for (nodes_t *copy = graph[i]; copy; copy = copy->next)
            if (index == copy->cellule.index) {
                copy->cellule.distance = new_distance;
                copy->previous = current;
            }
}

nodes_t *find_smaller(nodes_t **graph)
{
    int find_smaller = 1000000;
    nodes_t *result = NULL;

    for (int index = 0; graph[index]; index += 1)
        if (!graph[index]->cellule.visited && \
        find_smaller > graph[index]->cellule.distance) {
            find_smaller = graph[index]->cellule.distance;
            result = graph[index];
        }
    return (result);
}

int find_way(nodes_t **graph, storage_t *storage, int save_d)
{
    nodes_t *current = graph[storage->start->index];
    int save_i = 0;

    while (!is_finished(graph)) {
        if (!current)
            return (84);
        save_d = current->cellule.distance;
        save_i = current->cellule.index;
        for (nodes_t *copy = current->next; copy; copy = copy->next) {
            if (!copy->cellule.visited && save_d + 1 < copy->cellule.distance) {
                update_graph_d(graph, copy->cellule.index, save_d + 1, current);
            }
        }
        current->cellule.visited = true;
        for (int i = 0; graph[i]; i += 1)
            for (nodes_t *copy = graph[i]; copy; copy = copy->next)
                if (copy->cellule.index == save_i)
                    copy->cellule.visited = true;
        current = find_smaller(graph);
    }
    return (final_print(graph, storage));
}

int is_finished(nodes_t **nodes)
{
    nodes_t **copy = nodes;

    for (int index = 0; copy[index]; index += 1)
        if (!copy[index]->cellule.visited)
            return (0);
    return (1);
}