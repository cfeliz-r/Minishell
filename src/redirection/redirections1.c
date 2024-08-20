/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/20 11:55:54 by manufern         ###   ########.fr       */
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

 static int  ft_count(char **split_result)
{
    int i;

    i = 0;
    while(split_result[i])
        i++;
    return i;
}
static void handle_hdoc(char *heredoc_redirection, t_command *command)
{
    char **split_result;
    int i;
    int j;

    *heredoc_redirection = 0;
    heredoc_redirection += 2;
    split_result = ft_split(heredoc_redirection, ' ');
    if(!split_result)
        return;
    command->delimiters = malloc(sizeof(char *) * (ft_count(split_result) + 1));
    if (!command->delimiters)
        return;
    i = 0;
    j = 0;
    while(split_result[i])
    {
        if(ft_strncmp(split_result[i], "<<", 2) == 0)
        {
            i++;
            continue;
        }
        command->delimiters[j++] = ft_strdup(split_result[i++]);
    }
    command->delimiters[j] = NULL;
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
