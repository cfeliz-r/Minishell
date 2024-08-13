/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/13 15:55:26 by cfeliz-r         ###   ########.fr       */
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
        line = readline(JUNGLE_GREEN "🦧BABU_HERE_DOC🦧➤ " RESET);
        if (line == NULL)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted '", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("')\n", 2);
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

void handle_heredoc(t_command *commands, int i, int num_cmds)
{
    int fd;
    int heredoc_fd;

    if (commands[i].heredoc_delimiter != NULL && i == num_cmds - 1)
    {
        heredoc_fd = process_here_doc(commands[i].heredoc_delimiter);
        free(commands[i].heredoc_delimiter);
        if (heredoc_fd == -1)
        {
            manage_error(200, 0);
            exit(1);
        }
        dup2(heredoc_fd, STDIN_FILENO);
        close(heredoc_fd);
    }
    else if (commands[i].input_redirection != NULL)
    {
        fd = open(commands[i].input_redirection, O_RDONLY);
        if (fd == -1)
        {
            manage_error(200, 0);
            perror("minishell: open error");
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}
 

