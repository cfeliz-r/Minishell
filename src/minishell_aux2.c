/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:15 by manufern          #+#    #+#             */
/*   Updated: 2024/09/05 12:07:27 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_put_spaces(char *str)
{
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    size_t str_len = ft_strlen(str);
    char *new_str = malloc(sizeof(char) * (str_len * 2 + 2));
    if (new_str == NULL)
        return NULL;
    while (str[i] != '\0')
    {
        if (str[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            new_str[j++] = str[i++];
        }
        else if (str[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            new_str[j++] = str[i++];
        }
        else if (str[i + 1] != '\0' &&
        ((str[i] == '<' && str[i + 1] == '<') || 
         (str[i] == '>' && str[i + 1] == '>') || 
         (str[i] == '<' && str[i + 1] == '>') || 
         (str[i] == '>' && str[i + 1] == '<')) &&
        !in_single_quote && !in_double_quote)
        {
            if (str[i] != ' ')
                new_str[j++] = ' ';
            new_str[j++] = str[i++];
            new_str[j++] = str[i++];
            if (str[i] != ' ')
                new_str[j++] = ' ';
        }
        else if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && !in_single_quote && !in_double_quote)
        {
            if(str[i] != ' ')
                new_str[j++] = ' ';
            new_str[j++] = str[i++];
            if(str[i] != ' ')
                new_str[j++] = ' ';
        }
        else
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    printf("new_str: %s\n", new_str);
    return new_str;
}
