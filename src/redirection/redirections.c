/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:08:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/04 15:39:50 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redirections(t_cmd *command)
{
	if (handle_output_files(command) == -1)
		return (-1);
	if (handle_input_files(command) == -1)
		return (-1);
	return (0);
}

int	count_valid_redirections(char **split_result)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (split_result[i] != NULL)
	{
		if (ft_strcmp(split_result[i], ">") != 0)
			count++;
		i++;
	}
	return (count);
}

void	allocate_and_fill_outredirs(char **split_result, t_cmd *cmd, int count)
{
	int		i;
	int		flag;

	i = -1;
	cmd->out_index = 0;
	flag = 1;
	cmd->outredirs = malloc(sizeof(char *) * (count + 1));
	while (split_result[++i] != NULL)
	{
		if (search_string_outside_quotes(split_result[i], ">") == 1)
			flag = 1;
		else if (flag == 1)
		{
			if (contains_quotes(split_result[i]))
				split_result[i] = split_quotes(split_result[i]);
			cmd->outredirs[cmd->out_index++] = ft_strdup(split_result[i]);
			flag = 0;
		}
		else
		{
			cmd->cmd_cpt = safe_strjoin_free(cmd->cmd_cpt, " ");
			cmd->cmd_cpt = safe_strjoin_free(cmd->cmd_cpt, split_result[i]);
		}
	}
	cmd->outredirs[cmd->out_index] = NULL;
}

void	process_more_info(char **split_result, t_cmd *command, int *i)
{
	if (split_result[*i][0] == '<')
	{
		(*i)++;
		if (command->inredir)
			free(command->inredir);
		command->inredir = ft_strdup(split_result[*i]);
		return ;
	}
	command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, " ");
	command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, split_result[*i]);
}

void	update_flag(t_cmd *command)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = command->cmd_cpt;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '<' && ptr[i + 1] == '<' && (is_around(ptr, i) == 0))
		{
			command->last_redir_flag = 1;
			i += 2;
		}
		else if (ptr[i] == '<' && ptr[i + 1] != '<' && (is_around(ptr, i) == 0))
		{
			command->last_redir_flag = 2;
			i++;
		}
		else
			i++;
	}
}
