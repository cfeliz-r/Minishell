/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/16 20:57:00 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

struct sigaction old_sigint;
struct sigaction old_sigquit;
void disable_signals(void)
{
    struct sigaction sa;
    struct sigaction old_sigint;
struct sigaction old_sigquit;

    sa.sa_handler = SIG_IGN; // Ignorar SIGINT y SIGQUIT
    sigaction(SIGINT, &sa, &old_sigint);
    sigaction(SIGQUIT, &sa, &old_sigquit);
}

void restore_signals(void)
{
    struct sigaction old_sigint;
    struct sigaction old_sigquit;

    sigaction(SIGINT, &old_sigint, NULL);
    sigaction(SIGQUIT, &old_sigquit, NULL);
}

void enable_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler; // Reestablecer el handler para SIGINT
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &old_sigquit, NULL); // Restaurar SIGQUIT
}

int process_here_doc(char *delimiter)
{
    int pipefd[2];
    char *line;
    char *temp;
    struct sigaction sa_int;

    if (pipe(pipefd) == -1)
    {
        perror("minishell: pipe error");
        return -1;
    }
    sa_int.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa_int, NULL);
    sigaction(SIGQUIT, &sa_int, NULL);
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
    sa_int.sa_handler = sigint_handler_2;
    sigaction(SIGINT, &sa_int, NULL);
    sa_int.sa_handler = sigquit_handler;
    sigaction(SIGQUIT, &sa_int, NULL);
    return pipefd[0];
}

void handle_heredoc(t_command *commands, int i)
{
    int heredoc_fd;
    int j = 0;
    disable_signals();
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
     enable_signals();
}
