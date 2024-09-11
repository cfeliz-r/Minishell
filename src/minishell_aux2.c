/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:15 by manufern          #+#    #+#             */
/*   Updated: 2024/09/11 16:12:43 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *reduce_spaces(const char *str)
{
    int i = 0;
    int j = 0;
    int last_char_was_space = 0;
    int len = strlen(str);
    int in_quotes = 0;  // Variable para rastrear si estamos dentro de comillas

    // Reserva memoria para la nueva cadena
    char *new_str = malloc(len + 1);
    if (new_str == NULL)
        return NULL;

    while (str[i] != '\0')
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            in_quotes = !in_quotes;
            new_str[j++] = str[i];
        }
        else if (str[i] == ' ')
        {
            if (!last_char_was_space || in_quotes)
            {
                new_str[j++] = ' ';
                last_char_was_space = 1;
            }
        }
        else
        {
            new_str[j++] = str[i]; // Copia cualquier otro carácter
            last_char_was_space = 0;
        }
        i++;
    }

    new_str[j] = '\0'; // Termina la nueva cadena
    return new_str;
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
		else if (str[vars.i] == ' ' && !vars.in_single_quote && !vars.in_double_quote)
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
