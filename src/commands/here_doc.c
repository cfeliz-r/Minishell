/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/09 11:20:29 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_here_doc(char *delimiter, int fd[2])
{
    char *line;

    close(fd[0]);
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
            && line[ft_strlen(delimiter)] == '\n')
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd[1]);
        free(line);
    }
    close(fd[1]); // Cerramos el extremo de escritura de la tubería
}
