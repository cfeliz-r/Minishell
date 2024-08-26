/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:59:47 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 15:21:56 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

# define INITIAL_BUFFER_SIZE 1024
typedef struct s_list_envp
{
	char			*envp_content;
	struct s_list_envp	*next;
}	t_list_env;
typedef struct s_command
{
    char **args;
    char *cmd_cpt;
    char *path;
    char *inredir;
    char **delimiters;
    char **outredirs;
    int appd_out;
    int   flag;
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

typedef struct s_quote_context {
    int in_single_quotes;
    int in_double_quotes;
} t_quote_context;

typedef struct s_split_context {
    size_t  len;
    char    **commands;
    char    *current_command;
    size_t  i;
    size_t  j;
    size_t  cmd_idx;
    int     in_single_quotes;
    int     in_double_quotes;
} t_split_context;

typedef struct s_temp_file_data
{
    int         file_counter;
    char        *file_name;
    const char  *prefix;
    int         counter;
    int         prefix_len;
    int         counter_len;
    char        counter_str[11];
}               t_temp_file_data;

#endif