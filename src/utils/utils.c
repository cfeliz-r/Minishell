/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/31 15:12:18 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_up(char **args, char *path)
{
	int	i;

	i = 0;
	if (path)
		free(path);
	if (args)
	{
		while (args[i])
		{	
			free(args[i]);
			i++;
		}
		free(args);
	}
}

int count_char(char *str, char c)
{
	int i;
	int j;
	
	i  = 0;
	j  = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			j ++;
		i ++;
	}
	return (j);
}



void close_pipes(t_command *commands, int num_cmds)
{
	int		i;

	i = 0;
	while (i < num_cmds - 1) 
	{
		close(commands[i].pipefd[0]);
		close(commands[i].pipefd[1]);
	i++;
	}
}