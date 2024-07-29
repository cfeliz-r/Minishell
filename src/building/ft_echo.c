/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:06 by manufern          #+#    #+#             */
/*   Updated: 2024/07/29 19:21:45 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_echo(char *command)
{
	char	**str;
	int	i;
	int j;
	i = 0;
	j = 5;
	while(command[j] == ' ' && command[j] !=  '\0')
		j ++;
	str = ft_split(command + j, '\'');
	while (str[i] != NULL)
	{
		printf("%s", str[i]);
		i++;
	}
	clean_up(str, NULL);
	printf("\n");
}