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

char *interpret_command(char *command)
{
    int i;
    int j;
    int in_double_quotes;
    int in_single_quotes;
    char *result;

    i = 0;
    j = 0;
    in_double_quotes = 0;
    in_single_quotes = 0;
    result = malloc(ft_strlen(command) + 1);
    if (!result)
        return (NULL);
    while (command[i] != '\0')
    {
        if (command[i] == '"' && !in_single_quotes)
        {
            if (in_double_quotes && i > 0 && command[i - 1] == ' ')
            {
                free(result);
                return (NULL);
            }
            in_double_quotes = !in_double_quotes;
            i++;
        }
        else if (command[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            i++;
        }
        else
        {
            result[j++] = command[i++];
        }
    }
    result[j] = '\0';
    return (result);
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
