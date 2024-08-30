/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/30 14:10:21 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static void handle_input_redirection(char *input_redirection, t_command *command)
{
	char **split_result;
	int i;

	i = 0;
	if(ft_strncmp(command->cmd_cpt, "echo", 4) != 0)
		*input_redirection = 0;
	split_result = split_special(input_redirection + 1);
	if(split_result != NULL)
	{
		if (command->heredoc_file == NULL)
			command->inredir = ft_strdup(split_result[0]);
		else
			command->inredir = ft_strdup(command->heredoc_file);
	}
	while(split_result[++i] != NULL)
	{
		if(split_result[i][0] == '<')
		{
			i++;
			continue;
		}
		command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, " ");
		command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, split_result[i]);
	}
	clean_up(split_result, NULL, 0);
}

static void handle_output_redirection(char *output_redirection, t_command *command)
{
	char **split_result;
	int i = 0;
	int count = 0;

 	*output_redirection = 0;
	output_redirection++;
	if (*output_redirection == '>')
	{
		command->appd_out = 1;
		output_redirection++;
	}
	split_result = split_special(output_redirection);
	while (split_result[i] != NULL)
	{
		if (ft_strcmp(split_result[i], ">") != 0)
			count++;
		i++;
	}
	if (count > 0)
	{
		command->outredirs = malloc(sizeof(char *) * (count + 1));
		if (!command->outredirs)
		{
			clean_up(split_result, NULL, 0);
			return;
		}
	}
	i = 0;
	count = 0;
	while (split_result[i] != NULL)
	{
		if (split_result[i] != NULL && split_result[i][0] != '>' && split_result[i][0] != '<')
		{
			command->outredirs[count] = strip_quotes(split_result[i]);
			count++;
		}
		i++;
	}
	if (command->outredirs)
		command->outredirs[count] = NULL;
	clean_up(split_result, NULL, 0);
}

static void initialize_delimiters(char **split_result, t_command *command)
{
    int i;
    int j;

    i = -1;
    j = 0;
    command->flag = 1;
    while (split_result[++i] != NULL)
    {
        if (search_string_outside_quotes(split_result[i], "<<") == 1)
            command->flag = 1;
        else if (command->flag == 1)
        {
            if (contains_quotes(split_result[i]))
                split_result[i] = split_quotes(split_result[i]);
            command->delimiters[j++] = ft_strdup(split_result[i]);
            command->flag = 0;
        }
        else
        {
			if(split_result[i][0] == '<')
			{
				i++;
				continue;
			}
            command->flag = 0;
            command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, " ");
            command->cmd_cpt = safe_strjoin_free(command->cmd_cpt, split_result[i]);
        }
    }
    command->delimiters[j] = NULL;
}

static void handle_hdoc(char *heredoc_redirection, t_command *command)
{
    char **split_result;
    
    *heredoc_redirection = 0;
    heredoc_redirection += 2;
    split_result = split_special(heredoc_redirection);
    if (!split_result)
        return;
    command->delimiters = malloc(sizeof(char *) * (ft_count(split_result) + 1));
    if (!command->delimiters)
        return;
    initialize_delimiters(split_result, command);
    clean_up(split_result, NULL, 0);
}

void process_redirections(t_command *command)
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
	if (input_redirection != NULL)
		handle_input_redirection(input_redirection, command);
}

