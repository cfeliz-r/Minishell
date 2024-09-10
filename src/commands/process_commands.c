/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:43:52 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/10 10:11:52 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_signal_handler(struct sigaction *sa_int)
{
	sa_int->sa_handler = sigint_handler_ha;
	sigaction(SIGINT, sa_int, NULL);
}

static int	handle_here_doc(t_cmd *command,
	int **pipes, int num_cmds, char **env_array, t_list_env *envp)
{
	if (command->delimiters && process_here_doc(command, envp) == -1)
	{
		clean_up(env_array, NULL, num_cmds);
		close_pipes(pipes, num_cmds);
		return (-1);
	}
	return (0);
}

pid_t	fork_and_process(t_cmd *commands, int i,
	int num_cmds, char **env_array, t_list_env *envp, int **pipes)
{
	pid_t				pid;
	struct sigaction	sa_int;

	pid = fork();
	if (pid == 0)
	{
		sa_int.sa_handler = sigint_handler_ha;
		sa_int.sa_flags = 0;
		if (sigaction(SIGINT, &sa_int, NULL) == -1)
			exit(EXIT_FAILURE);
		setup_signal_handler(&sa_int);
		child_process(&commands[i], i, num_cmds, env_array, envp, pipes);
	}
	return (pid);
}

void	prepare_commands(t_cmd *commands, int num_cmds, t_list_env *envp)
{
	t_cmd_vars	vars;

	vars.pipes = malloc((num_cmds - 1) * sizeof(int *));
	setup_pipes(vars.pipes, num_cmds);
	vars.env_array = convert_envp_to_array(envp);
	vars.sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &vars.sa_ignore, NULL);
	vars.i = -1;
	while (++vars.i < num_cmds)
		if (handle_here_doc(&commands[vars.i], vars.pipes,
				num_cmds, vars.env_array, envp) == -1)
			return ;
	vars.i = -1;
	while (++vars.i < num_cmds)
	{
		vars.pid = fork_and_process(commands, vars.i,
				num_cmds, vars.env_array, envp, vars.pipes);
		if (vars.i == num_cmds - 1)
			vars.pid_last = vars.pid;
	}
	close_pipes(vars.pipes, num_cmds);
	vars.i = -1;
	while (++vars.i < num_cmds)
	{
		vars.pid = waitpid(-1, &vars.status, 0);
		if (vars.pid == vars.pid_last)
		{
			if (WIFEXITED(vars.status))
				vars.exit_status = WEXITSTATUS(vars.status);
			else if (WIFSIGNALED(vars.status))
				vars.exit_status = 128 + WTERMSIG(vars.status);
			manage_error(vars.exit_status, 0);
		}
	}
	if (num_cmds == 1)
	{
		handle_export(&commands[0], envp);
		handle_cd(&commands[0], envp);
		handle_unset(&commands[0], envp);
	}
	clean_up(vars.env_array, NULL, 0);
}
