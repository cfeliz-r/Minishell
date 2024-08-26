/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:03:33 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/26 11:58:36 by cfeliz-r         ###   ########.fr       */
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
    if (!file_name)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
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

int process_here_doc(t_command *command)
{
    int index = 0;
    char *buffer = NULL;
    char *input_line;
    size_t len = 0;
    size_t capacity = INITIAL_BUFFER_SIZE;
    int fd;
    char *temp_file_name;
    buffer = malloc(capacity);
    if (!buffer)
    {
        perror("malloc failed");
        return (-1);
    }
    temp_file_name = generate_temp_file_name();
    fd = open(temp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror("open failed");
        free(buffer);
        free(temp_file_name);
        return (-1);
    }
    while (1)
    {
        input_line = readline("> ");
        if (!input_line)
        {
            close(fd);
            unlink(temp_file_name);
            free(buffer);
            free(temp_file_name);
            return (-1);
        }
        if (ft_strcmp(input_line, command->delimiters[index]) == 0)
        {
            index++;
            free(input_line);
            if (command->delimiters[index] == command->delimiters[index - 1]
            || command->delimiters[index] == NULL
            || command->delimiters[index][0] == '>' ||command->delimiters[index][0] == '<' ||  command->appd_out == 1)
                    break;
            
            continue;
        }
        size_t input_len = ft_strlen(input_line);
        if (len + input_len + 1 >= capacity)
        {
            capacity *= 2;
            char *new_buffer = simple_realloc(buffer, capacity, len);
            buffer = new_buffer;
        }
        ft_strcpy(buffer + len, input_line);
        len += input_len;
        buffer[len++] = '\n';
        write(fd, buffer, len);
        free(input_line);
    }
    close(fd);
    free(buffer);
    command->inredir = temp_file_name;
    return (0);
}
