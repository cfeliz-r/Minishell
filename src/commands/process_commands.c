/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:43:52 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/09 13:59:10 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void setup_signal_handler(struct sigaction *sa_int)
{
	sa_int->sa_handler = sigint_handler_ha;
	sigaction(SIGINT, sa_int, NULL);
}

static int handle_here_doc(t_cmd *command, int **pipes, int num_cmds, char **env_array, t_list_env *envp)
{
	if (command->delimiters && process_here_doc(command, envp) == -1)
	{
		clean_up(env_array, NULL, num_cmds);
		close_pipes(pipes, num_cmds);
		return (-1);
	}
	return (0);
}

pid_t fork_and_process(t_cmd *commands, int i, int num_cmds, char **env_array, t_list_env *envp, int **pipes)
{
    pid_t pid = fork();
    struct sigaction sa_int;

    if (pid == 0)
    {
        sa_int.sa_handler = sigint_handler_ha;
        sa_int.sa_flags = 0;
        if (sigaction(SIGINT, &sa_int, NULL) == -1)
            exit(EXIT_FAILURE);
        setup_signal_handler(&sa_int);
        child_process(&commands[i], i, num_cmds, env_array, envp, pipes);
    }
    return pid;
}

void prepare_commands(t_cmd *commands, int num_cmds, t_list_env *envp)
{
    int **pipes;
    int i;
    char **env_array;
    struct sigaction sa_ignore;
    int status;
    pid_t pid, pid_last;

    pipes = malloc((num_cmds - 1) * sizeof(int *));
    setup_pipes(pipes, num_cmds);
    env_array = convert_envp_to_array(envp);
    sa_ignore.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa_ignore, NULL);
    i = -1;
    while (++i < num_cmds)
        if (handle_here_doc(&commands[i], pipes, num_cmds, env_array, envp) == -1)
            return;
    i = -1;
    while (++i < num_cmds)
    {
        pid = fork_and_process(commands, i, num_cmds, env_array, envp, pipes);
        if (i == num_cmds - 1)
            pid_last = pid;
    }
    close_pipes(pipes, num_cmds);
    i = -1;
    while (++i < num_cmds)
    {
        pid = waitpid(-1, &status, 0);

        if (pid == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (pid == pid_last)
        {
            if (WIFEXITED(status))
                g_exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                g_exit_status = 128 + WTERMSIG(status);
        }
    }
    if(num_cmds == 1)
    {
        handle_export(&commands[0], envp);
        handle_cd(&commands[0], envp);
        handle_unset(&commands[0], envp);  
    }
    clean_up(env_array, NULL, 0);
}   