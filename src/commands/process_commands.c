/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:43:52 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/07 14:19:58 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void setup_signals(void)
{
    struct sigaction sa_quit;
    struct sigaction sa_int;

    sa_quit.sa_handler = SIG_DFL;
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
    
    sa_int.sa_handler = sigint_handler_2;
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
}

static int setup_pipes_and_fork(int pipefd[2], pid_t *pid, int i, int num_cmds)
{
    if (i < num_cmds - 1 && pipe(pipefd) == -1)  
        return (perror("pipe"), -1);
    *pid = fork();
    if (*pid == -1)
        return (perror("fork"), -1);
    return (0);
}

static void child_process(t_command *commands, int i, int num_cmds, char **env_array)
{
    int status;
    
    setup_signals();
    if (i > 0)
        dup2(commands[i - 1].pipefd[0], STDIN_FILENO);
    if (i < num_cmds - 1)
        dup2(commands[i].pipefd[1], STDOUT_FILENO);
    close_pipes(commands, num_cmds);
    
    status = handle_redirections(&commands[i]);
    if (status == -1)
        return ;
    if (execve(commands[i].path, commands[i].args, env_array) == -1)
    {
        perror("execve");
        manage_error(200, 0);
        exit(1);
    }
}

void prepare_commands(t_command *commands, int num_cmds, t_list_env *envp)
{
    int i;
    char **env_array;

    i = -1;
    env_array = convert_envp_to_array(envp);
    while (++i < num_cmds)
    {
        if (setup_pipes_and_fork(commands[i].pipefd, &commands[i].pid, i, num_cmds) == -1)
            return ;
        if (commands[i].pid == 0)
            child_process(commands, i, num_cmds, env_array);
    }
    setup_signals();
    close_pipes(commands, num_cmds);
    i = -1;
    while (++i < num_cmds)
        waitpid(commands[i].pid, NULL, 0);
    clean_up(env_array, NULL, 0);
}
/* void prepare_commands(t_command *commands, int num_cmds, t_list_env *envp)
{
    int         i;
    char        **env_array;
    struct sigaction sa_quit;
    struct sigaction sa_int;
     
    i = 0;
    env_array = convert_envp_to_array(envp);
    while (i < num_cmds)
    {
        if (i < num_cmds - 1 && pipe(commands[i].pipefd) == -1)
        {
            perror("pipe");
            return ;
        }
        commands[i].pid = fork();
        if (commands[i].pid == -1)
        {
            perror("fork");
            return;
        }
        if (commands[i].pid == 0)
        {
        
            sa_quit.sa_handler = SIG_DFL;
            sa_quit.sa_flags = 0;
            sigaction(SIGQUIT, &sa_quit, NULL);
            if (i > 0)
                dup2(commands[i - 1].pipefd[0], STDIN_FILENO);
            if (i < num_cmds - 1)
                dup2(commands[i].pipefd[1], STDOUT_FILENO);
            close_pipes(commands, num_cmds);
            if (execve(commands[i].path, commands[i].args, env_array) == -1)
            {
                perror("execve");
                return ;
            }
        } 
        i++;
    }
    sa_int.sa_handler = sigint_handler_2;
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    close_pipes(commands, num_cmds);
    i = -1;
    while (++i < num_cmds)
        waitpid(commands[i].pid, NULL, 0);
    clean_up(env_array, NULL, 0);
} */