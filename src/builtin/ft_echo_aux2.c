/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_aux2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:56 by manufern          #+#    #+#             */
/*   Updated: 2024/08/24 13:16:55 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_command(t_split_context *ctx)
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

	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '"' && str[len - 1] == '"'))
	{
		result = malloc(len - 1);
		if (!result)
			return (NULL);
		ft_strncpy(result, str + 1, len - 2);
		result[len - 2] = '\0';
		return (result);
	}
	return (ft_strdup(str));
}
