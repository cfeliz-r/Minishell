/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/31 12:10:20 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_redirections(t_command *command)
{
	int fd;
	int fd2;
	int i = 0;

	if (command->heredoc_file != NULL)
	{
		fd = open(command->heredoc_file, O_RDONLY);
		if (fd == -1)
			return(perror(""), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror(""), -1);
		close(fd);
	}
	if (command->inredir != NULL && contains_quotes(command->inredir) == 0)
	{
		fd = open(command->inredir, O_RDONLY);
		if (fd == -1)
			return(perror(""), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror(""), -1);
		close(fd);
	}
	while (command->outredirs && command->outredirs[i] != NULL)
	{
		if (command->appd_out)
			fd2 = open(command->outredirs[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd2 = open(command->outredirs[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
		if (fd2 == -1)
			return(perror(""), -1);
		
		if (dup2(fd2, STDOUT_FILENO) == -1)
			return(perror(""), -1);
		close(fd2);
		i++;
	}
	return (0);
}
int count_valid_redirections(char **split_result)
{
	int count = 0;
	int i = 0;

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
	int i = 0;
	int out_index = 0;

	if (count > 0)
	{
		command->outredirs = malloc(sizeof(char *) * (count + 1));
		if (!command->outredirs)
		{
			clean_up(split_result, NULL, 0);
			return;
		}
	}

	while (split_result[i] != NULL)
	{
		if (split_result[i] != NULL && split_result[i][0] != '>' && split_result[i][0] != '<')
		{
			command->outredirs[out_index] = strip_quotes(split_result[i]);
			out_index++;
		}
		i++;
	}

	if (command->outredirs)
		command->outredirs[out_index] = NULL;
}