/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:04:40 by manufern          #+#    #+#             */
/*   Updated: 2024/09/06 16:45:25 by manufern         ###   ########.fr       */
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
		if (compare_until_equal_sign(temp->envp_content, str) == 1)
		{
			if (prev == NULL)
				*envp = temp->next;
			else
				prev->next = temp->next;
			free(temp->envp_content);
			free(temp);
			break ;
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
	const char	*ptr;

	if (!input || !envp)
		return ;
	if (ft_strcmp(input, "unset") == 0 && (input[5] == '\0'
			|| is_space((unsigned char)input[5])))
		return ;
	else if (ft_strncmp(input, "unset ", 6) == 0)
	{
		ptr = input + 6;
		remoove_unset(ptr, envp);
	}
}
