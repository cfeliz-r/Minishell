/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:59:47 by manufern          #+#    #+#             */
/*   Updated: 2024/07/24 19:09:58 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"
typedef struct s_comand_before_pip
{
	char	*comand_complete;
	struct s_comand_after_pip *comand_afeter_pip;
	struct s_comand_before_pip *next;
}	t_comand_before_pip;

typedef struct s_comand_after_pip
{
	char	*comand;
	char	**argument;
	struct s_comand_after_pip *next;
}   t_comand_after_pip;

typedef struct s_list_envp
{
	char			*envp_content;
	struct s_list_envp	*next;
}	t_list_env;

typedef struct s_command
{
	char **args;
	char *path;
	int pipefd[2];
	pid_t pid;
}	t_command;
#endif