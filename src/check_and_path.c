/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:27:25 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/29 18:42:44 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_paths(char *dir, char *cmd)
{
	char	*full_path;
	char	*result;

	full_path = ft_strjoin(dir, "/");
	result = ft_strjoin(full_path, cmd);
	clean_up(NULL, full_path);
	return (result);
}

static char **get_paths(t_list_env *envp)
{
    t_list_env *aux;
	 char	**paths;

    aux = envp;
    while (aux && ft_strnstr(aux->envp_content, "PATH=", 5) == 0)
        aux = aux->next;
    if (!aux)
        return (NULL);

    paths = ft_split(aux->envp_content + 5, ':');
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
			clean_up(paths, NULL);
			return (res);
		}
		clean_up(NULL ,res);
		i++;
	}
    clean_up(paths, NULL);
	return (cmd);
}

char *find_command_path(char *cmd, t_list_env *envp)
{
    char **paths;
    char *res;
    if (cmd[0] == '/')
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return (ft_strdup(cmd));
        else
            return (NULL);
    }
    
    paths = get_paths(envp);
    if (paths == NULL)
        return (NULL);

    res = search_paths(paths, cmd);
    return (res);
}