/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:59:47 by manufern          #+#    #+#             */
/*   Updated: 2024/09/06 14:14:20 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H
#include "minishell.h"

typedef struct s_list_envp
{
	char *envp_content;
	struct s_list_envp *next;
} t_list_env;
typedef struct s_cmd
{
	char **args;
	char *cmd_cpt;
	char *path;
	char *inredir;
	char *heredoc_file;
	char **delimiters;
	char **outredirs;
	int out_index;
	int hdc_index;
	int appd_out;
	int flag;
	int expand_heredoc;
} t_cmd;

typedef struct s_parse_context
{
	size_t i;
	size_t j;
	size_t in_single_quotes;
	size_t in_double_quotes;
	size_t buffer_size;
	size_t in_heredoc;
	char *result;
	int  can_expand;
} t_parse_context;

typedef struct s_quote_context
{
	int in_single_quotes;
	int in_double_quotes;
} t_quote_context;

typedef struct s_split_context
{
	size_t len;
	char **commands;
	char *current_command;
	size_t i;
	size_t j;
	size_t cmd_idx;
	int in_single_quotes;
	int in_double_quotes;
} t_split_context;

typedef struct s_temp_file_data
{
	int file_counter;
	char *file_name;
	const char *prefix;
	int counter;
	int prefix_len;
	int counter_len;
	char counter_str[11];
} t_temp_file_data;

typedef struct s_quote_remover
{
    size_t	i;
    size_t	j;
    size_t	len;
    char	*result;
    int		in_single_quote;
    int		in_double_quote;
} t_quote_remover;

#endif
