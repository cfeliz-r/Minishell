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
		if (ft_strncmp(envp_list->envp_content, key, ft_strlen(key)) == 0
			&& envp_list->envp_content[ft_strlen(key)] == '=')
			return (envp_list->envp_content + ft_strlen(key) + 1);
		envp_list = envp_list->next;
	}
	return (manage_error(200, 0), NULL);
}

char	*remove_front_and_back_spaces(char *str)
{
	int	start;
	int	end;
	int	length;

	start = 0;
	if (str != NULL)
	{
		while (str[start] && str[start] == ' ')
			start++;
		if (str[start] == '\0')
		{
			str[start] = '\0';
			return (str);
		}
		length = ft_strlen(str);
		end = length - 1;
		while (end > start && str[end] == ' ')
			end--;
		length = end - start + 1;
		ft_memmove(str, str + start, length);
		str[length] = '\0';
		return (str);
	}
	return (manage_error(200, 0), NULL);
}
