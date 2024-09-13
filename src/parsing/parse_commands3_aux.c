/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands3_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:05:01 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/13 12:35:20 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aux_hadle_dollar(const char *command, t_parse_context *ctx)
{
	ctx->result = append_char(ctx->result, '$',
			&(ctx->j), &(ctx->buffer_size));
	while (ft_isalnum(command[ctx->i]) || command[ctx->i] == '_')
	{
		ctx->result = append_char(ctx->result,
				command[ctx->i++], &(ctx->j), &(ctx->buffer_size));
	}
	ctx->in_heredoc = 0;
}

void	aux_process(const char *command,
	t_parse_context *ctx, t_list_env *envp)
{
	if (command[ctx->i] == '\'' && ctx->in_double_quotes == 0)
	{
		ctx->in_single_quotes = !ctx->in_single_quotes;
		ctx->result = append_char(ctx->result, command[ctx->i],
				&(ctx->j), &(ctx->buffer_size));
		ctx->i++;
	}
	else if (command[ctx->i] == '$' && (command[ctx->i + 1] == ' '
			|| command[ctx->i + 1] == '\0' || command[ctx->i + 1] == '\n'
			|| command[ctx->i + 1] == '"' || command[ctx->i + 1] == '\''))
	{
		ctx->result = append_char(ctx->result, '$',
				&(ctx->j), &(ctx->buffer_size));
		ctx->i++;
	}
	else if (command[ctx->i] == '$' && ctx->in_single_quotes == 0)
		ctx->result = handle_dollar_sign(command, ctx, envp);
	else
		ctx->result = append_char(ctx->result,
				command[(ctx->i)++], &(ctx->j), &(ctx->buffer_size));
}

void	aux_split(const char *input, t_split_commands *ctx)
{
	while (input[ctx->i] != '\0')
	{
		if (input[ctx->i] == '\'' && ctx->ctx.in_double_quotes == 0)
			ctx->ctx.in_single_quotes = !ctx->ctx.in_single_quotes;
		else if (input[ctx->i] == '"' && ctx->ctx.in_single_quotes == 0)
			ctx->ctx.in_double_quotes = !ctx->ctx.in_double_quotes;
		else if (input[ctx->i] == '|' && ctx->ctx.in_single_quotes == 0
			&& ctx->ctx.in_double_quotes == 0)
		{
			ctx->current_command[ctx->j] = '\0';
			ctx->commands[ctx->cmd_idx++] = ft_strdup(ctx->current_command);
			free(ctx->current_command);
			ctx->current_command = ft_calloc(ctx->len + 1, sizeof(char));
			if (!ctx->current_command)
				return ;
			ctx->j = 0;
			ctx->i++;
			continue ;
		}
		ctx->current_command[ctx->j++] = input[ctx->i++];
	}
}
