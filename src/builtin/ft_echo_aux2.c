/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_aux2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:56 by manufern          #+#    #+#             */
/*   Updated: 2024/09/11 13:20:39 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_command(t_split_context *ctx)
{
	if (ctx->j > 0)
	{
		ctx->current_command[ctx->j] = '\0';
		ctx->commands[ctx->cmd_idx] = ft_strdup(ctx->current_command);
		ctx->cmd_idx++;
		ctx->j = 0;
	}
}

void	init_vars(t_split_context *ctx)
{
	ctx->i = 0;
	ctx->j = 0;
	ctx->cmd_idx = 0;
	ctx->in_single_quotes = 0;
	ctx->in_double_quotes = 0;
}

void	split_and_add_commands(const char *input, t_split_context *ctx)
{
	while (input[ctx->i] != '\0')
	{
		handle_quotes_and_spaces(input, ctx);
		if (is_separator(input, ctx))
			add_command(ctx);
		else
		{
			ctx->current_command[ctx->j] = input[ctx->i];
			ctx->j++;
		}
		ctx->i++;
	}
	add_command(ctx);
}

char	**split_special(const char *input)
{
	t_split_context	ctx;

	init_memory(input, &ctx);
	if (!ctx.commands || !ctx.current_command)
		return (NULL);
	init_vars(&ctx);
	split_and_add_commands(input, &ctx);
	free(ctx.current_command);
	ctx.commands[ctx.cmd_idx] = NULL;
	return (ctx.commands);
}

char	*strip_quotes(char *str)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;
	char	current_quote;

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	current_quote = '\0';
	while (i < len)
	{
		if ((str[i] == '\'' || str[i] == '"') && current_quote == '\0')
			current_quote = str[i];
		else if (str[i] == current_quote)
			current_quote = '\0';
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
