/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:06 by manufern          #+#    #+#             */
/*   Updated: 2024/07/31 15:52:29 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_echo(char *comand)
{
	char	**str;
	int	i;
	int j;

	i = 0;
	j = 0;
	str = ft_split(comand + 5, ' ');
	if(ft_strcmp(str[i], "-n")== 0)
	{
		i = 1;
		j = 1;	
	}
	while (str[i] != NULL )
		printf("%s", str[i++]);
	clean_up(str, NULL);
	if (j == 1)
		return ;
	printf("\n");
}
