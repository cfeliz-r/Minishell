/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:13:40 by manufern          #+#    #+#             */
/*   Updated: 2024/08/20 18:47:06 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_up_echo(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

int	is_n_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0' && i != 1)
			return (1);
	}
	return (0);
}

void	init_memory(const char *input, t_split_context *ctx)
{
	ctx->len = ft_strlen(input);
	ctx->commands = malloc(sizeof(char *) * (ctx->len + 1));
	ctx->current_command = ft_calloc(ctx->len + 1, sizeof(char));
	if (!ctx->commands || !ctx->current_command)
	{
		free(ctx->commands);
		free(ctx->current_command);
		ctx->commands = NULL;
		ctx->current_command = NULL;
	}
}

void	handle_quotes_and_spaces(const char *input, t_split_context *ctx)
{
	if (input[ctx->i] == '\'' && !ctx->in_double_quotes)
		ctx->in_single_quotes = !ctx->in_single_quotes;
	else if (input[ctx->i] == '"' && !ctx->in_single_quotes)
		ctx->in_double_quotes = !ctx->in_double_quotes;
}

int	is_separator(const char *input, t_split_context *ctx)
{
	return (input[ctx->i] == ' '
		&& !ctx->in_single_quotes && !ctx->in_double_quotes);
}
