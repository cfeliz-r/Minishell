/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:45:33 by manufern          #+#    #+#             */
/*   Updated: 2024/09/11 13:43:42 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_temp_file(char **temp_file_name)
{
	int	fd;

	if (*temp_file_name)
		free(*temp_file_name);
	*temp_file_name = generate_temp_file_name();
	fd = open(*temp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	return (fd);
}

int	handle_stop_condition(char *input_line, t_cmd *cmd, int fd)
{
	if (!input_line || g_stop_status == 1)
	{
		if (!input_line)
		{
			printf("bash: warning: here-document at line 1 delimited \
			by end-of-file (wanted `end')\n");
		}
		else
		{
			manage_error(130, 0);
			free(input_line);
		}
		unlink(cmd->heredoc_file);
		g_stop_status = 0;
		close(fd);
		return (-1);
	}
	return (0);
}

static int	count_envp(t_list_env *envp)
{
	int	count;

	count = 0;
	if (envp == NULL)
		count = -1;
	while (envp)
	{
		count ++;
		envp = envp->next;
	}
	return (count);
}

char	**convert_envp_to_array(t_list_env *envp)
{
	int		i;
	int		count;
	char	**env_array;

	i = 0;
	count = count_envp(envp);
	if (count == -1)
		return (NULL);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (envp)
	{
		env_array[i] = ft_strdup(envp->envp_content);
		if (!env_array[i])
		{
			clean_up(env_array, NULL, 0);
			return (NULL);
		}
		envp = envp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	executor(t_list_env *envp, char *cmd)
{
	t_cmd	*commands;
	int		num_cmds;
	int		i;

	commands = parse_commands(cmd, &num_cmds);
	if (!commands)
	{
		clean_up(NULL, commands, 0);
		return ;
	}
	prepare_commands(commands, num_cmds, envp);
	i = -1;
	while (++i < num_cmds)
		free_command(&commands[i]);
	free(commands);
}
