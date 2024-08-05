/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/05 12:20:02 by cfeliz-r         ###   ########.fr       */
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
char *ft_redir_cmd(char *input, t_list_env *envp)
{
    char **aux;
    char *swap;
    char *result;
    char *command_path;
    int i;
    
    char *opt_cmd = ft_strdup(input);
    if (!opt_cmd)
        return (NULL);
    
    if (ft_strncmp(opt_cmd, "<", 1) == 0)
    {
        aux = ft_split(opt_cmd, ' ');
        command_path = find_command_path(aux[2], envp);
        
        if (access(command_path, X_OK) == -1)
        {
            printf("minishell: %s: No such file or directory\n", aux[2]);
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(aux[1], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            free(opt_cmd);
            free(command_path);
            return (NULL);
        }
        
        swap = ft_strdup(aux[1]);
        result = ft_strdup(aux[2]);
        result = ft_strjoin(result, " < ");
        result = ft_strjoin(result, swap);
        free(swap);   
        i = 3;
        while (aux[i])
        {
            result = ft_strjoin(result, " ");
            result = ft_strjoin(result, aux[i]);
            i++;
        }       
        free(opt_cmd);
    }
    else
        result = ft_strdup(opt_cmd);
    return (result);
}
