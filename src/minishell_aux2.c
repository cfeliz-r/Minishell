/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:15 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:05:25 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_string(const char *str, t_reduce_vars *vars)
{
	while (str[vars->i] != '\0')
	{
		if (str[vars->i] == '"' || str[vars->i] == '\'')
		{
			if (str[vars->i] == '"')
			{
				vars->new_str[vars->j++] = str[vars->i++];
				while (str[vars->i] != '"')
					vars->new_str[vars->j++] = str[vars->i++];
			}
			else if (str[vars->i] == '\'')
			{
				vars->new_str[vars->j++] = str[vars->i++];
				while (str[vars->i] != '\'')
					vars->new_str[vars->j++] = str[vars->i++];
			}
			vars->new_str[vars->j++] = str[vars->i];
			if (str[vars->i + 1] == ' ')
				vars->new_str[vars->j++] = ' ';
		}
		else
			handle_spaces_and_chars(str, vars);
		vars->i++;
	}
}

char	*reduce_spaces(const char *str)
{
	t_reduce_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.last_char_was_space = 0;
	vars.len = ft_strlen(str);
	vars.in_quotes = 0;
	vars.new_str = malloc(vars.len + 2);
	if (vars.new_str == NULL)
		return (NULL);
	process_string(str, &vars);
	vars.new_str[vars.j] = '\0';
	return (vars.new_str);
}

void	process_special_cases(t_vars *vars, char *str)
{
	if (!vars->in_single_quote && !vars->in_double_quote
		&& ((str[vars->i] == '<' && str[vars->i + 1] == '<')
			|| (str[vars->i] == '>' && str[vars->i + 1] == '>')
			|| (str[vars->i] == '<' && str[vars->i + 1] == '>')
			|| (str[vars->i] == '>' && str[vars->i + 1] == '<')))
	{
		if (vars->i > 0 && str[vars->i - 1] != ' '
			&& !vars->last_char_was_space)
			vars->new_str[vars->j++] = ' ';
		vars->new_str[vars->j++] = str[vars->i++];
		vars->new_str[vars->j++] = str[vars->i++];
		if (str[vars->i] != ' ' && str[vars->i] != '\0')
			vars->new_str[vars->j++] = ' ';
		vars->last_char_was_space = 1;
	}
	else
		process_single_char_cases(vars, str);
}

int	initialize_vars(t_vars *vars, char *str)
{
	vars->i = 0;
	vars->j = 0;
	vars->in_single_quote = 0;
	vars->in_double_quote = 0;
	vars->last_char_was_space = 0;
	vars->str_len = ft_strlen(str);
	vars->new_str = malloc(sizeof(char) * (vars->str_len * 2 + 2));
	if (vars->new_str == NULL)
		return (0);
	return (1);
}

char	*ft_put_spaces(char *str)
{
	t_vars	vars;
	char	*new_str;

	if (!initialize_vars(&vars, str))
		return (NULL);
	while (str[vars.i] != '\0')
	{
		if (str[vars.i] == '\'' && !vars.in_double_quote)
		{
			vars.new_str[vars.j++] = str[vars.i++];
			while (str[vars.i] != '\'')
				vars.new_str[vars.j++] = str[vars.i++];
			vars.new_str[vars.j++] = str[vars.i++];
		}
		else if (str[vars.i] == '"' && !vars.in_single_quote)
		{
			handle_double_quotes(&vars, str);
		}
		else
			process_special_cases(&vars, str);
	}
	vars.new_str[vars.j] = '\0';
	new_str = reduce_spaces(vars.new_str);
	return (free(vars.new_str), new_str);
}
