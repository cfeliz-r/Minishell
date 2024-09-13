/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:57:46 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/12 18:59:48 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**split_commands(const char *input)
{
	t_split_commands	ctx;

	ctx.len = ft_strlen(input);
	ctx.commands = malloc(sizeof(char *) * (ctx.len + 1));
	ctx.current_command = ft_calloc(ctx.len + 1, sizeof(char));
	ctx.ctx = (t_quote_context){0, 0};
	ctx.i = 0;
	ctx.j = 0;
	ctx.cmd_idx = 0;
	if (!ctx.commands || !ctx.current_command)
	{
		free(ctx.commands);
		free(ctx.current_command);
		return (NULL);
	}
	aux_split(input, &ctx);
	if (ctx.j > 0)
	{
		ctx.current_command[ctx.j] = '\0';
		ctx.commands[ctx.cmd_idx++] = ft_strdup(ctx.current_command);
	}
	free(ctx.current_command);
	ctx.commands[ctx.cmd_idx] = NULL;
	return (ctx.commands);
}

static t_cmd	*init_commands(char **command_strings, int num_cmds)
{
	int		i;
	t_cmd	*commands;

	commands = malloc(sizeof(t_cmd) * num_cmds);
	if (!commands || num_cmds == 0)
	{
		clean_up(command_strings, NULL, 0);
		return (NULL);
	}
	i = 0;
	while (i < num_cmds)
	{
		ft_memset(&commands[i], 0, sizeof(t_cmd));
		commands[i].cmd_cpt = ft_strdup(command_strings[i]);
		i++;
	}
	return (commands);
}

void	handle_key_redir(t_cmd *command)
{
	update_flag(command);
	process_redirections(command);
	command->args = split_special(command->cmd_cpt);
	if (!command->args)
	{
		free_command(command);
		return ;
	}
}

int	validate_command(t_cmd *command, t_list_env *envp)
{
	if (command->args == NULL || command->args[0] == NULL)
	{
		free_command(command);
		return (0);
	}
	command->path = find_command_path(command->args[0], envp);
	if (command->path == NULL)
	{
		ft_putstr_fd(command->args[0], 2);
		if (ft_strncmp(command->args[0], "./", 2) == 0)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	else if (ft_strcmp(command->args[0], ".") == 0)
	{
		ft_putstr_fd(".: filename argument required\n", 2);
		exit(2);
	}
	return (1);
}

t_cmd	*parse_commands(char *input, int *num_cmds)
{
	char		**command_strings;
	t_cmd		*commands;
	int			i;

	command_strings = split_commands(input);
	if (command_strings == NULL || command_strings[0] == NULL)
		return (manage_error(200, 0), free(command_strings), NULL);
	*num_cmds = 0;
	while (command_strings[*num_cmds] != NULL)
		(*num_cmds)++;
	commands = init_commands(command_strings, *num_cmds);
	i = -1;
	while (++i < *num_cmds)
		handle_key_redir(&commands[i]);
	clean_up(command_strings, NULL, 0);
	return (commands);
}
