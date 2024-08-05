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



char *find_env_value(t_list_env *envp_list, const char *key)
{
	while (envp_list)
	{
		if (ft_strncmp(envp_list->envp_content, key, ft_strlen(key)) == 0 &&
			envp_list->envp_content[ft_strlen(key)] == '=')
			return (envp_list->envp_content + ft_strlen(key) + 1);
		envp_list = envp_list->next;
	}
	return NULL;
}

/* char *interpret_command(const char *command, t_list_env *envp)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	in_single_quotes;
	size_t	in_double_quotes;
	size_t	buffer_size;
	size_t	old_buffer_size;
	char	*result;
	char	*new_result;
	char	*value;
	char	key[256];

	buffer_size = ft_strlen(command) * 2 + 1;
	result = malloc(buffer_size);
	old_buffer_size = buffer_size;
	in_double_quotes = 0;
	in_single_quotes = 0;
	j = 0;
	i = 0;
	if (!result)
		return NULL;
	while (command[i] != '\0')
	{
		if (command[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
		}
		else if (command[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
		}
		else if (command[i] == '\\')
		{
			if (command[i + 1] != '\0')
			{
				if (j >= buffer_size - 2)
				{
					old_buffer_size = buffer_size;
					buffer_size *= 2;
					new_result = simple_realloc(result, old_buffer_size, buffer_size);
					if (!new_result)
						return (free(result), NULL);
					result = new_result;
				}
				result[j++] = command[i++];
				result[j++] = command[i++];
			}
			else
				i++;
		}
		else if (command[i] == ';' && !in_single_quotes && !in_double_quotes)
		{
			if (j >= buffer_size - 1)
			{
				old_buffer_size = buffer_size;
				buffer_size *= 2;
				new_result = simple_realloc(result, old_buffer_size, buffer_size);
				if (!new_result)
					return (free(result), NULL);
				result = new_result;
			}
			result[j++] = command[i++];
		}
		else if (command[i] == '$' && in_double_quotes)
		{
			i++;
			k = 0;
			while (command[i] && (isalnum(command[i]) || command[i] == '_') && k < sizeof(key) - 1)
				key[k++] = command[i++];
			key[k] = '\0';
			value = find_env_value(envp, key);
			if (value)
			{
				while (*value)
				{
					if (j >= buffer_size - 1)
					{
						old_buffer_size = buffer_size;
						buffer_size *= 2;
						new_result = simple_realloc(result, old_buffer_size, buffer_size);
						if (!new_result)
							return (free(result), NULL);
						result = new_result;
					}
					result[j++] = *value++;
				}
			}
		}
		else
		{
			if (j >= buffer_size - 1)
			{
				old_buffer_size = buffer_size;
				buffer_size *= 2;
				new_result = simple_realloc(result, old_buffer_size, buffer_size);
				if (!new_result)
					return (free(result), NULL);
				result = new_result;
			}
			result[j++] = command[i++];
		}
	}
	if (in_double_quotes || in_single_quotes)
		return (free(result), NULL);
	result[j] = '\0';
	return result;
} */

int check_quotes(char *command)
{
	int i;
	int quotes_2;
	int quotes_1;

	i = 0;
	quotes_2 = 0;
	quotes_1 = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '"')
		{
			quotes_2++;
			i++;
			while (command[i] != '"' && command[i] != '\0')
				i++;
			if (command[i] == '"')
			{
				quotes_2++;
				i++;
			}
		}
		else if (command[i] == '\'')
		{
			quotes_1++;
			i++;
			while (command[i] != '\'' && command[i] != '\0')
				i++;
			if (command[i] == '\'')
			{
				quotes_1++;
				i++;
			}
		}
		else
			i++;
	}
	if (quotes_2 % 2 == 0 && quotes_1 % 2 == 0)
		return 1;
	else
		return 0;
}

char *remove_front_and_back_spaces(char *str)
{
	int start;
	int end;
	int length;

	start = 0;
	if (str != NULL)
	{
		while (str[start] && str[start] == ' ')
			start++;
		if (str[start] == '\0')
		{
			str[0] = '\0';
			return str;
		}
		length = ft_strlen(str);
		end = length - 1;
		while (end > start && str[end] == ' ')
			end--;
		length = end - start + 1;
		ft_memmove(str, str + start, length);
		str[length] = '\0';
		return str;
	}
	return (NULL);
}
