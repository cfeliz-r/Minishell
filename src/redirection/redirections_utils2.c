/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:14:42 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/13 12:01:00 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_delimiter(char **split_result, t_cmd *command, int *i, int *j)
{
	if (contains_quotes(split_result[*i]) == 1)
	{
		split_result[*i] = split_quotes(split_result[*i]);
		command->delimiters[(*j)++] = ft_strdup(split_result[*i]);
		command->expand_heredoc = 0;
	}
	else
	{
		command->delimiters[(*j)++] = ft_strdup(split_result[*i]);
		command->expand_heredoc = 1;
	}
	command->flag = 0;
}

int	handle_input_files(t_cmd *cmd)
{
	int	fd;

	if (cmd->heredoc_file != NULL && cmd->last_redir_flag == 1)
	{
		fd = open(cmd->heredoc_file, O_RDONLY);
		if (fd == -1)
			return (perror("BABUTERM"), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("BABUTERM"), -1);
		close(fd);
	}
	if (cmd->inredir != NULL && cmd->last_redir_flag == 2)
	{
		fd = open(cmd->inredir, O_RDONLY);
		if (fd == -1)
			return (perror("BABUTERM"), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("BABUTERM"), -1);
		close(fd);
	}
	return (0);
}

int	handle_output_files(t_cmd *cmd)
{
	int	fd2;
	int	i;

	i = -1;
	while (cmd->outredirs && cmd->outredirs[++i] != NULL)
	{
		if (cmd->appd_out)
			fd2 = open(cmd->outredirs[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd2 = open(cmd->outredirs[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd2 == -1)
			return (perror("BABUTERM"), -1);
		if (dup2(fd2, STDOUT_FILENO) == -1)
			return (perror("BABUTERM"), -1);
		close(fd2);
	}
	return (0);
}

int	is_around(char *str, int pos)
{
	if (!str || str[pos] == '\0')
		return (0);
	if (pos > 0 && (str[pos - 1] == '\'' || str[pos - 1] == '\"'))
		return (1);
	if (str[pos + 1] == '\'' || str[pos + 1] == '\"')
		return (1);
	return (0);
}
