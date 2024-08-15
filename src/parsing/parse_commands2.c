/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:57:46 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/15 13:43:15 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Función para manejar las comillas y hacer split en los pipes
static char **split_commands(const char *input) {
    size_t len = strlen(input);
    char **commands = malloc(sizeof(char *) * (len + 1)); // Asignar espacio para los comandos
    char *current_command = calloc(len + 1, sizeof(char));
    t_quote_context ctx = {0, 0};
    size_t i = 0, j = 0, cmd_idx = 0;

    if (!commands || !current_command)
        return NULL;

    while (input[i]) {
        if (input[i] == '\'' && ctx.in_double_quotes == 0)
            ctx.in_single_quotes = !ctx.in_single_quotes;
        else if (input[i] == '"' && ctx.in_single_quotes == 0)
            ctx.in_double_quotes = !ctx.in_double_quotes;
        else if (input[i] == '|' && ctx.in_single_quotes == 0 && ctx.in_double_quotes == 0) {
            // Encontramos un pipe fuera de comillas, cortar comando
            current_command[j] = '\0';
            commands[cmd_idx++] = strdup(current_command);
            free(current_command);
            current_command = calloc(len + 1, sizeof(char));
            j = 0;
            i++;
            continue;
        }
        current_command[j++] = input[i++];
    }

    if (j > 0) {
        current_command[j] = '\0';
        commands[cmd_idx++] = strdup(current_command);
    }
    
    free(current_command);
    commands[cmd_idx] = NULL;
    return commands;
}

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
t_command *parse_commands(char *input, t_list_env *envp, int *num_cmds) {
    char        **command_strings;
    t_command   *commands;
    int         i;

    // Primero manejar redirecciones y expansión de variables
    char *aux = ft_redir_cmd(input, envp);
    
    // Luego usar nuestra nueva función split_commands
    command_strings = split_commands(aux);
    free(aux);

    if (!command_strings || command_strings[0] == NULL)
        return (manage_error(200, 0), free(command_strings), NULL);

    *num_cmds = 0;
    while (command_strings[*num_cmds] != NULL)
        (*num_cmds)++;
    commands = init_commands(command_strings, *num_cmds);

    i = -1;
    while (++i < *num_cmds) {
        if (commands[i].is_correct)
            continue;
        handle_key_redir(command_strings[i], &commands[i]);
        if (!validate_command(&commands[i], envp))
            return (clean_up_and_return(command_strings, commands, *num_cmds));
    }

    clean_up(command_strings, NULL, 0);
    return (commands);
}
