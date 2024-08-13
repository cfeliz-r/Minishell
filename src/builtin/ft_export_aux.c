/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:32:29 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 18:38:24 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list_env *copy_list_export(t_list_env *original)
{
	t_list_env *current_original;
	t_list_env *current_new;
	t_list_env *new_list;
	
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

t_list_env *sort_list_export(t_list_env *head, char *temp)
{
	int			swapped;
	t_list_env	*current;
	t_list_env	*new_last_ptr;
	 
	new_last_ptr = NULL;
	while (1)
	{
		swapped = 0;
		current = head;
		while (current->next != new_last_ptr)
		{
			if (strcmp(current->envp_content, current->next->envp_content) > 0)
			{
				temp = current->envp_content;
				current->envp_content = current->next->envp_content;
				current->next->envp_content = temp;
				swapped = 1;
			}
			current = current->next;
		}
		if (!swapped)
			break ;
		new_last_ptr = current;
	}
	return head;
}



void update_content_export(t_list_env *current, const char *key, const char *value)
{
	char *new_content;
	size_t total_len;
	size_t key_len;
	size_t value_len;
	
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	total_len = key_len + value_len + 2;
	new_content = malloc(total_len);
	if (!new_content)
		return ;
	ft_strlcpy(new_content, key, key_len + 1);
	ft_strlcat(new_content, "=", total_len);
	ft_strlcat(new_content, value, total_len);
	free(current->envp_content);
	current->envp_content = new_content;
}

void add_or_update_export(t_list_env **head, const char *variable)
{
	char		*key;
	char		*value;
	char		*var_copy;
	t_list_env	*current;

	var_copy = ft_strdup(variable);
	if (!var_copy)
		return;
	value = ft_strchr(var_copy, '=');
	key = var_copy;
	if (value && *(value++))
		*(value - 1) = '\0';
	current = *head;
	while (current)
	{
		if (!ft_strncmp(current->envp_content, key, ft_strlen(key)) &&
			current->envp_content[ft_strlen(key)] == '=')
			return (update_content_export(current, key, value),
					free(var_copy));
		current = current->next;
	}
	ft_lstadd_back(head, create_node_export(variable));
	free(var_copy);
}


void handle_export_no_args(t_list_env **envp)
{
	t_list_env *copied_list;

	copied_list = copy_list_export(*envp);
	if (copied_list)
	{
		copied_list = sort_list_export(copied_list, NULL);
		print_list_export(copied_list);
		free_list_export(copied_list);
	}
}