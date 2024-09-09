/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:57:46 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/09 17:26:59 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**split_commands(const char *input)
{
	size_t len = ft_strlen(input);
	char **commands = malloc(sizeof(char *) * (len + 1));
	char *current_command = ft_calloc(len + 1, sizeof(char));
	t_quote_context ctx = {0, 0};
	size_t i = 0, j = 0, cmd_idx = 0;

	if (!commands || !current_command)
		return NULL;
	if(!input)
	{
		free(commands);
		free(current_command);
		return NULL;
	}

	while (input[i] != '\0')
	{
		if (input[i] == '\'' && ctx.in_double_quotes == 0)
			ctx.in_single_quotes = !ctx.in_single_quotes;
		else if (input[i] == '"' && ctx.in_single_quotes == 0)
			ctx.in_double_quotes = !ctx.in_double_quotes;
		else if (input[i] == '|' && ctx.in_single_quotes == 0 && ctx.in_double_quotes == 0)
		{
			current_command[j] = '\0';
			commands[cmd_idx++] = ft_strdup(current_command);
			free(current_command);
			current_command = ft_calloc(len + 1, sizeof(char));
			j = 0;
			i++;
			continue;
		}
		current_command[j++] = input[i++];
	}
	if (j > 0) {
		current_command[j] = '\0';
		commands[cmd_idx++] = ft_strdup(current_command);
	}
	
	free(current_command);
	commands[cmd_idx] = NULL;
	return commands;
}

t_cmd *init_commands(char **command_strings, int num_cmds)
{
	int i;
	t_cmd *commands;

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
void handle_key_redir(t_cmd *command)
{
	process_redirections(command);
	command->args = split_special(command->cmd_cpt);
	if(!command->args)
	{
		free_command(command);
		return ;
	}
}

int validate_command(t_cmd *command, t_list_env *envp)
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
		if(ft_strncmp(command->args[0], "./", 2) == 0)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	return (1);
}
t_cmd *parse_commands(char *input, int *num_cmds)
{
	char        **command_strings;
	t_cmd   *commands;
	int        i;

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
