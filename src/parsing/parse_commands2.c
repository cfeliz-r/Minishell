/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:57:46 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/05 19:14:24 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command *init_commands(char **command_strings, int num_cmds)
{
    int i;
    t_command *commands = malloc(sizeof(t_command) * num_cmds);
    if (!commands)
    {
        clean_up(command_strings, NULL, 0);
        return (manage_error(200, 0), NULL);
    }
    i = 0;
    while (i < num_cmds)
    {
        ft_memset(&commands[i], 0, sizeof(t_command));
        i++;
    }
    return commands;
}

void handle_redir(char *command_with_redirections, t_command *command)
{
    char *input_redirection = ft_strchr(command_with_redirections, '<');
    char *output_redirection = ft_strchr(command_with_redirections, '>');

    if (input_redirection)
    {
        *input_redirection = 0;
        input_redirection++;
        command->input_redirection = ft_split(input_redirection, ' ')[0];
    }
    if (output_redirection)
    {
        *output_redirection = 0;
        output_redirection++;
        if (*output_redirection == '>')
        {
            command->append_output = 1;
            output_redirection++;
        }
        command->output_redirection = ft_split(output_redirection, ' ')[0];
    }
    command->args = ft_split(command_with_redirections, ' ');
}

int validate_command(t_command *command, t_list_env *envp)
{
    command->path = find_command_path(command->args[0], envp);
    if (!command->path || access(command->path, F_OK) == -1)
    {
        command->is_correct = 1;
        ft_putstr(command->args[0]);
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
    *num_cmds = 0;
    while (command_strings[*num_cmds] != NULL)
        (*num_cmds)++;
    commands = init_commands(command_strings, *num_cmds);
    if (!commands)
        return (manage_error(200, 0), NULL);
    i = -1;
    while (++i < *num_cmds)
    {
        handle_redir(command_strings[i], &commands[i]);
        if (!validate_command(&commands[i], envp))
            return clean_up_and_return(command_strings, commands, *num_cmds);
    }
    clean_up(command_strings, NULL, 0);
    return (commands);
}
