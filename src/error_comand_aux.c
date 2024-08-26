/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:02:35 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 10:25:07 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_quotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	check_quotes(char *command)
{
	int	i;
	int	in_double_quotes;
	int	in_single_quotes;

	in_double_quotes = 0;
	in_single_quotes = 0;
	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (command[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		i++;
	}
	if (!in_double_quotes && !in_single_quotes)
		return (1);
	else
		return (manage_error(200, 0), 0);
}

int	check_special_chars(char *line)
{
	int	prev_char_was_special;

	prev_char_was_special = 0;
	while (*line)
	{
		if (*line == '|')
		{
			if (prev_char_was_special)
				return (0);
			prev_char_was_special = 1;
		}
		else
			prev_char_was_special = 0;
		line++;
	}
	return (1);
}

int	check_redirections(char *line)
{
	while (*line)
	{
		if (*line == '>' || *line == '<')
		{
			if (*(line + 1) == *line)
				line++;
			while (is_space(*(line + 1)))
				line++;
			if (*(line + 1) == '\0')
				return (0);
			else if (*(line + 1) == '|' || *(line + 1) == '<' || *(line + 1) == '>')
				return (0);
		}
		line++;
	}
	return (1);
}

int	check_syntax(char *line)
{
	char	*end;

	while (is_space(*line))
		line++;
	if (*line == '|')
		return (0);
	end = line + strlen(line) - 1;
	while (end > line && is_space(*end))
		end--;
	if (*end == '|')
		return (0);
	return (1);
}
