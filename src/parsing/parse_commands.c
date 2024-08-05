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
        if (strncmp(envp_list->envp_content, key, strlen(key)) == 0 &&
            envp_list->envp_content[strlen(key)] == '=')
        {
            return envp_list->envp_content + strlen(key) + 1; // Return the value
        }
        envp_list = envp_list->next;
    }
    return NULL; // Key not found
}

char *interpret_command(const char *command, t_list_env *envp)
{
    size_t i = 0, j = 0;
    size_t in_double_quotes = 0, in_single_quotes = 0;
    size_t buffer_size = strlen(command) * 2 + 1; // Initial size guess
    size_t old_buffer_size = buffer_size;
    char *result = malloc(buffer_size);
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
                // Ensure enough space for escape sequence
                if (j >= buffer_size - 2)
                {
                    old_buffer_size = buffer_size;
                    buffer_size *= 2;
                    char *new_result = simple_realloc(result, old_buffer_size, buffer_size);
                    if (!new_result)
                    {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                }
                result[j++] = command[i++];
                result[j++] = command[i++];
            }
            else
            {
                i++;
            }
        }
        else if (command[i] == ';' && !in_single_quotes && !in_double_quotes)
        {
            // Ensure enough space for semicolon
            if (j >= buffer_size - 1)
            {
                old_buffer_size = buffer_size;
                buffer_size *= 2;
                char *new_result = simple_realloc(result, old_buffer_size, buffer_size);
                if (!new_result)
                {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            result[j++] = command[i++];
        }
        else if (command[i] == '$' && in_double_quotes)
        {
            i++;
            char key[256];
            size_t k = 0;

            while (command[i] && (isalnum(command[i]) || command[i] == '_') && k < sizeof(key) - 1)
            {
                key[k++] = command[i++];
            }
            key[k] = '\0';

            char *value = find_env_value(envp, key);
            if (value)
            {
                while (*value)
                {
                    // Ensure enough space for environment variable expansion
                    if (j >= buffer_size - 1)
                    {
                        old_buffer_size = buffer_size;
                        buffer_size *= 2;
                        char *new_result = simple_realloc(result, old_buffer_size, buffer_size);
                        if (!new_result)
                        {
                            free(result);
                            return NULL;
                        }
                        result = new_result;
                    }
                    result[j++] = *value++;
                }
            }
        }
        else
        {
            // Ensure enough space for general characters
            if (j >= buffer_size - 1)
            {
                old_buffer_size = buffer_size;
                buffer_size *= 2;
                char *new_result = simple_realloc(result, old_buffer_size, buffer_size);
                if (!new_result)
                {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            result[j++] = command[i++];
        }
    }

    if (in_double_quotes || in_single_quotes)
    {
        free(result);
        return NULL;
    }

    result[j] = '\0';
    return result;
}

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
