/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:59:47 by manufern          #+#    #+#             */
/*   Updated: 2024/08/03 14:07:08 by cfeliz-r         ###   ########.fr       */
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
    char *path;
    int pipefd[2];
    pid_t pid;
    char *input_redirection;
    char *output_redirection;
    int append_output;
} t_command;

#endif