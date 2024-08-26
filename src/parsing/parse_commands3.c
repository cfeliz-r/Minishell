/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:57:31 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 18:10:59 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*append_char(char *result, char c, size_t *j, size_t *buffer_size)
{
	size_t	old_buffer_size;
	char	*new_result;

	if (*j >= *buffer_size - 1)
	{
		old_buffer_size = *buffer_size;
		*buffer_size *= 2;
		new_result = simple_realloc(result, old_buffer_size, *buffer_size);
		if (!new_result)
			return (free(result), NULL);
		result = new_result;
	}
	result[(*j)++] = c;
	return (result);
}

static char	*handle_variable_expansion(const char *command,
	t_parse_context *ctx, t_list_env *envp)
{
	char	key[256];
	size_t	k;
	char	*value;

	k = 0;
	while (command[ctx->i] != '\0' && (ft_isalnum(command[ctx->i])
			|| command[ctx->i] == '_') && k < sizeof(key) - 1)
		key[k++] = command[(ctx->i)++];
	key[k] = '\0';
	value = find_env_value(envp, key);
	while (value != NULL && *value != '\0')
	{
		ctx->result = append_char(ctx->result, *value++,
				&(ctx->j), &(ctx->buffer_size));
		if (!ctx->result)
			return (NULL);
	}
	return (ctx->result);
}

static char	*handle_dollar_sign(const char *command,
	t_parse_context *ctx, t_list_env *envp)
{
	char	*p;
	char	*status_str;
	int		status;

	(ctx->i)++;
	if (command[ctx->i] == '?')
	{
		(ctx->i)++;
		status = manage_error(0, 1);
		status_str = ft_itoa(status);
		if (status_str)
		{
			p = status_str;
			while (*p)
				ctx->result = append_char(ctx->result, *p++,
						&(ctx->j), &(ctx->buffer_size));
			free(status_str);
		}
	}
	else
		ctx->result = handle_variable_expansion(command, ctx, envp);
	return (ctx->result);
}

static char	*process_char(const char *command,
	t_parse_context *ctx, t_list_env *envp)
{
	if (command[ctx->i] == '"' && ctx->in_single_quotes == 0)
	{
		ctx->in_double_quotes = !ctx->in_double_quotes;
		ctx->result = append_char(ctx->result,
				command[ctx->i], &(ctx->j), &(ctx->buffer_size));
		ctx->i++;
	}
	else if (command[ctx->i] == '\'' && ctx->in_double_quotes == 0)
	{
		ctx->in_single_quotes = !ctx->in_single_quotes;
		ctx->result = append_char(ctx->result, command[ctx->i],
				&(ctx->j), &(ctx->buffer_size));
		ctx->i++;
	}
	else if (command[ctx->i] == '$' && ctx->in_single_quotes == 0)
		ctx->result = handle_dollar_sign(command, ctx, envp);
	else
	{
		ctx->result = append_char(ctx->result,
				command[(ctx->i)++], &(ctx->j), &(ctx->buffer_size));
	}
	return (ctx->result);
}

char	*interpret_command(const char *command, t_list_env *envp)
{
	t_parse_context	ctx;

	ctx.i = 0;
	ctx.j = 0;
	ctx.in_single_quotes = 0;
	ctx.in_double_quotes = 0;
	ctx.buffer_size = ft_strlen(command) * 2 + 1;
	ctx.result = malloc(ctx.buffer_size);
	if (ctx.result == NULL || command[0] == '\0')
		return (NULL);
	while (command[ctx.i] != '\0')
	{
		ctx.result = process_char(command, &ctx, envp);
		if (!ctx.result)
			return (NULL);
	}
	if (ctx.in_double_quotes || ctx.in_single_quotes)
		return (free(ctx.result), NULL);
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}
