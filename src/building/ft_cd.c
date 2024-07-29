/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:54:35 by manufern          #+#    #+#             */
/*   Updated: 2024/07/26 18:59:12 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *get_env_value(const char *name, t_list_env *envp)
{
	while (envp)
	{
		if (ft_strncmp(envp->envp_content, name, ft_strlen(name)) == 0
		&& envp->envp_content[ft_strlen(name)] == '=')
            return &envp->envp_content[ft_strlen(name) + 1];
        envp = envp->next;
    }
    return NULL;
}

void ft_cd(char *route, t_list_env *envp)
{
	char **str_route;
	int i;
	char *home;

	home = NULL;
	i = 0;
	str_route = ft_split(route ,' ');
	while (str_route[i] != NULL)
		i++;
	if (i == 1)
	{
		home = get_env_value("HOME", envp);
		chdir(home);
	}
	else if (i > 2)
		printf("cd: string not in pwd: %s\n", str_route[1]);
	else if (chdir(str_route[1]) != 0)
		perror("chdir failed");
	clean_up(str_route, NULL);
}