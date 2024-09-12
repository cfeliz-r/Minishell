/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand_aux2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:04:00 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 11:02:05 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_is_space(char *start, char *end)
{
	while (start < end)
	{
		if (!is_space(*start))
			return (0);
		start++;
	}
	return (1);
}

int	has_space(char *start, char *end)
{
	while (start < end)
	{
		if (is_space(*start))
			return (1);
		start++;
	}
	return (0);
}

void	exit_with_error(const char *message, int error_code)
{
	manage_error(error_code, 0);
	write(2, message, ft_strlen(message));
}

char	*remove_spaces(const char *str)
{
	size_t	length;
	size_t	i;
	size_t	j;
	char	*result;

	if (str == NULL)
		return (NULL);
	length = ft_strlen(str);
	i = 0;
	j = 0;
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	while (i < length)
	{
		if (str[i] != ' ')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
