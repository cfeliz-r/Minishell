/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:01:01 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/26 12:34:34 by cfeliz-r         ###   ########.fr       */
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
char *safe_strjoin_free(char *s1, const char *s2)
{
    char *new_str;
    char *temp;

    if (!s1 || !s2)
        return NULL;
    temp = s1;
    new_str = ft_strjoin(s1, (char *)s2);

    if (!new_str)
    {
        free(temp);
        return NULL;
    }
    free(temp);
    return new_str;
}
