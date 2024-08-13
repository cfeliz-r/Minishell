/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/13 17:33:37 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_input_redirection(char *input_redirection, t_command *command)
{
    char **split_result;

    *input_redirection = 0;
    input_redirection++;
    if (*input_redirection == '\0')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        command->is_correct = 1;
        return;
    }
    split_result = ft_split(input_redirection, ' ');
    if (split_result && split_result[0])
        command->input_redirection = ft_strdup(split_result[0]);
    else
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        command->is_correct = 1;
    }
    clean_up(split_result, NULL, 0);
}
void handle_output_redirection(char *output_redirection, t_command *command)
{
    char **split_result;

    *output_redirection = 0;
    output_redirection++;
    if (*output_redirection == '\0')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        command->is_correct = 1;
        return;
    }
    if (*output_redirection == '>')
    {
        command->append_output = 1;
        output_redirection++;
    }
    split_result = ft_split(output_redirection, ' ');
    if (split_result && split_result[0])
        command->output_redirection = ft_strdup(split_result[0]);
    clean_up(split_result, NULL, 0);
}
void handle_hdoc(char *heredoc_redirection, t_command *command)
{
    char **split_result;

    *heredoc_redirection = 0;
    heredoc_redirection += 2;
    if (*heredoc_redirection == '\0')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        command->is_correct = 1;
        return;
    }
    split_result = ft_split(heredoc_redirection, ' ');
    if (split_result && split_result[0])
        command->heredoc_delimiter = ft_strdup(split_result[0]);
    else
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        command->is_correct = 1;
    }
    clean_up(split_result, NULL, 0);
}

void process_redirections(char *command_with_redirections, t_command *command)
{
    char *heredoc_redirection = ft_strstr(command_with_redirections, "<<");
    char *input_redirection = ft_strchr(command_with_redirections, '<');
    char *output_redirection = ft_strchr(command_with_redirections, '>');

    if (heredoc_redirection)
        handle_hdoc(heredoc_redirection, command);
    if (input_redirection)
        handle_input_redirection(input_redirection, command);
    if (output_redirection)
        handle_output_redirection(output_redirection, command);
}
