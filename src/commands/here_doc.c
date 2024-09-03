/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/30 11:37:48 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *generate_temp_file_name(void)
{
    static int file_counter = 0;
    char *file_name;
    const char *prefix = "/tmp/heredoc_";
    int counter = file_counter;
    int prefix_len = strlen(prefix);
    int counter_len = 0;
    int temp_file_name_len;
    char counter_str[11];
	char *p;

    int temp_counter = counter;
    while (temp_counter > 0)
    {
        counter_len++;
        temp_counter /= 10;
    }
    if (counter == 0)
        counter_len = 1;
    temp_file_name_len = prefix_len + counter_len + 1;
    file_name = malloc(temp_file_name_len);
    ft_strcpy(file_name, prefix);
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
    file_counter++;
    return (file_name);
}

int process_here_doc(t_command *command, t_list_env *envp)
{
    int index = 0;
    char *input_line;
    int fd;
    char *temp_file_name;
    char *expanded_line;

    signal(SIGINT, sigint_handler_here_doc);
    temp_file_name = generate_temp_file_name();
    fd = open(temp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    while (1)
    {
        input_line = readline("> ");
        if (!input_line || stop == 1)
        {
            close(fd);
            if(!input_line)
                write(STDOUT_FILENO, "\n", 1);
            unlink(temp_file_name);
            free(input_line);
            free(temp_file_name);
            stop = 0;
            return (-1);
        }
        if (ft_strcmp(input_line, command->delimiters[index]) == 0)
        {
            index++;
            free(input_line);
            if (command->delimiters[index] == NULL)
                    break;
            else
                {
                    close(fd);
                    fd = open(temp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
                    continue;
                }
        }
        if (command->expand_heredoc == 1)
        {
            expanded_line = interpret_command(input_line, envp);
            write(fd, expanded_line, ft_strlen(expanded_line));
            free(expanded_line);
        }
        else
            write(fd, input_line, ft_strlen(input_line));
        write(fd, "\n", 1);
        free(input_line);
    }
    close(fd);
    command->heredoc_file = temp_file_name;
    return (0);
}
