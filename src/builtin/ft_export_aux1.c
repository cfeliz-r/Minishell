/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aux1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:03:28 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 13:35:17 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_or_update_variable_export(t_list_env **head, t_list_env *prev,
	t_list_env *new_node)
{
	if (prev)
		prev->next = new_node;
	else
		*head = new_node;
}

int	is_empty_or_space_export(char *input)
{
	return (ft_strcmp(input, "export") == 0 && (input[6] == '\0'
			|| isspace((unsigned char)input[6])));
}

void	process_export_command_export(t_list_env **envp)
{
	t_list_env	*copied_list;

	copied_list = copy_list_export(*envp);
	if (!copied_list)
		return ;
	copied_list = sort_list_export(copied_list, 0);
	print_list_export(copied_list);
	free_list_export(copied_list);
}

char	*find_variable_end_export(const char *ptr, int *inside_quotes)
{
	char	quote;
	char	*var_end;

	quote = '\0';
	if (*ptr == '"' || *ptr == '\'')
	{
		quote = *ptr++;
		*inside_quotes = 1;
		var_end = ft_strchr(ptr, quote);
		if (var_end)
			var_end++;
		else
			var_end = (char *)ptr + ft_strlen(ptr);
	}
	else
	{
		while (*ptr && (!isspace((unsigned char)*ptr) || *inside_quotes))
		{
			if (*ptr == '"' || *ptr == '\'')
				*inside_quotes = !*inside_quotes;
			ptr++;
		}
		var_end = (char *)ptr;
	}
	return (var_end);
}

void	extract_and_process_variable_export(t_list_env **envp, char *var_start,
	char *var_end)
{
	char		*variable_str;
	t_list_env	*variable_node;

	variable_str = ft_strndup(var_start, var_end - var_start);
	if (!variable_str)
		return ;
	variable_node = find_variable_in_list_export(*envp, variable_str);
	if (!variable_node)
	{
		variable_node = create_new_node_export(variable_str);
		if (variable_node)
		{
			add_or_update_variable_export(envp, NULL, variable_node);
		}
		else
		{
			free(variable_str);
			return ;
		}
	}
	update_variable_content_export(variable_node, variable_str, "");
	free(variable_str);
}
