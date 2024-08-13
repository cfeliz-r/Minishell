/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:57:46 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/13 19:48:35 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command *init_commands(char **command_strings, int num_cmds)
{
    int i;
    t_command *commands;

    commands = malloc(sizeof(t_command) * num_cmds);
    if (!commands || num_cmds == 0)
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
void handle_key_redir(char *command_with_redirections, t_command *command)
{
    process_redirections(command_with_redirections, command);

    if (command->is_correct == 0)
    {
        command->args = ft_split(command_with_redirections, ' ');
        if (!command->args || !command->args[0])
        {
            ft_putstr_fd("minishell: invalid argument\n", 2);
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
    char        **command_strings;
    t_command   *commands;
    char        *aux;
    int         i;

    aux = ft_redir_cmd(input, envp);
    command_strings = ft_split(aux, '|');
    if (!command_strings || command_strings[0] == NULL)
        return (manage_error(200, 0), free(aux), free(command_strings), NULL);
    free(aux);
    *num_cmds = 0;
    while (command_strings[*num_cmds] != NULL)
        (*num_cmds)++;
    commands = init_commands(command_strings, *num_cmds);
    i = -1;
    while (++i < *num_cmds)
    {
         if (commands[i].is_correct)
            continue;
        handle_key_redir(command_strings[i], &commands[i]);
        if (!validate_command(&commands[i], envp))
            return (clean_up_and_return(command_strings, commands, *num_cmds));
    }
    clean_up(command_strings, NULL, 0);
    return (commands);
}
