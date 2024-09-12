/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:31:03 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 10:31:24 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(t_list_env *nodess, char *home)
{
	while (nodess)
	{
		if (compare_until_equal_sign(nodess->envp_content, "PWD") == 1)
		{
			free(nodess->envp_content);
			ft_strcpy(home, "PWD=");
			getcwd(home + 4, PATH_MAX - 4);
			nodess->envp_content = ft_strdup(home);
			break ;
		}
		nodess = nodess->next;
	}
}
