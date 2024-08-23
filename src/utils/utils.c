/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/23 12:53:11 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_space(int c)
{
	unsigned char	character;

	character = (unsigned char) c;
	if (character == ' ' || character == '\t' || character == '\n' || character == '\v' || \
	character == '\f' || character == '\r')
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
		commands[j]->args = NULL;
		free(commands[j]->path);
		free(commands[j]->inredir);
		free(commands[j]->outredirs);
		free(commands[j]->cmd_cpt);
		free(commands[j]->delimiters);
		free(commands[j]);
		j++;
		i = 0;
	}
	free(commands);
}
