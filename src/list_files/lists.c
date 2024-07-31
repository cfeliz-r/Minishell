/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:04 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/31 15:15:21 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list_env *create_list_envp(char **envp)
{
	t_list_env *envp_list;
	char *content;
	int i;

	i = 0;
	envp_list = NULL;
	content = NULL;
	while (envp[i] != NULL)
	{
		content = ft_strdup(envp[i]);
		ft_lstadd_back(&envp_list, ft_lstnew(content));
		i++;
	}

	return envp_list;
}

void free_env_list(t_list_env *env_list)
{
	t_list_env *temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->envp_content);
		free(temp);
	}
}
