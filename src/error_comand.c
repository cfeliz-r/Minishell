/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:05:02 by manufern          #+#    #+#             */
/*   Updated: 2024/08/20 15:22:08 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_initial_checks(char *line, char **aux)
{
	*aux = line;
	if (!line || !*line)
	{
		exit_with_error("empty command line\n");
		return (1);
	}
	if (line != NULL)
	{
		*aux = remove_spaces(*aux);
		if (ft_strncmp(*aux, "\"<\"", 3) == 0
			|| ft_strncmp(*aux, "\">\"", 3) == 0
			|| ft_strncmp(*aux, "\">>\"", 4) == 0
			|| ft_strncmp(*aux, "\"<<\"", 4) == 0)
		{
			exit_with_error("command not found\n");
			free(*aux);
			return (1);
		}
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
	if (check_redirections(line) == 0)
	{
		exit_with_error("redirection syntax error\n");
		return (1);
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
