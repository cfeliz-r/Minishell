/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:54:35 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 09:56:53 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char *route)
{
	char	**str_route;
	int		i;

	i = 0;
	str_route = ft_split(route, ' ');
	manage_error(0, 0);
	while (str_route[i] != NULL)
	{
		i++;
	}
	if (i > 2)
		printf("cd: string not in pwd: %s\n", str_route[1]);
	else
	{
		if (i != 1 && access(str_route[1], F_OK | R_OK) == 0)
			chdir(str_route[1]);
		else
		{
			perror("invalid route");
			manage_error(1, 0);
		}
	}
	clean_up(str_route, NULL, 0);
}
