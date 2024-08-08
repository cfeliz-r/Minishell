/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:57:46 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/08 17:14:39 by manufern         ###   ########.fr       */
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

void handle_redir(char *command_with_redirections, t_command *command) {
    char *input_redirection = NULL;
    char *output_redirection = NULL;
    char **split_result = NULL;
    int i = 0;

    if (!command_with_redirections || !command) {
        // Manejo de punteros nulos
        fprintf(stderr, "Error: Null pointer passed to handle_redir.\n");
        return;
    }

    // Manejo de redirección de entrada
    input_redirection = ft_strchr(command_with_redirections, '<');
    output_redirection = ft_strchr(command_with_redirections, '>');
    
    if (input_redirection) {
        *input_redirection = '\0';  // Termina la cadena antes del símbolo '<'
        input_redirection++;  // Avanza el puntero después del símbolo '<'
        split_result = ft_split(input_redirection, ' ');

        if (split_result) {
            while (split_result[i]) i++;
            if (i > 1) {
                // Más de un argumento tras la redirección
                fprintf(stderr, "Error: Too many arguments after '<'.\n");
                clean_up(split_result, NULL, 0);
                return;
            } else if (i == 1) {
                command->input_redirection = strdup(split_result[0]);
            }
            clean_up(split_result, NULL, 0);
        } else {
            fprintf(stderr, "Error: Failed to split input redirection.\n");
        }
    }

    // Manejo de redirección de salida
    if (output_redirection) {
        *output_redirection = '\0';  // Termina la cadena antes del símbolo '>'
        output_redirection++;  // Avanza el puntero después del símbolo '>'
        
        if (*output_redirection == '>') {
            command->append_output = 1;
            output_redirection++;
        }

        split_result = ft_split(output_redirection, ' ');
        
        if (split_result) {
            if (split_result[0]) {
                command->output_redirection = strdup(split_result[0]);
            }
            clean_up(split_result, NULL, 0);
        } else {
            fprintf(stderr, "Error: Failed to split output redirection.\n");
        }
    }

    command->args = ft_split(command_with_redirections, ' ');
}


int validate_command(t_command *command, t_list_env *envp)
{
    command->path = find_command_path(command->args[0], envp);
    if (!command->path)
    {
        command->is_correct = 1;
        if (ft_strncmp(command->cmd_complete, "echo ", 5) == 0 || ft_strcmp(command->cmd_complete, "echo") == 0 || ft_strncmp(command->cmd_complete, "env ", 4) == 0 || ft_strcmp(command->cmd_complete, "env")== 0 || ft_strncmp(command->cmd_complete, "pwd ", 4) == 0 || ft_strcmp(command->cmd_complete, "pwd" ) == 0 || ft_strncmp(command->cmd_complete, "export", 6) == 0)
            return (1);
        ft_putstr(command->args[0]);
        ft_putstr_fd(": Command not found\n", 2);
        if(command->path)
            free(command->path);
        return 0;
    }
    return (1);
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
        handle_redir(command_strings[i], &commands[i]);
        if (!validate_command(&commands[i], envp))
            return clean_up_and_return(command_strings, commands, *num_cmds);
    }
    clean_up(command_strings, NULL, 0);
    return (commands);
}
