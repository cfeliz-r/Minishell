/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:04 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/11 13:30:43 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list_env	*create_list_envp(char **envp)
{
	t_list_env	*envp_list;
	char		*content;
	int			i;

	i = 0;
	envp_list = NULL;
	content = NULL;
	while (envp[i] != NULL)
	{
		content = ft_strdup(envp[i]);
		ft_lstadd_back(&envp_list, ft_lstnew(content));
		i++;
	}
	return (envp_list);
}
