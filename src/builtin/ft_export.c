/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:44 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 11:43:39 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_list(t_list_env *list)
{
	t_list_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->envp_content);
		free(tmp);
	}
}

static t_list_env	*create_node(const char *content)
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

static t_list_env	*copy_list(t_list_env *original)
{
	t_list_env	*current_original;
	t_list_env	*current_new;
	t_list_env	*new_list;

	if (!original)
		return (NULL);
	new_list = create_node(original->envp_content);
	if (!new_list)
		return (NULL);
	current_original = original->next;
	current_new = new_list;
	while (current_original)
	{
		current_new->next = create_node(current_original->envp_content);
		if (!current_new->next)
		{
			free_list(new_list);
			return (NULL);
		}
		current_new = current_new->next;
		current_original = current_original->next;
	}
	return (new_list);
}

static t_list_env	*sort_list(t_list_env *head, int swapped)
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

static void	print_list(t_list_env *list)
{
	while (list)
	{
		printf("declare -x %s\n", list->envp_content);
		list = list->next;
	}
}

static void	update_variable_content(t_list_env *current, const char *key,
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

static void	add_or_update_variable(t_list_env **head, const char *variable,
	char *key)
{
	char		*value;
	char		*var_copy;
	t_list_env	*current;
	t_list_env	*prev;
	t_list_env	*new_node;

	prev = NULL;
	current = *head;
	var_copy = ft_strdup(variable);
	if (!var_copy)
		return ;
	value = ft_strchr(var_copy, '=');
	if (value)
	{
		*value = '\0';
		value++;
	}
	else
		value = "";
	key = var_copy;
	while (current)
	{
		if (ft_strncmp(current->envp_content, key, ft_strlen(key)) == 0
			&& current->envp_content[ft_strlen(key)] == '=')
		{
			update_variable_content(current, key, value);
			free(var_copy);
			return ;
		}
		prev = current;
		current = current->next;
	}
	new_node = create_node(variable);
	if (!new_node)
	{
		free(var_copy);
		return ;
	}
	if (prev)
		prev->next = new_node;
	else
		*head = new_node;
	free(var_copy);
}

void	ft_export(char *input, t_list_env **envp)
{
	const char	*ptr;
	t_list_env	*copied_list;
	char		*var_start;
	char		*var_end;
	int			inside_quotes;
	char		quote;
	char		*variable;

	if (!input || !envp)
		return ;
	if (ft_strcmp(input, "export") == 0 && (input[6] == '\0'
			|| isspace((unsigned char)input[6])))
	{
		copied_list = copy_list(*envp);
		if (copied_list)
		{
			copied_list = sort_list(copied_list, 0);
			print_list(copied_list);
			free_list(copied_list);
		}
		else
			return ;
	}
	else if (ft_strncmp(input, "export ", 7) == 0)
	{
		ptr = input + 7;
		while (*ptr)
		{
			while (isspace((unsigned char)*ptr))
				ptr++;
			var_start = (char *)ptr;
			inside_quotes = 0;
			if (*ptr == '"' || *ptr == '\'')
			{
				quote = *ptr++;
				inside_quotes = 1;
				var_end = ft_strchr(ptr, quote);
				if (var_end)
					var_end++;
				else
					var_end = (char *)ptr + ft_strlen(ptr);
			}
			else
			{
				while (*ptr && (!isspace((unsigned char)*ptr) || inside_quotes))
				{
					if (*ptr == '"' || *ptr == '\'')
						inside_quotes = !inside_quotes;
					ptr++;
				}
				var_end = (char *)ptr;
			}
			if (var_start < var_end)
			{
				variable = ft_strndup(var_start, var_end - var_start);
				if (variable)
				{
					add_or_update_variable(envp, variable, NULL);
					free(variable);
				}
			}
			ptr = var_end;
		}
	}
}
