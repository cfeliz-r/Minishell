/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:44:06 by manufern          #+#    #+#             */
/*   Updated: 2024/07/29 20:49:40 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_echo(char *comand)
{
	char	**str;
	int	i;

	i = 0;
	str = ft_split(comand + 4, '"');
	while (str[i] != NULL)
	{
		printf("%s", str[i]);
		i++;
	}
	clean_up(str, NULL);
	printf("\n");
}