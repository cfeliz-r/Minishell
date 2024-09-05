/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:05:02 by manufern          #+#    #+#             */
/*   Updated: 2024/09/05 17:55:32 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirection_syntax(const char *line, int *i)
{
	if ((line[*i] == '>' && line[*i + 1] == '>') || (line[*i] == '<' && line[*i + 1] == '<'))
		*i += 1;
	else if (line[*i] == '>' || line[*i] == '<')
		return (1);
	if ((line[*i] == '>' && line[*i + 1] == '<') || (line[*i] == '<' && line[*i + 1] == '>'))
		return (0);
	return (1);
}

int	handle_initial_checks(char *line, char **aux)
{
	*aux = line;
	if (line == NULL || *line == '\0')
		return (1);
	if (line != NULL)
	{
		*aux = remove_spaces(*aux);
		free(*aux);
	}
	return (0);
}

int	check_quotes_and_special_chars(char *line)
{
	if (check_quotes(line) == 0)
	{
		exit_with_error("quotes error\n");
		return (1);
	}
	if (check_special_chars(line) == 0)
	{
		exit_with_error("special chars error\n");
		return (1);
	}
	return (0);
}

int	check_redirections_and_syntax(char *line)
{
	int in_single_quote = 0;
	int in_double_quote = 0;
	int i = 0;

	while (line[i])
	{
		if (line[i] == '\'' && in_double_quote == 0)
			in_single_quote = !in_single_quote;
		else if (line[i] == '"' && in_single_quote == 0)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (check_redirections(line) == 0)
			{
				exit_with_error("redirection syntax error\n");
				return (1);
			}
		}
		i++;
	}
	if (check_syntax(line) == 0)
	{
		exit_with_error("general syntax error\n");
		return (1);
	}
	if (validate_arguments(line) == 0)
	{
		exit_with_error("invalid argument error\n");
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

int	ft_parsing(char *line)
{
	char	*aux;

	if (handle_initial_checks(line, &aux) == 1)
		return (1);
	if (handle_syntax_checks(line) == 1)
		return (1);
	return (0);
}
