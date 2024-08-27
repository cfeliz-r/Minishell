/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_aux2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:56 by manufern          #+#    #+#             */
/*   Updated: 2024/08/27 13:15:27 by cfeliz-r         ###   ########.fr       */
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
	/* t_split_context	ctx;

	init_memory(input, &ctx);
	if (!ctx.commands || !ctx.current_command)
		return (NULL);
	init_vars(&ctx);
	split_and_add_commands(input, &ctx);
	free(ctx.current_command);
	ctx.commands[ctx.cmd_idx] = NULL;
	return (ctx.commands); */

	int inSingleQuote = 0, inDoubleQuote = 0;
    int start = 0, i = 0, tokenCount = 0;
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (tokens == NULL) {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }

    while (input[i] != '\0') {
        if (input[i] == '\'' && !inDoubleQuote) {
            inSingleQuote = !inSingleQuote;
        } else if (input[i] == '\"' && !inSingleQuote) {
            inDoubleQuote = !inDoubleQuote;
        } else if (input[i] == 32 && !inSingleQuote && !inDoubleQuote) {
            if (i > start) {
                tokens[tokenCount] = malloc((i - start + 1) * sizeof(char));
                if (tokens[tokenCount] == NULL) {
                    perror("Unable to allocate memory");
                    exit(EXIT_FAILURE);
                }
                strncpy(tokens[tokenCount], input + start, i - start);
                tokens[tokenCount][i - start] = '\0';
                tokenCount++;
            }
            start = i + 1;
        }
        i++;
    }

    // Add the last token if any
    if (i > start) {
        tokens[tokenCount] = malloc((i - start + 1) * sizeof(char));
        if (tokens[tokenCount] == NULL) {
            perror("Unable to allocate memory");
            exit(EXIT_FAILURE);
        }
        strncpy(tokens[tokenCount], input + start, i - start);
        tokens[tokenCount][i - start] = '\0';
        tokenCount++;
    }

    // Null-terminate the array of tokens
    tokens[tokenCount] = NULL;

    return tokens;

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
