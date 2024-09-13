/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:22:24 by manuel            #+#    #+#             */
/*   Updated: 2024/09/13 13:23:46 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_identifier(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (!ft_isprint(str[i]))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			manage_error(1, 0);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_blank_line(const char *line)
{
	if (line == NULL)
		return (1);
	while (*line)
	{
		if (is_space((unsigned char)*line) == 0)
		{
			return (0);
		}
		line++;
	}
	return (1);
}

void	handle_spaces_and_chars(const char *str, t_reduce_vars *vars)
{
	if (str[vars->i] == ' ')
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
}

void	handle_double_quotes(t_vars *vars, char *str)
{
	vars->new_str[vars->j++] = str[vars->i++];
	while (str[vars->i] != '"' && str[vars->i] != '\0')
		vars->new_str[vars->j++] = str[vars->i++];
	if (str[vars->i] == '"')
		vars->new_str[vars->j++] = str[vars->i++];
}
