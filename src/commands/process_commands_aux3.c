/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands_aux3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:27:44 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 13:39:12 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_process(t_process *ctx, int i, int num_cmds, t_list_env *envp)
{
	ctx->i = i;
	ctx->num_cmds = num_cmds;
	ctx->envp = envp;
}

void	init_process1(t_process *ctx, t_cmd *commands, int i, int **pipes)
{
	ctx->command = &commands[i];
	ctx->i = i;
	ctx->pipes = pipes;
}

void	init_process2(t_process *ctx, int i, int num_cmds, char **env_array)
{
	ctx->i = i;
	ctx->num_cmds = num_cmds;
	ctx->env_array = env_array;
}

void	manage_commands_three(t_cmd *commands,
	int num_cmds, t_list_env *envp, t_cmd_vars	*vars)
{
	close_pipes(vars->pipes, num_cmds);
	vars->i = -1;
	while (++vars->i < num_cmds)
	{
		vars->pid = waitpid(-1, &vars->status, 0);
		if (vars->pid == vars->pid_last)
		{
			if (WIFEXITED(vars->status))
				vars->exit_status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status))
				vars->exit_status = WTERMSIG(vars->status) + 128;
			manage_error(vars->exit_status, 0);
		}
	}
	if (num_cmds == 1)
	{
		handle_export(&commands[0], envp);
		handle_cd(&commands[0], envp);
		handle_unset(&commands[0], &envp);
	}
	clean_up(vars->env_array, NULL, 0);
}
