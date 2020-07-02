/*
** EPITECH PROJECT, 2019
** CPE_lemin_2019
** File description:
** main.c
*/

#include "../include/my.h"

void update_graph(nodes_t **graph, storage_t *storage, int i, int j)
{
    nodes_t *copy = NULL;

    for (copy = storage->nodes; copy; copy = copy->next)
        if (copy->cellule.index == j)
            break;
    add_node_back(&graph[i], copy->cellule);
}

nodes_t **create_graph(storage_t *storage)
{
    nodes_t **graph = my_malloc(sizeof(nodes_t *) * (storage->nb_nodes + 1));

    for (int i = 0; i < storage->nb_nodes; i += 1) {
        graph[i] = NULL;
        for (int j = 0; j < storage->nb_nodes; j += 1) {
            if (storage->links[i][j])
                update_graph(graph, storage, i, j);
        }
    }
    graph[storage->nb_nodes] = NULL;
    for (nodes_t *copy = storage->nodes; copy; copy = copy->next)
        add_front(&graph[copy->cellule.index], copy->cellule);
    return (graph);
}

void fourmitage(storage_t *storage, int *list, int len, int save)
{
    static int turn = 1;
    ants_t *position = update_struct(storage, list);
    int index = 0;

    do {
        for (index = 0; position[index].position == -1; index += 1);
        for (int i = index - 1; (turn > len) ? \
        index < len + i : index < turn; index += 1) {
            if (index >= save)
                break;
            position[index].index += 1;
            position[index].position = list[position[index].index];
        }
        good_print(position, save, list);
        for (int i = 0; i < save; i += 1)
            if (position[i].position == list[len - 1]) {
                storage->nb_ants -= 1;
                position[i].position = -1;
            }
        turn += 1;
    } while (storage->nb_ants > 0);
}

int final_print(nodes_t **graph, storage_t *storage)
{
    int len = 0;
    int len_list = 0;
    int *list = NULL;
    nodes_t *cur = graph[storage->end->index];

    my_printf("#moves\n");
    for (; cur; cur = cur->previous)
        len++;
    len_list = len;
    list = my_malloc(sizeof(int) * (len + 1));
    list[len] = -1;
    for (cur = graph[storage->end->index]; cur; cur = cur->previous)
        list[--len] = cur->cellule.index;
    fourmitage(storage, list, len_list, storage->nb_ants);
    return (0);
}

int main(int ac, char *av[])
{
    storage_t *storage = NULL;
    nodes_t **graph = NULL;
    (void)av;

    if (ac != 1)
        return (84);
    storage = create_storage(NULL, NULL, 100);
    if (!storage || !storage->nodes || !storage->links \
    || storage->nb_ants <= 0 || !storage->end || !storage->start \
    || storage->end->index == storage->start->index)
        return (84);
    for (nodes_t *copy = storage->nodes; copy; copy = copy->next)
        if (copy->cellule.index < 0 || copy->cellule.index >= storage->nb_nodes)
            return (84);
    graph = create_graph(storage);
    return (find_way(graph, storage, 0));
}