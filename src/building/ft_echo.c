/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:06 by manufern          #+#    #+#             */
/*   Updated: 2024/08/05 18:27:05 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void clean_up_echo(char **arr)
{
    int i = 0;
    if (arr) {
        while (arr[i])
        {
            free(arr[i++]);
        }
        free(arr);
    }
}

static int is_n_option(const char *arg)
{
    int i = 1;

    if (arg[0] == '-' && strlen(arg) > 1)
    {
        while (arg[i] != '\0')
        {
            if (arg[i] != 'n')
            {
                return 0;
            }
            i++;
        }
        return 1;
    }
    return 0;
}

static void print_echo_parts(char **str, int start_index)
{
    int first = 1;
    int i = start_index;

    while (str[i])
    {
        if (!first)
        {
            write(STDOUT_FILENO, " ", 1);
        }
        ft_putstr_fd(str[i], STDOUT_FILENO);
        first = 0;
        i++;
    }
}

int ft_echo(const char *comand)
{
    char **str;
    int i;
    int n_option;

    i = 0;
    n_option = 0;
    str = ft_split(comand + 5, ' ');
    if (!str || ft_strchr(comand, '|') || ft_strchr(comand, '>') || ft_strchr(comand, '<'))
    {
        if(str)
            clean_up_echo(str);
        return -1;
    }
    if (str[0] && is_n_option(str[0]))
    {
        n_option = 1;
        i = 1;
    }
    if (str)
    {
        print_echo_parts(str, i);
    }
    if (!n_option)
        write(STDOUT_FILENO, "\n", 1);
    clean_up_echo(str);
    manage_error(0, 0);
    return (1);
}
