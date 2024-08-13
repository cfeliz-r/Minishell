/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:44 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 13:15:58 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_variable_content_export(t_list_env *current, const char *key,
	const char *value)
{
	size_t	key_len;
	size_t	value_len;
	size_t	total_len;
	char	*new_content;

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

char	*duplicate_string_export(const char *str)
{
	return (ft_strdup(str));
}

void	extract_key_and_value_export(char *var_copy, char **key, char **value)
{
	*value = ft_strchr(var_copy, '=');
	if (*value)
	{
		**value = '\0';
		(*value)++;
	}
	else
		*value = "";
	*key = var_copy;
}

t_list_env	*find_variable_in_list_export(t_list_env *head, const char *key)
{
	t_list_env	*current;

	current = head;
	while (current)
	{
		if (ft_strncmp(current->envp_content, key, ft_strlen(key)) == 0
			&& current->envp_content[ft_strlen(key)] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_export(char *input, t_list_env **envp)
{
	const char	*ptr;
	char		*var_start;
	char		*var_end;
	int			inside_quotes;

	if (!input || !envp)
		return ;
	if (is_empty_or_space_export(input))
	{
		process_export_command_export(envp);
	}
	else if (ft_strncmp(input, "export ", 7) == 0)
	{
		ptr = input + 7;
		while (*ptr)
		{
			while (isspace((unsigned char)*ptr))
				ptr++;
			var_start = (char *)ptr;
			var_end = find_variable_end_export(ptr, &inside_quotes);
			if (var_start < var_end)
				extract_and_process_variable_export(envp, var_start, var_end);
			ptr = var_end;
		}
	}
}
