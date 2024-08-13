/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:32:34 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 18:36:56 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_list_export(t_list_env *list)
{
	t_list_env *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->envp_content);
		free(tmp);
	}
}

t_list_env *create_node_export(const char *content)
{
	t_list_env *new_node;

	new_node = malloc(sizeof(t_list_env));
	if (!new_node)
		return NULL;
	new_node->envp_content = ft_strdup(content);
	if (!new_node->envp_content)
	{
		free(new_node);
		return NULL;
	}
	new_node->next = NULL;
	return new_node;
}

void print_list_export(t_list_env *list)
{
	while (list)
	{
		printf("declare -x %s\n", list->envp_content);
		list = list->next;
	}
}