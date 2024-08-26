/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:15 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 16:27:52 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_put_spaces(char *str)
{
    int i = 0;
    int j = 0;
    char *new_str = malloc(sizeof(char) * (ft_strlen(str) * 2 + 1));
    if (!new_str)
        return NULL;
    while (str[i] != '\0')
    {
        if (str[i + 1] != '\0' && str[i + 1] == str[i])
        {
            new_str[j++] = ' ';
            new_str[j++] = str[i++];
            new_str[j++] = str[i++];
            new_str[j++] = ' ';
        }
        else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
        {
            new_str[j++] = ' ';
            new_str[j++] = str[i++];
            new_str[j++] = ' ';
        }
        else
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    return new_str;
}
