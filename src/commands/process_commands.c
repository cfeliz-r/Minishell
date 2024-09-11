/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:43:52 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/11 18:53:44 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_signal_handler(struct sigaction *sa_int)
{
	sa_int->sa_handler = sigint_handler_ha;
	sigaction(SIGINT, sa_int, NULL);
}

static int	handle_here_doc(t_cmd *command,
	int **pipes, int num_cmds, t_list_env *envp)
{
	if (command->delimiters && process_here_doc(command, envp) == -1)
	{
		close_pipes(pipes, num_cmds);
		return (-1);
	}
	return (0);
}

static pid_t	fork_and_process(t_process *ctx)
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
		child_process(ctx);
	}
	return (pid);
}

void	prepare_commands(t_cmd *commands, int num_cmds, t_list_env *envp)
{
	t_cmd_vars	vars;
	t_process	ctx;

	vars.pipes = malloc((num_cmds - 1) * sizeof(int *));
	setup_pipes(vars.pipes, num_cmds);
	vars.env_array = convert_envp_to_array(envp);
	vars.sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &vars.sa_ignore, NULL);
	vars.i = -1;
	while (++vars.i < num_cmds)
		if (handle_here_doc(&commands[vars.i], vars.pipes,
				num_cmds, envp) == -1)
			return (clean_up(vars.env_array, NULL, 0));
	vars.i = -1;
	while (++vars.i < num_cmds)
	{
		init_process(&ctx, vars.i, num_cmds, envp);
		init_process1(&ctx, commands, vars.i, vars.pipes);
		init_process2(&ctx, vars.i, num_cmds, vars.env_array);
		vars.pid = fork_and_process(&ctx);
		if (vars.i == num_cmds - 1)
			vars.pid_last = vars.pid;
	}
	manage_commands_three(commands, num_cmds, envp, &vars);
}
