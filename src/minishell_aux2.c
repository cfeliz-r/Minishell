/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:15 by manufern          #+#    #+#             */
/*   Updated: 2024/09/11 17:34:22 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

void	process_string(const char *str, t_reduce_vars *vars)
{
	while (str[vars->i] != '\0')
	{
		if (str[vars->i] == '"' || str[vars->i] == '\'')
		{
			vars->in_quotes = !vars->in_quotes;
			vars->new_str[vars->j++] = str[vars->i];
		}
		else if (str[vars->i] == ' ')
		{
			if (!vars->last_char_was_space || vars->in_quotes)
			{
				vars->new_str[vars->j++] = ' ';
				vars->last_char_was_space = 1;
			}
		}
		else
		{
			vars->new_str[vars->j++] = str[vars->i];
			vars->last_char_was_space = 0;
		}
		vars->i++;
	}
}

char	*reduce_spaces(const char *str)
{
	t_reduce_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.last_char_was_space = 0;
	vars.len = strlen(str);
	vars.in_quotes = 0;
	vars.new_str = malloc(vars.len + 1);
	if (vars.new_str == NULL)
		return (NULL);
	process_string(str, &vars);
	vars.new_str[vars.j] = '\0';
	return (vars.new_str);
}

char	*ft_put_spaces(char *str)
{
	t_vars	vars;
	char	*new_str;

	vars.i = 0;
	vars.j = 0;
	vars.in_single_quote = 0;
	vars.in_double_quote = 0;
	vars.last_char_was_space = 0;
	vars.str_len = ft_strlen(str);
	vars.new_str = malloc(sizeof(char) * (vars.str_len * 2 + 2));
	if (vars.new_str == NULL)
		return (NULL);
	while (str[vars.i] != '\0')
	{
		if (str[vars.i] == '\'' && !vars.in_double_quote)
		{
			vars.in_single_quote = !vars.in_single_quote;
			vars.new_str[vars.j++] = str[vars.i++];
			vars.last_char_was_space = 0;
		}
		else if (str[vars.i] == '"' && !vars.in_single_quote)
		{
			vars.in_double_quote = !vars.in_double_quote;
			vars.new_str[vars.j++] = str[vars.i++];
			vars.last_char_was_space = 0;
		}
		else if (!vars.in_single_quote && !vars.in_double_quote
			&& ((str[vars.i] == '<' && str[vars.i + 1] == '<')
				|| (str[vars.i] == '>' && str[vars.i + 1] == '>')
				|| (str[vars.i] == '<' && str[vars.i + 1] == '>')
				|| (str[vars.i] == '>' && str[vars.i + 1] == '<')))
		{
			if (vars.i > 0 && str[vars.i - 1] != ' '
				&& !vars.last_char_was_space)
				vars.new_str[vars.j++] = ' ';
			vars.new_str[vars.j++] = str[vars.i++];
			vars.new_str[vars.j++] = str[vars.i++];
			if (str[vars.i] != ' ' && str[vars.i] != '\0')
				vars.new_str[vars.j++] = ' ';
			vars.last_char_was_space = 1;
		}
		else if ((str[vars.i] == '|' || str[vars.i] == '<'
				|| str[vars.i] == '>')
			&& !vars.in_single_quote && !vars.in_double_quote)
		{
			if (vars.i > 0 && str[vars.i - 1] != ' '
				&& !vars.last_char_was_space)
				vars.new_str[vars.j++] = ' ';
			vars.new_str[vars.j++] = str[vars.i++];
			if (str[vars.i] != ' ' && str[vars.i] != '\0')
				vars.new_str[vars.j++] = ' ';
			vars.last_char_was_space = 1;
		}
		else if (str[vars.i] == ' '
			&& !vars.in_single_quote && !vars.in_double_quote)
		{
			vars.new_str[vars.j++] = str[vars.i++];
			vars.last_char_was_space = 1;
		}
		else
		{
			vars.new_str[vars.j++] = str[vars.i++];
			vars.last_char_was_space = 0;
		}
	}
	vars.new_str[vars.j] = '\0';
	new_str = reduce_spaces(vars.new_str);
	free (vars.new_str);
	return (new_str);
}
