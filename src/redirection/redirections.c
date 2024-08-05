/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/05 19:08:54 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_redirections(t_command *command)
{
	int fd;
	int fd2;
	
	if (command->input_redirection)
	{
		fd = open(command->input_redirection, O_RDONLY);
		if (fd == -1)
		perror("open input_redirection");
		
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 input_redirection");
		if(fd != -1)
			close(fd);
	}
	if (command->output_redirection)
	{
		if (command->append_output)
			fd2 = open(command->output_redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd2 = open(command->output_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd2 == -1)
			perror("open output_redirection");
		if (dup2(fd2, STDOUT_FILENO) == -1)
			perror("dup2 output_redirection");
		if(fd2 != -1)
			close(fd2);
	}
}

static int validate_command_cmd(char *command, t_list_env *envp, char *input_cmd)
{
    char *command_path;

	command_path = find_command_path(command, envp);
    if (!command_path || access(command_path, X_OK | F_OK) == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(input_cmd, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
		free(command_path);
        return (-1);
    }
    return 0;
}

char *process_redirection(char **aux, t_list_env *envp)
{
    char *swap;
    char *result;
    int i;

    if (validate_command_cmd(aux[2], envp, aux[1]) == -1)
	{
		clean_up(aux, NULL, 0);
		 return NULL;
	}
    swap = ft_strdup(aux[1]);
    result = ft_strdup(aux[2]);
    result = ft_strjoin(result, " < ");
    result = ft_strjoin(result, swap);
    free(swap);
    i = 2;
    while (aux[++i])
	{
        result = ft_strjoin(result, " ");
        result = ft_strjoin(result, aux[i]);
    }
	clean_up(aux, NULL, 0);
    return (result);
}

char *ft_redir_cmd(char *input, t_list_env *envp)
{
	char **aux;
	char *result;
	
	if (!input)
		return (NULL);
	if (ft_strncmp(input, "<", 1) == 0)
	{
		aux = ft_split(input, ' ');
		result = process_redirection(aux, envp);
		if (!result)
			free(aux);
	}
	else
		result = ft_strdup(input);
	return (result);
}