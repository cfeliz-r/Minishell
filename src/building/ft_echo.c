/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:24:04 by manufern          #+#    #+#             */
/*   Updated: 2024/08/07 18:25:51 by manufern         ###   ########.fr       */
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
int	is_n_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			++i;
		if (str[i] == '\0' && i != 1)
			return (1);
	}
	return (0);
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
    while(str[i] && is_n_option(str[i]))
    {
        n_option = 1;
        i ++;
    }
    if (str)
        print_echo_parts(str, i);
    if (!n_option)
        write(STDOUT_FILENO, "\n", 1);
    clean_up_echo(str);
    manage_error(0, 0);
    return (1);
}
