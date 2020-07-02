/*
** EPITECH PROJECT, 2019
** CPE_lemin_2019
** File description:
** error_handling.c
*/

#include "../include/my.h"

int is_num(char c)
{
    return (c >= '0' && c <= '9');
}

int challenge_me(char **arr)
{
    int index = 0;
    int nb_moins = 0;
    int temp = 0;

    for (; arr[0][index] && is_num(arr[0][index]); index += 1);
    for (; arr[0][index] && arr[0][index] == '-'; index += 1)
        nb_moins += 1;
    for (; arr[0][index] && is_num(arr[0][index]); index += 1)
        temp += 1;
    if (index == 0)
        return (84);
    if (!arr[0][index] && nb_moins == 1 && temp > 0)
        return (0);
    return (84);
}

int error_handling(char **arr, int state)
{
    int tab_len = 0;

    if (arr && arr[0][0] == '#')
        return (0);
    for (; arr[tab_len]; tab_len += 1);
    if (tab_len != 1 && tab_len != 3)
        return (84);
    for (int i = 0; arr[0][i]; i++)
        state = (arr[0][i] == '-') ? 4 : state;
    if (state == 4)
        return (challenge_me(arr));
    for (int index = 0; arr[index]; index += 1) {
        if (!my_str_isnum(arr[index]))
            return (84);
    }
    return (0);
}