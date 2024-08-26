/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:43:52 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/26 11:59:37 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_signal_handler(struct sigaction *sa_int)
{
	sa_int->sa_handler = sigint_handler_2;
	sigaction(SIGINT, sa_int, NULL);
}

static int	handle_here_doc(t_command *command, int **pipes, int num_cmds, char **env_array)
{
	if (command->delimiters && process_here_doc(command) == -1)
	{
		clean_up(env_array, command, num_cmds);
		close_pipes(pipes, num_cmds);
		return (-1);
	}
	return (0);
}

void	fork_and_process(t_command *commands, int i,
	int num_cmds, char **env_array, t_list_env *envp,
		int **pipes, struct sigaction *sa_int)
{
	if (fork() == 0)
	{
		sa_int->sa_handler = sigint_handler_ha;
		sigaction(SIGINT, sa_int, NULL);
		child_process(&commands[i], i, num_cmds, env_array, envp, pipes);
	}
}

void	prepare_commands(t_command *commands, int num_cmds, t_list_env *envp)
{
	int					**pipes;
	int					i;
	char				**env_array;
	struct sigaction	sa_int;

	ft_bzero(&sa_int, sizeof(sa_int));
	pipes = malloc((num_cmds - 1) * sizeof(int *));
	setup_pipes(pipes, num_cmds);
	env_array = convert_envp_to_array(envp);
	setup_signal_handler(&sa_int);
	i = -1;
	while (++i < num_cmds)
	{
		if (handle_here_doc(&commands[i], pipes, num_cmds, env_array) == -1)
			return ;
		fork_and_process(commands, i, num_cmds,
			env_array, envp, pipes, &sa_int);
	}
	close_pipes(pipes, num_cmds);
	i = -1;
	while (++i < num_cmds)
		waitpid(-1, NULL, 0);
	handle_cd(commands);
	free(pipes);
	clean_up(env_array, NULL, 0);
}
