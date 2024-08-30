/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/29 16:01:03 by cfeliz-r         ###   ########.fr       */
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
