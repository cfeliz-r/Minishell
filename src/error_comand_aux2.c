/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand_aux2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:04:00 by manufern          #+#    #+#             */
/*   Updated: 2024/09/09 16:59:34 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_is_space(char *start, char *end)
{
	while (start < end)
	{
		if (!is_space(*start))
			return (0);
		start++;
	}
	return (1);
}

int	has_space(char *start, char *end)
{
	while (start < end)
	{
		if (is_space(*start))
			return (1);
		start++;
	}
	return (0);
}

/* int	validate_arguments(char *line)
{
	char	*start;

	start = line;
	while (*start != '\0')
	{
		while ((is_space(*start) == 1) && *start != '\0')
			start++;
		if (*start == '\0')
			break ;
		if (*start == '"' || *start == '\'')
		{
			if (!handle_quotes_3(&start))
				return (0);
		}
		else
		{
			while (*start != '\0' && !is_space(*start)
				&& *start != '"' && *start != '\'')
				start++;
		}
	}
	return (1);
} */

void	exit_with_error(const char *message, int error_code)
{
	manage_error(error_code, 0);
	write(2, message, ft_strlen(message));
}

char	*remove_spaces(const char *str)
{
	size_t	length;
	size_t	i;
	size_t	j;
	char	*result;

	if (str == NULL)
		return (NULL);
	length = strlen(str);
	i = 0;
	j = 0;
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	while (i < length)
	{
		if (str[i] != ' ')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
