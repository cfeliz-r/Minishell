/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/17 15:05:01 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_here_doc(t_command *command)
{
	int		pipefd[2];
	char	*line;
	char	*temp;
	int		i = 0;

	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe error");
		return (-1);
	}

	while (command->heredoc_delimiters[i])
	{
		line = readline("pipe heredoc> ");
		if (line == NULL)
			break ;

		if (ft_strcmp(line, command->heredoc_delimiters[i]) == 0)
		{
			free(line);
			i++;
			if (command->heredoc_delimiters[i] == NULL)
				break ;  // Terminar el bucle si se han ingresado todos los delimitadores
			continue ; // Pedir el siguiente delimitador sin escribir la línea al pipe
		}

		temp = ft_strjoin(line, "\n");
		if (!temp)
		{
			perror("minishell: memory allocation error");
			free(line);
			break ;
		}

		if (write(pipefd[1], temp, strlen(temp)) == -1)
		{
			perror("minishell: write error");
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
