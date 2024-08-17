/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/17 17:21:15 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_here_doc(t_command *cmd)
{
	int		pipefd[2];
	char	*line;
	char	*temp;
	int		i = 0;

	if (pipe(pipefd) == -1)
		return (-1);
	while (cmd->delimiters[i])
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, cmd->delimiters[i]) == 0)
		{
			free(line);
			i++;
			if (cmd->delimiters[i] == cmd->delimiters[i - 1]
				|| cmd->inredir != NULL || cmd->outredir != NULL ||  cmd->appd_out != 0)
				break ;
			continue ; 
		}
		temp = ft_strjoin(line, "\n");
		if (!temp)
		{
			free(line);
			break ;
		}
		if (write(pipefd[1], temp, strlen(temp)) == -1)
		{
			free(temp);
			free(line);
			break ;
		}
		free(temp);
		free(line);
	}

	close(pipefd[1]);
	return (pipefd[0]);
}
