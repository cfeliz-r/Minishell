/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/03 15:56:49 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_redirections(t_command *command)
{
	int fd;
	int fd2;
	int i;

	i = -1;
	if(command->heredoc_file != NULL)
	{
		fd = open(command->heredoc_file, O_RDONLY);
		if (fd == -1)
			return(perror("BABUTERM"), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("BABUTERM"), -1);
		close(fd);
	}
	if (command->inredir != NULL && contains_quotes(command->inredir) == 0)
	{
		fd = open(command->inredir, O_RDONLY);
		if (fd == -1)
			return(perror("BABUTERM"), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("BABUTERM"), -1);
		close(fd);
	}
	while (command->outredirs && command->outredirs[++i] != NULL)
	{
		if (command->appd_out)
			fd2 = open(command->outredirs[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd2 = open(command->outredirs[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
		if (fd2 == -1)
			return(perror("BABUTERM"), -1);
		
		if (dup2(fd2, STDOUT_FILENO) == -1)
			return(perror("BABUTERM"), -1);
		close(fd2);
	}
	return (0);
}
int count_valid_redirections(char **split_result)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (split_result[i] != NULL)
	{
		if (ft_strcmp(split_result[i], ">") != 0)
			count++;
		i++;
	}
	return count;
}

void allocate_and_fill_outredirs(char **split_result, t_command *command, int count)
{
	int i;
	int out_index;
	int flag;
	
	i = -1;
	out_index = 0;
	flag = 1;
	command->outredirs = malloc(sizeof(char *) * (count + 1));
	while (split_result[++i] != NULL)
	{
		if (search_string_outside_quotes(split_result[i], ">") == 1)
			flag = 1;
		else if (flag == 1)
		{
			if (contains_quotes(split_result[i]))
				split_result[i] = split_quotes(split_result[i]);
			command->outredirs[out_index++] = ft_strdup(split_result[i]);
			flag = 0;
		}
		else
		{
			command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, " ");
			command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, split_result[i]);
		}
			
	}
	command->outredirs[out_index] = NULL;
}
void process_more_info(char **split_result, t_command *command, int *i)
{
	if (split_result[*i][0] == '<')
	{
		(*i)++;
		if(command->inredir)
			free(command->inredir);
		command->inredir = ft_strdup(split_result[*i]);
		return;
	}
	command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, " ");
	command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, split_result[*i]);
}