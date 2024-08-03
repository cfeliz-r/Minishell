/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/03 17:17:57 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
void handle_redirections(t_command *command)
{
    int fd;
    
    if (command->input_redirection)
    {

        fd = open(command->input_redirection, O_RDONLY);
        if (fd == -1)
           perror("open input_redirection");
        
        if (dup2(fd, STDIN_FILENO) == -1)
            perror("dup2 input_redirection");
        close(fd);
    }
    if (command->output_redirection)
    {
        int fd2;
        if (command->append_output)
            fd2 = open(command->output_redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd2 = open(command->output_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd2 == -1)
            perror("open output_redirection");
        if (dup2(fd2, STDOUT_FILENO) == -1)
            perror("dup2 output_redirection");
        close(fd2);
    }
}
