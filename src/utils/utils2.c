/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:45:06 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:25:17 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_up(char **args, t_cmd *commands, int num_cmds)
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
	if (commands != NULL)
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
	free(pipes);
}

void	free_command_args(t_cmd *command)
{
	int	i;

	if (command->args != NULL)
	{
		i = -1;
		while (command->args[++i] != NULL)
			free(command->args[i]);
		free(command->args);
	}
}

void	free_command(t_cmd *command)
{
	int	i;

	free_command_args(command);
	if (command->path != NULL)
		free(command->path);
	if (command->inredir != NULL)
		free(command->inredir);
	if (command->heredoc_file != NULL)
		free(command->heredoc_file);
	if (command->outredirs != NULL)
	{
		i = -1;
		while (command->outredirs[++i] != NULL)
			free(command->outredirs[i]);
		free(command->outredirs);
	}
	if (command->cmd_cpt != NULL)
		free(command->cmd_cpt);
	i = 0;
	clean_up(command->delimiters, NULL, 0);
	ft_memset(command, 0, sizeof(t_cmd));
}

void	free_list_env(t_list_env *list)
{
	t_list_env	*tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp->data);
		free(tmp);
	}
}
