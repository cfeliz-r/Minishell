/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands_aux2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:47:19 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 17:18:01 by manufern         ###   ########.fr       */
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

void	execute_command(t_cmd *command, char **env_array, t_list_env *envp)
{
	if (validate_command(command, envp) == 1)
		execve(command->path, command->args, env_array);
	exit(127);
}

int	ft_exit_command(char *exits)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (exits[i] != '\0')
	{
		printf("exits[i]: %c\n", exits[i]);
		if (ft_isdigit(exits[i]) == 1)
			i++;
		else
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 1)
	{
		printf("exit: %s: numeric argument required\n", exits);
		return (2);
	}
	exit (ft_atoi(exits));
}

void	child_process(t_process *ctx)
{
	int	j;

	set_signal_handlers();
	handle_pipes(ctx->i, ctx->num_cmds, ctx->pipes);
	if (handle_redirections(ctx->command) == -1)
		exit(1);
	remove_quotes_from_args(ctx->command->args);
	if (is_builtin_command(ctx->command->args[0]) == 0)
		execute_command(ctx->command, ctx->env_array, ctx->envp);
	if (ft_strcmp(ctx->command->args[0], "exit") == 0)
	{
		j = 0;
		while (ctx->command->args[j] != NULL)
			j++;
		if (j == 1)
			j = ft_exit_command(0);
		else if (j == 2)
			j = ft_exit_command(ctx->command->args[1]);
		else
			printf("exit: too many arguments\n");
		exit(j);
	}
	else if (build_up(ctx->command, ctx->envp) == 1)
		exit(0);
	exit(1);
}
