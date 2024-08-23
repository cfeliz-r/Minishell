/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/23 13:29:42 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

 static int  ft_count(char **split_result)
{
    int i;

    i = 0;
    while(split_result[i])
        i++;
    return i;
}

static void handle_input_redirection(char *input_redirection, t_command *command)
{
    char **split_result;
    
    if(ft_strncmp(command->cmd_cpt, "echo", 4) != 0)
        *input_redirection = 0;
    input_redirection++;
    split_result = split_special(input_redirection);
    if (split_result && split_result[0])
        command->inredir = ft_strdup(split_result[0]);
    clean_up(split_result, NULL, 0);
}

static void handle_output_redirection(char *output_redirection, t_command *command)
{
    char **split_result;
    int i = 0;
    int count = 0;

    *output_redirection = 0;
    output_redirection++;
    if (*output_redirection == '>')
    {
        command->appd_out = 1;
        output_redirection++;
    }
    output_redirection = ft_strtrim(output_redirection, " ");
    split_result = split_special(output_redirection);

    if (!split_result)
        return;

    while (split_result[i] != NULL)
    {
        if (ft_strcmp(split_result[i], ">") != 0)
            count++;
        i++;
    }

    if (count > 0)
    {
        command->outredirs = malloc(sizeof(char *) * (count + 1));
        if (!command->outredirs)
        {
            clean_up(split_result, NULL, 0);
            return;
        }
    }
    i = 0;
    count = 0;
    while (split_result[i] != NULL)
    {
        if (ft_strncmp(split_result[i], ">", 1) != 0)
        {
            command->outredirs[count] = ft_strdup(split_result[i]);
            count++;
        }
        i++;
    }
    if (command->outredirs)
        command->outredirs[count] = NULL;

    clean_up(split_result, NULL, 0);
    free(output_redirection);
}


static void handle_hdoc(char *heredoc_redirection, t_command *command)
{
    char **split_result;
    int i;
    int j;

    *heredoc_redirection = 0;
    heredoc_redirection += 2;
    split_result = split_special(heredoc_redirection);
    if (!split_result)
        return; 
    command->delimiters = malloc(sizeof(char *) * (ft_count(split_result) + 1));
    if (!command->delimiters)
        return;
    i = 0;
    j = 0;
    while (split_result[i] != NULL)
    {
        if (ft_strncmp(split_result[i], "<<", 2) == 0)
        {
            i++;
            continue;
        }
        command->delimiters[j++] = ft_strdup(split_result[i++]);
    }
    command->delimiters[j] = NULL;
    clean_up(split_result, NULL, 0);
}

void process_redirections(t_command *command)
{
    char *heredoc_redirection = ft_strstr(command->cmd_cpt, "<<");
    char *input_redirection = ft_strchr(command->cmd_cpt, '<');
    char *output_redirection = ft_strchr(command->cmd_cpt, '>');

    if (heredoc_redirection != 0)
        {
            if(contains_quotes(heredoc_redirection))
                return;
            handle_hdoc(heredoc_redirection, command);
        }
    if (input_redirection != 0 && !heredoc_redirection)
        handle_input_redirection(input_redirection, command);
    if (output_redirection != 0)
        handle_output_redirection(output_redirection, command);
}
