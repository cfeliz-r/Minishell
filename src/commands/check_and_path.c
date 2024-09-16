/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:27:25 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/16 14:21:44 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*join_paths(char *dir, char *cmd)
{
	char	*full_path;
	char	*result;

	full_path = ft_strjoin(dir, "/");
	result = ft_strjoin(full_path, cmd);
	free(full_path);
	return (result);
}

static char	**get_paths(t_list_env *envp)
{
	t_list_env	*aux;
	char		**paths;

	aux = envp;
	while (aux && ft_strnstr(aux->data, "PATH=", 5) == 0)
		aux = aux->next;
	if (!aux)
		return (NULL);
	paths = ft_split(aux->data + 5, ':');
	return (paths);
}

static char	*search_paths(char **paths, char *cmd)
{
	char	*res;
	int		i;

	i = 0;
	while (paths[i])
	{
		res = join_paths(paths[i], cmd);
		if (access(res, F_OK | X_OK) == 0)
		{
			clean_up(paths, NULL, 0);
			return (res);
		}
		free(res);
		i++;
	}
	clean_up(paths, NULL, 0);
	return (NULL);
}

static int	is_command_path_valid(char *cmd)
{
	if (ft_strcmp(cmd, "./") == 0 || ft_strcmp(cmd, "../") == 0
		|| ft_strcmp(cmd, "/") == 0)
	{
		if (access(cmd, F_OK) == 0)
		{
			ft_putstr(cmd);
			ft_putstr_fd("Is directory\n", 2);
			exit(126);
		}
	}
	else if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			return (1);
	}
	return (0);
}

char	*find_command_path(char *cmd, t_list_env *envp)
{
	char	**paths;

	if (cmd == NULL)
		return (NULL);
	if (is_command_path_valid(cmd) == 1)
		return (cmd);
	paths = get_paths(envp);
	if (paths == NULL)
		return (NULL);
	return (search_paths(paths, cmd));
}
