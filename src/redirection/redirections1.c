/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/17 17:19:48 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void handle_input_redirection(char *input_redirection, t_command *command)
{
    char **split_result;

    *input_redirection = 0;
    input_redirection++;
    split_result = ft_split(input_redirection, ' ');
    if (split_result && split_result[0])
        command->inredir = ft_strdup(split_result[0]);
    clean_up(split_result, NULL, 0);
}
static void handle_output_redirection(char *output_redirection, t_command *command)
{
    char **split_result;

    *output_redirection = 0;
    output_redirection++;
    if (*output_redirection == '>')
    {
        command->appd_out = 1;
        output_redirection++;
    }
    split_result = ft_split(output_redirection, ' ');
    if (split_result && split_result[0])
        command->outredir = ft_strdup(split_result[0]);
    clean_up(split_result, NULL, 0);
}
static void handle_hdoc(char *heredoc_redirection, t_command *command)
{
    char **split_result;
    int i;

    *heredoc_redirection = 0;
    heredoc_redirection += 2;
    split_result = ft_split(heredoc_redirection, ' ');
    if (!split_result)
        return;
    i = 0;
    while(split_result[i])
         i++;
    command->delimiters = malloc(sizeof(char *) * (i + 1));
    if (!command->delimiters)
    {
        command->is_correct = 1;
        clean_up(split_result, NULL, 0);
        return;
    }
    i = -1;
    while(split_result[++i])
        command->delimiters[i] = ft_strdup(split_result[i]);
    
    command->delimiters[i] = NULL;
    clean_up(split_result, NULL, 0);
}

void process_redirections(char *command_with_redirections, t_command *command)
{
    char *heredoc_redirection = ft_strstr(command_with_redirections, "<<");
    char *input_redirection = ft_strchr(command_with_redirections, '<');
    char *output_redirection = ft_strchr(command_with_redirections, '>');

    if (heredoc_redirection)
        handle_hdoc(heredoc_redirection, command);
    if (input_redirection && !heredoc_redirection)
        handle_input_redirection(input_redirection, command);
    if (output_redirection)
        handle_output_redirection(output_redirection, command);
}
