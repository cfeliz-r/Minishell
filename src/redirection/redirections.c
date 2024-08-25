/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:08 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_redirections(t_command *command)
{
	int fd;
	int fd2;
	int i = 0;

	if (command->inredir != NULL && contains_quotes(command->inredir) == 0)
	{
		fd = open(command->inredir, O_RDONLY);
		if (fd == -1)
			return(perror(""), -1);
		
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror(""), -1);
		close(fd);
	}

	while (command->outredirs && command->outredirs[i] != NULL)
	{
		if (command->appd_out)
			fd2 = open(command->outredirs[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd2 = open(command->outredirs[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
		if (fd2 == -1)
			return(perror(""), -1);
		
		if (dup2(fd2, STDOUT_FILENO) == -1)
			return(perror(""), -1);
		
		close(fd2);
		i++;
	}
	return (0);
}

static int validate_command_cmd(char *command, t_list_env *envp)
{
	char *command_path;

	command_path = find_command_path(command, envp);
	if (!command_path || access(command_path, X_OK | F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (command_path)
			free(command_path);
		return (-1);
	}
	free(command_path);
	return 0;
}

char *process_redirection(char **aux, t_list_env *envp)
{
	char *swap;
	char *result;
	int i;
	char *temp;

	if (validate_command_cmd(aux[2], envp) == -1)
	{
		clean_up(aux, NULL, 0);
		return NULL;
	}
	swap = ft_strdup(aux[1]);
	result = ft_strdup(aux[2]);
	if(aux[3])
	{
		i = 3;
		while (aux[i] && aux[i][0] != '<' && aux[i][0] != '>' && aux[i][0] != '|')
		{
			temp = ft_strjoin(result, " ");
			free(result);
			result = temp;
			temp = ft_strjoin(result, aux[i]);
			free(result);
			result = temp;
			i++;
		}
	}
	temp = ft_strjoin(result, " < ");
	free(result);
	result = temp;
	temp = ft_strjoin(result, swap);
	free(result);
	free(swap);
	result = temp;
	i = 2;
	while (aux[++i])
	{
		temp = ft_strjoin(result, " ");
		free(result);
		result = temp;
		temp = ft_strjoin(result, aux[i]);
		free(result);
		result = temp;
	}
	clean_up(aux, NULL, 0);
	return (result);
}

char *ft_redir_cmd(char *input, t_list_env *envp)
{
	char **aux;
	char *result;
	int i;

	if (!input)
		return (NULL);
	if (ft_strncmp(input, "<", 1) == 0 && ft_strncmp(input, "<<", 2) != 0)
	{
		aux = ft_split(input, ' ');
		i = 0;
		while(aux[i])
			i++;
		if (i < 3)
		{
			clean_up(aux, NULL, 0);
			return (NULL);
		}
		result = process_redirection(aux, envp);
	}
	else
		result = ft_strdup(input);
	return (result);
}
