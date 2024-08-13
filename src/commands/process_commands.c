/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:43:52 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/13 15:58:09 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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
    handle_heredoc(commands, i, num_cmds);
    if (i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (i < num_cmds - 1)
        dup2(pipes[i][1], STDOUT_FILENO);
    close_pipes(pipes, num_cmds);
    if (handle_redirections(&commands[i]) == -1)
        exit(0);  
    if (!(ft_strncmp(commands[i].cmd_complete, "echo ", 5) == 0 || 
          ft_strcmp(commands[i].cmd_complete, "echo") == 0 || 
          ft_strncmp(commands[i].cmd_complete, "env ", 4) == 0 || 
          ft_strcmp(commands[i].cmd_complete, "env") == 0 || 
          ft_strncmp(commands[i].cmd_complete, "pwd ", 4) == 0 || 
          ft_strcmp(commands[i].cmd_complete, "pwd") == 0) || 
          ft_strncmp(commands[i].cmd_complete, "cd ", 3) == 0 ||
          ft_strncmp(commands[i].cmd_complete, "cd\0", 3) == 0)
    {
        if (execve(commands[i].path, commands[i].args, env_array) == -1)
        {
            manage_error(200, 0);
            exit(1);
        }
    }
    if (build_up(&commands[i], envp) == 1)
        exit(0);
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
        if (fork() == 0)
        {
            sa_int.sa_handler = sigint_handler_ha;
            sigaction(SIGINT, &sa_int, NULL);
            child_process(commands, i, num_cmds, env_array, envp, pipes);
        }
    }
    close_pipes(pipes, num_cmds);
    i = -1;
    while(++i < num_cmds)
        waitpid(-1, NULL, 0);
    free(pipes);
    clean_up(env_array, NULL, 0);
}
