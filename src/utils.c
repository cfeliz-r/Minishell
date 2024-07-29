/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/26 16:12:32 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void free_env_list(t_list_env *env_list)
{
    t_list_env *temp;

    while (env_list != NULL)
    {
        temp = env_list;
        env_list = env_list->next;
        free(temp->envp_content);
		free(temp);
    }
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