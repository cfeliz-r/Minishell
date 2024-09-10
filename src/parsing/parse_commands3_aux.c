/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands3_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:05:01 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/10 12:16:35 by cfeliz-r         ###   ########.fr       */
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

void	aux_process_char(const char *command,
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
			|| command[ctx->i + 1] == '\0' || command[ctx->i + 1] == '\n'))
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
