/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/16 21:00:38 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int process_here_doc(char *delimiter)
{
    int pipefd[2];
    char *line;
    char *temp;

    if (pipe(pipefd) == -1)
    {
        perror("minishell: pipe error");
        return -1;
    }
    while (1)
    {
        line = readline(">");
        if (line == NULL)
        {
            break;
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        temp = ft_strjoin(line, "\n");
        write(pipefd[1], temp, ft_strlen(temp));
        free(temp);
        free(line);
    }
    close(pipefd[1]);
    return pipefd[0];
}

void handle_heredoc(t_command *commands, int i)
{
    int heredoc_fd;
    int j = 0;
    if (commands[i].heredoc_delimiters != NULL)
    {
        while (commands[i].heredoc_delimiters[j])
        {
            heredoc_fd = process_here_doc(commands[i].heredoc_delimiters[j]);
            if (heredoc_fd == -1)
            {
                manage_error(200, 0);
                return;
            }
            dup2(heredoc_fd, STDIN_FILENO);
            close(heredoc_fd);
            j++;
        }
    }
}
