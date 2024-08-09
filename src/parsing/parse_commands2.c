/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:57:46 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/09 11:25:08 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command *init_commands(char **command_strings, int num_cmds)
{
    int i;
    t_command *commands;

    commands = malloc(sizeof(t_command) * num_cmds);
    if (!commands)
    {
        clean_up(command_strings, NULL, 0);
        return (manage_error(200, 0), NULL);
    }
    i = 0;
    while (i < num_cmds)
    {
        ft_memset(&commands[i], 0, sizeof(t_command));
        commands[i].cmd_complete = ft_strdup(remove_front_and_back_spaces(command_strings[i]));
        i++;
    }      
    return (commands);
}

void handle_redir(char *command_with_redirections, t_command *command)
{
    char *input_redirection;
    char *output_redirection;
    char **split_result;

    input_redirection = ft_strchr(command_with_redirections, '<');
    output_redirection = ft_strchr(command_with_redirections, '>');
    if (input_redirection)
    {
        *input_redirection = 0;
        input_redirection++;
        if (*input_redirection == '\0')
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            command->is_correct = 1;
        }
        else
        {
            split_result = ft_split(input_redirection, ' ');
            if (split_result && split_result[0])
            {
                command->input_redirection = strdup(split_result[0]);
            }
            else
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
                command->is_correct = 1;
            }
            clean_up(split_result, NULL, 0);
        }
    }
    if (output_redirection)
    {
        *output_redirection = 0;
        output_redirection++;
        if (*output_redirection == '\0')
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            command->is_correct = 1;
        }
        else
        {
            if (*output_redirection == '>')
            {
                command->append_output = 1;
                output_redirection++;
            }
            split_result = ft_split(output_redirection, ' ');
            if (split_result && split_result[0])
            {
                command->output_redirection = strdup(split_result[0]);
            }
            clean_up(split_result, NULL, 0);
        }
    }
    if (command->is_correct == 0)
    {
        command->args = ft_split(command_with_redirections, ' ');
        if (!command->args || !command->args[0])
        {
            ft_putstr_fd("minishell: invalid command after redirection\n", 2);
            command->is_correct = 1;
        }
    }
}

int validate_command(t_command *command, t_list_env *envp)
{
    if (!command->args || !command->args[0])
    {
        command->is_correct = 1;
        return 0;
    }

    command->path = find_command_path(command->args[0], envp);
    if (!command->path)
    {
        command->is_correct = 1;
        ft_putstr_fd(command->args[0], 2);
        ft_putstr_fd(": Command not found\n", 2);
        return 0;
    }
    return 1;
}


t_command *clean_up_and_return(char **command_strings, t_command *commands, int num_cmds)
{
    int i = 0;
    while (i < num_cmds)
    {
        free_command(&commands[i]);
        i++;
    }
    free(commands);
    clean_up(command_strings, NULL, 0);
    return (manage_error(127, 0), NULL);
}
t_command *parse_commands(char *input, t_list_env *envp, int *num_cmds)
{
    char **command_strings;
    t_command *commands;
    char *aux;
    int i;

    aux = ft_redir_cmd(input, envp);
    command_strings = ft_split(aux, '|');
    if (!command_strings)
        return (manage_error(200, 0), NULL);
    free(aux);
    *num_cmds = 0;
    while (command_strings[*num_cmds] != NULL)
        (*num_cmds)++;
    commands = init_commands(command_strings, *num_cmds);
    if (!commands)
    {
        clean_up(command_strings, NULL, 0);
        return (manage_error(200, 0), NULL);
    }
    i = -1;
    while (++i < *num_cmds)
    {
         if (commands[i].is_correct)
            continue;
        handle_redir(command_strings[i], &commands[i]);
        if (!validate_command(&commands[i], envp))
            return clean_up_and_return(command_strings, commands, *num_cmds);
    }
    clean_up(command_strings, NULL, 0);
    return (commands);
}
