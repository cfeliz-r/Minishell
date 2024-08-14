/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:04:40 by manufern          #+#    #+#             */
/*   Updated: 2024/08/14 12:41:31 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void remove_env_var_unset(t_list_env **envp, char *var)
{
    t_list_env   *current;
    t_list_env   *previous;
    t_list_env   *temp;

    current = *envp;
    previous = NULL;
    while (current)
    {
        if (ft_strncmp(current->envp_content, var, ft_strlen(var)) == 0 &&
            current->envp_content[ft_strlen(var)] == '=')
        {
            if (previous == NULL)
                *envp = current->next;
            else
                previous->next = current->next;
            temp = current;
            current = current->next;
            free(temp->envp_content);
            free(temp);
            return;
        }
        previous = current;
        current = current->next;
    }
}

static void process_command_unset(t_list_env **envp, char **command)
{
    int i;

    i = 1;
    while (command[i])
    {
        
        remove_env_var_unset(envp, command[i]);
        i++;
    }
}

void ft_unset(char *input, t_list_env **envp)
{
    char **command;

    if (!input || !envp || !*envp)
        return;
    command = ft_split(input, ' ');
    if (!command)
        return;
    process_command_unset(envp, command);
    clean_up(command, NULL, 0);
}
