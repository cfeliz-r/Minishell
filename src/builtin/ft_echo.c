/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:47:30 by manufern          #+#    #+#             */
/*   Updated: 2024/08/20 12:47:56 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



static void	clean_up_echo(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
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
			i++;
		if (str[i] == '\0' && i != 1)
			return (1);
	}
	return (0);
}

static void	print_echo_parts(char **str, int start_index)
{
	int	first;
	int	i;

	first = 1;
	i = start_index;
	while (str[i] != NULL)
	{
		if (ft_strcmp(str[i], ">") == 0)
			break ;
		else if (ft_strcmp(str[i], "<") == 0)
		{
			if (str[i + 1] && access(str[i + 1], F_OK) == -1)
			{
				printf("%s: No such file or directory\n", str[i + 1]);
				break ;
			}
			else
			{
				i += 2;
				continue ;
			}
		}
		if (!first)
			write(STDOUT_FILENO, " ", 1);
		ft_putstr_fd(str[i], STDOUT_FILENO);
		first = 0;
		i++;
	}
}

void	ft_echo(char *comand)
{
	char	**str;
	int		i;
	int		n_option;

	i = 0;
	n_option = 0;
	str = ft_split(comand + 5, ' ');
	if (!str)
		return ((void)manage_error(200, 0));
	while (str[i] && is_n_option(str[i]))
	{
		n_option = 1;
		i++;
	}
	if (str)
		print_echo_parts(str, i);
	if (!n_option)
		write(STDOUT_FILENO, "\n", 1);
	clean_up_echo(str);
	manage_error(0, 0);
	return ;
}

