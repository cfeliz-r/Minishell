/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:46:24 by manufern          #+#    #+#             */
/*   Updated: 2024/08/07 21:51:02 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(t_list_env *env, char *command)
{
	t_list_env	*aux;
	char		**str_route;
	int			i;

	aux = env;
	i = 0;
	str_route = ft_split(command, ' ');
	manage_error(0, 0);
	while(str_route[i])
		i ++;
	if(i > 1)
	{
		printf("env: %s: No such file or directory\n", str_route[1]);
		manage_error(127, 0);
	}
	else
	{
		while (aux != NULL)
		{
			printf("%s\n", aux->envp_content);
			aux=aux->next;
		}
	}
	clean_up(str_route, NULL, 0);
}
