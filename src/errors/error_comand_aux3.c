/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand_aux3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:24:25 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 11:01:45 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_quotes_3(char **start)
{
	char	quote_char;

	quote_char = **start;
	(*start)++;
	while (**start != '\0' && **start != quote_char)
		(*start)++;
	if (**start != quote_char)
		return (0);
	(*start)++;
	return (1);
}

int	check_syntax(char *line)
{
	char	*end;

	while (is_space(*line))
		line++;
	if (*line == '|')
		return (0);
	end = line + ft_strlen(line) - 1;
	while (end > line && is_space(*end))
		end--;
	if (*end == '|')
		return (0);
	return (1);
}

int	check_sintax_and_errors(char *line)
{
	if (check_syntax(line) == 0)
	{
		exit_with_error("syntax error near unexpected token\n", 2);
		return (1);
	}
	return (0);
}

int	handle_syntax_checks(char *line)
{
	if (check_quotes_and_special_chars(line) == 1)
		return (1);
	if (check_redirections_and_syntax(line) == 1)
		return (1);
	return (0);
}
