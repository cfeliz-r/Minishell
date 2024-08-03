/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.your42network.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 00:54:29 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/28 00:54:56 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command *parse_commands(char *input, t_list_env *envp, int *num_cmds)
{
    char **command_strings;
    t_command *commands;
    char *command_with_redirections;
    char *input_redirection;
    char *output_redirection;
    int i;
    
    command_strings = ft_split(input, '|');
    if (!command_strings)
        return NULL;

    *num_cmds = 0;
    while (command_strings[*num_cmds] != NULL)
        (*num_cmds)++;

    commands = malloc(sizeof(t_command) * (*num_cmds));
    if (!commands) {
        clean_up(command_strings, NULL, 0);
        return NULL;
    }

    i = 0;
    while (i < *num_cmds)
    {
        commands[i].is_correct = 0;
        commands[i].input_redirection = NULL;
        commands[i].output_redirection = NULL;
        commands[i].append_output = 0;
        command_with_redirections = command_strings[i];
        input_redirection = ft_strchr(command_with_redirections, '<');
        output_redirection = ft_strchr(command_with_redirections, '>'); 
        if (input_redirection) 
        {
            *input_redirection = 0;
            input_redirection++;
            if (*input_redirection)
                commands[i].input_redirection = ft_split(input_redirection, ' ')[0];
            else
                commands[i].input_redirection = NULL;
        }
        if (output_redirection)
        {
            *output_redirection = 0;
            output_redirection++;
            if (*output_redirection == '>')
            {
                commands[i].append_output = 1;
                output_redirection++;
            }
            if (*output_redirection)
                commands[i].output_redirection = ft_split(output_redirection, ' ')[0];
            else
                commands[i].output_redirection = NULL;
        }
        commands[i].args = ft_split(command_with_redirections, ' ');
        if (commands[i].args == NULL)
        {
            ft_putstr(command_strings[i]);
            ft_putstr_fd(": Command not found\n", 2);
            while (i >= 0)
            {
                free_command(&commands[i]);
                i--;
            }
            free(commands);
            clean_up(command_strings, NULL, 0);
            return NULL;
        }
        commands[i].path = find_command_path(commands[i].args[0], envp);
        if (!commands[i].path || access(commands[i].path, F_OK) == -1)
        {
            commands[i].is_correct = 1;
            ft_putstr(commands[i].args[0]);
            ft_putstr_fd(": Command not found\n", 2);
            while (i >= 0)
            {
                free_command(&commands[i]);
                i--;
            }
            free(commands);
            clean_up(command_strings, NULL, 0);
            return NULL;
        }

        commands[i].pid = -1;
        commands[i].pipefd[0] = -1;
        commands[i].pipefd[1] = -1;
        i++;
    }
    clean_up(command_strings, NULL, 0);
    return commands;
}

char *interpret_command(char *command)
{
    int i;
    int j;
    int in_double_quotes;
    int in_single_quotes;
    char *result;

    i = 0;
    j = 0;
    in_double_quotes = 0;
    in_single_quotes = 0;
    result = malloc(ft_strlen(command) + 1);
    if (!result)
        return (NULL);
    while (command[i] != '\0')
    {
        if (command[i] == '"' && !in_single_quotes)
        {
            if (in_double_quotes && i > 0 && command[i - 1] == ' ')
            {
                free(result);
                return (NULL);
            }
            in_double_quotes = !in_double_quotes;
            i++;
        }
        else if (command[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            i++;
        }
        else
        {
            result[j++] = command[i++];
        }
    }
    result[j] = '\0';
    return (result);
}

int check_quotes(char *command)
{
	int i;
	int quotes_2;
	int quotes_1;

	i = 0;
	quotes_2 = 0;
	quotes_1 = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '"')
		{
			quotes_2++;
			i++;
			while (command[i] != '"' && command[i] != '\0')
				i++;
			if (command[i] == '"')
			{
				quotes_2++;
				i++;
			}
		}
		else if (command[i] == '\'')
		{
			quotes_1++;
			i++;
			while (command[i] != '\'' && command[i] != '\0')
				i++;
			if (command[i] == '\'')
			{
				quotes_1++;
				i++;
			}
		}
		else
			i++;
	}
	if (quotes_2 % 2 == 0 && quotes_1 % 2 == 0)
		return 1;
	else
		return 0;
}

char *remove_front_and_back_spaces(char *str)
{
	int start;
	int end;
	int length;

	start = 0;
    if (str != NULL)
    {
        while (str[start] && str[start] == ' ')
            start++;
        if (str[start] == '\0')
        {
            str[0] = '\0';
            return str;
        }
        length = ft_strlen(str);
        end = length - 1;
        while (end > start && str[end] == ' ')
            end--;
        length = end - start + 1;
        ft_memmove(str, str + start, length);
        str[length] = '\0';
        return str;
    }
    return (NULL);
}
