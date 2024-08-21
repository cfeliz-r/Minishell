/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:45:06 by manufern          #+#    #+#             */
/*   Updated: 2024/08/21 10:01:33 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_up(char **args, t_command *commands, int num_cmds)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i] != NULL)
			free(args[i ++]);
		free(args);
	}
	i = 0;
	if (commands)
	{
		while (i < num_cmds)
		{
			free(commands[i].args);
			free(commands[i].path);
			free(commands[i].inredir);
			free(commands[i].outredirs);
			free(commands[i].cmd_cpt);
			i++;
		}
		free(commands);
	}
}

int	count_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			j ++;
		i ++;
	}
	return (j);
}

void	close_pipes(int **pipes, int num_cmds)
{
	int	i;

	i = -1;
	while (++i < num_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
}

void	free_command_args(t_command *command)
{
	int	i;

	if (command->args)
	{
		i = -1;
		while (command->args[++i])
			free(command->args[i]);
		free(command->args);
	}
}

void	free_command(t_command *command)
{
	int	i;

	free_command_args(command);
	if (command->path)
		free(command->path);
	if (command->inredir)
		free(command->inredir);
	if (command->outredirs)
		{
			i = -1;
			while (command->outredirs[++i])
				free(command->outredirs[i]);
			free(command->outredirs);
		}
	if (command->cmd_cpt)
		free(command->cmd_cpt);
	i = 0;
	if (command->delimiters)
	{
		while (command->delimiters[i])
			free(command->delimiters[i++]);
		free(command->delimiters);
	}
	ft_memset(command, 0, sizeof(t_command));
}
