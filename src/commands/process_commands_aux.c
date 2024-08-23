/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands_aux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:42:14 by manufern          #+#    #+#             */
/*   Updated: 2024/08/23 17:43:34 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin_command(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0)
	{
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_args(char **args)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (args[i])
	{
		new_arg = remove_quotes(args[i]);
		if (new_arg)
		{
			free(args[i]);
			args[i] = new_arg;
		}
		i++;
	}
}

void	setup_pipes(int **pipes, int num_cmds)
{
	int	i;

	i = -1;
	while (++i < num_cmds - 1)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (pipes[i] == NULL || pipe(pipes[i]) == -1)
		{
			perror("Error pipe");
			return ;
		}
	}
}
