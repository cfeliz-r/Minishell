/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aux3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:37:10 by manufern          #+#    #+#             */
/*   Updated: 2024/08/23 14:38:48 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_key_value(const char *variable, char **value)
{
	char	*var_copy;
	char	*key;

	var_copy = ft_strdup(variable);
	if (!var_copy)
		return (NULL);
	*value = ft_strchr(var_copy, '=');
	key = var_copy;
	if (*value && *(*value)++)
		*(*value - 1) = '\0';
	return (key);
}

int	compare_keys(const char *envp_content, const char *key)
{
	return (!ft_strncmp(envp_content, key, ft_strlen(key))
		&& (envp_content[ft_strlen(key)] == '='
			|| envp_content[ft_strlen(key)] == '\0'));
}

void	handle_existing_variable(t_list_env *current,
	const char *key, const char *value)
{
	if (value)
		update_content_export(current, key, value);
	else if (strchr(current->envp_content, '=') == NULL)
		update_content_export(current, key, "");
}

void	process_existing_variable(t_list_env **head,
	const char *key, const char *value, char *var_copy)
{
	t_list_env	*current;

	current = *head;
	while (current)
	{
		if (compare_keys(current->envp_content, key))
		{
			handle_existing_variable(current, key, value);
			free(var_copy);
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(head, create_node_export(key));
	free(var_copy);
}

void	add_or_update_export(t_list_env **head, const char *variable)
{
	char	*key;
	char	*value;
	char	*var_copy;

	key = get_key_value(variable, &value);
	if (!key)
		return ;
	var_copy = key;
	process_existing_variable(head, key, value, var_copy);
}
