/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:55 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 19:33:25 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_list_env **envp)
{
	static char	buf[PATH_MAX];

	manage_error(0, 0);
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		while (*envp)
		{
			if (compare_until_equal_sign((*envp)->envp_content,
					"_ROUTE_BABUTERM_") == 1)
			{
				printf("%s\n", (*envp)->envp_content + 17);
				break ;
			}
			*envp = (*envp)->next;
		}
		return ;
	}
	printf("%s\n", buf);
}
