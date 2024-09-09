/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:56:03 by manufern          #+#    #+#             */
/*   Updated: 2024/09/09 09:51:42 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_within_quotes(const char *text, int index)
{
	int	in_quotes;
	int	i;

	in_quotes = 0;
	i = 0;
	while (i <= index)
	{
		if (text[i] == '"' || text[i] == '\'')
			in_quotes = !in_quotes;
		i++;
	}
	return (in_quotes);
}

int	search_string_outside_quotes(const char *text, const char *search)
{
	int	text_len;
	int	search_len;
	int	in_quotes;
	int	i;

	text_len = ft_strlen(text);
	search_len = ft_strlen(search);
	in_quotes = 0;
	i = 0;
	while (i <= text_len - search_len)
	{
		if (text[i] == '"' || text[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && ft_strncmp(&text[i], search, search_len) == 0)
		{
			if ((i == 0 || !is_within_quotes(text, i - 1))
				&& (i + search_len == text_len
					|| !is_within_quotes(text, i + search_len - 1)))
				return (1);
		}
		i++;
	}
	return (0);
}
