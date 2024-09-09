/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:15 by manufern          #+#    #+#             */
/*   Updated: 2024/09/09 17:14:55 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_put_spaces(char *str)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	int		last_char_was_space;
	size_t	str_len;
	char	*new_str;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	last_char_was_space = 0;
	str_len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (str_len * 2 + 2));
	if (new_str == NULL)
		return (NULL);

	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			new_str[j++] = str[i++];
			last_char_was_space = 0;
		}
		else if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			new_str[j++] = str[i++];
			last_char_was_space = 0;
		}
		else if (!in_single_quote && !in_double_quote
			&& ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '>')
			|| (str[i] == '>' && str[i + 1] == '<')))
		{
			if (i > 0 && str[i - 1] != ' ' && !last_char_was_space)
				new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			if (str[i] != ' ' && str[i] != '\0')
				new_str[j++] = ' ';
			last_char_was_space = 1;
		}
		else if ((str[i] == '|' || str[i] == '<' || str[i] == '>')
			&& !in_single_quote && !in_double_quote)
		{
			if (i > 0 && str[i - 1] != ' ' && !last_char_was_space)
				new_str[j++] = ' ';
			new_str[j++] = str[i++];
			if (str[i] != ' ' && str[i] != '\0')
				new_str[j++] = ' ';
			last_char_was_space = 1;
		}
		else if (str[i] == ' ' && !in_single_quote && !in_double_quote)
		{
			new_str[j++] = str[i++];
			last_char_was_space = 1;
		}
		else
		{
			new_str[j++] = str[i++];
			last_char_was_space = 0;
		}
	}
	new_str[j] = '\0';
	printf("new_str: %s\n", new_str);
	return (new_str);
}
