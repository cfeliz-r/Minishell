/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands_aux2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:47:19 by manufern          #+#    #+#             */
/*   Updated: 2024/08/24 18:02:43 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_signal_handlers(void)
{
	struct sigaction	sa_quit;

	sa_quit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static void	handle_pipes(int i, int num_cmds, int **pipes)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_pipes(pipes, num_cmds);
}
void	execute_command(t_command *command, char **env_array, t_list_env *envp)
{
	if (validate_command(command, envp) == 0)
		exit(1);
	if (execve(command->path, command->args, env_array) == -1)
	{
		manage_error(200, 0);
		exit(1);
	}
}

void	child_process(t_command *command, int i, int num_cmds, char **env_array, t_list_env *envp, int **pipes)
{
	set_signal_handlers();
	handle_pipes(i, num_cmds, pipes);
	if (handle_redirections(command) == -1)
		exit(1);
	remove_quotes_from_args(command->args);
	if (is_builtin_command(command->args[0]) == 0)
		execute_command(command, env_array, envp);
	if (build_up(command, envp) == 1)
		exit(0);
	exit(1);
}
