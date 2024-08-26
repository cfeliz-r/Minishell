/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:45:33 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 13:32:00 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_envp(t_list_env *envp)
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

void	execute_commands(t_list_env *envp, char *cmd)
{
	t_command	*commands;
	int			num_cmds;
	int			i;

	commands = parse_commands(cmd, envp, &num_cmds);
	if (!commands)
	{
		clean_up(NULL, commands, 0);
		return ;
	}
	for(i = 0; i < num_cmds; i++)
	{
		printf("Command[%d]; cmd_cpt: %s\n", i, commands[i].cmd_cpt);
	}
	prepare_commands(commands, num_cmds, envp);
	i = -1;
	while (++i < num_cmds)
		free_command(&commands[i]);
	free(commands);
}
