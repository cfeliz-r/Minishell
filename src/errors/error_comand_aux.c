/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:02:35 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 11:01:52 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		return (0);
}

int	is_inside_quotes(char *line)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*line)
	{
		if (*line == '\'')
			single_quotes = !single_quotes;
		else if (*line == '\"')
			double_quotes = !double_quotes;
		line++;
	}
	return (single_quotes || double_quotes);
}

int	check_redirections(char *line)
{
	int	inside_quotes;

	inside_quotes = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes && *line == '|' && *(line + 1) == '|')
			return (0);
		if (!inside_quotes && (*line == '>' || *line == '<'))
		{
			if (*(line + 1) == *line || (*line == '<' && *(line + 1) == '>'))
				line++;
			while (is_space(*(line + 1)))
				line++;
			if (*(line + 1) == '\0')
				return (0);
			else if (*(line + 1) == '|' || *(line + 1) == '<'
				|| *(line + 1) == '>')
				return (0);
		}
		line++;
	}
	return (1);
}
