/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/22 12:31:56 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_space(int c)
{
	unsigned char	c_c;

	c_c = (unsigned char) c;
	if (c_c == ' ' || c_c == '\t' || c_c == '\n' || c_c == '\v' || \
	c_c == '\f' || c_c == '\r')
		return (1);
	return (0);
}

size_t	aux_count(char **array)
{
	size_t	count;

	count = 0;
	if (!array)
		return (0);
	while (*array)
	{
		count++;
		array++;
	}
	return (count);
}

int	all_digits(const char *str)
{
	const char	*ptr;

	ptr = str;
	if (!ptr || *ptr == '\0')
		return (0);
	while (*ptr)
	{
		if (!ft_isdigit((unsigned char)*ptr))
			return (0);
		ptr++;
	}
	return (1);
}

void	clean_up_aux(t_command **commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (commands[j] != NULL)
	{
		while (commands[j]->args[i] != NULL)
			free(commands[j]->args[i++]);
		free(commands[j]->args);
		free(commands[j]->path);
		j++;
		i = 0;
	}
}
