/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.your42network.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 00:54:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/28 00:54:56 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_env_value(t_list_env *envp_list, const char *key)
{
	while (envp_list != NULL)
	{
		if (ft_strncmp(envp_list->data, key, ft_strlen(key)) == 0
			&& envp_list->data[ft_strlen(key)] == '=')
			return (envp_list->data + ft_strlen(key) + 1);
		envp_list = envp_list->next;
	}
	return (NULL);
}
