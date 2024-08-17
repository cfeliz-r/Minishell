/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:43:52 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/17 15:18:22 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_builtin_command(char *cmd)
{
    if (ft_strncmp(cmd, "echo ", 5) == 0 ||
        ft_strcmp(cmd, "\"echo\"") == 0 ||
        ft_strcmp(cmd, "'echo'") == 0 ||
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strncmp(cmd, "env ", 4) == 0 ||
        ft_strcmp(cmd, "\"env\"") == 0 ||
        ft_strcmp(cmd, "'env'") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strncmp(cmd, "pwd ", 4) == 0 ||
        ft_strcmp(cmd, "\"pwd\"") == 0 ||
        ft_strcmp(cmd, "'pwd'") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strncmp(cmd, "cd ", 3) == 0 ||
        ft_strcmp(cmd, "\"cd\"") == 0 ||
        ft_strcmp(cmd, "'cd'") == 0 ||
        ft_strcmp(cmd, "cd") == 0)
    {
        return 1;
    }
    return 0;
}
char *remove_quotes(char *str)
{
    char *result;
    int i, j;

    result = malloc(strlen(str) + 1);
    if (!result)
        return NULL;
    
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '"')
        {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    return result;
}

void remove_quotes_from_args(char **args)
{
    int i;
    char *new_arg;

    i = 0;
    while (args[i])
    {
        new_arg = remove_quotes(args[i]);
        if (new_arg)
        {
            free(args[i]);
            args[i] = new_arg;
        }
        i++;
    }
}


static void setup_pipes(int **pipes, int num_cmds)
{
    int i;

    i = -1;
    while (++i < num_cmds - 1)
    {
        pipes[i] = malloc(2 * sizeof(int));
        if (pipes[i] == NULL || pipe(pipes[i]) == -1)
        {
            perror("Error pipe");
            return;
        }
    }
}
static void child_process(t_command *commands, int i, int num_cmds, char **env_array, t_list_env *envp, int **pipes)
{
    struct sigaction sa_quit;

    sa_quit.sa_handler = SIG_DFL;
    sigaction(SIGQUIT, &sa_quit, NULL);
    if (i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (i < num_cmds - 1)
        dup2(pipes[i][1], STDOUT_FILENO);
    close_pipes(pipes, num_cmds);
    if(handle_redirections(&commands[i]) == -1)
        exit(1);
    remove_quotes_from_args(commands[i].args);
    if (is_builtin_command(commands[i].cmd_complete) == 0)
    {
        if (validate_command(&commands[i], envp) == 0)
            exit(1);
        if (execve(commands[i].path, commands[i].args, env_array) == -1)
        {
            manage_error(200, 0);
            exit(1);
        }
    }
    if (build_up(&commands[i], envp) == 1)
        exit(0);
    exit(1);
}

void prepare_commands(t_command *commands, int num_cmds, t_list_env *envp)
{
    int **pipes;
    int i;
    char **env_array;
    struct sigaction sa_int;

    pipes = malloc((num_cmds - 1) * sizeof(int *));
    setup_pipes(pipes, num_cmds);
    env_array = convert_envp_to_array(envp);
    sa_int.sa_handler = sigint_handler_2;
    sigaction(SIGINT, &sa_int, NULL);
    i = -1;
    while (++i < num_cmds)
    {
         if (commands[i].heredoc_delimiters)
        {
            if (process_here_doc(&commands[i]) == -1)
            {
                close_pipes(pipes, num_cmds);
                clean_up(env_array, NULL, 0);
                return;
            }
        }
        if (fork() == 0)
        {
            sa_int.sa_handler = sigint_handler_ha;
            sigaction(SIGINT, &sa_int, NULL);
            child_process(commands, i, num_cmds, env_array, envp, pipes);
        }
    }

    close_pipes(pipes, num_cmds);
    i = -1;
    while (++i < num_cmds)
        waitpid(-1, NULL, 0);
    handle_cd(commands);
    free(pipes);
    clean_up(env_array, NULL, 0);
}

