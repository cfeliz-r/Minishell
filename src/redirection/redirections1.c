/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/13 12:03:21 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_input_redirection(char *input, t_cmd *command)
{
	char	**split_result;
	int		i;

	i = 0;
	*input = 0;
	split_result = split_special(input + 1);
	if (split_result[0] != NULL)
		command->inredir = strip_quotes(split_result[0]);
	if (split_result[0] != NULL)
	{
		while (split_result[++i] != NULL)
			process_more_info(split_result, command, &i);
	}
	clean_up(split_result, NULL, 0);
}

static void	handle_output_redirection(char *output, t_cmd *command)
{
	char	**split_result;
	int		count;

	*output = 0;
	output++;
	if (*output == '>')
	{
		command->appd_out = 1;
		output++;
	}
	split_result = split_special(output);
	count = count_valid_redirections(split_result);
	allocate_and_fill_outredirs(split_result, command, count);
	clean_up(split_result, NULL, 0);
}

static void	initialize_delimiters(char **split_result, t_cmd *command)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	command->flag = 1;
	command->expand_heredoc = 1;
	while (split_result[++i] != NULL)
	{
		if (search_string_outside_quotes(split_result[i], "<<") == 1)
			command->flag = 1;
		else if (command->flag == 1)
			process_delimiter(split_result, command, &i, &j);
		else
			process_more_info(split_result, command, &i);
	}
	command->delimiters[j] = NULL;
}

static void	handle_hdoc(char *heredoc_redirection, t_cmd *command)
{
	char	**split_result;

	*heredoc_redirection = 0;
	heredoc_redirection += 2;
	split_result = split_special(heredoc_redirection);
	if (!split_result)
		return ;
	command->delimiters = malloc(sizeof(char *) * (ft_count(split_result) + 1));
	if (!command->delimiters)
		return ;
	initialize_delimiters(split_result, command);
	clean_up(split_result, NULL, 0);
}

void	process_redirections(t_cmd *command)
{
	char	*heredoc_redirection;
	char	*input_redirection;
	char	*output_redirection;

	heredoc_redirection = correct_strstr(command->cmd_cpt, "<<");
	if (heredoc_redirection != NULL)
		handle_hdoc(heredoc_redirection, command);
	output_redirection = correct_strstr(command->cmd_cpt, ">");
	if (output_redirection != NULL)
		handle_output_redirection(output_redirection, command);
	input_redirection = correct_strstr(command->cmd_cpt, "<");
	if (input_redirection != NULL && input_redirection[1] != '<')
		handle_input_redirection(input_redirection, command);
}
