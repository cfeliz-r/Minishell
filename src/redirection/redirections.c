/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/05 15:10:15 by manufern         ###   ########.fr       */
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
		close(fd2);
	}
}

static int validate_command_cmd(char *command, t_list_env *envp, char *input_cmd)
{
    char *command_path = find_command_path(command, envp);
    if (!command_path)
        return (-1);
    if (access(command_path, X_OK | F_OK) == -1)
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
        return NULL;
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
    return result;
}

char *ft_redir_cmd(char *input, t_list_env *envp)
{
	char **aux;
	char *result;
	char *opt_cmd;
	
	opt_cmd = ft_strdup(input);
	if (!opt_cmd)
		return (NULL);
	if (ft_strncmp(opt_cmd, "<", 1) == 0)
	{
		aux = ft_split(opt_cmd, ' ');
		result = process_redirection(aux, envp);
		if (!result)
			free(aux);
	}
	else
		result = ft_strdup(opt_cmd);
	return (result);
}
