/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/31 14:48:35 by cfeliz-r         ###   ########.fr       */
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


char *remove_front_and_back_spaces(char *str)
{
	int start;
	int end;
	int length;
	
	start = 0;
	while (str[start] && str[start] == ' ')
		start++;
	if (str[start] == '\0')
	{
		str[0] = '\0';
		return str;
	}
	length = strlen(str);
	end = length - 1;
	while (end > start && str[end] == ' ')
		end--;
	length = end - start + 1;
	ft_memmove(str, str + start, length);
	str[length] = '\0';
	return str;
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