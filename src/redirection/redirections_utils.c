/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:01:01 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/24 15:13:38 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int  ft_count(char **split_result)
{
	int i;

	i = 0;
	while(split_result[i])
		i++;
	return i;
}

char *split_quotes(char *str)
{
    size_t len;
    char *result;
    size_t i;
	size_t j;
	
	j = 0;
	i = 0;
	len = ft_strlen(str);
	result = malloc(len + 1);
    if (!result)
        return (NULL);
    while (i < len)
    {
        if (str[i] != '"' && str[i] != '\'')
        {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    free(str);
    return (result);
}
