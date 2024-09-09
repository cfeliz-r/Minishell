/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands_aux2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:47:19 by manufern          #+#    #+#             */
/*   Updated: 2024/09/09 17:27:13 by cfeliz-r         ###   ########.fr       */
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
void execute_command(t_cmd *command, char **env_array, t_list_env *envp)
{
    if (validate_command(command, envp) == 0)
		exit(127);
    else if (execve(command->path, command->args, env_array) == -1)
        exit(0);
}

int	ft_exit_command(char *exits)
{
	exit (ft_atoi(exits));
}

void	child_process(t_cmd *command, int i, int num_cmds, char **env_array, t_list_env *envp, int **pipes)
{
	int	j;
	
	set_signal_handlers();
	handle_pipes(i, num_cmds, pipes);
	if (handle_redirections(command) == -1)
		exit(1);
	remove_quotes_from_args(command->args);
	if (is_builtin_command(command->args[0]) == 0)
		execute_command(command, env_array, envp);
	if (ft_strcmp(command->args[0], "exit") == 0)
	{
		j = 0;
		while(command->args[j] != NULL)
			j ++;
		if (j == 1)
			j = ft_exit_command(0);
		else if (j == 2)
			j = ft_exit_command(command->args[1]);
		else
		{
			printf("exit: too many arguments\n");
		}
		exit (j);
		
	}	
	else if (build_up(command, envp) == 1)
		exit (0);
	exit (1);
}
