/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:04:40 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:21:44 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remoove(char *str, t_list_env **envp)
{
	t_list_env	*temp;
	t_list_env	*prev;

	temp = *envp;
	prev = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->data, str, ft_strlen(str)) == 0
			&& (temp->data[ft_strlen(str)] == '='
				|| temp->data[ft_strlen(str)] == '\0'))
		{
			if (prev == NULL)
				envp = &temp->next;
			else
				prev->next = temp->next;
			free(temp->data);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	remoove_unset(const char *input, t_list_env **envp)
{
	char	**split;
	int		i;

	split = split_special(input);
	i = 0;
	while (split[i] != NULL)
	{
		remoove(split[i], envp);
		i++;
	}
	clean_up(split, NULL, 0);
}

void	ft_unset(char *input, t_list_env **envp)
{
	char	*ptr;

	manage_error(0, 0);
	if (!input || !envp)
		return ;
	if (ft_strcmp(input, "unset") == 0 && (input[5] == '\0'
			|| is_space((unsigned char)input[5])))
		return ;
	else if (ft_strncmp(input, "unset ", 6) == 0)
	{
		ptr = input + 6;
		if (ft_strcmp(ptr, "BABUTERM") == 0
			|| ft_strcmp(ptr, "_ROUTE_BABUTERM_") == 0)
		{
			ft_putstr_fd("protected variable, cannot UNSET\n", 2);
			return ;
		}
		remoove_unset(ptr, envp);
	}
}
