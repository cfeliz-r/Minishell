/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:06:48 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 13:35:32 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_list_export(t_list_env *list)
{
	t_list_env	*current;
	t_list_env	*next;

	current = list;
	while (current != NULL)
	{
		next = current->next;
		free(current->envp_content);
		free(current);
		current = next;
	}
}

t_list_env	*create_node_export(const char *content)
{
	t_list_env	*new_node;

	new_node = malloc(sizeof(t_list_env));
	if (!new_node)
		return (NULL);
	new_node->envp_content = ft_strdup(content);
	if (!new_node->envp_content)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_list_env	*copy_list_export(t_list_env *original)
{
	t_list_env	*current_original;
	t_list_env	*current_new;
	t_list_env	*new_list;

	if (!original)
		return (NULL);
	new_list = create_node_export(original->envp_content);
	if (!new_list)
		return (NULL);
	current_original = original->next;
	current_new = new_list;
	while (current_original)
	{
		current_new->next = create_node_export(current_original->envp_content);
		if (!current_new->next)
		{
			free_list_export(new_list);
			return (NULL);
		}
		current_new = current_new->next;
		current_original = current_original->next;
	}
	return (new_list);
}

t_list_env	*sort_list_export(t_list_env *head, int swapped)
{
	t_list_env	*curr;
	t_list_env	*new_last_ptr;
	char		*temp;

	new_last_ptr = NULL;
	while (1)
	{
		swapped = 0;
		curr = head;
		while (curr->next != new_last_ptr)
		{
			if (ft_strcmp(curr->envp_content, curr->next->envp_content) > 0)
			{
				temp = curr->envp_content;
				curr->envp_content = curr->next->envp_content;
				curr->next->envp_content = temp;
				swapped = 1;
			}
			curr = curr->next;
		}
		if (!swapped)
			break ;
		new_last_ptr = curr;
	}
	return (head);
}

void	print_list_export(t_list_env *list)
{
	while (list)
	{
		printf("declare -x %s\n", list->envp_content);
		list = list->next;
	}
}
