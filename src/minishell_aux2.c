/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:03:15 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 20:05:56 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_put_spaces(char *str) {
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    size_t str_len = ft_strlen(str);
    char *new_str = malloc(sizeof(char) * (str_len * 2 + 1));
    if (new_str == NULL) {
        return NULL;
    }

    while (str[i] != '\0') {
        // Toggle quote status
        if (str[i] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
            new_str[j++] = str[i++];
        } else if (str[i] == '"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
            new_str[j++] = str[i++];
        } else if (str[i + 1] != '\0' && str[i + 1] == str[i] && !in_single_quote && !in_double_quote) {
            // Add space between duplicated characters outside quotes
            new_str[j++] = str[i++];
            new_str[j++] = str[i++];
        } else if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && !in_single_quote && !in_double_quote) {
            // Add space around special characters outside quotes
            new_str[j++] = ' '; // Add space before special character
            new_str[j++] = str[i++];
            new_str[j++] = ' '; // Add space after special character
        } else {
            new_str[j++] = str[i++];
        }
    }
    
    new_str[j] = '\0'; // Null-terminate the new string

    return new_str;
}
