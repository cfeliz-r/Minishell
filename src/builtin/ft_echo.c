/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:47:30 by manufern          #+#    #+#             */
/*   Updated: 2024/09/05 11:57:48 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_parts(char **str, int start_index, int *first_part)
{
	char	*part;

	while (str[start_index] != NULL)
	{
		if ((str[start_index][0] == '<' && !(str[start_index][0] == '<'))
			|| str[start_index][0] == '>')
		{
			start_index = start_index + 2;
			continue ;
		}
		part = strip_quotes(str[start_index]);
		if (part)
		{
			if (!*first_part)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, part, ft_strlen(part));
			free(part);
			*first_part = 0;
		}
		start_index++;
	}
}

void	handle_n_option(char **str, int *n_option)
{
	int	i;

	i = 0;
	while (str[i] && is_n_option(str[i]))
	{
		*n_option = 1;
		i++;
	}
}

char *remove_quotes_echo(const char *command)
{
    size_t i;
    size_t j;
    size_t len;
    char *result;
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (!command)
        return NULL;

    len = strlen(command);
    result = malloc(len + 1);
    if (!result)
        return NULL;

    i = 0;
    j = 0;
    while (i < len)
    {
        if (command[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            i++;
        }
        else if (command[i] == '\"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            i++;
        }
        else
        {
            result[j++] = command[i++];
        }
    }

    result[j] = '\0';
    return result;
}

void	ft_echo(char *command)
{
	char	**str;
	int		n_option;
	int		start_index;
	int		first_part;

	n_option = 0;
	if (ft_strlen(command) >= 5)
	{
		str = split_special(command + 5);
		if (!str)
			return ;
		handle_n_option(str, &n_option);
		start_index = 0;
		first_part = 1;
		print_parts(str, start_index, &first_part);
		if (!n_option)
			write(STDOUT_FILENO, "\n", 1);
		clean_up_echo(str);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
}
