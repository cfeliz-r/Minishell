/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/12 19:01:22 by manufern         ###   ########.fr       */
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
				free(commands[i].input_redirection);
				free(commands[i].output_redirection);
				free(commands[i].cmd_complete);
				free(commands[i].heredoc_delimiter);
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
		if (command->input_redirection)
			free(command->input_redirection);
		if (command->output_redirection)
			free(command->output_redirection);
		if (command->cmd_complete)
			free(command->cmd_complete);
		if(command->heredoc_delimiter)
			free(command->heredoc_delimiter);
		ft_memset(command, 0, sizeof(t_command));
		
	}
 