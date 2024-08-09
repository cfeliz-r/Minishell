/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:59:47 by manufern          #+#    #+#             */
/*   Updated: 2024/08/09 13:27:48 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_list_envp
{
	char			*envp_content;
	struct s_list_envp	*next;
}	t_list_env;

typedef struct s_command
{
    int is_correct;
    char **args;
    char *cmd_complete;
    char *path;
    int pipefd[2];
    pid_t pid;
    char *input_redirection;
    char *output_redirection;
    int append_output;
} t_command;

typedef struct s_parse_context
{
    size_t  i;
    size_t  j;
    size_t  in_single_quotes;
    size_t  in_double_quotes;
    size_t  buffer_size;
    size_t  flag_double;
    size_t  flag_single;
    char    *result;
}   t_parse_context;

#endif