/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/17 17:19:48 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t aux_count(char **array)
{
    size_t count;

	count = 0;
    if (!array)
        return 0;
    while (*array)
    {
        count++;
        array++;
    }
    return count;
}

int all_digits(const char *str)
{
    const char *ptr;

	ptr = str;
    if (!ptr || *ptr == '\0')
        return 0;
    while (*ptr)
    {
        if (!ft_isdigit((unsigned char)*ptr))
            return 0;
        ptr++;
    }
    return 1;
}

	void clean_up_aux(t_command **commands)
	{
		int i;
		int j;

		i = 0;
		j = 0;
		while (commands[j] != NULL)
		{
			while (commands[j]->args[i] != NULL)
				free(commands[j]->args[i++]);
			free(commands[j]->args);
			free(commands[j]->path);
			j++;
			i = 0;
		}
	}

	void clean_up(char **args, t_command *commands, int num_cmds)
	{
		int i;

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
			while( i < num_cmds) 
			{
				free(commands[i].args);
				free(commands[i].path);
				free(commands[i].inredir);
				free(commands[i].outredir);
				free(commands[i].cmd_cpt);
				i++;
			}
			free(commands);
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

	void close_pipes(int **pipes, int num_cmds)
	{
    	int i;

    	i = -1;
    	while( ++i < num_cmds - 1)
    	{
        	close(pipes[i][0]);
        	close(pipes[i][1]);
        	free(pipes[i]);
    	}
	}

	void free_command(t_command *command)
	{
		int i;

		if (command->args)
		{
			i = -1;
			while (command->args[++i])
				free(command->args[i]);
			free(command->args);
		}
		i = 0;
		if (command->path)
			free(command->path);
		if (command->inredir)
			free(command->inredir);
		if (command->outredir)
			free(command->outredir);
		if (command->cmd_cpt)
			free(command->cmd_cpt);
		if (command->delimiters)
		{
			while (command->delimiters[i])
				free(command->delimiters[i++]);
			free(command->delimiters);
		}
		ft_memset(command, 0, sizeof(t_command));
		
	}
 