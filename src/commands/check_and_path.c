/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:27:25 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/23 17:16:42 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_paths(char *dir, char *cmd)
{
	char	*full_path;
	char	*result;

	full_path = ft_strjoin(dir, "/");
	result = ft_strjoin(full_path, cmd);
	free(full_path);
	return (result);
}

char	**get_paths(t_list_env *envp)
{
	t_list_env	*aux;
	char		**paths;

	aux = envp;
	while (aux && ft_strnstr(aux->envp_content, "PATH=", 5) == 0)
		aux = aux->next;
	if (!aux)
		return (NULL);
	paths = ft_split(aux->envp_content + 5, ':');
	return (paths);
}

char	*search_paths(char **paths, char *cmd)
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

char	*clean_command(char *cmd)
{
	char	*clean_cmd;

	clean_cmd = ft_strdup(cmd);
	if (clean_cmd[0] == '"' && clean_cmd[strlen(clean_cmd) - 1] == '"')
	{
		clean_cmd[strlen(clean_cmd) - 1] = '\0';
		memmove(clean_cmd, clean_cmd + 1, strlen(clean_cmd));
	}
	else if (clean_cmd[0] == '\'' && clean_cmd[strlen(clean_cmd) - 1] == '\'')
	{
		clean_cmd[strlen(clean_cmd) - 1] = '\0';
		ft_memmove(clean_cmd, clean_cmd + 1, ft_strlen(clean_cmd));
	}
	return (clean_cmd);
}

char	*find_command_path(char *cmd, t_list_env *envp)
{
	char	*clean_cmd;
	char	*res;

	if (cmd == NULL)
		return (NULL);
	clean_cmd = clean_command(cmd);
	if (is_builtin_command(clean_cmd))
		return (clean_cmd);
	if (is_command_path_valid(clean_cmd))
		return (clean_cmd);
	res = handle_command_path(clean_cmd, envp);
	free(clean_cmd);
	return (res);
}
