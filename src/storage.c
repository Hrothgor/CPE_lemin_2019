/*
** EPITECH PROJECT, 2019
** CPE_lemin_2019
** File description:
** storage.c
*/

#include "../include/my.h"

int fill_links(storage_t *ret, char *str)
{
    static int init = 0;
    char **arr = my_str_to_word_array(str, "-");

    if (!init++) {
        ret->links = my_malloc(sizeof(int *) * ret->nb_nodes);
        for (int i = 0; i < ret->nb_nodes; i++) {
            ret->links[i] = my_malloc(sizeof(int) * ret->nb_nodes);
            for (int j = 0; j < ret->nb_nodes; j++)
                ret->links[i][j] = 0;
        }
    }
    if (my_getnbr(arr[0]) >= ret->nb_nodes || \
    my_getnbr(arr[1]) >= ret->nb_nodes)
        return (84);
    ret->links[my_getnbr(arr[0])][my_getnbr(arr[1])] = 1;
    ret->links[my_getnbr(arr[1])][my_getnbr(arr[0])] = 1;
    return (0);
}

void change_state(char **arr, int *state)
{
    if (!my_strcmp(arr[0], "##end")) {
        *state = 3;
        return;
    }
    if (!my_strcmp(arr[0], "##start")) {
        *state = 2;
        return;
    }
    for (int i = 0; arr[0][i]; i++) {
        if (arr[0][i] == '-') {
            *state = 4;
            return;
        }
    }
    return;
}

int create_storage_bis(storage_t *ret, char **arr, char *buffer, int state)
{
    static int i = 0;
    static int j = 0;

    if (state == 0) {
        my_printf("#number_of_ants\n");
        ret->nb_ants = my_getnbr(arr[0]);
        state = 1;
        return (state);
    }
    (i++ == 0) ? my_printf("#rooms\n") : 0;
    change_state(arr, &state);
    if ((state == 1 || state == 2 || state == 3) && arr[0][0] != '#') {
        if (!arr[0] || !arr[1] || !arr[2] || fill_nodes(ret, arr, state) == 84)
            return (84);
        ret->nb_nodes += 1;
        state = 1;
    }
    if (state == 4)
        (j++ == 0) ? my_printf("#tunnels\n") : 0;
    return ((state == 4 && fill_links(ret, buffer) == 84) ? 84 : state);
}

void print_array(char **arr)
{
    for (int i = 0; arr[i]; i++) {
        my_printf("%s", arr[i]);
        if (arr[i + 1] != NULL)
            my_printf(" ");
    }
    my_printf("\n");
}

storage_t *create_storage(char *buffer, char **arr, size_t sizet)
{
    storage_t *ret = my_malloc(sizeof(storage_t));
    int state = 0;

    ret->nb_nodes = 0;
    ret->nodes = NULL;
    ret->end = NULL;
    ret->start = NULL;
    ret->links = NULL;
    while (getline(&buffer, &sizet, stdin) != -1) {
        arr = clean_array(my_str_to_word_array(buffer, "\n \t"));
        if (!arr || !arr[0])
            continue;
        if (error_handling(arr, state) == 84)
            return (NULL);
        state = create_storage_bis(ret, arr, buffer, state);
        if (state == 84)
            return (NULL);
        print_array(arr);
    }
    free(buffer);
    return (ret);
}