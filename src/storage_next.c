/*
** EPITECH PROJECT, 2019
** CPE_lemin_2019
** File description:
** storage_next.c
*/

#include "../include/my.h"

void good_print(ants_t *position, int end, int *list)
{
    int index = 0;
    int check = 0;

    for (; index < end && position[index].position == -1; index += 1);
    for (; index < end; index += 1) {
        if (position[index].position == list[0])
            break;
        if (check == 0)
            my_printf("P%d-%d", index + 1, position[index].position);
        else
            my_printf(" P%d-%d", index + 1, position[index].position);
        check += 1;
    }
    my_printf("\n");
}

char **clean_array(char **arr)
{
    for (int i = 0; arr[i]; i++) {
        if (arr[i][0] != '\0' && (arr[i][0] == '#' && arr[i][1] != '#')) {
            arr[i] = NULL;
            return (arr);
        }
    }
    return (arr);
}

cell_t *init_cell(int index, int x, int y, int distance)
{
    cell_t *ret = my_malloc(sizeof(cell_t));

    ret->index = index;
    ret->x = x;
    ret->y = y;
    ret->distance = distance;
    ret->visited = false;
    return (ret);
}

int fill_nodes(storage_t *ret, char **arr, int state)
{
    int index = my_getnbr(arr[0]);
    int x = my_getnbr(arr[1]);
    int y = my_getnbr(arr[2]);

    if (state == 2)
        ret->start = init_cell(index, x, y, 0);
    if (state == 3)
        ret->end = init_cell(index, x, y, 1000000);
    for (nodes_t *copy = ret->nodes; copy; copy = copy->next)
        if (copy->cellule.index == index)
            return (84);
    if (state == 2)
        add_node_back(&ret->nodes, (cell_t){index, y, x, 0, false});
    else
        add_node_back(&ret->nodes, (cell_t){index, y, x, 1000000, false});
    return (0);
}
