/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:14:45 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/16 14:55:50 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aux_exit(char **aux, t_list_env *envp)
{
	int	i;

	i = 0;
	while (aux_count(aux) == 2 && aux[1][i] != '\0')
	{
		if (i > 0 && (aux[1][i] == '-' || aux[1][i] == '+'))
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			free_list_env(envp);
			exit (2);
		}
		i++;
	}
	if (aux_count(aux) == 2 && !all_digits(aux[1])
		&& aux[1][0] != '-' && aux[1][0] != '+')
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		free_list_env(envp);
		exit (2);
	}
}

int	is_space(int c)
{
	unsigned char	character;

	character = (unsigned char) c;
	if (character == ' ' || character == '\t'
		|| character == '\n' || character == '\v' || \
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

void	clean_up_aux(t_cmd **commands)
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
