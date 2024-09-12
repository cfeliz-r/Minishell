/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:01:01 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/12 10:53:59 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count(char **split_result)
{
	int	i;

	i = 0;
	while (split_result[i])
		i++;
	return (i);
}

char	*split_quotes(char *str)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			result[j++] = str[i];
		}
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

int	search_string(const char *text, const char *search)
{
	int		text_len;
	int		search_len;
	int		in_quotes;
	int		i;

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
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*correct_strstr(const char *str, const char *to_find)
{
	int		index;

	if (!str || !to_find)
		return (NULL);
	index = search_string(str, to_find);
	if (index == -1)
		return (NULL);
	return ((char *)&str[index]);
}

char	*safe_strjoin_free(char *s1, const char *s2)
{
	char	*new_str;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	temp = s1;
	new_str = ft_strjoin(s1, (char *)s2);
	if (!new_str)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (new_str);
}
