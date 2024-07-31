/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.your42network.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 00:54:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/28 00:54:56 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command *parse_commands(char *input, t_list_env *envp, int *num_cmds)
{
    char        **command_strings;
    t_command   *commands;
    int         i;
    command_strings = ft_split(input, '|');
    if (!command_strings)
        return NULL;
    *num_cmds = 0;
    while (command_strings[*num_cmds] != NULL)
            (*num_cmds)++;

    commands = malloc(sizeof(t_command) * (*num_cmds));
    if (!commands)
    {
        clean_up(command_strings, NULL);
        return NULL;
    }
    i = 0;
    while (i < *num_cmds)
    {
        commands[i].args = ft_split(command_strings[i], ' ');
        commands[i].path = find_command_path(commands[i].args[0], envp);
        if(commands[i].path == NULL || access(commands[i].path, F_OK) == -1)
        {   
            free(commands[i].path);
            free(commands[i].args);
            free(commands);
            clean_up(command_strings, NULL);
            return NULL;
        }
        commands[i].pid = -1;
        commands[i].pipefd[0] = -1;
        commands[i].pipefd[1] = -1;
        if (!commands[i].args || !commands[i].path)
        {
            ft_putstr(command_strings[i]);
            ft_putstr_fd(": Command not found\n", 2);
            clean_up(command_strings, NULL);
            free(commands);
            return NULL;
        }
    i++;
    }
    clean_up(command_strings, NULL);
    return commands;
}
