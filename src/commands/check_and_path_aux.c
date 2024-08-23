/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_path_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:49:01 by manufern          #+#    #+#             */
/*   Updated: 2024/08/23 16:50:23 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_command_path_valid(char *clean_cmd)
{
	if (clean_cmd[0] == '/' || ft_strncmp(clean_cmd, "./", 2) == 0)
	{
		if (access(clean_cmd, F_OK | X_OK) == 0)
			return (1);
		else
		{
			free(clean_cmd);
			return (0);
		}
	}
	return (0);
}

char	*handle_command_path(char *clean_cmd, t_list_env *envp)
{
	char	**paths;

	paths = get_paths(envp);
	if (paths == NULL)
		return (NULL);
	return (search_paths(paths, clean_cmd));
}
