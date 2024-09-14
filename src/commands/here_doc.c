/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/11 17:31:39 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	append_counter_to_file_name(char *file_name, int counter)
{
	char	counter_str[11];
	char	*p;
	int		temp_counter;

	p = counter_str + sizeof(counter_str) - 1;
	*p = '\0';
	temp_counter = counter;
	while (temp_counter > 0)
	{
		*(--p) = '0' + (temp_counter % 10);
		temp_counter /= 10;
	}
	if (counter == 0)
		*(--p) = '0';
	ft_strcat(file_name, p);
}

static int	calculate_counter_length(int counter)
{
	int		counter_len;
	int		temp_counter;

	counter_len = 0;
	temp_counter = counter;
	while (temp_counter > 0)
	{
		counter_len++;
		temp_counter /= 10;
	}
	if (counter == 0)
		return (1);
	else
		return (counter_len);
}

char	*generate_temp_file_name(void)
{
	static int	file_counter = 0;
	const char	*prefix;
	int			counter_len;
	int			temp_file_name_len;
	char		*file_name;

	prefix = "/tmp/heredoc_";
	counter_len = calculate_counter_length(file_counter);
	temp_file_name_len = ft_strlen(prefix) + counter_len + 1;
	file_name = malloc(temp_file_name_len);
	ft_strcpy(file_name, prefix);
	append_counter_to_file_name(file_name, file_counter);
	if (access(file_name, F_OK) != -1)
	{
		free(file_name);
		file_counter++;
		return (generate_temp_file_name());
	}
	file_counter++;
	return (file_name);
}

static int	handle_line(char *input_line, t_cmd *cmd, int fd, t_list_env *envp)
{
	char	*expanded_line;

	if (!input_line)
	{
		cmd->hdc_index ++;
		return (1);
	}
	else if (ft_strcmp(input_line, cmd->delimiters[cmd->hdc_index]) == 0)
	{
		free(input_line);
		cmd->hdc_index++;
		return (1);
	}
	else if (cmd->expand_heredoc == 1 && is_builtin_command(cmd->args[0]) == 0)
	{
		expanded_line = interpret_command(input_line, envp, 1);
		write(fd, expanded_line, ft_strlen(expanded_line));
		free(expanded_line);
	}
	else
		write(fd, input_line, ft_strlen(input_line));
	write(fd, "\n", 1);
	return (0);
}

int	process_here_doc(t_cmd *cmd, t_list_env *envp)
{
	char	*input_line;
	int		fd;

	cmd->hdc_index = 0;
	fd = open_temp_file(&cmd->heredoc_file);
	signal(SIGINT, sigint_handler_here_doc);
	while (1)
	{
		input_line = readline("> ");
		if (handle_stop_condition(input_line, cmd, fd) == -1)
			return (-1);
		if (handle_line(input_line, cmd, fd, envp) == 1)
		{
			if (cmd->delimiters[cmd->hdc_index] == NULL)
				break ;
			close(fd);
			fd = open_temp_file(&cmd->heredoc_file);
			continue ;
		}
		free(input_line);
	}
	close(fd);
	return (0);
}
